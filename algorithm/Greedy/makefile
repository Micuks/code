RUST_BACKTRACE := 1

CC := g++
RUSTC := rustc

huffman_from := 0
huffman_to := 1000

from := 0
to := 1000
amount := 5000

BUILD_DIR := build

cli_parser_dir := src/utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp

huffman_parent := Huffman/
huffman_src_dir := src/Huffman
huffman_filename := Huffman
huffman_rs_filename := HuffmanRS
huffman_cpp := $(huffman_src_dir)/Huffman.cpp
huffman_rs := $(huffman_src_dir)/mod.rs

huffman_gen_cpp := src/data_gen/huffman_data_gen.cpp
huffman_gen_filename := build/huffman_data_gen
huffman_gen_sample := data/huffman_yasample.in
huffman_gen_out := data/huffman_yasample.out
huffman_rs_gen_out := data/huffman_rs_yasample.out

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

# cxxflags := -Wall -std=c++17 -O3
cxxflags := -Wall -std=c++17 -g
# rustflass := -O
rustflags := -g --edition 2021

.PHONY: all
all: mkdir huffman

.PHONY: huffman
huffman: $(huffman_parent)/*
	$(MAKE) -C $(huffman_parent)/ all

.PHONY: test
test: huffman
	$(MAKE) -C $(huffman_parent)/ test

docs: $(docs)
	# make docs
	$(MAKE) -C docs/ all
mkdir:
	$(shell mkdir -p $(BUILD_DIR))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
