#ifndef VMEM_H
#define VMEM_H

/**
 * Define a virtual memory addressing table that can be represented as either a
 * tlb cache or a page table.
 */
typedef struct VMemTable {
    // Page number array.
    int *page_num_arr;
    // Frame number array.
    int *frame_num_arr;
    // Age of each index.
    int *entry_age_arr;
    int length;
    int page_fault_count;
    int tlb_hit_count;
    int tlb_miss_count;
} VMemTable;

/**
 * Create a new Virtual Memory Table for Logical Address Referencing.
 * Can represent TLB or Page Table Cache.
 */
VMemTable *create_vmem_table(int length);

/**
 * Print contents of the VMemTable.
 */
void display_table(VMemTable **table);

/**
 * Free memory that allocated on heap.
 */
void free_vmem_table(VMemTable **table);

/**
 * Accept an int double pointer for creating simulated memory space.
 */
int **dram_allocate(int frame_count, int block_size);

/**
 * Free DRAM memory after use.
 */
void free_DRAM(int ***dbl_pptr_arr, int frame_count);

/**
 * 32-bit masking function to extract page number.
 */
int get_page_number(int mask, int value, int shift);

/**
 * 32-bit masking function to extract page offset.
 */
int get_offset(int mask, int value);

#endif // !VMEM_H
