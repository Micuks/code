import scrapy


class SecondHandSpider(scrapy.Spider):
    name = 'second_hand'
    allowed_domains = ['bj.lianjia.com']
    start_urls = ['http://bj.lianjia.com/']

    def parse(self, response):
        pass
