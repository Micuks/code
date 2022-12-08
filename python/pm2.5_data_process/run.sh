#! /bin/bash

# sample process for testing.
# python src/main.py \
#     -i data/sample.csv \
#     -o data/processed_sample.csv

# # process Beijing PM2.5 data.
python src/main.py \
    -i ./data/BeijingPM20100101_20151231.csv \
    -o ./data/processed_BeijingPM20100101_20151231.csv
