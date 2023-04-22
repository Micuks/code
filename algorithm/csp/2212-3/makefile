CC := g++
cxxflags := -std=c++14 -Wall

.PHONY: all test clean

all: datagen t158 sample
	./t158 < in > out
	./sample < in > sample_out
	diff sample_out out

dategen: datagen.cpp
	@echo Compilling $@...
	$(CC) $(cxxflags) $< -o $@

t158: t158.cpp
	@echo Compilling $@...
	$(CC) $(cxxflags) $< -o $@ -g

sample: sample.cpp
	@echo Compilling $@...
	$(CC) $(cxxflags) $< -o $@ 

test: datagen t158 sample
	@echo testing...
	./datagen
	./t158 < in > out
	./sample < in > sample_out
	diff sample_out out

clean:
	rm t158 datagen sample
