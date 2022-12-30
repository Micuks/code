import scrapy
import logging
from ..items import *

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)


class BusinessAreaSpider(scrapy.Spider):
    name = "BusinessAreaSpider"
    allowed_domains = [
        "bj.lianjia.com",
        "sh.lianjia.com",
        "gz.lianjia.com",
        "sz.lianjia.com",
        "wf.lianjia.com",
    ]
    # path_to_save_response = "beijing_community_response.html"
    custom_settings = {
        "ITEM_PIPELINES": {
            "lianjia.pipelines.DownBusinessAreaUrlPipeline": 100,
        }
    }

    def start_requests(self):
        urls = [
            "https://bj.lianjia.com/xiaoqu/dongcheng/",
            "https://sh.lianjia.com/xiaoqu/pudong/",
            "https://gz.lianjia.com/xiaoqu/tianhe/",
            "https://sz.lianjia.com/xiaoqu/luohuqu/",
            "https://wf.lianjia.com/xiaoqu/linquxian/",
        ]
        cities = ["北京", "上海", "广州", "深圳", "潍坊"]
        # urls = ['file:///Users/micuks/dev/mycode/python/final/lianjia/'+self.path_to_save_response]
        for i, url in enumerate(urls):
            yield scrapy.Request(
                url=url, callback=self.parse, cb_kwargs={"city": cities[i]}
            )

    def parse(self, response, city="Unknown"):
        # If there's two-level region filter,
        # first crawl all administrative district href,
        # then the second level(business area level).
        # Else let city by first level, then
        # treat first and the only level as business area level.
        region_levels = response.xpath(
            "//div[@data-role='ershoufang']/div"
        ).getall()
        logger.debug(f"len(region_levels)[{len(region_levels)}]")

        administrative_district_hrefs = response.xpath(
            "//div[@data-role='ershoufang']/div[1]/a/@href"
        ).getall()
        for href in administrative_district_hrefs:
            href = response.urljoin(href)
            # Crawl each district href.
            yield scrapy.Request(
                url=href,
                callback=self.parse_district,
                cb_kwargs={"city": city},
            )

    # For those cities who has only one level filter. Cities like this has not
    # been found yet.
    def parse_one_level_district(self, response, city="Unknown"):
        """Crawl districts in cities that have only one-level region filter.
        - Crawl business area url of each administrative district,
        - And yield business areas to pipeline.

        Args:
            response : Scrapy response.
            city (str, optional): This city. Defaults to "Unknown".
        """

        # Current administrative district
        business_curr_district = city
        # Business area names in current district
        business_area_name = response.xpath(
            "//div[@data-role='ershoufang']/div/a/text()"
        ).getall()
        # Business area hrefs
        business_area_href = response.xpath(
            "//div[@data-role='ershoufang']/div/a/@href"
        ).getall()

        for name, href in zip(business_area_name, business_area_href):
            area_url = response.urljoin(href)
            area_name = name
            logger.info(
                "Crawling district info: {} {} {}[{}]".format(
                    city,
                    business_curr_district,
                    area_name,
                    area_url,
                )
            )

            item = BusinessAreaItem(
                business_area_url=area_url,
                business_area_name=area_name,
                business_area_region=business_curr_district,
                business_area_city=city,
            )
            yield item

    def parse_district(self, response, city="Unknown"):
        """
        - Crawl business area url of each administrative district,
        - And yield business areas to pipeline.
        """

        # Current administrative district
        business_curr_district = response.xpath(
            "//div[@data-role='ershoufang']//a[@class='selected']/text()"
        ).get()

        # Business area names in current district
        business_area_name = response.xpath(
            "//div[@data-role='ershoufang']/div[2]/a/text()"
        ).getall()

        # Business area hrefs in current district
        business_area_href = response.xpath(
            "//div[@data-role='ershoufang']/div[2]/a/@href"
        ).getall()

        for name, href in zip(business_area_name, business_area_href):
            area_url = response.urljoin(href)
            area_name = name

            logger.info(
                "Crawling district info: {} {} {}[{}]".format(
                    city,
                    business_curr_district,
                    area_name,
                    area_url,
                )
            )

            item = BusinessAreaItem(
                business_area_url=area_url,
                business_area_name=area_name,
                business_area_region=business_curr_district,
                business_area_city=city,
            )
            yield item
