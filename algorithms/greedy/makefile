# RUST_BACKTRACE := 0

CC := g++
RUSTC := rustc

huffman_from := 0
huffman_to := 1000

from := 0
to := 1000
amount := 5000

BUILD_DIR := build

report := docs/report.tex
content := $(wildcard docs/content/*.tex)
docs := $(report) $(content)

# cxxflags := -Wall -std=c++17 -O3
cxxflags := -Wall -std=c++17 -g
# rustflass := -O
rustflags := -g --edition 2021

.PHONY: all
all: mkdir huffman dijkstra prim kruskal

.PHONY: huffman dijkstra prim kruskal
huffman: Huffman/*
	$(MAKE) -C Huffman/ all

dijkstra: Dijkstra/*
	$(MAKE) -C Dijkstra/ all

prim: Prim/*
	$(MAKE) -C Prim/ all

kruskal: kruskal/*
	$(MAKE) -C Kruskal/ all

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
