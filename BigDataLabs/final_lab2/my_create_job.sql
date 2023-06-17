-- 数据源：Kafka
CREATE TABLE book_sales_raw (
  date STRING,
  book_category STRING,
  book_title STRING,
  total_sales BIGINT,
  total_revenue DOUBLE,
  last_sale_time STRING
) WITH (
  'connector' = 'kafka',
  'properties.bootstrap.servers' = '192.168.0.84:9092,192.168.0.48:9092,192.168.0.99:9092', 
  'properties.group.id' = 'book_sales', 
  'topic' = 'book_sales_info_wql', 
  'format' = 'json',
  'scan.startup.mode' = 'latest-offset'
);

-- 临时表
CREATE VIEW book_sales_stats_tmp AS
SELECT 
  date,
  book_category,
  COUNT(DISTINCT book_title) AS num_titles,
  SUM(total_sales) AS total_sales,
  AVG(total_sales) AS avg_sales,
  MAX(total_sales) AS max_sales,
  MIN(total_sales) AS min_sales,
  SUM(total_revenue) AS total_revenue,
  MAX(last_sale_time) AS last_sale_time
FROM book_sales_raw
GROUP BY date, book_category;

-- 结果表：MySQL
CREATE TABLE daily_book_sales_stats (
  date STRING,
  book_category STRING,
  num_titles BIGINT,
  total_sales BIGINT,
  avg_sales DOUBLE,
  max_sales BIGINT,
  min_sales BIGINT,
  total_revenue DOUBLE,
  last_sale_time STRING,
  flink_current_time STRING,
  PRIMARY KEY (date, book_category) NOT ENFORCED
) WITH (
  'connector' = 'jdbc',
  'url' = 'jdbc:mysql://192.168.0.10:3306/dli-wql',
  'table-name' = 'daily_book_sales_stats',
  'username' = 'root',
  'password' = 'km6Gexhua',
  'sink.buffer-flush.max-rows' = '1000',
  'sink.buffer-flush.interval' = '1s'
);

-- 将数据从临时表转移到 MySQL 结果表
INSERT INTO daily_book_sales_stats
SELECT 
  date,
  book_category,
  num_titles,
  total_sales,
  avg_sales,
  max_sales,
  min_sales,
  total_revenue,
  last_sale_time,
  CAST(LOCALTIMESTAMP AS STRING) AS flink_current_time
FROM book_sales_stats_tmp;

