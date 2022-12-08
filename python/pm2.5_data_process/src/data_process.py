import argparse
from enum import Enum
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime
import pandas as pd


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

    def add_zh_cn_support(self):
        # Set default Chinese font.
        plt.rcParams["font.sans-serif"] = ["Songti SC"]
        plt.rcParams["axes.unicode_minus"] = False

    def customize_colors(self):
        # Customize colors.
        CB91_Blue = "#2CBDFE"
        CB91_Green = "#47DBCD"
        CB91_Pink = "#F3A0F2"
        CB91_Purple = "#9D2EC5"
        CB91_Violet = "#661D98"
        CB91_Amber = "#F5B14C"
        color_list = [
            CB91_Blue,
            CB91_Pink,
            CB91_Green,
            CB91_Amber,
            CB91_Purple,
            CB91_Violet,
        ]
        plt.rcParams["axes.prop_cycle"] = plt.cycler(color=color_list)
        self.colors = color_list

    def customize_plot(self):
        plt.rcParams["font.size"] = 12
        plt.rcParams["axes.titlesize"] = 20
        plt.rcParams["axes.labelsize"] = 15

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
        Load data from in_file, store in dictionary self.raw_data
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
        # Store values modified.

        def process(column):
            cnt = 0
            # Linear interpolate
            new_col = column.interpolate(
                method="linear", limit_direction="forward")

            # Process highly anomalous data that exceeds 3 standard deviations.
            std = column.std()
            mean = column.mean()
            new_col[column > mean + 3 * std] = 3 * std + mean
            new_col[column < mean - 3 * std] = 3 * std - mean

            # Count how many cells modified.
            for i in range(len(new_col)):
                if new_col[i] != column[i]:
                    cnt += 1

            print(f"Modified {cnt} cells.")
            return new_col

        print(f"Linear interpolate and process highly anomalous data in HUMI.")
        df["HUMI"] = process(df["HUMI"])
        print(f"Linear interpolate and process highly anomalous data in PRES.")
        df["PRES"] = process(df["PRES"])
        print(f"Linear interpolate and process highly anomalous data in PRES.")
        df["TEMP"] = process(df["TEMP"])

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
            print(f"Handled {len([x for x in cp[cp > 500]])} values")
            cp[cp > 500] = 500
            return cp

        print(f"Handle values larger than 500 in PM_Dongsi.")
        df["PM_Dongsi"] = process(df["PM_Dongsi"])
        print(f"Handle values larger than 500 in PM_Dongsihuan.")
        df["PM_Dongsihuan"] = process(df["PM_Dongsihuan"])
        print(f"Handle values larger than 500 in PM_Nongzhanguan.")
        df["PM_Nongzhanguan"] = process(df["PM_Nongzhanguan"])

    def modify_cbwd(self):
        '''
        Fill the cells whose value is 'cv' in the cbwd column with the following
        cell data from bottom to top.
        '''
        df = self.processed_df
        cnt = 0

        cbwd = df["cbwd"].copy()
        for i in range(len(cbwd.index), 1, -1):
            if cbwd[i-1] == 'cv':
                cnt += 1
            cbwd[i-1] = cbwd[i] if cbwd[i-1] == "cv" else cbwd[i-1]

        print(f"Modified {cnt} cells whose value is 'cv' in column 'cbwd'.")
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
        print(f"0-1 nomalized column 'DEWP'.")

        # Normalize column TEMP with Z-Score
        def norm_z(x, mean, std): return (x - mean) / std
        mean = df["TEMP"].mean()
        std = df["TEMP"].std()
        def norm_z_col(col): return [norm_z(col[i], mean, std) for i in
                                     range(len(col))]
        df["TEMP"] = norm_z_col(df["TEMP"])
        print(f"z-score normalized column 'TEMP'.")

    def visualize_normalized_data(self):
        '''
        Visualize normalized columns DEWP and TEMP in scatter.
        '''
        df = self.processed_df

        df.info()
        self.add_zh_cn_support()
        self.customize_colors()
        self.customize_plot()
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

        print(f"Discretize the air quality index of PM_Dongsi.")
        discretize_pm(df["PM_Dongsi"], PM_Dongsi_AQI)
        print(f"Discretize the air quality index of PM_Dongsi.")
        discretize_pm(df["PM_Dongsihuan"], PM_Dongsihuan_AQI)
        print(f"Discretize the air quality index of PM_Dongsi.")
        discretize_pm(df["PM_Nongzhanguan"], PM_Nongzhanguan_AQI)
        print(f"Discretize the air quality index of PM_Dongsi.")
        discretize_pm(df["PM_US Post"], PM_US_Post_AQI)

        print(f"Finished discretizing the air quality index.")

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
        zh_classes = ["优", "良", "轻度污染", "中度污染", "重度污染", "严重污染"]

        def count(col):
            '''
            Count AQI categories. Ignore NaN values.
            '''
            rslt = [0 for i in range(len(classes))]
            for row in col:
                if row in classes:
                    rslt[classes.index(row)] += 1
            return rslt

        data_dongsi = count(df["PM_Dongsi_AQI"])
        data_dongsihuan = count(df["PM_Dongsihuan_AQI"])
        data_nongzhanguan = count(df["PM_Nongzhanguan_AQI"])
        data_us = count(df["PM_US Post_AQI"])

        def print_statistics(d):
            '''
            Pretty printing AQI statistics data stored in d.'''
            print(f"    Excellent[{d[0]}]\n"
                  f"    Good[{d[1]}]\n"
                  f"    Lightly Polluted[{d[2]}]\n"
                  f"    Moderately Polluted[{d[3]}]\n"
                  f"    Heavily Polluted[{d[4]}]\n"
                  f"    Severely Polluted[{d[5]}]\n")

        print(f"PM_Dongsi statistics:")
        print_statistics(data_dongsi)
        print(f"PM_Dongsihuan statistics:")
        print_statistics(data_dongsihuan)
        print(f"PM_Nongzhanguan statistics:")
        print_statistics(data_nongzhanguan)
        print(f"PM_US Post statistics:")
        print_statistics(data_us)

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

            wedges, texts, autotexts = ax.pie(data, wedgeprops=dict(
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
                ax.annotate(classes[i] + " " + zh_classes[i], xy=(x, y), xytext=(
                    1.35*np.sign(x), 1.2*y), horizontalalignment=horizontalalignment, **kw)

        # Set plotting parameters.
        self.add_zh_cn_support()
        self.customize_colors()
        self.customize_plot()

        fig, ax = plt.subplots(figsize=(
            12, 8), subplot_kw=dict(aspect="equal"))
        draw_sub_pie(data_dongsi, 0, 0)
        ax.set_title("Dongsi PM AQI")
        plt.show()

        fig, ax = plt.subplots(figsize=(
            12, 8), subplot_kw=dict(aspect="equal"))
        draw_sub_pie(data_dongsihuan, 0, 1)
        ax.set_title("Dongsihuan PM AQI")
        plt.show()

        fig, ax = plt.subplots(figsize=(
            12, 8), subplot_kw=dict(aspect="equal"))
        draw_sub_pie(data_nongzhanguan, 1, 0)
        ax.set_title("Nongzhanguan PM AQI")
        plt.show()

        fig, ax = plt.subplots(figsize=(
            12, 8), subplot_kw=dict(aspect="equal"))
        draw_sub_pie(data_us, 1, 1)
        ax.set_title("US Post PM AQI")
        plt.show()

    def write_data(self):
        """
        Write self.processed_data to csv_file
        """
        out_file = self.out_file
        try:
            self.processed_df.to_csv(out_file, encoding='utf-8')
        except:
            print(f"Error writing to {out_file}")
        else:
            print(f"Successfully written file to {out_file}")


if __name__ == "__main__":
    pass
