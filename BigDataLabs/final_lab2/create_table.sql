DROP TABLE if exists `dli-wql`.`trade_channel_collect`;

CREATE TABLE `dli-wql`.`trade_channel_collect` (
  `begin_time` varchar(32) not null,
  `channel_code` varchar(32) not null,
  `channel_name` varchar(32) not null,
  `cur_gmv` double unsigned null,
  `cur_order_user_count` bigint unsigned null,
  `cur_order_count` bigint unsigned null,
  `last_pay_time` varchar(32) null,
  `flink_current_time` varchar(32) null,
  PRIMARY KEY(`begin_time`, `channel_code`)
) engine = InnoDB
default character set = utf8mb4
collate = utf8mb4_general_ci
comment = '各渠道的销售总额实时统计';
