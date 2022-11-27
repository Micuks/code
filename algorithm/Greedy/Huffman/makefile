# RUST_BACKTRACE := 1

CC := g++
RUSTC := rustc

huffman_from := 0
huffman_to := 1000
amount := 5000

BUILD_DIR := ../build

cli_parser_dir := src/utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp

huffman_src_dir := src
huffman_filename := Huffman
huffman_rs_filename := HuffmanRS
huffman_cpp := $(huffman_src_dir)/Huffman.cpp
huffman_rs := $(huffman_src_dir)/mod.rs

huffman_gen_cpp := src/data_gen/huffman_data_gen.cpp
huffman_gen_filename := $(BUILD_DIR)/huffman_data_gen
huffman_gen_sample := data/huffman_yasample.in
huffman_gen_out := data/huffman_yasample.out
huffman_rs_gen_out := data/huffman_rs_yasample.out

# cxxflags := -Wall -std=c++17 -O3
cxxflags := -Wall -std=c++17 -g
# rustflass := -O
rustflags := -g --edition 2021

.PHONY: all
all: mkdir huffman huffman_rs

huffman: $(BUILD_DIR)/Huffman

huffman_rs: $(BUILD_DIR)/HuffmanRS

# Huffman
$(BUILD_DIR)/Huffman: $(BUILD_DIR)/Huffman.o $(BUILD_DIR)/CLIParser.o
	$(CC) $(cxxflags) $(BUILD_DIR)/CLIParser.o $(BUILD_DIR)/Huffman.o -o $(BUILD_DIR)/Huffman

$(BUILD_DIR)/Huffman.o: $(huffman_cpp)
	$(CC) -c $(cxxflags) $(huffman_cpp) -o $(BUILD_DIR)/Huffman.o

$(BUILD_DIR)/CLIParser.o: $(cli_parser_cpp)
	$(CC) -c $(cxxflags) $(cli_parser_cpp) -o $(BUILD_DIR)/CLIParser.o

# Huffman Rust
$(BUILD_DIR)/HuffmanRS: $(huffman_rs)
	$(RUSTC) $(rustflags) -o $(BUILD_DIR)/$(huffman_rs_filename) $(huffman_rs)

# test
.PHONY: test
test: mkdir huffman_test
# test: huffman_default_test

# Huffman Test
huffman_default_test: huffman huffman_rs
	$(BUILD_DIR)/$(huffman_filename) --in data/huffman/huffman.in --out data/huffman/huffman.out
	$(BUILD_DIR)/$(huffman_rs_filename) --in data/huffman/huffman.in --out data/huffman/huffman_rs.out
	diff data/huffman/huffman.out data/huffman/huffman_rs.out

huffman_test: $(huffman_gen_filename) huffman huffman_rs huffman_generate_yasample
	$(BUILD_DIR)/$(huffman_filename) --in $(huffman_gen_sample) --out $(huffman_gen_out)
	$(BUILD_DIR)/$(huffman_rs_filename) --in $(huffman_gen_sample) --out $(huffman_rs_gen_out)
	diff $(huffman_gen_out) $(huffman_rs_gen_out)

huffman_generate_yasample: huffman_data_gen
	echo "[INFO]: Generate $(amount) random frequences sum to 1."
	$(huffman_gen_filename) $(huffman_from) $(huffman_to) $(amount)

# Huffman Data Generator
.PHONY: huffman_data_gen
huffman_data_gen: $(huffman_gen_filename)

$(huffman_gen_filename): $(huffman_gen_cpp)
	$(CC) $(cxxflags) $(huffman_gen_cpp) -o $(huffman_gen_filename)

mkdir:
	$(shell mkdir -p $(BUILD_DIR))
