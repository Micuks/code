#include <sys/shm.h>

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

typedef struct shm_data {
    int reads;
    int writes;
    long double avg_time;
};

// Initialize shared memory.
int shm_init(key_t key, int size);

// Return a pointer to memory.
shm_data *shm_at(int shm_id);

// Detach memory
int shm_detach(shm_data *shm_ptr);

// Deallocate memory
int shm_delete(int shm_id);

#endif