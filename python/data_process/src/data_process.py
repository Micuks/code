import argparse
import json
import csv


class json2csv:
    def __init__(self, in_file, out_file):
        self.in_file = in_file
        self.out_file = out_file
        self.data=[]

    def load_data(self):
        '''
        Load data from in_file, store in dictionary self.data
        '''
        in_file=self.in_file
        with open(in_file) as json_file:
            print("Load data from {}".format(in_file))
            self.data = json.load(json_file)

    def data_to_string(self):
        print(self.data)

    def write_data(self):
        '''
        Write self.data to csv_file
        '''
        out_file = self.out_file
        csv_file = open(out_file, 'w', newline='')
        csv_writer = csv.writer(csv_file)

        count = 0
        for section in self.data:
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
        prog="Lianjia house data \
    processor.",
        description="A script to process lianjia data crawled from \
    Linajia.",
        epilog="This is epilog.",
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

    processor = json2csv(in_file,out_file)
    processor.load_data()
    # processor.data_to_string()
    processor.write_data()
