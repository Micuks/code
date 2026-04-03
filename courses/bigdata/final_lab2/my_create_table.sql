DROP TABLE IF EXISTS `dli-wql`.`daily_book_sales_stats`;

CREATE TABLE `dli-wql`.`daily_book_sales_stats` (
    `cur_date` VARCHAR(32) NOT NULL,
    `book_category` VARCHAR(32) NOT NULL,
    `num_titles` BIGINT UNSIGNED NULL,
    `total_sales` BIGINT UNSIGNED NULL,
    `avg_sales` DOUBLE UNSIGNED NULL,
    `max_sales` BIGINT UNSIGNED NULL,
    `min_sales` BIGINT UNSIGNED NULL,
    `total_revenue` DOUBLE UNSIGNED NULL,
    `last_sale_time` VARCHAR(32) NULL,
    `flink_current_time` VARCHAR(32) NULL,
    PRIMARY KEY (`cur_date`, `book_category`)
) ENGINE = InnoDB
  DEFAULT CHARACTER SET = utf8mb4
  COLLATE = utf8mb4_general_ci
  COMMENT = '每日各种图书的销售统计';
