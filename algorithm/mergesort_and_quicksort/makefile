CCXX := clang++
from := -1000
to := 1000
amount := 50

mergesort_cpp := mergesort/mergesort.cpp
mergesort_filename := build/mergesort

quicksort_cpp := quicksort/quicksort.cpp
quicksort_filename := build/quicksort

quicksort_kthSmallest_cpp := quicksort/quicksort_kthSmallest.cpp
quicksort_kthSmallest_filename := build/quicksort_kthSmallest

stdsort_cpp := data_gen/stdsort.cpp
stdsort_filename := build/stdsort

gen_cpp := data_gen/data_gen.cpp
gen_filename := build/data_gen
gen_sample := samples/yet_another_sample.in

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

BUILD_DIR := build

cxxflags := -Wall -std=c++11 -O3

all:mkdir make_and_test

docs: $(docs)
	# make docs
	$(MAKE) -C docs/ all

make_and_test: sort testg_all

test:
	$(mergesort_filename) samples/mergesort.in
	$(quicksort_filename) samples/quicksort.in
	$(quicksort_kthSmallest_filename) samples/quicksort.in
	$(stdsort_filename) samples/quicksort.in
	diff samples/stssort.out samples/mergesort.out
	diff samples/stssort.out samples/quicksort.out
	diff samples/stssort.out samples/quicksort_kthSmallest.out

testg_all: $(gen_filename) $(stdsort_filename) generate_yasample
	$(mergesort_filename) $(gen_sample)
	$(quicksort_filename) $(gen_sample)
	$(quicksort_kthSmallest_filename) $(gen_sample)
	$(stdsort_filename)
	diff samples/stdsort.out samples/mergesort.out
	diff samples/stdsort.out samples/quicksort.out
	diff samples/stdsort.out samples/quicksort_kthSmallest.out

testg: $(gen_filename) generate_yasample
	$(mergesort_filename) $(gen_sample)
	$(quicksort_filename) $(gen_sample)
	$(quicksort_kthSmallest_filename) $(gen_sample)

testg_ascend: $(stdsort_filename) $(gen_filename) generate_yasample
	$(stdsort_filename) ascend
	cp samples/stdsort.out $(gen_sample)
	$(mergesort_filename) $(gen_sample)
	$(quicksort_filename) $(gen_sample)
	$(quicksort_kthSmallest_filename) $(gen_sample)

testg_descend: $(stdsort_filename) $(gen_filename) generate_yasample
	$(stdsort_filename) descend
	cp samples/stdsort.out $(gen_sample)
	$(mergesort_filename) $(gen_sample)
	$(quicksort_filename) $(gen_sample)
	$(quicksort_kthSmallest_filename) $(gen_sample)

generate_yasample:
	echo "[INFO]: generage $(amount) random numbers from $(from) to $(to)."
	$(gen_filename) $(from) $(to) $(amount)

$(gen_filename): $(gen_cpp)
	$(CCXX) $(cxxflags)  $(gen_cpp) -o $(gen_filename)

$(stdsort_filename): $(stdsort_cpp)
	$(CCXX) $(cxxflags) $(stdsort_cpp) -o $(stdsort_filename)

sort: $(mergesort_filename) $(quicksort_filename) $(quicksort_kthSmallest_filename)

$(quicksort_kthSmallest_filename): $(quicksort_kthSmallest_filename).o
	$(CCXX) $(cxxflags) $(quicksort_kthSmallest_filename).o -o $(quicksort_kthSmallest_filename)

$(quicksort_kthSmallest_filename).o: $(quicksort_kthSmallest_cpp)
	$(CCXX) $(cxxflags) -c -g $(quicksort_kthSmallest_cpp) -o $(quicksort_kthSmallest_filename).o

$(quicksort_filename): $(quicksort_filename).o
	$(CCXX) $(cxxflags) $(quicksort_filename).o -o $(quicksort_filename)

$(quicksort_filename).o: $(quicksort_cpp)
	$(CCXX) $(cxxflags) -c -g $(quicksort_cpp) -o $(quicksort_filename).o

$(mergesort_filename): $(mergesort_filename).o
	$(CCXX) $(cxxflags) $(mergesort_filename).o -o $(mergesort_filename)

$(mergesort_filename).o: $(mergesort_cpp)
	$(CCXX) $(cxxflags) -c -g $(mergesort_cpp) -o $(mergesort_filename).o

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
