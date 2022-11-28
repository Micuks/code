# RUST_BACKTRACE := 1

CC := g++
RUSTC := rustc

dijkstra_from := 0
dijkstra_to := 1000
amount := 5000

BUILD_DIR := ../build

cli_parser_dir := src/utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp

dijkstra_src_dir := src/
dijkstra_filename := Dijkstra
dijkstra_rs_filename := DijkstraRS
dijkstra_cpp := $(dijkstra_src_dir)/Dijkstra.cpp
dijkstra_rs := $(dijkstra_src_dir)/main.rs

dijkstra_gen_cpp := src/data_gen/dijkstra_data_gen.cpp
dijkstra_gen_filename := $(BUILD_DIR)/dijkstra_data_gen
dijkstra_gen_sample := data/dijkstra_yasample.in
dijkstra_gen_out := data/dijkstra_yasample.out
dijkstra_rs_gen_out := data/dijkstra_rs_yasample.out

# cxxflags := -Wall -std=c++17 -O3
cxxflags := -Wall -std=c++17 -g
# rustflass := -O
rustflags := -g --edition 2021

.PHONY: all
all: mkdir dijkstra dijkstra_rs

dijkstra: $(BUILD_DIR)/Dijkstra

dijkstra_rs: $(BUILD_DIR)/DijkstraRS

# Dijkstra
$(BUILD_DIR)/Dijkstra: $(BUILD_DIR)/Dijkstra.o $(BUILD_DIR)/CLIParser.o
	$(CC) $(cxxflags) $(BUILD_DIR)/CLIParser.o $(BUILD_DIR)/Dijkstra.o -o $(BUILD_DIR)/Dijkstra

$(BUILD_DIR)/Dijkstra.o: $(dijkstra_cpp)
	$(CC) -c $(cxxflags) $(dijkstra_cpp) -o $(BUILD_DIR)/dijkstra.o

$(BUILD_DIR)/CLIParser.o: $(cli_parser_cpp)
	$(CC) -c $(cxxflags) $(cli_parser_cpp) -o $(BUILD_DIR)/CLIParser.o

# dijkstra Rust
$(BUILD_DIR)/DijkstraRS: $(dijkstra_rs)
	$(RUSTC) $(rustflags) -o $(BUILD_DIR)/$(dijkstra_rs_filename) $(dijkstra_rs)

# test
.PHONY: test
test: mkdir dijkstra_test
# test: dijkstra_default_test

# dijkstra Test
default_test: dijkstra dijkstra_rs
	$(BUILD_DIR)/$(dijkstra_filename) --in data/dijkstra.in --out data/dijkstra.out
	$(BUILD_DIR)/$(dijkstra_rs_filename) --in data/dijkstra.in --out data/dijkstra_rs.out
	diff data/dijkstra.out data/dijkstra_rs.out

dijkstra_test: $(dijkstra_gen_filename) dijkstra dijkstra_rs generate_yasample
	$(BUILD_DIR)/$(dijkstra_filename) --in $(dijkstra_gen_sample) --out $(dijkstra_gen_out)
	$(BUILD_DIR)/$(dijkstra_rs_filename) --in $(dijkstra_gen_sample) --out $(dijkstra_rs_gen_out)
	diff $(dijkstra_gen_out) $(dijkstra_rs_gen_out)

generate_yasample: data_gen
	echo "[INFO]: Generate $(amount) random frequences sum to 1."
	$(dijkstra_gen_filename) $(dijkstra_from) $(dijkstra_to) $(amount)

# dijkstra Data Generator
.PHONY: dijkstra_data_gen
data_gen: $(dijkstra_gen_filename)

$(dijkstra_gen_filename): $(dijkstra_gen_cpp)
	$(CC) $(cxxflags) $(dijkstra_gen_cpp) -o $(dijkstra_gen_filename)

mkdir:
	$(shell mkdir -p $(BUILD_DIR))
