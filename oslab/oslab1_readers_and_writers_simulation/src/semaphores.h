#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

// Create and initialize semaphores
int sem_init(key_t key, int num_sems);

// Delete semaphores
int sem_del(int sel_id, int num_sems);

// Sem up
int sem_up(int sem_id, int sem_num);

// Sem down
int sem_down(int sem_id, int sem_num);

#endif