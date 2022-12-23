#include <sys/shm.h>

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

typedef struct shm_data {
    int reads;
    int writes;
} ShmData;

/**
 * @brief Initialize shared memory.
 *
 * @param key
 * @param size
 * @return int
 */
int shm_init(key_t key, int size);

/**
 * @brief Return a pointer to memory.
 *
 * @param shm_id
 * @return shm_data*
 */
ShmData *shm_at(int shm_id);

/**
 * @brief Detach memory
 *
 * @param shm_ptr
 * @return int
 */
int shm_detach(void *shm_ptr);

/**
 * @brief Deallocate memory
 *
 * @param shm_id
 * @return int
 */
int shm_delete(int shm_id);

#endif
