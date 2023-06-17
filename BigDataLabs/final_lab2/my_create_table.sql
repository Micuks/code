DROP TABLE IF EXISTS `dli-xyz`.`daily_book_sales`;

CREATE TABLE `dli-xyz`.`daily_book_sales` (
    `date` DATE NOT NULL,
    `book_category` VARCHAR(64) NOT NULL,
    `total_sales` INT UNSIGNED NULL,
    `total_revenue` DOUBLE UNSIGNED NULL,
    `last_sale_time` DATETIME NULL,
    PRIMARY KEY (`date`, `book_category`)
) ENGINE = InnoDB
  DEFAULT CHARACTER SET = utf8mb4
  COLLATE = utf8mb4_general_ci
  COMMENT = '每日各种图书的销售统计';

