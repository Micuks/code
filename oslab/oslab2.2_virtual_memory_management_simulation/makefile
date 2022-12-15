CC := gcc
CFLAGS := -g -std=gnu17 -Wall -Werror -Wextra

AMOUNT := 100000
UPPER_BORDER := 256


BUILDDIR := build/
OBJS := $(BUILDDIR)/vmem.o $(BUILDDIR)/vmem_sim.o

INPUT := config/input.txt

all: mkdir main

test: data_gen
	@echo "Generate $(AMOUNT) virtual addresses to access from $(FROM) to $(TO)."
	$(BUILDDIR)/data_gen $(AMOUNT) $(UPPER_BORDER)
	$(BUILDDIR)/main $(INPUT)

main: src/main.c vmem_sim vmem
	$(CC) $(CFLAGS) src/main.c $(OBJS) -o $(BUILDDIR)/main

vmem_sim: src/vmem_sim.c src/vmem_sim.h
	$(CC) $(CFLAGS) -c src/vmem_sim.c -o $(BUILDDIR)/vmem_sim.o

vmem: src/vmem.c src/vmem.h
	$(CC) $(CFLAGS) -c src/vmem.c -o $(BUILDDIR)/vmem.o

data_gen: src/data_gen.c
	$(CC) $(CFLAGS) src/data_gen.c -o $(BUILDDIR)/data_gen

mkdir:
	$(shell mkdir -p $(BUILDDIR)) 

clean:
	rm -rf $(BUILDDIR)
