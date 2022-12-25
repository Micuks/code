import json
import logging
import scrapy
import sqlite3
from ..items import *

# logging.basicConfig(
#     format="%(asctime)s [%(filename)s:%(lineno)d] %(levelname)s: %(message)s",
#     datefmt="%Y-%m-%dT%H:%M:%S",
#     level=logging.DEBUG,
# )

logger = logging.getLogger(__name__)


class BeijingCommunitySpider(scrapy.Spider):
    name = "BeijingCommunitySpider"
    allowed_domains = ["bj.lianjia.com"]
    start_urls = []
    custom_settings = {
        "ITEM_PIPELINES": {
            "lianjia.pipelines.DownBeijingCommunityInfoPipeline": 101,
        }
    }

    def __init__(self):
        self.con = sqlite3.connect("database/Lianjia.db")
        self.cur = self.con.cursor()

    def start_requests(self):
        """
        Crawl all business areas in '北京'.
        """
        sql = """
        select business_area_url
        from business_area
        where business_area_accessbit=0
        and business_area_city='北京';
        """
        self.cur.execute(sql)
        business_area_urls = self.cur.fetchall()
        for area_url in business_area_urls:
            try:
                print(f"Crawling business area {area_url[0]}")
                yield scrapy.Request(area_url[0])
            except:
                continue

    def parse(self, response):
        """
        Crawl all communities in each business area of '北京'.
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
                        item["communityRentUrl"] = list_item.xpath(
                            ".//div[@class='houseInfo']/a[2]/@href"
                        ).get()
                    elif len(urls) == 3:
                        item["communityRentUrl"] = list_item.xpath(
                            ".//div[@class='houseInfo']/a[3]/@href"
                        ).get()
                except:
                    logger.info(
                        "INFO: This community has no rent info: "
                        + community_url
                    )
                    item["communityRentUrl"] = None

                position_info = list_item.xpath(
                    ".//div[@class='positionInfo']/a/text()"
                ).getall()

                item["communityUrl"] = community_url
                item["communityName"] = list_item.xpath(
                    ".//div[@class='title']/a/text()"
                ).get()
                item["communityRegion"] = position_info[0]
                item["communityBusinessArea"] = position_info[1]

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
            try:
                pagedata = json.loads(pagedata)
                logger.debug(f"Pagedata json: {pagedata}")
                total_page = pagedata["totalPage"]
                curr_page = pagedata["curPage"]

                # Crawl next page if not the last page.
                if curr_page < total_page:
                    curr_page += 1
                    next_url = main_url + "pg%d/" % curr_page
                    logger.debug(f"next_url: {next_url}")
                    try:
                        logger.info(
                            "Crawl next community page in {}".format(
                                item["communityBusinessArea"]
                            )
                        )
                        yield scrapy.Request(url=next_url, callback=self.parse)
                    except:
                        logger.error(
                            "Error crawling next community page "
                            + next_url
                            + " in "
                            + item["communityBusinessArea"]
                        )
                else:
                    self.finish_area(main_url)
            except Exception as e:
                logger.error(e)

    def finish_area(self, main_url):
        # Set accessbit to 1 for resume crawling.
        logger.debug(f"in finish_area: main_url{main_url}")

        update_sql = (
            " update business_area set business_area_accessbit=1 where business_area_url='%s' and business_area_city='北京'; "
            % main_url
        )

        get_area_sql = (
            " select business_area_name from business_area where business_area_url='%s' and business_area_city='北京'; "
            % main_url
        )

        self.cur.execute(get_area_sql)
        business_area_name = self.cur.fetchone()
        logger.debug(f"business_area_name[{business_area_name}]")

        try:
            self.cur.execute(update_sql)
            self.con.commit()
            logger.info(
                'Finished crawling "北京" business area '
                + business_area_name[0]
                + "["
                + main_url
                + "]"
            )
        except Exception as e:
            self.con.rollback()
            logger.error(
                'Error updating accessbit of "北京" business area '
                + business_area_name[0]
                + "["
                + main_url
                + "]"
            )
            logger.error(e)
