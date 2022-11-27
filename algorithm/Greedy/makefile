CC := g++
RUSTC := rustc

huffman_from := 0
huffman_to := 1000

from := 0
to := 1000
amount := 500

BUILD_DIR := build

cli_parser_dir := src/utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp

huffman_src_dir := src/Huffman
huffman_filename := Huffman
huffman_rs_filename := HuffmanRS
huffman_cpp := $(huffman_src_dir)/Huffman.cpp
huffman_rs := $(huffman_src_dir)/yaHuffman.rs

huffman_gen_cpp := src/data_gen/huffman_data_gen.cpp
huffman_gen_filename := build/huffman_data_gen
huffman_gen_sample := data/huffman_yasample.in
huffman_gen_out = data/huffman_yasample.out

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

# cxxflags := -Wall -std=c++17 -O3
cxxflags := -Wall -std=c++17 -g
# rustflass := -O
rustflags := -g --edition 2021

.PHONY: all
all: mkdir huffman huffman_rs

huffman: $(BUILD_DIR)/Huffman

huffman_rs: $(BUILD_DIR)/HuffmanRS

docs: $(docs)
	# make docs
	$(MAKE) -C docs/ all

# Huffman
$(BUILD_DIR)/Huffman: $(BUILD_DIR)/Huffman.o $(BUILD_DIR)/CLIParser.o
	$(CC) $(cxxflags) $(BUILD_DIR)/CLIParser.o $(BUILD_DIR)/Huffman.o -o $(BUILD_DIR)/Huffman

$(BUILD_DIR)/Huffman.o: $(huffman_cpp)
	$(CC) -c $(cxxflags) $(huffman_cpp) -o $(BUILD_DIR)/Huffman.o

$(BUILD_DIR)/CLIParser.o: $(cli_parser_cpp)
	$(CC) -c $(cxxflags) $(cli_parser_cpp) -o $(BUILD_DIR)/CLIParser.o

# Huffman Rust
$(BUILD_DIR)/HuffmanRS:
	$(RUSTC) $(rustflags) -o $(BUILD_DIR)/$(huffman_rs_filename) $(huffman_rs)

# Huffman Test
huffman_test: $(huffman_gen_filename) huffman huffman_generate_yasample
	$(huffman_gen_filename) $(huffman_gen_sample)
	$(BUILD_DIR)/$(huffman_filename) --in $(huffman_gen_sample) --out $(huffman_gen_out)

huffman_generate_yasample:
	echo "[INFO]: Generate $(amount) random frequences sum to 1."
	$(huffman_gen_filename) $(huffman_from) $(huffman_to) $(amount)

# Huffman Data Generator
$(huffman_gen_filename): $(huffman_gen_cpp)
	$(CC) $(cxxflags) $(huffman_gen_cpp) -o $(huffman_gen_filename)

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
