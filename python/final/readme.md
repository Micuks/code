吴清柳 2020211597的Python期末大作业

爬虫在lianjia文件夹下. 在当前根目录可进行scrapyd部署.
三个爬虫分别叫BusinessAreaSpider, CommunitySpider和RentSpider, 分别负责爬取板块,
小区和租房信息.

数据分析部分在data_analysis下, 采用jupyter notebook.

文档分别在docs和data_analysis下. docs里是爬虫的文档, data_analysis重的jupyter
notebook即是数据分析代码, 也是数据分析文档.

组合好的文档为2020211597-吴清柳-实验报告.pdf. 由于gif不能插入pdf,
故单独放出制作的可交互饼图, 名字为`可交互饼图.gif`. 打开
data_analysis下的lianjia_analysis.ipynb可以找到这一可交互饼图并与其进行交互.

数据采用SQLite3保存, 导出了租房表rental.csv, 保存在data_analysis/database目录下.
