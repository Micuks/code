from data_process import DataProcessor
import pandas as pd
import argparse


class Parser:
    """
    Parser wrapped argparse to process CLI arguments.
    """

    def __init__(self):
        self.parser = argparse.ArgumentParser(
            prog="python main.py",
            description="Scripts to process Beijing PM2.5 data and visulize"
            "the data.",
            epilog="Author: 2020211323-2020211597-吴清柳",
        )
        parser = self.parser

        # Defile cli arguments.
        parser.add_argument(
            "-i",
            "--infile",
            help="CSV file to process.",
            type=str,
            default="../data/BeijingPM20100101_20151231.csv",
        )
        parser.add_argument(
            "-o",
            "--outfile",
            help="Path to save processed data.",
            type=str,
            default="../data/ProcessedBeijingPM.csv",
        )

        # Parse cli arguments.
        self.args = parser.parse_args()

        args = self.args
        self.in_file = args.infile
        self.out_file = args.outfile

    def get_arguments(self) -> tuple[str, str]:
        """
        Get cli arguments value.

        Returns a tuple containing the following items:
            - in_file: csv file to load data from.
            - out_file: path to write processed data to in csv format.
        """

        return (self.in_file, self.out_file)


if __name__ == "__main__":

    parser = Parser()
    in_file, out_file = parser.get_arguments()
    processor = DataProcessor(in_file, out_file)

    # Print raw_data for dev.
    # df.info()
    print(processor.raw_df.head(100))

    # show quick statistic
    # print(df.describe())

    # linear interpolate and truncate values in HUMI, PRES and TEMP that larget than
    # 3*sigma+mean.
    processor.linear_interpolate()
    processor.handle_values_over_500()
    processor.modify_cbwd()
    processor.normalize_process()
    processor.discretize_aqi()

    df = processor.processed_df
    print(df.head(100))

    # processor.visualize_normalized_data()
    processor.visualize_AQI()
