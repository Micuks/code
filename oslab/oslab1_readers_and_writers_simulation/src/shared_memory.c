#include "shared_memory.h"
#include <stdio.h>

int shm_init(key_t key, int size) {
    int shm_id;
    if ((shm_id = shmget(key, size, IPC_CREAT | 0666)) == -1) {
        printf("Error: shared memory failed %d \n", size);
    }

    return shm_id;
}

ShmData *shm_at(int shm_id) { return (ShmData *)shmat(shm_id, 0, 0); }

int shm_detach(void *shm_ptr) {
    if (shmdt(shm_ptr) == -1) {
        printf("Error: memory detach failed %p \n", shm_ptr);

        return 0;
    }

    return 1;
}

int shm_delete(int shm_id) {
    if (shmctl(shm_id, IPC_RMID, 0) == -1) {
        printf("Error: memory deallocation failed %d \n", shm_id);

        return 0;
    }

    return 1;
}
