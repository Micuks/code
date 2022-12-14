#ifndef VMEM_SIM_H
#define VMEM_SIM_H

#include "vmem.h"
#include <stdio.h>
#include <time.h>
#define FRAME_SIZE 256        // Size of each frame
#define TOTAL_FRAME_COUNT 256 // Total number of frames in physical memory
#define PAGE_MASK 0xFF00      // Mask to get page number
#define OFFSET_MASK 0xFF      // Mask to get offset
#define SHIFT 8               // Bitmask shift amount
#define TLB_SIZE 16           // size of TLB
#define PAGE_TABLE_SIZE 256   // size of page table
#define MAX_ADDR_LEN                                                           \
    10 // The number of characters to read for each line from
       // input file
#define PAGE_READ_SIZE 256 // Number of bytes to read

typedef enum { FIFO = '1', LRU = '2' } ReplacementMethod;
typedef enum { YES = 'y', NO = 'n' } DisplayOption;

typedef enum { True = 0, False = 1 } Boolean;

extern VMemTable *tlbTable;
extern VMemTable *pageTable;
extern int **dram;

extern ReplacementMethod replace_method;
extern DisplayOption display_option;

extern FILE *address_file;
extern char secondary_storage_name[];
extern FILE *secondary_storage;

extern int virtual_addr;
extern int page_number;
extern int offset_number;

extern int translation_count;

extern char *algo_name;

/**
 * Translate virtual memory address into physical memory address, retrieve the
 * translated value stored.
 *
 * Parameters:
 * - replace_method: Replacement method used for TLB replacement.
 *   1 is FIFO, and 2 is LRU.
 */
void translate_address();

void read_from_store(int page_number);

void tlb_fifo_insert(int page_number, int frame_number);

void tlb_lru_insert(int page_number, int frame_number);

int get_oldest_entry(int tlb_size);

double get_avg_time_in_secondary_storage();

#endif // !VMEM_SIM_H
