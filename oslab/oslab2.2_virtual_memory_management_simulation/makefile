CC := gcc
CFLAGS := -g -std=gnu17 -Wall -Werror -Wextra

BUILDDIR := build/
OBJS := $(BUILDDIR)/vmem.o $(BUILDDIR)/vmem_sim.o

all: mkdir main

main: src/main.c vmem_sim vmem
	$(CC) $(CFLAGS) src/main.c $(OBJS) -o $(BUILDDIR)/main

vmem_sim: src/vmem_sim.c src/vmem_sim.h
	$(CC) $(CFLAGS) -c src/vmem_sim.c -o $(BUILDDIR)/vmem_sim.o

vmem: src/vmem.c src/vmem.h
	$(CC) $(CFLAGS) -c src/vmem.c -o $(BUILDDIR)/vmem.o

mkdir:
	$(shell mkdir -p $(BUILDDIR)) 

clean:
	rm -rf $(BUILDDIR)
