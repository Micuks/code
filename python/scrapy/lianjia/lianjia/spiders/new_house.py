import scrapy


class NewHouseSpider(scrapy.Spider):
    name = 'new_house'
    allowed_domains = ['bj.fang.lianjia.com']
    current_page = 1
    path_to_save_response = 'response.html'

    def start_requests(self):
        urls = ['http://bj.fang.lianjia.com/loupan/pg' +
                str(i)+'/' for i in range(3, 8, 1)]
        # urls = ['file:///Users/micuks/dev/mycode/python/scrapy/lianjia/response.html']
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        # Ensure that proxy really returns the target page by checking the
        # lianjia logo. If not, retry request with dont_filter=True
        # if not response.xpath("//a[@class='logo']"):
        #     yield scrapy.Request(url=response.url, dont_filter=True)
        # Write response to file for debugging
        with open(self.path_to_save_response, "w") as response_file:
            response_file.write(response.text)

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

            def decode_unicode_str(str):
                return str.encode('utf-8').decode('unicode_escape')

            def decode_unicode_list(lstr):
                return [decode_unicode_str(s) for s in lstr]

            yield {
                'house_name': house_name,
                'resblock_type': resblock_type,
                'resblock_location': [s for s in resblock_location],
                'resblock_room': resblock_room,
                'resblock_area': resblock_area,
                'house_avg_price': house_avg_price,
                'house_total_price': house_total_price,
            }
