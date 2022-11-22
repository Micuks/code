import scrapy


class SecondHandSpider(scrapy.Spider):
    name = 'second_hand'
    allowed_domains = ['bj.lianjia.com']
    path_to_save_response = 'second_hand_house_response.html'

    def start_requests(self):
        urls = [
            'file:///Users/micuks/dev/mycode/python/scrapy/lianjia/second_hand_house_response.html']
        # urls = ['https://bj.lianjia.com/ershoufang/pg' +
        #         str(i)+'/' for i in range(3, 4, 1)]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        with open(self.path_to_save_response, 'w') as response_file:
            response_file.write(response.text)

        houses = response.xpath(
            "//li[@class='clear LOGVIEWDATA LOGCLICKDATA']")

        for house in houses:
            # list house_name
            house_name =\
                house.xpath(
                    ".//div[@class='info clear']/div[@class='title']/a/text()").get().split()

            # list house_location
            house_location = house.xpath(
                ".//div[@class='positionInfo']/a/text()").getall()

            # list house_type
            house_type = house.xpath(
                ".//div[@class='houseInfo']/text()").get().strip().split('|')

            # string house_avg_price
            house_avg_price =\
                house.xpath(".//div[@class='unitPrice']/span/text()").get()

            # string house_total_price
            house_total_price = house.xpath(
                ".//div[@class='priceInfo']//span/text()").get()
            house_total_price += house.xpath(
                ".//div[@class='priceInfo']//i/text()")[1].get()

            def decode_unicode_str(str):
                return str.encode('utf-8').decode('utf-8')

            def decode_unicode_list(lstr):
                return [decode_unicode_str(s) for s in lstr]

            yield {
                'house_name': decode_unicode_list(house_name),
                'house_location': decode_unicode_list(house_location),
                'house_type': decode_unicode_list(house_type),
                'house_avg_price': decode_unicode_str(house_avg_price),
                'house_total_price': decode_unicode_str(house_total_price),
            }
