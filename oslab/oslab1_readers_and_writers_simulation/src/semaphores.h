#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

/**
 * @brief Create and initialize semaphore.
 * 
 * @param key 
 * @param sem_num 
 * @return int 
 */
int sem_init(key_t key, int sem_num);

/**
 * @brief Delete semaphore.
 * 
 * @param sem_id 
 * @param sem_num 
 * @return int 
 */
int sem_del(int sem_id, int sem_num);

/**
 * @brief Semaphore up.
 * 
 * @param sem_id 
 * @param sem_num 
 * @return int 
 */
int sem_up(int sem_id, int sem_num);

/**
 * @brief Sem down.
 * 
 * @param sem_id 
 * @param sem_num 
 * @return int 
 */
int sem_down(int sem_id, int sem_num);

#endif