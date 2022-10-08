CCXX := clang++
from := -1000
to := 1000
amount := 50

mergesort_cpp := mergesort/mergesort.cpp
mergesort_filename := build/mergesort

stdsort_cpp := data_gen/stdsort.cpp
stdsort_filename := build/stdsort

gen_cpp := data_gen/data_gen.cpp
gen_filename := build/data_gen
gen_sample := samples/yet_another_sample.in

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

BUILD_DIR := build

cxxflags := -Wall -std=c++11

all:mkdir make_and_test

docs: $(docs)
	# make docs
	$(MAKE) -C docs/ all

make_and_test: sort testg_all

test:
	$(mergesort_filename) samples/mergesort.in

testg_all: $(gen_filename) $(stdsort_filename) generate_yasample
	$(mergesort_filename) $(gen_sample)
	$(stdsort_filename)
	diff $(gen_sample) samples/mergesort.out

testg: $(gen_filename) generate_yasample
	$(mergesort_filename) $(gen_sample)

testg_ascend: $(stdsort_filename) $(gen_filename) generate_yasample
	$(stdsort_filename) ascend
	$(mergesort_filename) $(gen_sample)

testg_descend: $(stdsort_filename) $(gen_filename) generate_yasample
	$(stdsort_filename) descend
	$(mergesort_filename) $(gen_sample)

generate_yasample:
	echo "generage $(amount) random numbers from $(from) to $(to)."
	$(gen_filename) $(from) $(to) $(amount)

$(gen_filename): $(gen_cpp)
	$(CCXX) $(cxxflags)  $(gen_cpp) -o $(gen_filename)

$(stdsort_filename): $(stdsort_cpp)
	$(CCXX) $(cxxflags) $(stdsort_cpp) -o $(stdsort_filename)

sort: $(mergesort_filename)

$(mergesort_filename): $(mergesort_filename).o
	$(CCXX) $(cxxflags) $(mergesort_filename).o -o $(mergesort_filename)

$(mergesort_filename).o: $(mergesort_cpp)
	$(CCXX) $(cxxflags) -c -g $(mergesort_cpp) -o $(mergesort_filename).o

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
