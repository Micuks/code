#ifndef VMEM_H
#define VMEM_H

/**
 * Dual direction linked list.
 */
typedef struct LLNode {
    int page_index;
    int frame_index;
    int age;
    struct LLNode *prev;
    struct LLNode *next;
} EntryNode;

/**
 * Allocate new linked list node.
 */
void *new_node();

void free_list(struct LLNode *list);

void insert_node(struct LLNode *curr_node, struct LLNode *new_node);

void delete_next_node(struct LLNode *node);

/**
 * Get length of linked list.
 */
int list_len(struct LLNode *node);

/**
 * Define a virtual memory addressing table that can be represented as either a
 * tlb cache or a page table.
 */
typedef struct VMemTable {
    // Entry list WITH HEAD NODE.
    EntryNode *entryList;
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
