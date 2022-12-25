import scrapy
import logging
from ..items import *

logger = logging.getLogger(__name__)


class BusinessAreaSpider(scrapy.Spider):
    name = "BusinessAreaSpider"
    allowed_domains = [
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
            "https://sh.lianjia.com/xiaoqu/",
            "https://gz.lianjia.com/xiaoqu/",
            "https://sz.lianjia.com/xiaoqu/",
            "https://wf.lianjia.com/xiaoqu/",
        ]
        cities = ["上海", "广州", "深圳", "潍坊"]
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
        if len(region_levels) == 2:
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

        elif len(region_levels) == 1:
            one_level_districts = response.xpath(
                "//div[@data-role='ershoufang']/div[1]/a/@href"
            ).getall()
            for href in one_level_districts:
                href = response.urljoin(href)
                yield scrapy.Request(
                    url=href,
                    callback=self.parse_one_level_district,
                    cb_kwargs={"city": city},
                )

        else:
            logger.error(f"Unknown region level depth: {len(region_levels)}")

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
                "Crawling district info:",
                city,
                business_curr_district,
                area_name,
                area_url,
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
                "Crawling district info: ",
                city,
                business_curr_district,
                area_name,
                area_url,
            )

            item = BusinessAreaItem(
                business_area_url=area_url,
                business_area_name=area_name,
                business_area_region=business_curr_district,
                business_area_city=city,
            )
            yield item
