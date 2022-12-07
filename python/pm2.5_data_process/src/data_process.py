import argparse
import numpy as np
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
        dataset = pd.read_csv(
            in_file,
            parse_dates={"Date": ["year", "month", "day", "hour"]},
            date_parser=lambda x: datetime.strptime(x, "%Y %m %d %H"),
            infer_datetime_format=True,
            index_col="Date",
            na_values=["NaN", "?"],
        )
        self.raw_df = dataset

    def linear_interpolate(self):
        """
        - Process linear interpolate on column HUMI, PRES and TEMP.
        - For data above or below mean +(-) 3*sigma, truncate them to
          mean +(-) 3*sigma.
        """
        df = self.raw_df.copy()

        def process(column):
            # Linear interpolate
            # print(column)
            column = column.interpolate(method="linear", limit_direction="forward")

            # Process highly anomalous data that exceeds 3 standard deviations.
            std = column.std()
            mean = column.mean()
            column[column > mean + 3 * std] = 3 * std + mean
            column[column < mean - 3 * std] = 3 * std - mean

            return column

        df["HUMI"] = process(df["HUMI"])
        df["PRES"] = process(df["PRES"])
        df["TEMP"] = process(df["TEMP"])
        # for col in (df["HUMI"], df["PRES"], df["TEMP"]):
        #     col = process(col)
        #     print(col)

        self.processed_df = df

    def handle_values_over_500(self):
        """
        Replace values over 500 with 500 on column PM_Dongsi, PM_Dongsihuan and
        PM_Nongzhanguan.

        Don't process NaN values.
        """
        df = self.processed_df

        def process(col):
            col[col > 500] = 500

            return col

        df["PM_Dongsi"] = process(df["PM_Dongsi"])
        df["PM_Dongsihuan"] = process(df["PM_Dongsihuan"])
        df["PM_Nongzhanguan"] = process(df["PM_Nongzhanguan"])

    def modify_cbwd(self):
        '''
        Fill the cells whose value is 'cv' in the cbwd column with the following
        cell data.
        '''
        df = self.processed_df

        cbwd = df["cbwd"]
        for i in range(len(cbwd.index)-1):
            cbwd[i] = cbwd[i+1] if cbwd[i] == "cv" else cbwd[i]

    def normalize_process(self):
        '''
        - Normalize column DEWP with 0-1 normalization.
        - Normalize column TEMP with Z-Score normalization.
        '''

        # Normalize column DEMP to [0, 1].
        df = self.processed_df
        # for col in df["DEWP"]:
        #     df[col] = (df[col] - df[col].min()) / (df[col].max() - df[col].min())

        min = df["DEWP"].min()
        max = df["DEWP"].max()

        norm = lambda x, min, max: (x - min) / (max - min)
        normalize_col = lambda col:[norm(col[i], min, max) for i in
                                    range(len(col))]

        df["DEWP"] = normalize_col(df["DEWP"])


    def data_to_string(self):
        print(self.raw_df)

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

    # def process_humi_pres


if __name__ == "__main__":
    pass
