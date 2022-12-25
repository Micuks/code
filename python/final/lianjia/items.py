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
    business_area_url = scrapy.Field()
    business_area_name = scrapy.Field()
    business_area_region = scrapy.Field()


class CommunityItem(scrapy.Item):
    # Community
    community_url = scrapy.Field()
    community_name = scrapy.Field()
    community_region = scrapy.Field()
    community_business_area = scrapy.Field()
    community_rent_url = scrapy.Field()


class RentalItem(scrapy.Item):
    # Rental info
    rental_name = scrapy.Field()
    rental_url = scrapy.Field()
    rental_city=scrapy.Field()
    rental_region = scrapy.Field()
    rental_business_area = scrapy.Field()
    rental_community_url=scrapy.Field()
    rental_community = scrapy.Field()
    rental_area = scrapy.Field()
    rental_lighting = scrapy.Field()
    rental_rooms = scrapy.Field()
    rental_liverooms = scrapy.Field()
    rental_bathrooms = scrapy.Field()
    rental_price = scrapy.Field()
    rental_timestamp = scrapy.Field()
