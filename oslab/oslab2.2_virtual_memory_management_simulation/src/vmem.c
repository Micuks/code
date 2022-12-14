#include "vmem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Create new virtual memory addressing table.
 */
VMemTable *create_vmem_table(int length) {
    VMemTable *new_table = malloc(sizeof(VMemTable));
    if (new_table == NULL) {
        printf("Error: failed to allocate memory for Virtual Memory Addressing "
               "table.\n");
        exit(-1);
    }
    new_table->length = length;
    new_table->page_num_arr = (int *)malloc(length * sizeof(int));
    new_table->frame_num_arr = (int *)malloc(length * sizeof(int));
    new_table->entry_age_arr = (int *)malloc(length * sizeof(int));
    new_table->page_fault_count = 0;
    new_table->tlb_hit_count = 0;
    new_table->tlb_miss_count = 0;

    if (new_table->page_num_arr == NULL || new_table->frame_num_arr == NULL ||
        new_table->entry_age_arr == NULL) {
        printf("Error: failed to allocate memory for Virtual Memory Addressing "
               "table.\n");
        exit(-1);
    }

    for (int i = 0; i < length; i++) {
        new_table->page_num_arr[i] = 0;
    }

    return new_table;
}

/**
 * Free the memory that virtual memory allocation table occupied.
 */
void free_vmem_table(VMemTable **table) {
    if ((*table)->page_num_arr != NULL) {
        free((*table)->page_num_arr);
    }
    if ((*table)->frame_num_arr != NULL) {
        free((*table)->frame_num_arr);
    }
    if ((*table)->entry_age_arr != NULL) {
        free((*table)->entry_age_arr);
    }
}

/**
 * Print contents of the VMemTable.
 */
void display_table(VMemTable **table) {
    printf("------VIRTUAL MEMORY TABLE BEGIN------");
    for (int i = 0; i < (*table)->length; i++) {
        printf("INDEX[%4d]: PAGE NUMBER[%4d] FRAME NUMBER[%4d]\n", i,
               (*table)->page_num_arr[i], (*table)->frame_num_arr[i]);
    }
    printf("------VIRTUAL MEMORY TABLE END------");
}

/**
 * Accept an int double pointer for creating simulated memory space.
 */
int **dram_allocate(int frame_count, int block_size) {
    int **temp;
    temp = (int **)malloc(frame_count * sizeof(int *));
    if (temp == NULL) {
        fprintf(stderr, "Error: failed to allocated space for DRAM.\n");
        exit(-1);
    }

    for (int i = 0; i < frame_count; i++) {
        temp[i] = (int *)malloc(block_size * sizeof(int));
        for (int j = 0; j < block_size; j++) {
            temp[i][j] = 0;
        }
    }

    return temp;
}

/**
 * Free DRAM memory after use.
 */
void free_DRAM(int ***dbl_ptr_arr, int frame_count) {
    for (int i = 0; i < frame_count; i++) {
        if ((*dbl_ptr_arr)[i] != NULL) {
            free((*dbl_ptr_arr)[i]);
        }
    }

    free(*dbl_ptr_arr);
}

/**
 * 32-bit masking function to extract page number.
 */
int get_page_number(int mask, int value, int shift) {
    return ((value & mask) >> shift);
}

/**
 * 32-bit masking function to extract page offset.
 */
int get_offset(int mask, int value) { return value & mask; }
