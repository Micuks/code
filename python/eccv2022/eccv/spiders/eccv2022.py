import scrapy


class EccvSpider(scrapy.Spider):
    name = "eccv"
    allowed_domains = ["ecva.net"]
    path_to_save_response = "eccv2022.html"
    pdf_directory = "./papers/"

    def start_requests(self):
        urls = ["https://www.ecva.net/papers.php#"]
        # urls = ['file:///Users/micuks/dev/mycode/python/scrapy/lianjia/new_house_response.html']
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):

        url_prefix = "https://www.ecva.net/"

        pdf_path = "./papers/"  # Path to save pdfs.
        # Write response to file for debugging
        with open(self.path_to_save_response, "w") as response_file:
            response_file.write(response.text)

        # 2020 - 2022 papers
        papers = response.xpath("//div[@class='accordion-content']/div/dl")[0]
        papers_dt = papers.xpath("./dt")
        papers_dd = papers.xpath("./dd")

        for i, paper_name in enumerate(papers_dt):
            paper_authors = papers_dd[2 * i]
            paper_url = papers_dd[2 * i + 1]

            paper_name = paper_name.xpath("./a/text()").get()[1:]

            paper_authors = paper_authors.xpath("./text()").get()[1:]

            paper_pdf = paper_url.xpath("./a/@href").get()
            paper_pdf = url_prefix + paper_pdf

            # if "detect" in paper_name or "Detect" in paper_name:
            # Paper metadata
            yield {
                "paper_name": paper_name,
                "paper_authors": paper_authors,
                "paper_pdf": paper_pdf,
            }

            # Download and save paper pdf.
            yield scrapy.Request(
                url=paper_pdf,
                callback=self.parse_pdf,
                cb_kwargs={"paper_name": paper_name},
            )

    def parse_pdf(self, response, paper_name: str):
        """
        Save paper pdf.

        Args:
            response (_type_): paper pdf response

        Yields:
            _type_: _description_
        """
        filename = self.pdf_directory + paper_name + ".pdf"

        with open(filename, "wb") as f:
            f.write(response.body)
