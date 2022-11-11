CCXX := clang++
from := -100000000
to := 100000000
amount := 1000000

BUILD_DIR := build

backpack_src_dir := 01bp
backpack_filename := BackPack01
backpack_cpp := ${backpack_src_dir}/$(backpack_filename).cpp

jump_point_backpack_src_dir := 01bp_optimized
jump_point_backpack_filename := JumpPointBackPack
jump_point_backpack_cpp := $(jump_point_backpack_src_dir)/$(jump_point_backpack_filename).cpp

# gen_cpp := data_gen/data_gen.cpp
# gen_filename := build/data_gen
# gen_sample := samples/yet_another_sample.in

# report := docs/report.tex
# content := $(wildcard docs/content/*.tex)
# docs := $(report) $(content)

cxxflags := -Wall -std=c++17 -O3

.PHONY: all
all: mkdir backpack jump_point_backpack

backpack: $(BUILD_DIR)/$(backpack_filename).o $(BUILD_DIR)/$(backpack_filename)

jump_point_backpack: $(BUILD_DIR)/$(jump_point_backpack_filename).o $(BUILD_DIR)/$(jump_point_backpack_filename)

docs: $(docs)
	# make docs
	$(MAKE) -C docs/ all

testg: $(gen_filename) $(stdsort_filename) generate_yasample
	$(mergesort_filename) $(gen_sample)
	$(quicksort_filename) $(gen_sample)
	$(quicksort_kthSmallest_filename) $(gen_sample)
	$(stdsort_filename)
	diff samples/stdsort.out samples/mergesort.out
	diff samples/stdsort.out samples/quicksort.out
	diff samples/stdsort.out samples/quicksort_kthSmallest.out

generate_yasample:
	echo "[INFO]: Generate $(amount) random numbers ranging from $(from) to $(to)."
	$(gen_filename) $(from) $(to) $(amount)

$(gen_filename): $(gen_cpp)
	$(CCXX) $(cxxflags)  $(gen_cpp) -o $(gen_filename)

sort: mkdir $(backpack_filename)

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

# $(MAKE) -C docs/ clean
