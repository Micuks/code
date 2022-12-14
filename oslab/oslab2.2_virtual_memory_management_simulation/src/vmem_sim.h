#include <stdio.h>
#include <time.h>
#define FRAME_SIZE 256 // Size of each frame
#define TOTAL_FRAME_COUNT 256
#define PAGE_MASK 0xFF00
#define OFFSET_MASK 0xFF
#define SHIFT 8
#define TLB_SIZE 16
#define PAGE_TABLE_SIZE 256
#define MAX_ADDR_LEN 10
#define PAGE_READ_SIZE 256

typedef enum { false = 0, true = !false } bool;

/**
 * vmemTable is a generic struct defined to implement any number of caches for
 * logical address translation.
 */
vmemTable_t *tlbTable;  // The TLB struct.
vmemTable_t *pageTable; // The Page Table.
int **dram;             // Physical memory.

char algo_choice;    // Menu stdin.
char display_choice; // Menu stdin.

int next_tlb_entry = 0; // Next available index of TLB entry.
int next_page = 0;      // Next available page in page table.
int next_frame = 0;     // Next available frame TLB or page table.

// Input file and backup.
FILE *address_file;
FILE *backing_store;

// Store data read from input file.
char address_read_buf[MAX_ADDR_LEN];
int virtual_addr;
int page_number;
int offset_number;

// Generating length of time for a function.
clock_t start, end;
double cpu_time_used;
int function_call_count = 0;

// The buffer containing reads from backing store.
signed char file_read_buf[PAGE_READ_SIZE];

// The translated value of the byte(signed char) in memory.
signed char translated_value;

// Function definitions.
void translate_address();
void read_from_store(int page_number);
void tlb_fifo_insert(int page_number, int frame_number);
void tlb_lru_insert(int page_number, int frame_number);
int get_oldest_entry(int tlb_size);
double get_avg_time_in_backup();
