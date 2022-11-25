CCXX := clang++
from := 0
to := 1000
amount := 500

BUILD_DIR := build

huffman_src_dir := Huffman
huffman_filename := Huffman
huffman_cpp := $(huffman_src_dir)/Huffman.cpp

gen_cpp := data_gen/data_gen.cpp
gen_filename := build/data_gen
gen_sample := samples/yet_another_sample.in

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

cxxflags := -Wall -std=c++17 -O3

.PHONY: all
all: mkdir huffman

huffman: $(BUILD_DIR)/Huffman.o $(BUILD_DIR)/Huffman

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
	$(CCXX) $(cxxflags)  $(gen_cpp) -o $(gen_filename)

# Huffman
$(BUILD_DIR)/Huffman: $(BUILD_DIR)/Huffman.o
	$(CCXX) $(cxxflags) $(BUILD_DIR)/Huffman.o -o $(BUILD_DIR)/Huffman

$(BUILD_DIR)/Huffman.o: $(huffman_cpp)
	$(CCXX) -c -g $(cxxflags) $(huffman_cpp) -o $(BUILD_DIR)/Huffman.o

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
