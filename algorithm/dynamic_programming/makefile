CCXX := clang++
from := 0
to := 1000
amount := 500

BUILD_DIR := build

backpack_src_dir := 01bp
backpack_filename := BackPack01
backpack_cpp := ${backpack_src_dir}/$(backpack_filename).cpp

jump_point_backpack_src_dir := 01bp_optimized
jump_point_backpack_filename := JumpPointBackPack
jump_point_backpack_cpp := $(jump_point_backpack_src_dir)/$(jump_point_backpack_filename).cpp

gen_cpp := data_gen/data_gen.cpp
gen_filename := build/data_gen
gen_sample := samples/yet_another_sample.in

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

cxxflags := -Wall -std=c++17 -O3

.PHONY: all
all: mkdir backpack jump_point_backpack

backpack: $(BUILD_DIR)/$(backpack_filename).o $(BUILD_DIR)/$(backpack_filename)

jump_point_backpack: $(BUILD_DIR)/$(jump_point_backpack_filename).o $(BUILD_DIR)/$(jump_point_backpack_filename)

docs: $(docs)
	# make docs
	$(MAKE) -C docs/ all

test_default: backpack jump_point_backpack
	$(BUILD_DIR)/$(backpack_filename)
	$(BUILD_DIR)/$(jump_point_backpack_filename)

test: $(gen_filename) backpack jump_point_backpack generate_yasample
	$(BUILD_DIR)/$(backpack_filename) $(gen_sample)
	$(BUILD_DIR)/$(jump_point_backpack_filename) $(gen_sample)

	diff samples/bag.out samples/jump_bag.out

generate_yasample:
	echo "[INFO]: Generate $(amount) random numbers ranging from $(from) to $(to)."
	$(gen_filename) $(from) $(to) $(amount)

# Data Generator
$(gen_filename): $(gen_cpp)
	$(CCXX) $(cxxflags)  $(gen_cpp) -o $(gen_filename)

# BackPack
$(BUILD_DIR)/$(backpack_filename): $(BUILD_DIR)/$(backpack_filename).o
	$(CCXX) $(cxxflags) $(BUILD_DIR)/$(backpack_filename).o -o $(BUILD_DIR)/$(backpack_filename)

$(BUILD_DIR)/$(backpack_filename).o: $(backpack_cpp)
	$(CCXX) -c -g $(cxxflags) $(backpack_cpp) -o $(BUILD_DIR)/$(backpack_filename).o

# JumpPointBackPack
$(BUILD_DIR)/$(jump_point_backpack_filename): $(BUILD_DIR)/$(jump_point_backpack_filename).o
	$(CCXX) $(cxxflags) $(BUILD_DIR)/$(jump_point_backpack_filename).o -o $(BUILD_DIR)/$(jump_point_backpack_filename)

$(BUILD_DIR)/$(jump_point_backpack_filename).o: $(jump_point_backpack_cpp)
	$(CCXX) -c -g $(cxxflags) $(jump_point_backpack_cpp) -o $(BUILD_DIR)/$(jump_point_backpack_filename).o

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
