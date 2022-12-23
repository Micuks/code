import scrapy
from items import *


class BeijingCommunitySpider(scrapy.Spider):
    name = "beijing_community"
    allowed_domains = ["bj.lianjia.com"]
    path_to_save_response = "beijing_community_response.html"
    custom_settings = {
        "ITEM_PIPELINES": {
            "webCrawler.pipelines.DownBeijingCommunityUrlPipeline": 100,
        }
    }

    def start_requests(self):
        urls = ["https://bj.lianjia.com/xiaoqu/"]
        # urls = ['file:///Users/micuks/dev/mycode/python/scrapy/lianjia/'+path_to_save_response]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        # Write response to file for debugging
        with open(self.path_to_save_response, "w") as response_file:
            response_file.write(response.text)

        # Crawl all administrative district href.
        administrative_district_hrefs = response.xpath(
            "//div[@data-role='ershoufang']/div[1]/a/@href"
        )
        for href in administrative_district_hrefs:
            href = response.urljoin(href)
            # Crawl each district href.
            yield scrapy.Request(url=href, callback=self.parse_district)

            # def decode_unicode_str(str):
            #     return str.encode("utf-8").decode("utf-8")

            # def decode_unicode_list(lstr):
            #     return [decode_unicode_str(s) for s in lstr]

    def parse_district(self, response):
        '''
        - Crawl business area url of each administrative district, 
        - And yield business areas to pipeline.
        '''

        # Current administrative district
        business_curr_district = response.xpath(
            "//div[@data-role='ershoufang']//a[@class='selected']/text()"
        ).getall()

        # Business area names in current district
        business_area_name = response.xpath(
            "//div[@data-role='ershoufang']/div[2]/a/text()"
        )

        # Business area hrefs in current district
        business_area_href = response.xpath(
            "//div[@data-role='ershoufang']/div[2]/a/@href"
        )

        for name, href in zip(business_area_name, business_area_href):
            area_url = response.urljoin(href)
            area_name = name

            print(business_curr_district, area_name, area_url)

            item = BusinessAreaItem(
                businessAreaUrl=area_url,
                businessAreaName=area_name,
                businessAreaRegion=business_curr_district,
            )

            yield item
