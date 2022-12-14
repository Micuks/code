#ifndef VMEM_SIM_H
#define VMEM_SIM_H

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

typedef enum { false = 0, true = !false } bool;

// Function definitions.
void translate_address(char replace_method);
void read_from_store(int page_number);
void tlb_fifo_insert(int page_number, int frame_number);
void tlb_lru_insert(int page_number, int frame_number);
int get_oldest_entry(int tlb_size);
double get_avg_time_in_secondary_storage();

#endif // !VMEM_SIM_H
