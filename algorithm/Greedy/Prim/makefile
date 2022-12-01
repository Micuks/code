# RUST_BACKTRACE := 1

CC := g++
RUSTC := rustc

# Debug flag
CXX_DBGFLAGS = -O0 -g -DDEBUG
RUST_DBGFLAGS = -g --features debug

prim_from := 0
prim_to := 1000
amount := 5000

BUILD_DIR := ../build

cli_parser_dir := src/utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp
cli_parser_rs :=  $(cli_parser_dir)/mod.rs

prim_src_dir := src/
prim_filename := prim
prim_rs_filename := primRS
prim_cpp := $(prim_src_dir)/prim.cpp
prim_rs_src := $(prim_src_dir)/main.rs

prim_gen_cpp := src/data_gen/prim_data_gen.cpp
prim_gen_filename := $(BUILD_DIR)/prim_data_gen
prim_gen_sample := data/prim_yasample.in
prim_gen_out := data/prim_yasample.out
prim_rs_gen_out := data/prim_rs_yasample.out

cxxflags := -Wall -std=c++17 -O3
rustflags := -O --edition 2021

###################
# Debug flag zone #
###################

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	cxxflags := -Wall -Werror -Wextra -std=c++17 -O0 -DDEBUG
	rustflags := -g --edition 2021 --cfg 'feature="debug"'
else
	cxxflags := -Wall -std=c++17 -O3 -DNDEBUG
	rustflags := -O --edition 2021 --cfg 'feature=""'
endif

# Default, release mode.
.PHONY: all
all: mkdir prim prim_rs
	$(BUILD_DIR)/$(prim_filename) --in $(prim_gen_sample) --out $(prim_gen_out)
	echo "-------------------------------------------------------------------"
	$(BUILD_DIR)/$(prim_rs_filename) --in $(prim_gen_sample) --out $(prim_rs_gen_out)

.PHONY: prim
prim: $(BUILD_DIR)/prim

.PHONY: prim_rs
prim_rs: $(BUILD_DIR)/primRS

# prim
$(BUILD_DIR)/prim: $(BUILD_DIR)/prim.o $(BUILD_DIR)/CLIParser.o
	$(CC) $(cxxflags) $(BUILD_DIR)/CLIParser.o $(BUILD_DIR)/prim.o -o $(BUILD_DIR)/prim

$(BUILD_DIR)/prim.o: $(prim_cpp)
	$(CC) -c $(cxxflags) $(prim_cpp) -o $(BUILD_DIR)/prim.o

$(BUILD_DIR)/CLIParser.o: $(cli_parser_cpp)
	$(CC) -c $(cxxflags) $(cli_parser_cpp) -o $(BUILD_DIR)/CLIParser.o

# prim Rust
$(BUILD_DIR)/primRS: $(prim_rs_src) $(cli_parser_rs)
	$(RUSTC) $(rustflags) -o $(BUILD_DIR)/$(prim_rs_filename) $(prim_rs_src)

# test
.PHONY: test
test: mkdir prim_test
# test: prim_default_test

# prim Test
default_test: prim prim_rs
	$(BUILD_DIR)/$(prim_filename) --in data/prim.in --out data/prim.out
	$(BUILD_DIR)/$(prim_rs_filename) --in data/prim.in --out data/prim_rs.out
	diff data/prim.out data/prim_rs.out

prim_test: $(prim_gen_filename) prim prim_rs generate_yasample
	$(BUILD_DIR)/$(prim_filename) --in $(prim_gen_sample) --out $(prim_gen_out)
	$(BUILD_DIR)/$(prim_rs_filename) --in $(prim_gen_sample) --out $(prim_rs_gen_out)
	diff $(prim_gen_out) $(prim_rs_gen_out)

generate_yasample: data_gen
	echo "[INFO]: Generate $(amount) nodes."
	$(prim_gen_filename) $(prim_from) $(prim_to) $(amount)

# prim Data Generator
.PHONY: prim_data_gen
data_gen: $(prim_gen_filename)

$(prim_gen_filename): $(prim_gen_cpp)
	$(CC) $(cxxflags) $(prim_gen_cpp) -o $(prim_gen_filename)

.PHONY: mkdir
mkdir:
	$(shell mkdir -p $(BUILD_DIR))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/prim*
