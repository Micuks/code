# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import sqlite3
import logging
import os

logger = logging.getLogger(__name__)
# logger.setLevel(logging.INFO)

class LianjiaPipeline:
    def process_item(self, item, spider):
        return item

class DownBusinessAreaUrlPipeline(object):
    """
    Save business area records to SQLite3 database.
    """

    def open_spider(self, spider):
        os.makedirs("./database/", exist_ok=True)
        db_path = "database/Lianjia.db"
        # Connect to database.
        self.con = sqlite3.connect(db_path)

        # Create cursor, used to execute commands.
        self.cur = self.con.cursor()
        self.cur.execute("PRAGMA database_list;")
        rows = self.cur.fetchall()
        for row in rows:
            print("database physical file path: ", row[0], row[1], row[2])

        try:
            # Create Beijing business area table if none exists.
            self.cur.execute(
                """
                create table if not exists city(
                    city_id integer not null,
                    city_name varchar(20) unique not null,
                    primary key(city_id)
                );
                """
            )

            self.cur.execute(
                """
                create table if not exists region(
                    region_id integer not null,
                    region_name varchar(20) not null,
                    city_name varchar(20) not null,
                    primary key(region_id),
                    unique(region_name, city_name),
                    foreign key (city_name) references city(city_name)
                );
                """
            )

            self.cur.execute(
                """
                create table if not exists business_area(
                    business_area_id integer not null,
                    business_area_name varchar(20) not null,
                    business_area_url varchar(100) unique not null,
                    business_area_region varchar(20) not null,
                    business_area_city varchar(20) not null,
                    business_area_accessbit integer default 0 not null,

                    unique(business_area_name, business_area_city),
                    primary key(business_area_id),
                    foreign key (business_area_region, business_area_city)
                    references region(region_name, region_city),
                    foreign key(business_area_city) references city(city_name)
                );
                """
            )
            self.con.commit()
        except Exception as e:
            logger.error("Error creating table city, region or business_area.")
            raise (e)

    def process_item(self, item, spider):
        # Check and update city
        sql_select = """
        select *
        from city
        where city_name='%s';
        """ % (
            item["business_area_city"]
        )
        self.cur.execute(sql_select)
        result = self.cur.fetchall()
        if not result:
            logger.info("Insert new city {}".format(item["business_area_city"]))
            sql_insert = (
                """
                insert into city(city_name)
                values("%s");
                """
                % item["business_area_city"]
            )
            try:
                self.cur.execute(sql_insert)
                self.con.commit()
            except Exception as e:
                self.con.rollback()
                logger.error(
                    "Error inserting new city {}".format(
                        item["business_area_city"]
                    )
                )

        # Check and update region
        sql_select = (
            """
        select *
        from region
        where region_name='%s';
        """
            % item["business_area_region"]
        )
        self.cur.execute(sql_select)
        result = self.cur.fetchall()
        if not result:
            sql_insert = """
            insert into region(region_name, city_name)
            values(?, ?);
            """
            logger.info(
                "Insert new region {} in city {}.".format(
                    item["business_area_region"], item["business_area_city"]
                )
            )
            try:
                self.cur.execute(
                    sql_insert,
                    (
                        item["business_area_region"],
                        item["business_area_city"],
                    ),
                )
                self.con.commit()
            except Exception as e:
                self.con.rollback()
                logger.error(
                    "Error inserting new region {} in city {}".format(
                        item["business_area_region"],
                        item["business_area_city"],
                    )
                )
                logger.error(e)

        # Check and update business area
        sql_select = (
            """
        select *
        from business_area
        where business_area_url='%s';
        """
            % item["business_area_url"]
        )

        self.cur.execute(sql_select)
        result = self.cur.fetchone()
        if result:
            logger.info(result)
            logger.info(
                f"Business area[{item['business_area_name']}] already exists in"
                "SQLite database."
            )
        else:
            sql_add = """
                    insert into business_area(
                            business_area_name, business_area_url,
                            business_area_region, business_area_city
                    ) values (?, ?, ?, ?);
                    """
            try:
                # Insert if no exception.
                self.cur.execute(
                    sql_add,
                    (
                        item["business_area_name"],
                        item["business_area_url"],
                        item["business_area_region"],
                        item["business_area_city"],
                    ),
                )
                # Commit if no exception.
                self.con.commit()

            except Exception as e:
                # Rollback if exception.
                logger.error(
                    "Error inserting {} into table business_area.".format(
                        item["business_area_name"]
                    )
                )
                logger.error(e)
                self.con.rollback()

            return item

    def close_spider(self, spider):
        self.cur.close()
        self.con.close()


class DownCommunityInfoPipeline(object):
    """
    Save community records to SQLite3 database.
    """

    def open_spider(self, spider):
        os.makedirs("./database/", exist_ok=True)
        db_path = "database/Lianjia.db"
        self.con = sqlite3.connect(db_path)
        self.cur = self.con.cursor()

        self.cur.execute("PRAGMA database_list;")
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
        self.con.commit()

    def process_item(self, item, spider):
        sql_select = """
        select *
        from community
        where community_url='%s';
        """ % (
            item["community_url"]
        )
        self.cur.execute(sql_select)
        result = self.cur.fetchall()

        if result:
            logger.info(
                "The community %s is already in table community."
                % item["community_name"]
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
                item["community_city"],
            )

            try:
                self.cur.execute(sql_add)
                self.con.commit()
            except Exception as e:
                logger.error(
                    "Error inserting {} community "
                    + item["community_name"]
                    + "["
                    + item["community_url"]
                    + "]".format(item["community_city"])
                )
                logger.error(e)
                self.con.rollback()

            return item

    def close_spider(self, spider):
        self.cur.close()
        self.con.close()


class DownRentalInfoPipeline(object):
    """
    Save rental info records to SQLite3 database.
    """

    def open_spider(self, spider):
        os.makedirs("./database/", exist_ok=True)
        db_path = "database/Lianjia.db"
        self.con = sqlite3.connect(db_path)
        self.cur = self.con.cursor()

        self.cur.execute("PRAGMA database_list;")
        rows = self.cur.fetchall()
        for row in rows:
            print("database physical file path:", row[0], row[1], row[2])

        # Create beijing rental info database if not exists.
        try:
            self.cur.execute(
                """
                create table if not exists rental(
                rental_id integer not null,
                rental_name varchar(40) not null,
                rental_url varchar(100) unique not null,
                rental_city varchar(20) not null,
                rental_region varchar(20) not null,
                rental_business_area varchar(20) not null,
                rental_community_url varchar(100) not null,
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
                foreign key(rental_community, rental_community_url)
                references community(community_name, community_url)
                );
            """
            )
            self.con.commit()
        except Exception as e:
            self.con.rollback()
            logger.error("Error creating rental table.")
            logger.error(e)

    def process_item(self, item, spider):
        sql_select = (
            """
        select *
        from rental
        where rental_url='%s';
        """
            % item["rental_url"]
        )

        try:
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
                rental_region, rental_business_area, rental_community_url,
                rental_community, rental_area, rental_lighting, rental_rooms,
                rental_liverooms, rental_bathrooms, rental_price, rental_timestamp)
                values(?,?,?,
                       ?,?,?,
                       ?,?,?,?,
                       ?,?,?,?);
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
                            item["rental_community_url"],
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
        except Exception as e:
            logger.error(
                f"Error processing item[{item['rental_name']}] in pipeline."
            )
            logger.error(e)
            self.con.rollback()

    def close_spider(self, spider):
        self.cur.close()
        self.con.close()
