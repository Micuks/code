# RUST_BACKTRACE := 1

CC := g++
RUSTC := rustc

kruskal_from := 0
kruskal_to := 1000
amount := 5000

BUILD_DIR := ../build

cli_parser_dir := src/utils
cli_parser_cpp := $(cli_parser_dir)/CLIParser.cpp
cli_parser_rs :=  $(cli_parser_dir)/mod.rs

kruskal_src_dir := src/
kruskal_filename := kruskal
kruskal_rs_filename := kruskalRS
kruskal_cpp := $(kruskal_src_dir)/kruskal.cpp
kruskal_rs_src := $(kruskal_src_dir)/main.rs

kruskal_gen_cpp := src/data_gen/kruskal_data_gen.cpp
kruskal_gen_filename := $(BUILD_DIR)/kruskal_data_gen
kruskal_gen_sample := data/kruskal_yasample.in
kruskal_gen_out := data/kruskal_yasample.out
kruskal_rs_gen_out := data/kruskal_rs_yasample.out

# cxxflags := -Wall -std=c++17 -O3
cxxflags := -Wall -std=c++17 -g
# rustflass := -O
rustflags := -g --edition 2021

.PHONY: all
all: mkdir kruskal

kruskal: $(BUILD_DIR)/kruskal

kruskal_rs: $(BUILD_DIR)/kruskalRS

# kruskal
$(BUILD_DIR)/kruskal: $(BUILD_DIR)/kruskal.o $(BUILD_DIR)/CLIParser.o
	$(CC) $(cxxflags) $(BUILD_DIR)/CLIParser.o $(BUILD_DIR)/kruskal.o -o $(BUILD_DIR)/kruskal

$(BUILD_DIR)/kruskal.o: $(kruskal_cpp)
	$(CC) -c $(cxxflags) $(kruskal_cpp) -o $(BUILD_DIR)/kruskal.o

$(BUILD_DIR)/CLIParser.o: $(cli_parser_cpp)
	$(CC) -c $(cxxflags) $(cli_parser_cpp) -o $(BUILD_DIR)/CLIParser.o

# kruskal Rust
$(BUILD_DIR)/kruskalRS: $(kruskal_rs_src) $(cli_parser_rs)
	$(RUSTC) $(rustflags) -o $(BUILD_DIR)/$(kruskal_rs_filename) $(kruskal_rs_src)

# test
.PHONY: test
test: mkdir kruskal_test
# test: kruskal_default_test

# kruskal Test
default_test: kruskal kruskal_rs
	$(BUILD_DIR)/$(kruskal_filename) --in data/kruskal.in --out data/kruskal.out
	$(BUILD_DIR)/$(kruskal_rs_filename) --in data/kruskal.in --out data/kruskal_rs.out
	diff data/kruskal.out data/kruskal_rs.out

kruskal_test: $(kruskal_gen_filename) kruskal kruskal_rs generate_yasample
	$(BUILD_DIR)/$(kruskal_filename) --in $(kruskal_gen_sample) --out $(kruskal_gen_out)
	$(BUILD_DIR)/$(kruskal_rs_filename) --in $(kruskal_gen_sample) --out $(kruskal_rs_gen_out)
	diff $(kruskal_gen_out) $(kruskal_rs_gen_out)

generate_yasample: data_gen
	echo "[INFO]: Generate $(amount) nodes."
	$(kruskal_gen_filename) $(kruskal_from) $(kruskal_to) $(amount)

# kruskal Data Generator
.PHONY: kruskal_data_gen
data_gen: $(kruskal_gen_filename)

$(kruskal_gen_filename): $(kruskal_gen_cpp)
	$(CC) $(cxxflags) $(kruskal_gen_cpp) -o $(kruskal_gen_filename)

mkdir:
	$(shell mkdir -p $(BUILD_DIR))

clean:
	$(MAKE) -C ../ clean
