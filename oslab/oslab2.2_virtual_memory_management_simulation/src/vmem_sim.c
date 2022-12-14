#include "vmem_sim.h"
#include <time.h>

// Generating length of time for a function.
clock_t start, end;
double cpu_time_elapsed;
int function_call_count = 0;

int **dram; // Physical memory.

int next_tlb_entry = 0; // Next available index of TLB entry.
int next_page = 0;      // Next available page in page table.
int next_frame = 0;     // Next available frame TLB or page table.

ReplacementMethod replace_method; // Menu stdin.
DisplayOption display_option;     // Menu stdin.
                                  //

// Input file and backup.
FILE *address_file;
char secondary_storage_name[] = "config/secondary_storage.bin";
FILE *secondary_storage;

// Store data read from input file.
int virtual_addr;
int page_number;
int offset_number;

// The translated value of the byte(signed char) in memory.
signed char translated_value;

VMemTable *tlbTable;  // The TLB struct.
VMemTable *pageTable; // The Page Table.
int translation_count = 0;
char *algo_name;

void translate_address() {
    // Try to find page in TLB.
    int frame_number = -1;

    for (int i = 0; i < tlbTable->length; i++) {
        if (tlbTable->page_num_arr[i] == page_number) {
            frame_number = tlbTable->frame_num_arr[i];
            tlbTable->tlb_hit_count++;
            break;
        }
    }

    // If page is not hit in TLB, find page in page table, and increment tlb
    // miss count.
    // If page is not found in page table, find it in secondary storage DRAM,
    // and increment page table fault count.
    if (frame_number == -1) {
        tlbTable->tlb_hit_count++;

        // Iterative through page table to find the demanding page.
        for (int i = 0; i < next_page; i++) {
            if (pageTable->page_num_arr[i] == page_number) {
                // Page found, retrieve corresponding frame number.
                frame_number = pageTable->frame_num_arr[i];
                break;
            }
        }

        // Page table fault.
        if (frame_number == -1) {
            // Increment the number of page faults.
            pageTable->page_fault_count++;

            // Read from secondary storage, and count time elapsed.
            int start = clock();
            read_from_store(page_number);
            cpu_time_elapsed += (double)(clock() - start) / CLOCKS_PER_SEC;

            function_call_count++;

            // Set the frame_number to current next_frame index.
            frame_number = next_page - 1;
        }
    }

    // Page replacement.
    if (replace_method == FIFO) {
        // FIFO replacement method to insert the page number and frame number
        // into TLB.
        tlb_fifo_insert(page_number, frame_number);
    } else {
        tlb_lru_insert(page_number, frame_number);
    }

    // Get translated value with frame_number and offset_number.
    translated_value = dram[frame_number][offset_number];

    // Debug.
    printf("\n Frame number[%d], offset[%d]\n", frame_number, offset_number);

    if (display_option == YES) {
        // Print the virtual address, physical address and translated value of
        // the signed char.
        printf("\nVirtual address[%d]\tPhysical address[%d]\tValue[%d]",
               virtual_addr, (frame_number << SHIFT) | offset_number,
               translated_value);
    }
}

void read_from_store(int page_number) {}
void tlb_fifo_insert(int page_number, int frame_number);
void tlb_lru_insert(int page_number, int frame_number);
int get_oldest_entry(int tlb_size);
double get_avg_time_in_secondary_storage();
