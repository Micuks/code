mergesort_cpp := mergesort/mergesort.cpp
mergesort_filename := build/mergesort
report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)
BUILD_DIR := build

cxxflags := -Wall -std=c++11

make_and_test: sort test

sort: $(mergesort_filename)

all:mkdir sort
	# make docs
	$(MAKE) -C docs/ all

$(mergesort_filename): $(mergesort_filename).o
	clang++ $(cxxflags) build/mergesort.o -o build/mergesort

$(mergesort_filename).o: $(mergesort_cpp)
	clang++ $(cxxflags) -c -g $(mergesort_cpp) -o build/mergesort.o

test:
	$(mergesort_filename) samples/mergesort.in

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

clean:
	rm -rf $(BUILD_DIR)/*
	$(MAKE) -C docs/ clean
