# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class LianjiaItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    pass

class BusinessAreaItem(scrapy.Item):
    # 商圈
    businessAreaUrl = scrapy.Field()
    businessAreaName = scrapy.Field()
    businessAreaRegion = scrapy.Field()