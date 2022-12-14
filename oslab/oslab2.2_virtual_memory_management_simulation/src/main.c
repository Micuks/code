#include "vmem.h"
#include "vmem_sim.h"
#include <stdio.h>
#include <stdlib.h>

extern VMemTable *tlbTable;
extern VMemTable *pageTable;
extern int **dram;

extern ReplacementMethod replace_method;
extern DisplayOption display_option;

extern FILE *address_file;
extern char *secondary_storage_name;
extern FILE *secondary_storage;

extern int virtual_addr;
extern int page_number;
extern int offset_number;

extern int translation_count;

extern char *algo_name;

char address_read_buf[MAX_ADDR_LEN];

// The buffer containing reads from backing store.
signed char file_read_buf[PAGE_READ_SIZE];

int main(int argc, char *argv[]) {

    /**
     * vmemTable is a generic struct defined to implement any number of caches
     * for logical address translation.
     */
    tlbTable = create_vmem_table(TLB_SIZE);
    pageTable = create_vmem_table(PAGE_TABLE_SIZE);
    dram = dram_allocate(TOTAL_FRAME_COUNT, FRAME_SIZE);

    if (argc != 2) {
        fprintf(stderr, "Usage: build/main <input file>\n");
        return -1;
    }

    // Open secondary storage file.
    secondary_storage = fopen(secondary_storage_name, "rb");
    if (secondary_storage == NULL) {
        fprintf(stderr, "Error opening %s\n", secondary_storage_name);
        return -1;
    }

    // Open the file containing logical addresses.
    address_file = fopen(argv[1], "r");

    if (address_file == NULL) {
        fprintf(stderr,
                "Error opening %s. Expecting input file containing logical "
                "addresses.\n",
                argv[1]);

        return -1;
    }

    printf("\nVIRTUAL MEMORY SIMULATION\n");
    printf("\nLogical pages: %d\n", PAGE_TABLE_SIZE);
    printf("Page size: %d bytes.\n", PAGE_READ_SIZE);
    printf("Page table size: %d\n", PAGE_TABLE_SIZE);
    printf("TLB size: %d entries.\n", TLB_SIZE);
    printf("Frame size: %d bytes.\n", FRAME_SIZE);
    printf("Physical frames: %d\n", TOTAL_FRAME_COUNT);
    printf("Physical memory size: %d\n", PAGE_READ_SIZE * FRAME_SIZE);

    do {
        printf("\nDisplay all physical addresses? [y/n]: ");
        scanf("%u", &display_option);
    } while (display_option != 'n' && display_option != 'y');

    do {
        printf("Chose TLB replacement method: \n");
        printf("1: FIFO\n");
        printf("2: LRU\n");
        scanf("%u", &replace_method);
    } while (replace_method != '1' && replace_method != '2');

    // Read through the input file and print virtual addresses.
    while (fgets(address_read_buf, MAX_ADDR_LEN, address_file) != NULL) {
        virtual_addr = atoi(address_read_buf);

        // Get page number.
        page_number = get_page_number(PAGE_MASK, virtual_addr, SHIFT);

        // Get offset.
        offset_number = get_offset(OFFSET_MASK, virtual_addr);

        // Get physical address and translated value stored at that address.
        translate_address(replace_method);
        translation_count++;
    }

    // Set stdout replacement method name.
    algo_name = (replace_method == FIFO) ? "FIFO" : "LRU";

    printf("\n------VIRTUAL MEMORY STATISTICS------\n");
    printf("\nReplacement method: %s", algo_name);
    printf("Number of addresses translated: %d\n", translation_count);
    double pf_rate = (double)pageTable->page_fault_count / translation_count;
    double tlb_rate = (double)tlbTable->tlb_hit_count / translation_count;

    printf("Page faults: %d\n", pageTable->page_fault_count);
    printf("Page fault rate: %.3f%%\n", pf_rate * 100);
    printf("TLB hits: %d\n", tlbTable->tlb_hit_count);
    printf("TLB hit rate: %.3f%%\n", tlb_rate * 100);
    printf("Average thme retrieving data from secondary storage: %.3f ms\n",
           get_avg_time_in_secondary_storage());

    // Close input file and secondary storage file.
    fclose(address_file);
    fclose(secondary_storage);

    // Free memory allocated on heap.
    free_vmem_table(&tlbTable);
    free_vmem_table(&pageTable);
    free_DRAM(&dram, TOTAL_FRAME_COUNT);

    return 0;
}
