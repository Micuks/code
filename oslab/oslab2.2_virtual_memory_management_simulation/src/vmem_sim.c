#include "vmem_sim.h"
#include <stdio.h>
#include <time.h>

// Generating length of time for a function.
clock_t start, end;
double cpu_time_elapsed;
int secondary_storage_call_count = 0;

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

// The buffer containing reads from backing store.
signed char file_read_buf[PAGE_READ_SIZE];

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

            secondary_storage_call_count++;

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
    printf("Frame number[%04d], offset[%04d]\n", frame_number, offset_number);

    if (display_option == YES) {
        // Print the virtual address, physical address and translated value of
        // the signed char.
        printf("Virtual address[%04d]\tPhysical address[%04d]\tValue[%04d]\n",
               virtual_addr, (frame_number << SHIFT) | offset_number,
               translated_value);
    }
}

void read_from_store(int page_number) {
    // Seek to byte PAGE_READ_SIZE in secondary storage.
    // SEEL_SET lets fseek() to seek from the beginning of file.
    if (fseek(secondary_storage, page_number * PAGE_READ_SIZE, SEEK_SET) != 0) {
        fprintf(stderr, "Error seeking in secondary storage.\n");
    }

    // Now read PAGE_READ_SIZE bytes from secondary storage to file_read_buf.
    if (fread(file_read_buf, sizeof(signed char), PAGE_READ_SIZE,
              secondary_storage) == 0) {
        fprintf(stderr, "Error reading secondary storage.\n");
    }

    // Load bytes into the first available fram in the physical memory 2D array.
    for (int i = 0; i < PAGE_READ_SIZE; i++) {
        dram[next_frame][i] = file_read_buf[i];
    }

    // Load the frame number into page table in the next page.
    pageTable->page_num_arr[next_page] = page_number;
    pageTable->frame_num_arr[next_page] = next_frame;

    // Increment counters to track the next available frame.
    next_frame++;
    next_page++;
}

// Circular queue to implement FIFO.
void tlb_fifo_insert(int page_number, int frame_number) {
    int i = 0;
    // Break if page already in TLB.
    for (i = 0; i < next_tlb_entry; i++) {
        if (tlbTable->page_num_arr[i] == page_number) {
            break;
        }
    }

    // Page not found in TLB.
    if (i == next_tlb_entry) {
        tlbTable->page_num_arr[next_tlb_entry % TLB_SIZE] = page_number;
        tlbTable->frame_num_arr[next_tlb_entry % TLB_SIZE] = frame_number;
    } else {
        // If another frame with the same page index already in TLB.
        for (; i < next_tlb_entry; i++) {
            tlbTable->page_num_arr[i] = tlbTable->page_num_arr[i + 1];
            tlbTable->frame_num_arr[i] = tlbTable->frame_num_arr[i + 1];
        }

        // Append page to end of TLB.
        tlbTable->page_num_arr[next_tlb_entry % TLB_SIZE] = page_number;
        tlbTable->frame_num_arr[next_tlb_entry % TLB_SIZE] = frame_number;
    }

    // Next tlb entry in circular queue.
    next_tlb_entry = (next_tlb_entry + 1) % TLB_SIZE;
}

void tlb_lru_insert(int page_number, int frame_number) {
    Boolean free_spot_found = False;
    Boolean already_here = False;
    int replace_index = -1;

    // Find the index to replace and increment age for all other entries.
    for (int i = 0; i < TLB_SIZE; i++) {
        if ((tlbTable->page_num_arr[i] != page_number) &&
            (tlbTable->page_num_arr[i] != 0)) {
            // If entry does not exist in TLB and is not a free spot, increment
            // its age.
            tlbTable->entry_age_arr[i]++;
        } else if ((tlbTable->page_num_arr[i] != page_number) &&
                   (tlbTable->page_num_arr[i] == 0)) {
            // A free entry in TLB.
            if (!free_spot_found) {
                replace_index = i;
                free_spot_found = True;

                // Don't exit for need to increment age for remaining entries.
            }
        } else if (tlbTable->page_num_arr[i] == page_number) {
            // Entry already in TLB, reset its age.
            if (!already_here) {
                tlbTable->entry_age_arr[i] = 0;
                already_here = True;
            } else {
                // Duplicate entry with the same page number.
                fprintf(stderr,
                        "Error: Same page appeared twice in LRU TLB.\nPage "
                        "number[%d]",
                        page_number);
            }
        }
    }

    // Replacement.
    if (already_here) {
        // Already in TLB, do nothing.
        return;
    } else if (free_spot_found) {
        // Free entry available in TLB.
        tlbTable->page_num_arr[replace_index] = page_number;
        tlbTable->frame_num_arr[replace_index] = frame_number;
        tlbTable->entry_age_arr[replace_index] = 0;
    } else {
        // No free entry available in TLB, replace the oldest entry.
        replace_index = get_oldest_entry(TLB_SIZE);
        tlbTable->page_num_arr[replace_index] = page_number;
        tlbTable->frame_num_arr[replace_index] = frame_number;
        tlbTable->entry_age_arr[replace_index] = 0;
    }
}

int get_oldest_entry(int tlb_size) {
    int max = tlbTable->entry_age_arr[0];
    int idx_max = -1;
    for (int i = 0; i < tlb_size; i++) {
        if (tlbTable->entry_age_arr[i] > max) {
            max = tlbTable->entry_age_arr[i];
            idx_max = i;
        }
    }

    if (idx_max == -1) {
        fprintf(stderr, "Error getting oldest entry in TLB to replace.\n");
    }
    return idx_max;
}

double get_avg_time_in_secondary_storage() {
    double tmp = (double)cpu_time_elapsed / secondary_storage_call_count;
    return tmp * 1e6;
}
