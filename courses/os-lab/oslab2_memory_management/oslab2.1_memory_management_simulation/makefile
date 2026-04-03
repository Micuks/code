CC := gcc
CCFLAGS := -O3 -std=gnu17 -Wall -Wextra -Werror

BUILDDIR := build/

FROM := 0
TO := 1000
NUM_BLOCKS := 1000
NUM_PROCESSES := 1000

.PHONY: all, test, mkdir, clean
all: mkdir main

test: main data_gen
	$(BUILDDIR)/data_gen $(FROM) $(TO) $(NUM_BLOCKS) $(NUM_PROCESSES)
	@echo "Generated $(NUM_BLOCKS) memory blocks and" \
		"$(NUM_PROCESSES) processes. Size from $(FROM) to $(TO)."
	$(BUILDDIR)/main

main: src/main.c schemas util
	$(CC) $(CCFLAGS) src/main.c \
		$(BUILDDIR)/schemas.o \
		$(BUILDDIR)/util.o \
		-o $(BUILDDIR)/main

schemas: src/schemas.c src/schemas.h util
	$(CC) $(CCFLAGS) -c src/schemas.c -o $(BUILDDIR)/schemas.o

util: src/util.c src/util.h
	$(CC) $(CCFLAGS) -c src/util.c -o $(BUILDDIR)/util.o

data_gen: src/data_gen.c
	$(CC) $(CCFLAGS) src/data_gen.c -o $(BUILDDIR)/data_gen

mkdir:
	$(shell mkdir -p $(BUILDDIR))

clean:
	rm -rf $(BUILDDIR)
