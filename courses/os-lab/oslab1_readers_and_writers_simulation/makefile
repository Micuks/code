PEERS := 10
RW_RATIO := 90
SHM_SIZE := 10

CC := gcc
CCFLAGS := -std=gnu17 -Wall -Werror -Wextra -lm

LOGDIR := logs/
BUILDDIR := build/
SRCDIR := src/

.PHONY: all clean mkdir test

all: mkdir reader_priority writer_priority
	@echo "Usage: $(BUILDDIR)[reader_priority | writer_priority] $(PEERS) $(RW_RATIO) $(SHM_SIZE)"
 
reader_priority: src/main_reader_priority.c \
	semaphores \
	shared_memory
	$(CC) $(CCFLAGS) src/main_reader_priority.c \
		$(BUILDDIR)/semaphores.o \
		$(BUILDDIR)/shared_memory.o \
		-o $(BUILDDIR)/reader_priority

writer_priority: src/main_writer_priority.c \
	semaphores \
	shared_memory
	$(CC) $(CCFLAGS) src/main_writer_priority.c \
		$(BUILDDIR)/semaphores.o \
		$(BUILDDIR)/shared_memory.o \
		-o $(BUILDDIR)/writer_priority

test: test_reader_priority test_writer_priority

test_reader_priority:
	$(BUILDDIR)/reader_priority $(PEERS) $(RW_RATIO) $(SHM_SIZE)

test_writer_priority:
	$(BUILDDIR)/writer_priority $(PEERS) $(RW_RATIO) $(SHM_SIZE)

semaphores: src/semaphores.c src/semaphores.h
	$(CC) -c $(CCFLAGS) src/semaphores.c -o $(BUILDDIR)/semaphores.o

shared_memory: src/shared_memory.c src/shared_memory.h
	$(CC) -c $(CCFLAGS) src/shared_memory.c -o $(BUILDDIR)/shared_memory.o

mkdir:
	$(shell mkdir -p $(BUILDDIR))
	$(shell mkdir -p $(LOGDIR))

clean:
	rm -rf $(BUILDDIR)
