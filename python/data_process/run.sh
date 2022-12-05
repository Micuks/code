#! /bin/bash

# Sample data
# python data_process.py \
#     -i ../data/sample.json \
#     -o ../data/sample.csv
#
# New house data
python src/data_process.py \
    -i ./data/converted_new_house.json \
    -o ./data/converted_new_house.csv
