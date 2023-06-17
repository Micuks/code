------------------------------------------------------------
-- Data source: trade_order_detail_info (order detail table)
------------------------------------------------------------
CREATE TABLE trade_order_detail (
  order_id string, -- Order id
  order_channel string, -- 渠道
  order_time string, -- Order create time
  pay_amount double, -- Order amount
  real_pay double, -- 实际付费金额
  pay_time string, -- Pay time
  user_id string, -- User id
  user_name string, -- User name
  area_id string, -- Area id
) WITH (
"connector" = "kafka",
"properties.bootstrap.servers" = "XXXX:9092,XXXX:9092,XXXX:9092", -- FIXME: Fix me with Kafka connect address
"properties.group.id" = "trade_order", -- Kafka groupID
"topic" = "trade_order_detail_info_wql", -- Kafka topic
"format" = "json",
"scan.startup.mode" = "latest-offset"
);

-----------------------------------------------------
-- Result table: trade_channel_collect (各渠道的销售总额实时统计)
-----------------------------------------------------
CREATE TABLE trade_channel_collect (
  begin_time string, -- Begin time of statistics
  channel_code string, -- Channel code
  channel_name string, -- Channel name
  cur_gmv double, -- 当天 GMV
  cur_order_user_count bigint, -- 当天付款人数
  cur_order_count biging, -- 当天付款订单数
  last_pay_time string, -- 最近结算时间
  flink_current_time string,
  PRIMARY KEY(begin_time, channel_code) not enforced
) WITH (
"connector" = "jdbc",
"url" = "jdbc:mysql://XXXX:3306/dli-wql", -- FIXME: MySQL connect address, in JDBC format
"table-name" = "trade_channel_collect", -- MySQL table name
"username" = "root", -- MySql username
"password" = "FIXME", -- FIXME: MySQL password
"sink.buffer-flush.max-rows" = "1000",
"sink.buffer-flush.interval" = "1s"
);

----------------------------
-- Contemporary middle table
----------------------------
CREATE VIEW tmp_order_detail AS
SELECT 
    *,
    CASE 
        WHEN t.order_channel NOT IN ("webShop", "appShop", "miniAppShop") THEN "other"
        ELSE t.order_channel 
    END AS channel_code, -- 重新定义统计渠道 只有四个枚举值[webShop、appShop、miniAppShop、other]
    CASE 
        WHEN t.order_channel = "webShop" THEN _UTF16"网页商城"
        WHEN t.order_channel = "appShop" THEN _UTF16"app商城"
        WHEN t.order_channel = "miniAppShop" THEN _UTF16"小程序商城"
        ELSE _UTF16"其他" 
    END AS channel_name -- 渠道名称
FROM 
(
    SELECT 
        *,
        ROW_NUMBER() OVER(PARTITION BY order_id ORDER BY order_time DESC) AS rn, -- 去除重复订单数据
        CONCAT(SUBSTR("2021-03-25 12:03:00", 1, 10), " 00:00:00") AS begin_time,
        CONCAT(SUBSTR("2021-03-25 12:03:00", 1, 10), " 23:59:59") AS end_time
    FROM 
        trade_order_detail
    WHERE 
        pay_time >= CONCAT(SUBSTR("2021-03-25 12:03:00", 1, 10), " 00:00:00") -- 取今天数据，为了方便运行，这里使用"2021-03-25 12:03:00"替代cast(LOCALTIMESTAMP as string)
        AND real_pay IS NOT NULL
) t
WHERE 
    t.rn = 1;

-- 按渠道统计各个指标
INSERT INTO trade_channel_collect
SELECT
      begin_time  --统计数据的开始时间
    , channel_code
    , channel_name
    , CAST(COALESCE(sum(real_pay), 0) as double) as cur_gmv --当天GMV
    , COUNT(distinct user_id) as cur_order_user_count --当天付款人数
    , COUNT(1) as cur_order_count --当天付款订单数
    , MAX(pay_time) as last_pay_time --最近结算时间
	, CAST(LOCALTIMESTAMP as string) as flink_current_time --flink任务中的当前时间
FROM tmp_order_detail
WHERE pay_time >= concat(substr("2021-03-25 12:03:00", 1, 10), " 00:00:00")
GROUP BY begin_time, channel_code, channel_name;

