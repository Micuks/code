CC := g++
from := 0
to := 1000
amount := 500

BUILD_DIR := build

cli_parser_dir := utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp

huffman_src_dir := Huffman
huffman_filename := Huffman
huffman_cpp := $(huffman_src_dir)/Huffman.cpp

gen_cpp := data_gen/data_gen.cpp
gen_filename := build/data_gen
gen_sample := samples/yet_another_sample.in

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

# cxxflags := -Wall -std=c++17 -O3
cxxflags := -Wall -std=c++17 -g

.PHONY: all
all: mkdir huffman

huffman: $(BUILD_DIR)/Huffman

docs: $(docs)
	# make docs
	$(MAKE) -C docs/ all

test_default: backpack jump_point_backpack
	$(BUILD_DIR)/$(backpack_filename)
	$(BUILD_DIR)/$(jump_point_backpack_filename)

test: $(gen_filename) backpack jump_point_backpack generate_yasample
	$(BUILD_DIR)/$(backpack_filename) $(gen_sample)
	$(BUILD_DIR)/$(jump_point_backpack_filename) $(gen_sample)

generate_yasample:
	echo "[INFO]: Generate $(amount) random numbers ranging from $(from) to $(to)."
	$(gen_filename) $(from) $(to) $(amount)

# Data Generator
$(gen_filename): $(gen_cpp)
	$(CC) $(cxxflags)  $(gen_cpp) -o $(gen_filename)

# Huffman
$(BUILD_DIR)/Huffman: $(BUILD_DIR)/Huffman.o $(BUILD_DIR)/CLIParser.o
	$(CC) $(cxxflags) $(BUILD_DIR)/CLIParser.o $(BUILD_DIR)/Huffman.o -o $(BUILD_DIR)/Huffman

$(BUILD_DIR)/Huffman.o: $(huffman_cpp)
	$(CC) -c -g $(cxxflags) $(huffman_cpp) -o $(BUILD_DIR)/Huffman.o

$(BUILD_DIR)/CLIParser.o: $(cli_parser_cpp)
	$(CC) -c -g $(cxxflags) $(cli_parser_cpp) -o $(BUILD_DIR)/CLIParser.o

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
