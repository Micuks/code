#include "vmem_sim.h"
#include "vmem.h"
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

// The translated value of the byte(signed char) in memory.
signed char translated_value;

VMemTable *tlbTable;  // The TLB struct.
VMemTable *pageTable; // The Page Table.
int translation_count = 0;
char *algo_name;

// The buffer containing reads from backing store.
signed char file_read_buf[PAGE_READ_SIZE];

void translate_address(int virtual_addr, int page_number, int offset_number) {
    // Try to find page in TLB.
    int frame_number = -1;

    EntryNode *entry_node = tlbTable->entryList;
    while (entry_node->next) {
        entry_node = entry_node->next;

        if (entry_node->page_index == page_number) {
            frame_number = entry_node->frame_index;
            tlbTable->tlb_hit_count++;
            break;
        }
    }

    // If page is not hit in TLB, find page in page table, and increment TLB
    // miss count.
    // If page is not found in page table, find it in secondary storage DRAM,
    // and increment page table fault count.
    if (frame_number == -1) {
        tlbTable->tlb_miss_count++;

        // Iterative through page table to find the demanding page.
        entry_node = pageTable->entryList;
        while (entry_node->next) {
            entry_node = entry_node->next;
            if (entry_node->page_index == page_number) {
                frame_number = entry_node->frame_index;
                break;
            }

            entry_node = entry_node->next;
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
            frame_number = next_frame - 1;
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
    printf("\nFrame Number[0x%04x]\tOffset[0x%04x]\n", frame_number,
           offset_number);

    if (display_option == YES) {
        // Print the virtual address, physical address and translated value of
        // the signed char.
        printf(
            "Virtual address[0x%04x]\tPhysical address[0x%04x]\tValue[%04d]\n",
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
    EntryNode *entry_node = pageTable->entryList;
    // NOTE: Maybe wrong: exceed by 1 node.
    entry_node = entry_node->next;
    for (int i = 0; i < next_page; i++) {
        entry_node = entry_node->next;
    }

    entry_node->page_index = page_number;
    entry_node->frame_index = next_frame;

    // Increment counters to track the next available frame.
    next_frame++;
    next_page++;
}

// TLB fifo insert method.
void tlb_fifo_insert(int page_number, int frame_number) {
    int i = 0;
    EntryNode *entry_node = tlbTable->entryList;
    // Break if page already in TLB.
    for (i = 0; i < next_tlb_entry; i++) {
        entry_node = entry_node->next;

        if (entry_node->page_index == page_number) {
            break;
        }
    }

    // Page not found in TLB.
    if (i == next_tlb_entry) {
        if (next_tlb_entry == tlbTable->length) {
            // TLB table is full, replace first entry.

            // Allocate new node.
            EntryNode *new_enode = new_node();
            new_enode->page_index = page_number;
            new_enode->frame_index = frame_number;

            // Append new node to the end of TLB.
            insert_node(entry_node, new_enode);

            // Delete first node.
            delete_next_node(tlbTable->entryList);
        } else {
            // TLB table is not full, append to end of table.
            EntryNode *next_node = entry_node->next;
            next_node->page_index = page_number;
            next_node->frame_index = frame_number;
            next_node->age = 0;
        }
    } else {
        // If another frame with the same page index already in TLB.

        EntryNode *prev_node = entry_node->prev;

        // Go to last page in TLB.
        for (; i < next_tlb_entry; i++) {
            entry_node = entry_node->next;
        }

        // Delete the node with the same page index.
        delete_next_node(prev_node);

        // Append page to end of TLB.
        EntryNode *new_enode = new_node();
        new_enode->page_index = page_number;
        new_enode->frame_index = frame_number;
        insert_node(entry_node, new_enode);
    }

    // Increment next tlb entry.
    if (next_tlb_entry < tlbTable->length) {
        next_tlb_entry = next_tlb_entry + 1;
    }
}

void tlb_lru_insert(int page_number, int frame_number) {
    Boolean free_spot_found = False;
    Boolean already_here = False;
    EntryNode *entry_node = tlbTable->entryList;
    EntryNode *to_replace_node = NULL;

    // Find the index to replace and increment age for all other entries.
    for (int i = 0; i < TLB_SIZE; i++) {
        entry_node = entry_node->next;

        if ((entry_node->page_index) &&
            (entry_node->page_index != page_number)) {
            // If entry does not exist in TLB and is not a free spot, increment
            // its age.
            entry_node->age++;
        } else if (entry_node->page_index == 0) {
            // A free entry in TLB.
            if (!free_spot_found) {
                to_replace_node = entry_node;
                free_spot_found = True;

                // Don't exit for need to increment age for remaining entries.
            }
        } else if (entry_node->page_index == page_number) {
            // Entry already in TLB, reset its age.
            if (!already_here) {
                entry_node->age = 0;
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
        to_replace_node->page_index = page_number;
        to_replace_node->frame_index = frame_number;
        to_replace_node->age = 0;
    } else {
        // No free entry available in TLB, replace the oldest entry.
        to_replace_node = get_oldest_entry(TLB_SIZE);
        to_replace_node->page_index = page_number;
        to_replace_node->frame_index = frame_number;
        to_replace_node->age = 0;
    }
}

EntryNode *get_oldest_entry(int tlb_size) {
    EntryNode *entry_node = tlbTable->entryList;
    int max = entry_node->age;
    EntryNode *max_age_node = NULL;

    // Iterate through TLB to find max age node.
    for (int i = 0; i < tlb_size; i++) {
        entry_node = entry_node->next;

        if (entry_node->age > max) {
            max = entry_node->age;
            max_age_node = entry_node;
        }
    }

    if (max_age_node == NULL) {
        fprintf(stderr, "Error getting oldest entry in TLB to replace.\n");
    }

    // Return max age node.
    return max_age_node;
}

double get_avg_time_in_secondary_storage() {
    double tmp = (double)cpu_time_elapsed / secondary_storage_call_count;
    return tmp * 1e6;
}
