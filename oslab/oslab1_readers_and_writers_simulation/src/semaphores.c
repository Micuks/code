#include "semaphores.h"

int sem_init(key_t key, int sem_num) {
    int sem_id;
    // The semget() system call returns the System V semaphore set
    //    identifier associated with the argument key.  It may be used
    //    either to obtain the identifier of a previously created semaphore
    //    set (when semflg is zero and key does not have the value
    //    IPC_PRIVATE), or to create a new set.
    sem_id = semget(key, sem_num, 0666 | IPC_CREAT);

    union semun sem_union;
    sem_union.val = 1;

    for (size_t i = 0; i < sem_num; i++) {
        if (semctl(sem_id, i, SETVAL, sem_union) == -1) {
            printf("Error: semaphore init failed %d\n", sem_num);
            return 0;
        }
    }

    return sem_id;
}

int sem_del(int sem_id, int sem_num) {
    union semun sem_union;
    return semctl(sem_id, 0, IPC_RMID, sem_union);
}

/**
 * @brief Increase semval of semaphore sem_id by 1.
 * 
 * @param sem_id 
 * @param sem_num 
 * @return int 
 */
int sem_up(int sem_id, int sem_num) {
    struct sembuf sem_b;
    sem_b.sem_num = sem_num;
    sem_b.sem_op = 1; // V()
    sem_b.sem_flg = 0;

    if (semop(sem_id, &sem_b, 1) == -1) {
        printf("Error: semaphore up failed %d", sem_num);
        return 0;
    }

    return 1;
}

/**
 * @brief Decrease semaphore sem_id by abs(sem_op) if semval of sem_id is greater or equal
 * to abs(sem_op), else increase semcnt of sem_id and the calling process will
 * be suspended until semval of sem_id is greater or equal to abs(sem_op), then
 * decrease semcnt of sem_id and sustract abs(sem_op) from semval of sem_id. Here sem_op is -1.
 * 
 * @param sem_id 
 * @param sem_num 
 * @return int 
 */
int sem_down(int sem_id, int sem_num) {
    struct sembuf sem_b;
    sem_b.sem_num = sem_num;
    sem_b.sem_op = -1; // V()
    sem_b.sem_flg = 0;

    if(semop(sem_id, &sem_b, 1) == -1) {
        printf("Error: semaphore down failed %d", sem_num);
    }
}
