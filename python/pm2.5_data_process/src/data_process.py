import argparse
from enum import Enum
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime
import pandas as pd
import csv
from plot_drawer import plot_drawer


class DataProcessor:
    def __init__(self, in_file: str, out_file: str) -> None:
        self.in_file = in_file
        self.out_file = out_file
        self.aqicategories = self.AQICategories

        # Load data.
        self._load_data()
        #
        # # Process data.
        # self._data_process()

    class AQICategories(Enum):
        '''
        AQI Categories.
        - Excellent: 0 - 50
        - Good: 51 - 100
        - Lightly Polluted: 101 - 150
        - Moderately Polluted: 151 - 200
        - Heavily Polluted: 201 - 300
        - Severely Polluted: > 300
        '''
        excellent = "Excellent"
        good = "Good"
        lightly_polluted = "Lightly Polluted"
        moderately_polluted = "Moderately Polluted"
        heavily_polluted = "Heavily Polluted"
        severely_polluted = "Severely Polluted"

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
            column = column.interpolate(
                method="linear", limit_direction="forward")

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
            cp = col.copy()
            cp[cp > 500] = 500

            return cp

        df["PM_Dongsi"] = process(df["PM_Dongsi"])
        df["PM_Dongsihuan"] = process(df["PM_Dongsihuan"])
        df["PM_Nongzhanguan"] = process(df["PM_Nongzhanguan"])

    def modify_cbwd(self):
        '''
        Fill the cells whose value is 'cv' in the cbwd column with the following
        cell data.
        '''
        df = self.processed_df

        cbwd = df["cbwd"].copy()
        for i in range(len(cbwd.index)-1):
            cbwd[i] = cbwd[i+1] if cbwd[i] == "cv" else cbwd[i]

        df["cbwd"] = cbwd

    def normalize_process(self):
        '''
        - Normalize column DEWP with 0-1 normalization.
        - Normalize column TEMP with Z-Score normalization.
        '''

        # Normalize column DEMP to [0, 1].
        df = self.processed_df

        min = df["DEWP"].min()
        max = df["DEWP"].max()

        def norm01(x, min, max): return (x - min) / (max - min)
        def norm01_col(col): return [norm01(col[i], min, max) for i in
                                     range(len(col))]

        df["DEWP"] = norm01_col(df["DEWP"])

        # Normalize column TEMP with Z-Score
        def norm_z(x, mean, std): return (x - mean) / std
        mean = df["TEMP"].mean()
        std = df["TEMP"].std()
        def norm_z_col(col): return [norm_z(col[i], mean, std) for i in
                                     range(len(col))]
        df["TEMP"] = norm_z_col(df["TEMP"])

    def visualize_normalized_data(self):
        '''
        Visualize normalized columns DEWP and TEMP in scatter.
        '''
        df = self.processed_df

        df.info()
        df.plot(x="DEWP", y="TEMP", kind='scatter')
        plt.show()

    def discretize_aqi(self):
        '''
        Discretize the air quality index of PM_Dongsi, PM_Dongsihuan and
        PM_Nongzhanguan into 5 levels as follows.
        - Excellent: 0 - 50
        - Good: 51 - 100
        - Lightly Polluted: 101 - 150
        - Moderately Polluted: 151 - 200
        - Heavily Polluted: 201 - 300
        - Severely Polluted: > 300
        '''
        PM_Dongsi_AQI = []
        PM_Dongsihuan_AQI = []
        PM_Nongzhanguan_AQI = []
        PM_US_Post_AQI = []

        df = self.processed_df
        aqis = self.aqicategories

        # Discretize PM_Dongsi into PM_Dongsi_AQI:
        def discretize_pm(column, discretized_column):
            for row in column:
                if 0 <= row <= 50:
                    discretized_column.append(aqis.excellent._value_)
                elif 51 <= row <= 100:
                    discretized_column.append(aqis.good._value_)
                elif 101 <= row <= 150:
                    discretized_column.append(aqis.lightly_polluted._value_)
                elif 151 <= row <= 200:
                    discretized_column.append(aqis.moderately_polluted._value_)
                elif 201 <= row <= 300:
                    discretized_column.append(aqis.heavily_polluted._value_)
                elif row > 300:
                    discretized_column.append(aqis.severely_polluted._value_)
                else:
                    # Handle NaN value.
                    discretized_column.append(row)

        discretize_pm(df["PM_Dongsi"], PM_Dongsi_AQI)
        discretize_pm(df["PM_Dongsihuan"], PM_Dongsihuan_AQI)
        discretize_pm(df["PM_Nongzhanguan"], PM_Nongzhanguan_AQI)
        discretize_pm(df["PM_US Post"], PM_US_Post_AQI)

        # Append discretized PM2.5 AQI into Dataframe df.
        df["PM_Dongsi_AQI"] = PM_Dongsi_AQI
        df["PM_Dongsihuan_AQI"] = PM_Dongsihuan_AQI
        df["PM_Nongzhanguan_AQI"] = PM_Nongzhanguan_AQI
        df["PM_US Post_AQI"] = PM_US_Post_AQI

    def visualize_AQI(self):
        '''
        Visualize the proportion of AQI classification of PM_Dongsi, PM_Dongsihuan,
        PM_Nongzhanguan and PM_US Post_AQI.
        '''
        df = self.processed_df
        cols = ["PM_Dongsi_AQI", "PM_Dongsihuan_AQI", "PM_Nongzhanguan_AQI",
                "PM_US Post_AQI"]
        aqis = df[cols]

        classes = [self.aqicategories.excellent._value_,
                   self.aqicategories.good._value_,
                   self.aqicategories.lightly_polluted._value_,
                   self.aqicategories.moderately_polluted._value_,
                   self.aqicategories.heavily_polluted._value_,
                   self.aqicategories.severely_polluted._value_]

        def count(col):
            '''
            Count AQI categories. Ignore NaN values.
            '''
            rslt = [0 for i in range(len(classes))]
            for row in col:
                if row in classes:
                    rslt[classes.index(row)] += 1

            print(rslt)
            return rslt

        data_dongsi = count(df["PM_Dongsi_AQI"])
        data_dongsihuan = count(df["PM_Dongsihuan_AQI"])
        data_nongzhanguan = count(df["PM_Nongzhanguan_AQI"])
        data_us = count(df["PM_US Post_AQI"])

        fig, ax = plt.subplots(2, 2, figsize=(
            12, 8), subplot_kw=dict(aspect="equal"))

        def draw_sub_pie(data, ax_x, ax_y):
            '''
            Draw subplot of pie.
            '''
            def get_absolute(pct, allvals):
                '''
                Get absolute value of days from percentage.
                '''
                absolute = int(np.round(pct/100.*np.sum(allvals)))
                return "{:.1f}%\n({:d} days)".format(pct, absolute)

            wedges, texts, autotexts = ax[ax_x, ax_y].pie(data, wedgeprops=dict(
                width=0.618), startangle=90, autopct=lambda pct: get_absolute(pct, data))
            bbox_props = dict(boxstyle="square,pad=0.3",
                              fc="w", ec="k", lw=0.72)
            kw = dict(arrowprops=dict(arrowstyle="-"),
                      bbox=bbox_props, zorder=0, va="center")

            # Compute angle of label line
            for i, p in enumerate(wedges):
                ang = (p.theta2 - p.theta1)/2. + p.theta1
                y = np.sin(np.deg2rad(ang))
                x = np.cos(np.deg2rad(ang))
                horizontalalignment = {-1: "right", 1: "left"}[int(np.sign(x))]
                connectionstyle = "angle,angleA=0,angleB={}".format(ang)
                kw["arrowprops"].update({"connectionstyle": connectionstyle})
                ax[ax_x, ax_y].annotate(classes[i] + " " + str(data[i]), xy=(x, y), xytext=(
                    1.35*np.sign(x), 1.2*y), horizontalalignment=horizontalalignment, **kw)

        draw_sub_pie(data_dongsi, 0, 0)
        draw_sub_pie(data_dongsihuan, 0, 1)
        draw_sub_pie(data_nongzhanguan, 1, 0)
        draw_sub_pie(data_us, 1, 1)
        ax[0, 0].set_title("Dongsi PM AQI")

        plt.show()

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
