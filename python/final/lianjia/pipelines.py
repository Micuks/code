# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from asyncio.log import logger
from itemadapter import ItemAdapter
import sqlite3


class LianjiaPipeline:
    def process_item(self, item, spider):
        return item


class DownBeijingBusinessAreaUrlPipeline(object):
    """
    Save business area records to SQLite3 database.
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
            print("database physical file path: ", row[0], row[1], row[2])

        # Create Beijing business area table if none exists.
        self.cur.execute(
            """
            create table if not exists business_area(
            business_area_id integer not null,
            business_area_name varchar(20) unique not null,
            business_area_url varchar(100) unique not null,
            business_area_region varchar(20) not null,
            business_area_city varchar(20) not null,
            business_area_accessbit integer default 0 not null,

            primary key(business_area_id),
            foreign key (business_area_region) references region(region_name),
            foreign key(business_area_city) references city(city_name)
            );
            """
        )

    def process_item(self, item, spider):
        sql_select = """
        select *
        from business_area
        where business_area_url='%s'
        and business_area_city='北京';
        """ % (
            item["businessAreaUrl"]
        )

        self.cur.execute(sql_select)
        result = self.cur.fetchone()
        if result:
            print(result)
            print(
                f"""Business area[{item['businessAreaName']}] already exists in
                 SQLite database."""
            )

        else:
            sql_add = """
                    insert into business_area(
                            business_area_name, business_area_url,
                            business_area_region, business_area_city
                    ) values (?, ?, ?, '北京');
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
        self.cur.close()
        self.con.close()


class DownBeijingCommunityInfoPipeline(object):
    """
    Save community records to SQLite3 database.
    """

    def __init__(self) -> None:
        db_path = "database/Lianjia.db"
        self.con = sqlite3.connect(db_path)
        self.cur = self.con.cursor()

        self.cur.execute("PRAGMA database_list")
        rows = self.cur.fetchall()
        for row in rows:
            print("database physical file path:", row[0], row[1], row[2])

        # Create Beijing community database if not exists.
        self.cur.execute(
            """
            create table if not exists community(
            community_id integer not null,
            community_name varchar(40) not null,
            community_url varchar(100) unique not null,
            community_rent_url varchar(100) unique,
            community_business_area varchar(20) not null,
            community_region varchar(20) not null,
            community_city varchar(20) not null,
            community_accessbit integer default 0 not null,

            primary key(community_id),
            unique (community_id, community_name),
            foreign key(community_business_area) references
            business_area(business_area_name),
            foreign key(community_region) references region(region_name),
            foreign key(community_city) references city(city_name)
            );
            """
        )

    def process_item(self, item, spider):
        sql_select = """
        select *
        from community
        where community_url='%s';
        """ % (
            item["communityUrl"]
        )
        self.cur.execute(sql_select)
        result = self.cur.fetchall()
        if result:
            logger.info("The community is already in beijing_community_info")
            pass
        else:
            sql_add = """
            insert into community(community_name, community_url,
            community_rent_url, community_business_area, community_region,
            community_city) values(%s, %s,
            %s, %s, %s,
            %s)
            """ % (
                item['communityName'],
                item['communityUrl'],
                item['communityRentUrl'],
                item['communityBusinessArea'],
                item['communityRegion'],
                "北京"
            )
            
            self.cur.execute(sql_add)
            return item
