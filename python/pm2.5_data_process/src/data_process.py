import argparse
from datetime import datetime
import pandas as pd
import json
import csv
import re
from plot_drawer import plot_drawer


class DataProcessor:
    def __init__(self, in_file: str, out_file: str) -> None:
        self.in_file = in_file
        self.out_file = out_file
        self.raw_data = []
        self.processed_data = []

        # Load data.
        self._load_data()
        #
        # # Process data.
        # self._data_process()

    def _load_data(self):
        """
        Load data from in_file, store in dictionary self.data
        """
        in_file = self.in_file

        print("Load data from {}".format(in_file))
        # Read csv using pandas and store data in self.raw_dat and store data in
        # self.raw_data.
        dataset = pd.read_csv(in_file, 
                              parse_dates= {"dt": ['year','month','day','hour']},
                              date_parser = lambda x: \
                              datetime.strptime(x, "%Y %m %d %H"),
                              infer_datetime_format=True,
                              index_col='dt',
                              na_values=['NaN', '?']
                              )
        self.raw_data = dataset

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
    pass
