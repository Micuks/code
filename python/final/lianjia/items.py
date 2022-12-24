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
    # Business area
    businessAreaUrl = scrapy.Field()
    businessAreaName = scrapy.Field()
    businessAreaRegion = scrapy.Field()
    
class CommunityItem(scrapy.Item):
    # Community
    communityUrl = scrapy.Field()
    communityName = scrapy.Field()
    communityRegion = scrapy.Field()
    communityBusinessArea = scrapy.Field()
    communityRentUrl = scrapy.Field()
    communityAccessBit = scrapy.Field()