from ..items import *
import datetime
import re
import scrapy
import sqlite3
import logging

logger = logging.getLogger(__name__)


class RentSpider(scrapy.Spider):
    name = "RentSpider"
    allowed_domains = [
        "bj.lianjia.com",
        "sh.lianjia.com",
        "gz.lianjia.com",
        "sz.lianjia.com",
        "wf.lianjia.com",
    ]
    start_urls = [
        "https://bj.lianjia.com/",
        "https://sh.lianjia.com/",
        "https://gz.lianjia.com/",
        "https://sz.lianjia.com/",
        "https://wf.lianjia.com/",
    ]
    custom_settings = {
        "ITEM_PIPELINES": {
            "lianjia.pipelines.DownRentalInfoPipeline": 102,
        }
    }

    con = sqlite3.connect("database/Lianjia.db")
    cur = con.cursor()

    def start_requests(self):
        # Fetch communities that has not been crawled yet.
        sql = """
            select community_name, community_rent_url, community_city
            from community
            where community_rent_url!='None'
            and community_accessbit=0;
            """
        self.cur.execute(sql)
        rent_items = self.cur.fetchall()

        for rent_item in rent_items:
            community_name, community_rent_url, community_city = rent_item
            try:
                logger.info(
                    f"Crawling rent info in community {community_name}[{community_rent_url}] in {community_city}"
                )
                yield scrapy.Request(
                    url=community_rent_url,
                    callback=self.parse,
                    cb_kwargs={"city": community_city},
                )
            except Exception as e:
                logger.error(
                    f"Error crawling community {community_name}[{community_rent_url}] in {community_city}"
                )
                logger.error(e)
                continue

    def parse(self, response, city):
        # Crawl rental's details
        num_rents = response.xpath("//span[@class='q']/text()").get()
        num_rents = re.match(r"^[^\d]+(\d+)", num_rents).group(1)
        logger.debug("Number of houses available on rent[%s]" % num_rents)
        url_now = response.url
        community_name = str()
        if "0" != num_rents:
            content_list_items = response.xpath(
                "//div[@class='content__list--item']"
            )
            for content_list_item in content_list_items:
                try:
                    # Get rental element
                    item_main = content_list_item.xpath(
                        ".//div[@class='content__list--item--main']"
                    )
                    item_title = item_main.xpath(
                        ".//p[@class='content__list--item--title']"
                    )

                    # Name of rental
                    rent_name = (
                        item_title.xpath(".//a[@target='_blank']/text()")
                        .get()
                        .strip()
                    )
                    rent_url = item_title.xpath(
                        ".//a[@target='_blank']/@href"
                    ).get()
                    url_fragments = response.url.split("/")
                    rent_url = (
                        url_fragments[0] + "//" + url_fragments[2] + rent_url
                    )

                    # Get rental's location info
                    item_des = item_main.xpath(
                        ".//p[@class='content__list--item--des']"
                    )
                    rent_locations = item_des.xpath(".//a/text()").getall()
                    rent_region = rent_locations[0]
                    rent_business_area = rent_locations[1]
                    rent_community = rent_locations[2]
                    rent_community_rent_url = item_des.xpath(
                        ".//a/@href[2]"
                    ).get()
                    rent_areainfo = item_des.xpath(".//text()").getall()
                    for info in rent_areainfo:
                        if "㎡" in info:
                            # Rental area info (in m^2)
                            logger.debug(f"area info[{info}]")
                            rent_area = re.match(
                                r"^[\s]*?(\d+\.?\d*).*?", info
                            ).group(1)
                        elif "卫" in info:
                            logger.debug(f"room info[{info}]")
                            # Rental room info(%d rooms, %d live rooms, %d bathrooms)
                            rent_rooms = None
                            rent_liverooms = None
                            rent_bathrooms = None
                            try:
                                re_rent_roominto = re.match(
                                    r"^[\s]*?(\d+)室(\d+)厅(\d+)卫.*?", info
                                )
                                rent_rooms = re_rent_roominto.group(1)
                                rent_liverooms = re_rent_roominto.group(2)
                                rent_bathrooms = re_rent_roominto.group(3)
                            except:
                                try:
                                    re_rent_roominto = re.match(
                                        r"^[\s]*?(\d+)房间(\d+)卫.*?", info
                                    )
                                    rent_rooms = re_rent_roominto.group(1)
                                    rent_liverooms = 0
                                    rent_bathrooms = re_rent_roominto.group(2)
                                except:
                                    rent_rooms = 0
                                    rent_liverooms = 0
                                    rent_bathrooms = 0

                        elif (
                            "南" in info
                            or "北" in info
                            or "东" in info
                            or "西" in info
                        ):
                            logger.debug(f"lighting info[{info}]")
                            # Rental window direction info
                            rent_lighting = info.strip()

                    # Get rental's price
                    rent_price = item_main.xpath(
                        ".//span[@class='content__list--item-price']/em/text()"
                    ).get()

                    # Timestamp of this rental record
                    rent_timestamp = datetime.datetime.now().strftime(
                        "%Y-%m-%d"
                    )

                    # Update community_name for logger info
                    community_name = rent_community

                    item = RentalItem(
                        rental_name=rent_name,
                        rental_url=rent_url,
                        rental_city=city,
                        rental_region=rent_region,
                        rental_business_area=rent_business_area,
                        rental_community_url=url_now,
                        rental_community=rent_community,
                        rental_area=rent_area,
                        rental_lighting=rent_lighting,
                        rental_rooms=rent_rooms,
                        rental_liverooms=rent_liverooms,
                        rental_bathrooms=rent_bathrooms,
                        rental_price=rent_price,
                        rental_timestamp=rent_timestamp,
                    )
                    yield item

                except Exception as e:
                    logger.error(
                        f"Error crawling rentals in community {response.url} in {city}"
                    )
                    logger.error(e)
                    continue

            pagedata = response.xpath("//div[@class='content__pg']")
            total_page = pagedata.xpath("./@data-totalpage").get()
            curr_page = pagedata.xpath("./@data-curpage").get()
            if int(curr_page) < int(total_page):
                url_fragments = response.url.split("/")
                next_page = str(int(curr_page) + 1)
                if "pg" in url_now:
                    next_url = url_now.replace(
                        "pg%s" % curr_page, "pg%s", next_page
                    )
                else:
                    next_url = (
                        url_fragments[0]
                        + "//"
                        + url_fragments[2]
                        + "/"
                        + url_fragments[3]
                        + "/pg%s" % next_page
                        + url_fragments[4]
                        + "/"
                    )

                try:
                    logger.info(
                        "Crawl next page's rentals: [{}]".format(next_url)
                    )
                    yield scrapy.Request(
                        url=next_url,
                        callback=self.parse,
                        cb_kwargs={"city": city},
                    )
                except Exception as e:
                    logger.error(
                        "Error attempting to crawl next page's rentals[{}]",
                        next_url,
                    )
                    logger.error(e)
            else:
                # Finished crawling all rentals in current community.
                sql = (
                    """update community
                    set community_accessbit=1
                    where community_rent_url='%s';
                    """
                    % url_now
                )
                logger.debug(f"Update sql[{sql}]")
                community_name = community_name
                try:
                    self.cur.execute(sql)
                    self.con.commit()
                    logger.info(
                        f"Finished crawling all rentals in community {community_name}[{url_now}] in {city}."
                    )

                except Exception as e:
                    self.con.rollback()
                    logger.error(
                        "Error setting accessbit=1 o community[{}] in {}".format(
                            url_now, city
                        )
                    )
                    logger.error(
                        f"Failed crawling all rentals in community {community_name}[{url_now}] in {city}."
                    )

        else:
            # No rentals in current page.
            logger.info(
                f"Community {community_name}[{response.url}] in {city} has no rental info. "
                "Skip this community."
            )
            sql = (
                """update community
                set community_accessbit=2
                where community_rent_url='%s';
                """
                % url_now
            )
            try:
                self.cur.execute(sql)
                self.con.commit()
            except Exception as e:
                logger.error(
                    "Error setting accessbit=2 in community[{}] in {}".format(
                        url_now, city
                    )
                )
                self.con.rollback()
