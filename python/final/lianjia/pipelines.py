# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import sqlite3
import logging

logging.basicConfig(
    format="%(asctime)s [%(filename)s:%(lineno)d] %(levelname)s: %(message)s",
    datefmt="%Y-%m-%dT%H:%M:%S",
    level=logging.DEBUG,
)

logger = logging.getLogger(__name__)


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
            item["business_area_url"]
        )

        self.cur.execute(sql_select)
        result = self.cur.fetchone()
        if result:
            logger.info(result)
            logger.info(
                f"""Business area[{item['business_area_name']}] already exists in
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
                        item["business_area_name"],
                        item["business_area_url"],
                        item["business_area_region"],
                    ),
                )
                # Commit if no exception.
                self.con.commit()

            except Exception as e:
                # Rollback if exception.
                logger.error("Error inserting into table business_area.")
                logger.error(e)
                self.con.rollback()

            return item

    def close_spider(self, spider):
        self.cur.close()
        self.con.close()


class DownBeijingCommunityInfoPipeline(object):
    """
    Save community records to SQLite3 database.
    """

    def __init__(self):
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
            community_rent_url varchar(100),
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
            logger.info(
                "The community %s is already in table community."
                % item["communityName"]
            )
            pass
        else:
            sql_add = """
            insert into community(community_name, community_url,
            community_rent_url, community_business_area, community_region,
            community_city) values("%s", "%s",
            "%s", "%s", "%s",
            "%s");
            """ % (
                item["community_name"],
                item["community_url"],
                item["community_rent_url"],
                item["community_business_area"],
                item["community_region"],
                "北京",
            )

            try:
                self.cur.execute(sql_add)
                self.con.commit()
            except Exception as e:
                logger.error(
                    "Error inserting '北京' community "
                    + item["community_name"]
                    + "["
                    + item["community_url"]
                    + "]"
                )
                logger.error(e)
                self.con.rollback()

            return item

    def close_spider(self, spider):
        self.cur.close()
        self.con.close()


class DownBeijingRentalInfoPipeline(object):
    """
    Save rental info records to SQLite3 database.
    """

    def __init__(self) -> None:
        db_path = "database/Lianjia.db"
        self.con = sqlite3.connect(db_path)
        self.cur = self.con.cursor()

        self.cur.execute("PRAGMA database_list")
        rows = self.cur.fetchall()
        for row in rows:
            print("database physical file path:", row[0], row[1], row[2])

        # Create beijing rental info database if not exists.
        self.cur.execute(
            """
        create table if not exists rental(
            rental_id integer not null,
            rental_name varchar(40) not null,
            rental_url varchar(100) unique not null,
            rental_city varchar(20) not null,
            rental_region varchar(20) not null,
            rental_business_area varchar(20) not null,
            rental_community_id integer not null,
            rental_community varchar(40) not null,
            rental_area numeric(10, 2) not null,
            rental_lighting varchar(10) not null,
            rental_rooms integer not null,
            rental_liverooms integer not null,
            rental_bathrooms integer not null,
            rental_price integer not null,
            rental_timestamp data not null,
            rental_accessbit integer default 0 not null,
            primary key(rental_id),
            foreign key(rental_city) references city(city_name),
            foreign key(rental_region) references region(region_name),
            foreign key(rental_business_area)
            references business_area(business_area_name),
            foreign key(rental_community_id, rental_community_name)
            references community(community_id, community_name)
        );
        """
        )

    def process_item(self, item, spider):
        sql_select = (
            """
        select *
        from rental
        where rental_url='%s'
        """
            % item["rental_url"]
        )

        self.cur.execute(sql_select)
        result = self.cur.fetchall()
        if result:
            logger.info(
                "The rental %s is already in table rental."
                % item["rental_name"]
            )
            pass
        else:
            sql_add = """
            insert into rental(rental_name, rental_url, rental_city,
            rental_region, rental_business_area, rental_community_id,
            rental_community, rental_area, rental_lighting, rental_rooms,
            rental_liverooms, rental_bathrooms, rental_price, rental_timestamp)
            values(?,?,?
                   ?,?,?,
                   ?,?,?,?,
                   ?,?,?,?)
            """
            try:
                self.cur.execute(
                    sql_add,
                    (
                        item["rental_name"],
                        item["rental_url"],
                        item["rental_city"],
                        item["rental_region"],
                        item["rental_business_area"],
                        item["rental_community_id"],
                        item["rental_community"],
                        item["rental_area"],
                        item["rental_lighting"],
                        item["rental_rooms"],
                        item["rental_liverooms"],
                        item["rental_bathrooms"],
                        item["rental_price"],
                        item["rental_timestamp"],
                    ),
                )
                self.con.commit()
            except Exception as e:
                self.con.rollback()
                logger.error("Error inserting into table rental.")
                logger.error(e)
            
            return item
        
    def close_spider(self, spider):
        self.cur.close()
        self.con.close()
