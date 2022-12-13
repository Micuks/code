#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <unistd.h>

#include "semaphores.h"
#include "shared_memory.h"

const int LOOPS = 10;

double u(int x) { return (double)(x + 1) / 10; }
double exp_time() {
    int x = rand() % 10 / 100;
    return (-(log(u(x))) * 1e6);
}

int main(int argc, char *argv[]) {
    int rw_ratio, shm_size, peers, max_readers = 3;
    ShmData *shmData;
    int shm_id, shm_stat_id;
    int readers_counter_id;
    int *readers_counter_data;
    long *stat_data;
    pid_t pid;
    int read_id, write_id, sem_id, mutex_id, counter_id, print_id;

    if (argc != 4) {
        printf("Error: not enough CLI arguments %d\n ", argc);
    }

    peers = atoi(argv[1]);
    // For inputs between 1 and 100 -> between 1% and 100%.
    rw_ratio = atoi(argv[2]) - 1;

    srand(getpid());

    // Initialize the shared matrix.
    // Allocate shared memory for ShmData.
    key_t shm_key = 597;
    shm_id = shm_init(shm_key, sizeof(ShmData) * shm_size);
    shmData = shm_at(shm_id);
    for (int i = 0; i < shm_size; i++) {
        shmData[i].avg_time = 0;
        shmData[i].writes = 0;
        shmData[i].reads = 0;
    }

    // Initialize shared counter for readers
    readers_counter_id = shm_init((key_t)211, shm_size * sizeof(int));
    readers_counter_data = (int *)shm_at(readers_counter_id);
    for (int i = 0; i < shm_size; i++) {
        readers_counter_data[i] = 0;
    }

    /** Initialize shared memory to keep stats
     * 0: Writer waiting time;
     * 1: Reader waiting time;
     * 2: Total waiting time;
     */
    shm_stat_id = shm_init((key_t)2022, 3 * sizeof(long));
    stat_data = (long *)shm_at(shm_stat_id);
    for (int i = 0; i < 3; i++) {
        stat_data[i] = 0;
    }

    // Initalize array for child pid.
    pid_t child_pid[peers];

    // Initialize semaphores.
    read_id = sem_init((key_t)10001, shm_size);
    write_id = sem_init((key_t)20001, shm_size);
    counter_id = sem_init((key_t)30001, shm_size);
    print_id = sem_init((key_t)40001, shm_size);

    // Initialize counters for statistics.
    struct timeval stop, start;
    double avg_time = 0;
    double avg_time_writer = 0;
    double avg_time_reader = 0;
    long total_time_reader = 0;
    long total_time_writer = 0;
    long curr_time = 0;
    long total_time = 0;
    int reads = 0;
    int writes = 0;
    int entry = 0;

    // File to print statistics.
    char *log_file_path = "logs/file.log";
    FILE *log_file = fopen(log_file_path, "w+");
    char *log_stat_path = "logs/stat.log";
    FILE *log_stat = fopen(log_stat_path, "a");

    for (int i = 0; i < peers; i++) {
        pid = fork();
        // Child process
        if (pid == 0) {
            break;
        }
        child_pid[i] = pid;
    }

    // R/W processes.
    if (pid != 0) {
        // parent
        printf("Parent with pid: %d\n", pid);
    } else {
        // child
        printf("Child with pid: %d\n", pid);
        srand(getpid());
        // counter for average time in microseconds.
        for (int i = 0; i < LOOPS; i++) {
            if (rand() % 100 > rw_ratio) {
                // child become writer
                entry = rand() % shm_size;
                writes++;
                gettimeofday(&start, NULL);

                /**
                 * CRITICAL SECTION OF WRITER
                 */
                sem_down(write_id, entry);

                gettimeofday(&stop, NULL);
                curr_time = (stop.tv_sec - start.tv_sec) * 1e6 + stop.tv_usec -
                            start.tv_usec;
                usleep(exp_time());
                shmData[entry].writes++;

                sem_up(write_id, entry);
                /**
                 * EXIT CRITICAL SECTION OF WRITER
                 */

                // Update statistic data.
                total_time_writer += curr_time;
                total_time += curr_time;
            } else {
                // child become reader.
                entry = rand() % shm_size; // Access a random shared value in
                                           // shared memory.
                reads++;

                gettimeofday(&start, NULL);
                // Update counter.
                sem_down(counter_id, entry);
                readers_counter_data[entry]++;
                if (readers_counter_data[entry] == 1) {
                    // Prevent writer from entering critical section.
                    sem_down(write_id, entry);
                }
                sem_up(counter_id, entry);

                /**
                 * CRITICAL SECTION OF READER
                 */
                sem_down(read_id, entry);

                gettimeofday(&stop, NULL);
                curr_time = (stop.tv_sec - start.tv_sec) * 1e6 + stop.tv_usec -
                            start.tv_usec;
                // Wait exponential time.
                usleep(exp_time());
                shmData[entry].reads++;

                sem_up(read_id, entry);
                /**
                 * EXIT CRITICAL ZONE OF READER.
                 */

                // Update counter.
                sem_down(counter_id, entry);
                readers_counter_data[entry]--;
                if (readers_counter_data[entry] == 0) {
                    // Release writer lock.
                    sem_up(write_id, entry);
                }
                sem_up(counter_id, entry);

                // Update timer.
                total_time_reader += curr_time;
                total_time += curr_time;
            }
        }
    }

    return 0;
}
