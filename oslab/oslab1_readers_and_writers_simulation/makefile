CC := gcc
CCFLAGS := -std=gnu17 -Wall -Werror -Wextra -lm

LOGDIR := logs/
BUILDDIR := build/
SRCDIR := src/

.PHONY: all clean mkdir

all: mkdir main

main: src/main.c semaphores shared_memory
	$(CC) $(CCFLAGS) src/main.c \
		$(BUILDDIR)/semaphores.o \
		$(BUILDDIR)/shared_memory.o \
		-o $(BUILDDIR)/main

semaphores: src/semaphores.c src/semaphores.h
	$(CC) -c $(CCFLAGS) src/semaphores.c -o $(BUILDDIR)/semaphores.o

shared_memory: src/shared_memory.c src/shared_memory.h
	$(CC) -c $(CCFLAGS) src/shared_memory.c -o $(BUILDDIR)/shared_memory.o

mkdir:
	$(shell mkdir -p $(BUILDDIR))
	$(shell mkdir -p $(LOGDIR))

clean:
	rm -rf $(BUILDDIR)
