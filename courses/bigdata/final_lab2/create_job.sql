--********************************************************************--
-- 数据源：trade_order_detail_info (订单详情宽表)
--********************************************************************--
create table trade_order_detail (
  order_id string,      -- 订单ID
  order_channel string,   -- 渠道
  order_time string,     -- 订单创建时间
  pay_amount double,     -- 订单金额
  real_pay double,      -- 实际付费金额
  pay_time string,      -- 付费时间
  user_id string,      -- 用户ID
  user_name string,     -- 用户名
  area_id string       -- 地区ID
) with (
  "connector" = "kafka",
  "properties.bootstrap.servers" = "192.168.0.84:9092,192.168.0.48:9092,192.168.0.99:9092", -- Kafka连接地址
  "properties.group.id" = "trade_order",   -- Kafka groupID
  "topic" = "trade_order_detail_info_wql",     -- Kafka topic
  "format" = "json",
  "scan.startup.mode" = "latest-offset"
);

  --********************************************************************--
-- 结果表：trade_channel_collect (各渠道的销售总额实时统计)
--********************************************************************--
create table trade_channel_collect(
  begin_time string,       --统计数据的开始时间
  channel_code string,      -- 渠道编号
  channel_name string,      -- 渠道名
  cur_gmv double,         -- 当天GMV
  cur_order_user_count bigint, -- 当天付款人数
  cur_order_count bigint,    -- 当天付款订单数
  last_pay_time string,     -- 最近结算时间
  flink_current_time string,
  primary key (begin_time, channel_code) not enforced
) with (
  "connector" = "jdbc",
  "url" = "jdbc:mysql://192.168.0.10:3306/dli-wql",    -- mysql连接地址，jdbc格式
  "table-name" = "trade_channel_collect",            -- mysql表名
  "username" = "root",                    -- mysql用户名
  "password" = "km6Gexhua",                   -- mysql密码
  "sink.buffer-flush.max-rows" = "1000",
  "sink.buffer-flush.interval" = "1s"
);
--********************************************************************--
-- 临时中间表
--********************************************************************--
create view tmp_order_detail
as
select *
    , case when t.order_channel not in ("webShop", "appShop", "miniAppShop") then "other"
           else t.order_channel end as channel_code --重新定义统计渠道 只有四个枚举值[webShop、appShop、miniAppShop、other]
    , case when t.order_channel = "webShop" then _UTF16"网页商城"
           when t.order_channel = "appShop" then _UTF16"app商城"
           when t.order_channel = "miniAppShop" then _UTF16"小程序商城"
           else _UTF16"其他" end as channel_name --渠道名称
from (
    select *
        , row_number() over(partition by order_id order by order_time desc ) as rn --去除重复订单数据
        , concat(substr("2021-03-25 12:03:00", 1, 10), " 00:00:00") as begin_time
        , concat(substr("2021-03-25 12:03:00", 1, 10), " 23:59:59") as end_time
    from trade_order_detail
    where pay_time >= concat(substr("2021-03-25 12:03:00", 1, 10), " 00:00:00") --取今天数据，为了方便运行，这里使用"2021-03-25 12:03:00"替代cast(LOCALTIMESTAMP as string)
    and real_pay is not null
) t
where t.rn = 1;

-- 按渠道统计各个指标
insert into trade_channel_collect
select
      begin_time  --统计数据的开始时间
    , channel_code
    , channel_name
    , cast(COALESCE(sum(real_pay), 0) as double) as cur_gmv --当天GMV
    , count(distinct user_id) as cur_order_user_count --当天付款人数
    , count(1) as cur_order_count --当天付款订单数
    , max(pay_time) as last_pay_time --最近结算时间
	, cast(LOCALTIMESTAMP as string) as flink_current_time --flink任务中的当前时间
from tmp_order_detail
where pay_time >= concat(substr("2021-03-25 12:03:00", 1, 10), " 00:00:00")
group by begin_time, channel_code, channel_name;
             
