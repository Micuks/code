#include "vmem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Linked list implementation
 */

void *new_node() {
    struct LLNode *node = malloc(sizeof(struct LLNode));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate new linked list node.\n");
        exit(-1);
    }
    node->next = NULL;
    node->prev = NULL;
    node->page_index = 0;
    node->frame_index = 0;
    node->age = 0;

    return node;
}

/**
 * Delete given node's next node.
 */
void delete_next_node(struct LLNode *node) {
    struct LLNode *next_node = node->next;
    // Return if node has no next node.
    if (!next_node) {
        return;
    }

    // Next node is the last node.
    if (!(next_node->next)) {
        free(next_node);
        node->next = NULL;
    } else {
        // Next node is not the last node.
        struct LLNode *new_next_node = next_node->next;
        free(next_node);
        node->next = new_next_node;
        new_next_node->prev = node;
    }
}

void free_list(struct LLNode *list) {
    struct LLNode *node = list;
    struct LLNode *next_node = NULL;
    if (node->next) {
        next_node = node->next;
    }
    while (!node) {
        free(node);

        node = next_node;

        // Next node will be NULL when come to the last node.
        next_node = node->next;
    }
}

/**
 * Insert new_node after curr_node. If curr_node is linked to next node, insert
 * new_node between two nodes.
 */
void insert_node(struct LLNode *curr_node, struct LLNode *new_node) {
    if (curr_node->next != NULL) {
        // Has hext node.
        struct LLNode *next_node = curr_node->next;
        new_node->prev = curr_node;
        new_node->next = next_node;

        curr_node->next = new_node;
        next_node->prev = new_node;
    } else {
        // No next node.
        curr_node->next = new_node;
        new_node->prev = curr_node;
    }
}

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
    // Allocate head node.
    new_table->entryList = new_node();
    // Allocate the rest length nodes.
    struct LLNode *curr_node = new_table->entryList;
    for (int i = 0; i < length; i++) {
        EntryNode *node = new_node();
        insert_node(curr_node, node);
        curr_node = curr_node->next;
    }

    new_table->page_fault_count = 0;
    new_table->tlb_hit_count = 0;
    new_table->tlb_miss_count = 0;

    return new_table;
}

/**
 * Free the memory that virtual memory allocation table occupied.
 */
void free_vmem_table(VMemTable **table) {
    free_list((*table)->entryList);

    free(*table);
}

/**
 * Print contents of the VMemTable.
 */
void display_table(VMemTable **table) {
    EntryNode *entryNode = (*table)->entryList;
    printf("------VIRTUAL MEMORY TABLE BEGIN------");
    for (int i = 0; i < (*table)->length; i++) {
        entryNode = entryNode->next;
        if (!entryNode) {
            break;
        }

        printf("INDEX[%4d]: PAGE NUMBER[%4d] FRAME NUMBER[%4d]\n", i,
               entryNode->page_index, entryNode->frame_index);
        entryNode = entryNode->next;
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
