import scrapy


class NewHouseSpider(scrapy.Spider):
    name = 'new_house'
    allowed_domains = ['bj.fang.lianjia.com']
    current_page = 1

    def start_requests(self):
        urls = ['http://bj.fang.lianjia.com/pg' +
                str(i)+'/' for i in range(3, 4, 1)]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        houses = \
            response.xpath(
                "//ul[@class='resblock-list-wrapper']/li[contains(@class,'resblock-list')]")
        # TODO: houses maybe single house due to li.

        for house in houses:
            resblock_name = house.xpath(".//div[@class='resblock-name']")
            # Get house_name and resblock_type
            house_name = \
                resblock_name.xpath("./a/text()").get()
            resblock_type = \
                resblock_name.xpath(
                    "./span[@class='resblock-type']/text()").get()

            # Get resblock_location
            resblock_location = house.xpath(
                ".//div[@class='resblock-location']/span/text()").getall()
            resblock_location.extend(house.xpath(
                ".//div[@class='resblock-location']/a/text()").getall())

            # Get resblock_room
            resblock_room = house.xpath(
                ".//a[@class='resblock-room']/span/text()").get()
            resblock_area = \
                house.xpath(".//div[@class='resblock-area']/span/text()").get()

            house_avg_price = \
                house.xpath(
                    ".//div[@class='main-price']/span[@class='number']/text()").get()
            house_total_price = \
                house.xpath(
                    ".//div[@class='resblock-price']/div[@class='second']/text()").get()

            yield {
                'house_name': house_name,
                'resblock_type': resblock_type,
                'resblock_location': resblock_location,
                'resblock_room': resblock_room,
                'resblock_area': resblock_area,
                'house_avg_price': house_avg_price,
                'house_total_price': house_total_price,
            }
