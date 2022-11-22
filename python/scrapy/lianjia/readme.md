---
title: "Python数据抓取作业"
author: "吴清柳 2020211597"
data: November 22, 2022
---

# 作业要求

分别爬取链家官网新房和二手房的数据(从第3页开始到第5页).
新房需要爬取以下数据: 楼盘名称 类型 地点 房型 面积 单价 总价;
二手房需要爬取以下数据: 小区名称, 地点, 房型, 单价, 总价;
爬取的数据保存在json文件中.

# 内容

制作了两个爬虫new_house和second_hand, 分别爬取链家的新房和二手房信息.

由于Scrapy默认保存的json文件中使用了escape-unicode字符格式, 且一个json条目放在一行,
让人类无法阅读. 为了解决这个问题,
制作了`unicode2str.py`来将escape-unicode字符转为UTF-8格式的人类可阅读的json文件.

# 测试环境

Python 3.11.0, Scrapy 2.7.1, Clang 14.0.4, macOS 13.1 22C5050e arm64; 使用neovim v8.0.0编写.

# 使用方法

使用前可以考虑在settings.py中停用`'lianjia.middlewares.ProxiesMiddleware'`中间件,
或者在`middlewares.py`中的`ProxiesMiddleware`类中更改代理为自己的代理.

```shell
# Run scrapy spiders to crawl Lianjia new house and second-hand house info and
# store them in json format.
scrapy crawl new_house -O new_house.json
scrapy crawl second_hand -O second_hand.json

# The data crawled are stored in new_house.json and second_hand.json.

# Considering that they are difficult for human to read, convert them into more
# readable type.
py unicode2str.py

# Converted json files are saved as converted_new_house.json and
# converted_second_hand.json

# Converted json files are saved as converted_new_house.json and
# converted_second_hand.json.
```

# 防反爬策略

在settings.py中进行如下设置来避免被链家屏蔽请求.

- 随机User-Agent: 使用`scrapy-user-agents`来随机切换UA,
  放入DOWNLOADER_MIDDLEWARES中.
- 使用代理IP: 制作代理中间件ProxiesMiddleware在middlewares.py中,
    将通往代理的本机8001接口用作代理, 放入DOWNLOADER_MIDDLEWARES中.
- 设置下载延迟DOWNLOAD_DELAY = 3
- 设置并行请求数CONCURRENT_REQUESTS_PER_DOMAIN = 2,
    CONCURRENT_REQUESTS_PER_IP = 2.
- 不使用cookie: COOKIES_ENABLED = False.
