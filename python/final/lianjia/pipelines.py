# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import sqlite3


class LianjiaPipeline:
    def process_item(self, item, spider):
        return item


class DownBusinessAreaUrlPipeline(object):
    """
    Save business area records to MySQL database.
    """

    def __init__(self):
        db_path = "database/Lianjia.db"
        # Connect to database.
        self.con = sqlite3.connect(db_path)

        # Create cursor, used to execute commands.
        self.cur = self.con.cursor()
        self.cur.execute("PRAGMA database_list")
        rows = self.cur.fetchall()
        for row in rows:
            print("database path", row[0], row[1], row[2])

        # Create Beijing business area table if none exists.
        self.cur.execute(
            """
            create table if not exists beijing_business_area(
            b_id integer not null,
            b_name varchar(20) not null,
            b_url varchar(100) not null,
            b_region varchar(20) not null,
            b_accessbit integer default 0 not null,
            primary key(b_id)
            );
            """
        )

    def process_item(self, item, spider):
        sql_select = """
        select *
        from beijing_business_area
        where b_url='%s';
        """ % (
            item["businessAreaUrl"]
        )

        self.cur.execute(sql_select)
        result = self.cur.fetchone()
        if result:
            print(result)
            print(
                f"Business area[{item['businessAreaName']}] already exists in SQLite database."
            )

        else:
            sql_add = """
            insert into beijing_business_area(
                    b_name, b_url, b_region
            ) values (?, ?, ?);
            """
            try:
                # Insert if no exception.
                self.cur.execute(
                    sql_add,
                    (
                        item["businessAreaName"],
                        item["businessAreaUrl"],
                        item["businessAreaRegion"],
                    ),
                )
                # Commit if no exception.
                self.con.commit()

            except Exception as e:
                # Rollback if exception.
                print("------EXCEPTION DURING INSERT------")
                print(e)
                self.con.rollback()

            return item

    def close_spider(self, spider):
        sql_display = """
        select * from beijing_business_area;
        """
        self.cur.execute(sql_display)
        result = self.cur.fetchall()
        for a in result:
            print(a)

        self.cur.close()
        self.con.close()
