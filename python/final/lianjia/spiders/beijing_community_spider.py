from asyncio.log import logger
import json
import scrapy
import sqlite3
from ..items import *


class BeijingCommunitySpider(scrapy.Spider):
    name = "BeijingCommunitySpider"
    allowed_domains = ["bj.lianjia.com"]
    start_urls = []
    custom_settings = {
        "ITEM_PIPELINES": {
            "lianjia.pipelines.DownCommunityInfoPipeline": 101,
        }
    }

    def __init__(self, name=None, **kwargs):
        self.con = sqlite3.connect("database/Lianjia.db")
        self.cur = self.con.cursor()

    def start_requests(self):
        '''
        Crawl all business areas in '北京'.
        '''
        sql = """
        select business_area_url
        from business_area
        where b_accessbit=0
        and business_area_city='北京';
        """
        self.cur.execute(sql)
        business_area_urls = self.cur.fetchall()
        for area_url in business_area_urls:
            try:
                print(f"Crawling business area {area_url}")
                yield scrapy.Request(area_url)
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
                        item["communityRentUrl"] = urls.xpath(
                            ".//div[@class='title']/a[2]/@href"
                        ).get()
                    elif len(urls) == 3:
                        item["communityRentUrl"] = urls.xpath(
                            ".//div[@class='title']/a[3]/@href"
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
        json_pagedata = json.loads(pagedata)
        total_page = pagedata["totalPage"]
        curr_page = pagedata["curPage"]

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

        # Crawl next page if not the last page.
        if curr_page < total_page:
            curr_page += 1
            next_url = main_url + "pg%d/" % curr_page
            print(next_url)
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
            print("------------")
            # Set accessbit to 1 for resume crawling.
            sql = (
                """
            update business_area
            set business_area_accessbit=1
            where b_url='%s'
            and business_area_city='北京';
            """
                % main_url
            )
            try:
                self.cur.execute(sql)
                logger.info(
                    "Finished crawling \"北京\" business area "
                    + item["communityBusinessArea"]
                    + "["
                    + main_url
                    + "]"
                )
            except Exception as e:
                logger.error(
                    "Error updating accessbit of \"北京\" business area "
                    + item["communityBusinessArea"]
                    + "["
                    + main_url
                    + "]"
                )