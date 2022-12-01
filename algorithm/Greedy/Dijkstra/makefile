# RUST_BACKTRACE := 1

CC := g++
RUSTC := rustc

dijkstra_from := 0
dijkstra_to := 1000
amount := 5000

BUILD_DIR := ../build

cli_parser_dir := src/utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp
cli_parser_rs := $(cli_parser_dir)/mod.rs

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

###################
# Debug flag zone #
###################

# DEBUG flag default to be 0
DEBUG ?= 0
ifeq ($(DEBUG),1)
	cxxflags := -Wall -Werror -Wextra -std=c++17 -O0 -DDEBUG
	rustflags := -g --edition 2021 --cfg 'feature="debug"'
else
	cxxflags := -Wall -std=c++17 -O3 -DNDEBUG
	rustflags := -O --edition 2021 --cfg 'feature=""'
endif

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
test: clean mkdir dijkstra_test

# dijkstra Test
default_test: clean dijkstra dijkstra_rs
	$(BUILD_DIR)/$(dijkstra_filename) --in data/dijkstra.in --out data/dijkstra.out
	@echo "--------------------END OF C++ OUTPUT-----------------------"
	@echo "------------------------------------------------------------"
	@echo "-------------------BEGIN OF RUST OUTPUT---------------------"
	$(BUILD_DIR)/$(dijkstra_rs_filename) --in data/dijkstra.in --out data/dijkstra_rs.out
	@echo "--------------------END OF RUST OUTPUT----------------------"
	diff data/dijkstra.out data/dijkstra_rs.out

# Rerun previous test. Require an existing $(kruskal_gen_sample).
.PHONY: last_test
last_test: clean mkdir kruskal kruskal_rs $(kruskal_gen_sample)
	$(BUILD_DIR)/$(kruskal_filename) --in $(kruskal_gen_sample) --out $(kruskal_gen_out)
	@echo "--------------------END OF C++ OUTPUT-----------------------"
	@echo "------------------------------------------------------------"
	@echo "-------------------BEGIN OF RUST OUTPUT---------------------"
	$(BUILD_DIR)/$(kruskal_rs_filename) --in $(kruskal_gen_sample) --out $(kruskal_rs_gen_out)
	@echo "--------------------END OF RUST OUTPUT----------------------"
	diff $(kruskal_gen_out) $(kruskal_rs_gen_out)

dijkstra_test: $(dijkstra_gen_filename) dijkstra dijkstra_rs generate_yasample
	$(BUILD_DIR)/$(dijkstra_filename) --in $(dijkstra_gen_sample) --out $(dijkstra_gen_out)
	@echo "--------------------END OF C++ OUTPUT-----------------------"
	@echo "------------------------------------------------------------"
	@echo "-------------------BEGIN OF RUST OUTPUT---------------------"
	$(BUILD_DIR)/$(dijkstra_rs_filename) --in $(dijkstra_gen_sample) --out $(dijkstra_rs_gen_out)
	@echo "--------------------END OF RUST OUTPUT----------------------"
	diff $(dijkstra_gen_out) $(dijkstra_rs_gen_out)

generate_yasample: data_gen
	@echo "[INFO]: Generate $(amount) nodes."
	$(dijkstra_gen_filename) $(dijkstra_from) $(dijkstra_to) $(amount)

# dijkstra Data Generator
.PHONY: dijkstra_data_gen
data_gen: $(dijkstra_gen_filename)

$(dijkstra_gen_filename): $(dijkstra_gen_cpp)
	$(CC) $(cxxflags) $(dijkstra_gen_cpp) -o $(dijkstra_gen_filename)

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

clean:
	rm -rf $(BUILD_DIR)/dijkstra*
