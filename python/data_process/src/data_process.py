import argparse
import json
import csv
import re
from plot_drawer import plot_drawer


class json2csv:
    def __init__(self, in_file, out_file):
        self.in_file = in_file
        self.out_file = out_file
        self.raw_data = []
        self.processed_data = []

        # Load data.
        self._load_data()

        # Process data.
        self._data_process()

    def _load_data(self):
        """
        Load data from in_file, store in dictionary self.data
        """
        in_file = self.in_file
        with open(in_file) as json_file:
            print("Load data from {}".format(in_file))
            self.raw_data = json.load(json_file)

    def _data_process(self):
        """
        Process the data crawled by Spyder in json format.

        Only preserve those keys: house_name: 名称, resblock_type: 类型, resblock_location:
        地理位置, resblock_room: 房型, resblock_area: 面积, house_total_price:
        总价(万元, integer), house_avg_price: 均价(元, integer), store them in
        new dict.

        The detailed tasks are as follows.
        - Remove trailing whitespaces in *house_name*.
        - Split *resblock_location* into three level.
        - Convert *house_total_price* and *house_avg_price* into integer.
        """
        raw_data = self.raw_data
        processed_data = self.processed_data

        for dict in raw_data:
            tmpdict = {}
            # Remove triling whitespace in string.
            rmtri = lambda s: s.strip()

            # Update {key: value} into tmpdict. If value is string, remove
            # triling whitespaces.
            upd = lambda key, value: tmpdict.update(
                {key: rmtri(value) if isinstance(value, str) else value}
            )

            # Extract the first one or two integer(s) from string.
            int_re = re.compile(r"^[\D]*(\d+)[\D]*(\d+)?")

            # Extract the *average* if there's at least *two numbers* else the
            # *min*.
            def extract_price(s):
                if s is None:
                    return -1
                match_rslt = int_re.match(s)
                # print(match_rslt.groups())

                return (
                    int((int(match_rslt.group(1)) + int(match_rslt.group(2))) / 2)
                    if match_rslt.group(2) is not None
                    else int(match_rslt.group(1))
                )

            upd("名称", dict["house_name"])
            upd("类型", dict["resblock_type"])
            upd("行政区", dict["resblock_location"][0])
            upd("次级地理位置", dict["resblock_location"][1])
            upd("末级地理位置", dict["resblock_location"][2])
            upd("房型", dict["resblock_room"])
            upd("面积", extract_price(dict["resblock_area"]))
            upd("总价", extract_price(dict["house_total_price"]))
            upd("均价", extract_price(dict["house_avg_price"]))

            processed_data.append(tmpdict)

        # Debug: Print processed_data
        jsonobj = json.dumps(processed_data, indent=4, ensure_ascii=False)
        print(jsonobj)

    def data_to_string(self):
        print(self.raw_data)

    def write_data(self):
        """
        Write self.processed_data to csv_file
        """
        out_file = self.out_file
        csv_file = open(out_file, "w", newline="")
        csv_writer = csv.writer(csv_file)

        count = 0
        for section in self.processed_data:
            if count == 0:
                header = section.keys()
                csv_writer.writerow(header)
                count += 1
            csv_writer.writerow(section.values())

        print(f"Successfully written file to {csv_file}")

        # Close file after write.
        csv_file.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="python data_process.py",
        description="A script to process lianjia data crawled from \
    Linajia.",
        epilog="author: 2020211323-2020211597 吴清柳",
    )
    parser.add_argument(
        "-i",
        "--infile",
        help="Json file to \
                        procecss.",
        type=str,
        default="../data/converted_new_house.json",
    )
    parser.add_argument(
        "-o",
        "--outfile",
        help="Path to output processed csv.",
        type=str,
        default="../data/converted_new_house.csv",
    )
    args = parser.parse_args()
    in_file = args.infile
    out_file = args.outfile

    # Load and process data stored in json.
    processor = json2csv(in_file, out_file)
    # Write data to csv.
    processor.write_data()

    # Draw plot.
    drawer = plot_drawer(processor.processed_data)
    drawer.draw_price_scatter_plot()
    drawer.draw_estate_distribution_pie_figure()
    drawer.draw_avg_of_avg_price_bar_figure()
    drawer.draw_avg_of_total_price_bar_figure()
    drawer.draw_compare_avg_and_total_price_plot()
