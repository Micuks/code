from asyncio.log import logger
from ..items import *
import datetime
import re
import scrapy
import sqlite3


class BeijingRentSpider(scrapy.Spider):
    name = "BeijingRentSpider"
    allowed_domains = ["bj.lianjia.com"]
    start_urls = ["https://bj.lianjia.com/"]
    custom_settings = {
        "ITEM_PIPELINES": {
            "lianjia.pipelines.DownBeijingRentInfoPipeline": 102,
        }
    }

    def __init__(self, name=None, **kwargs):
        self.con = sqlite3.connect("database/Lianjia.db")
        self.cur = self.con.cursor()

    def start_requests(self):
        sql = "select community_name, community_rent_url from community where community_rent_url!='None'"
        self.cur.execute(sql)
        rent_items = self.cur.fetchall()

        for rent_item in rent_items:
            community_name, community_rent_url = rent_item
            try:
                logger.info(
                    f"Crawling rent info in community {community_name}[{community_rent_url}]"
                )
                yield scrapy.Request(
                    url=community_rent_url, callback=self.parse
                )
            except Exception as e:
                logger.error(
                    f"Error crawling community {community_name}[{community_rent_url}]"
                )
                logger.error(e)
                continue

    def parse(self, response):
        # Crawl rental's details
        num_rents = response.xpath("//span[@class='q']/text()").get()
        num_rents = re.match(r"^[^\d]+(\d+)", num_rents).group(1)
        logger.debug("Number of houses available on rent: ", num_rents)
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
                    rent_name = item_title.xpath(
                        ".//a[@target='_blank']/text()"
                    ).get()

                    # Get rental's location info
                    item_des = item_main.xpath(
                        ".//p[@class='content__list--item--des']"
                    )
                    rent_locations = item_des.xpath(".//a/text()").getall()
                    rent_region = rent_locations[0]
                    rent_business_area = rent_locations[1]
                    rent_community = rent_locations[2]
                    rent_areainfo = item_des.xpath(".//i/text()").getall()
                    # Rental area info (in m^2)
                    rent_area = rent_areainfo[0]
                    rent_area = re.match(r"^(\d+).*", rent_area)

                    # Rental window direction info
                    rent_lighting = rent_areainfo[1]

                    # Rental room info(%d rooms, %d live rooms, %d bathrooms)
                    rent_roominfo = rent_areainfo[2]
                    re_rent_roominto = re.match(
                        r"(\d+)室(\d+)厅(\d+)卫", rent_roominfo
                    )
                    rent_rooms = re_rent_roominto.group(1)
                    rent_liverooms = re_rent_roominto.group(2)
                    rent_bathrooms = re_rent_roominto.group(3)

                    # Get rental's price
                    rent_price = item_main.xpath(
                        ".//span[@class='content__list--item-price']/em/text()"
                    ).get()

                    # Timestamp of this rental record
                    rent_timestamp = datetime.datetime.now().strftime(
                        "%Y-%m-%d"
                    )

                    item = RentalItem(
                        rental_name=rent_name,
                        rental_region=rent_region,
                        rental_business_area=rent_business_area,
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
                        f"Error crawling rentals in community {response.url}"
                    )
                    logger.error(e)
                    continue

            pagedata = response.xpath("//div[@class='content__pg']")
            total_page = pagedata.xpath("./@data-totalpage").get()
            curr_page = pagedata.xpath("./@data-curpage").get()
            url_now = response.url
            if int(curr_page) < int(total_page):
                url_fragments = response.url.split("/")
                next_page = str(int(curr_page) + 1)
                if "pg" in url_now:
                    next_url = url_now.replace(
                        "pg%s" % curr_page, "pt%s", next_page
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
                    yield scrapy.Request(url=next_url, callback=self.parse)
                except Exception as e:
                    logger.error(
                        "Error attempting to crawl next page's rentals[{}]",
                        next_url,
                    )
                    logger.error(e)
            else:
                # Finished crawling all rentals in current community.
                sql = (
                    "update community set community_accessbit=1 where community_rent_url=%s;"
                    % url_now
                )
                logger.debug(f"Update sql[{sql}]")
                self.cur.execute(sql)
                self.con.commit()
                community_name = get_community_name()
                logger.info(
                    f"Finished crawling all rentals in community {community_name}[{url_now}]."
                )

        else:
            # No rentals in current page.
            community_name = get_community_name()
            logger.info(
                f"Community {community_name}[{response.url}] has no rental info. Skip this community."
            )
            sql = (
                "update community set community_accessbit=2 where community_rent_url=%s;"
                % url_now
            )
            self.cur.execute(sql)
            self.con.commit()
            pass

        def get_community_name() -> str:
            """
            Get current community name.
            """
            url_now = response.url
            sql = (
                "select community_name from community where community_rent_url=%s;"
                % url_now
            )
            logger.debug("Get community name sql[{}]".format(sql))
            self.cur.execute(sql)
            return self.cur.fetchone()[0]
