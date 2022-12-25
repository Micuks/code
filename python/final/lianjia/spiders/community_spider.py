import json
import logging
import scrapy
import sqlite3
from ..items import *
import logging

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)


class CommunitySpider(scrapy.Spider):
    """Crawl all communities in current region

    Args:
        scrapy : spider

    Yields:
        item: item crawled
    """

    name = "CommunitySpider"
    allowed_domains = [
        "bj.lianjia.com",
        "sh.lianjia.com",
        "gz.lianjia.com",
        "sz.lianjia.com",
        "wf.lianjia.com",
    ]
    start_urls = []
    custom_settings = {
        "ITEM_PIPELINES": {
            "lianjia.pipelines.DownCommunityInfoPipeline": 101,
        }
    }

    con = sqlite3.connect("database/Lianjia.db")
    cur = con.cursor()

    def start_requests(self):
        """
        Crawl all business areas in given cities.
        """
        sql = """
        select business_area_url, business_area_city
        from business_area
        where business_area_accessbit=0;
        """
        self.cur.execute(sql)
        business_areas = self.cur.fetchall()
        for area_url, area_city in business_areas:
            try:
                print(f"Crawling business area {area_url} in {area_city}")
                yield scrapy.Request(
                    url=area_url,
                    callback=self.parse,
                    cb_kwargs={"city": area_city},
                )
            except:
                continue

    def parse(self, response, city="Unknown"):
        """
        Crawl all communities in current business area of current city.
        """
        community_list_items = response.xpath(
            "//li[@class='clear xiaoquListItem']"
        )
        for list_item in community_list_items:
            item = CommunityItem()
            try:
                community_url = list_item.xpath(
                    ".//div[@class='title']/a/@href"
                ).get()
                urls = list_item.xpath(".//div[@class='houseInfo']/a")

                # zone of urls containing rent url varies.
                try:
                    if len(urls) == 2:
                        item["community_rent_url"] = list_item.xpath(
                            ".//div[@class='houseInfo']/a[2]/@href"
                        ).get()
                    elif len(urls) == 3:
                        item["community_rent_url"] = list_item.xpath(
                            ".//div[@class='houseInfo']/a[3]/@href"
                        ).get()
                except:
                    logger.info(
                        "INFO: This community has no rent info: "
                        + community_url
                    )
                    item["community_rent_url"] = None

                position_info = list_item.xpath(
                    ".//div[@class='positionInfo']/a/text()"
                ).getall()

                item["community_url"] = community_url
                item["community_name"] = list_item.xpath(
                    ".//div[@class='title']/a/text()"
                ).get()
                item["community_region"] = position_info[0]
                item["community_business_area"] = position_info[1]
                item["community_city"] = city

                # Crawl each community detail page separately if more detailed
                # data is needed.
                # yield scrapy.Request(
                #     url=community_url,
                #     callback=self.parse_community,
                #     meta={"item": item},
                # )

                # Or just yield community item to pipeline
                yield item

            except Exception as e:
                logger.error(
                    "ERROR: Something wrong while crawling community url: "
                    + response.url
                )

        # Jump page
        pagedata = response.xpath(
            "//div[@class='page-box house-lst-page-box']/@page-data"
        ).get()
        logger.debug(f"Pagedata: {pagedata}")

        url_framents = response.url.split("/")
        main_url = (
            url_framents[0]
            + "//"
            + url_framents[2]
            + "/"
            + url_framents[3]
            + "/"
            + url_framents[4]
            + "/"
        )

        if pagedata:
            pagedata = json.loads(pagedata)
            logger.debug(f"Pagedata json: {pagedata}")
            total_page = pagedata["totalPage"]
            curr_page = pagedata["curPage"]

            # Crawl next page if not the last page.
            if curr_page < total_page:
                curr_page += 1
                try:
                    next_url = main_url + f"pg{curr_page}/"
                except Exception as e:
                    logger.error(f"next_url: {next_url}")
                    logger.error(e)

                try:
                    logger.info(
                        "Crawl next community page in {}".format(
                            item["community_business_area"]
                        )
                    )
                    yield scrapy.Request(
                        url=next_url,
                        callback=self.parse,
                        cb_kwargs={"city": city},
                    )
                except:
                    logger.error(
                        "Error crawling next community page "
                        + next_url
                        + " in "
                        + item["community_business_area"]
                    )
            else:
                self.finish_area(main_url, city)

    def finish_area(self, main_url, city):
        # Set accessbit to 1 for resume crawling.
        logger.debug(f"in finish_area of {main_url} in {city}")

        get_area_sql = """ select business_area_name
            from business_area
            where business_area_url='%s'
            and business_area_city='%s';
            """ % (
            main_url,
            city,
        )

        update_sql = """ update business_area
            set business_area_accessbit=1
            where business_area_url='%s'
            and business_area_city='%s';
            """ % (
            main_url,
            city,
        )

        self.cur.execute(get_area_sql)
        business_area_name = self.cur.fetchone()
        logger.debug(f"business_area_name[{business_area_name}]")

        try:
            self.cur.execute(update_sql)
            self.con.commit()
            logger.info(
                'Finished crawling "%s" business area ' % business_area_name[0]
                + "["
                + main_url
                + "] in %s" % city
            )
        except Exception as e:
            self.con.rollback()
            logger.error(
                'Error updating accessbit of "%s" business area '
                % business_area_name[0]
                + "["
                + main_url
                + "] in %s" % city
            )
            logger.error(e)
