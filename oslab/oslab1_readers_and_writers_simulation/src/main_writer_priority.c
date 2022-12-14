/**
 * Reader-Preference readers and writers simulation.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <unistd.h>

#include "semaphores.h"
#include "shared_memory.h"

char time_buf[64];

char *log_time() {
    char *output = time_buf;
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(output, "[%d-%d-%dT%02d:%02d:%02d]", timeinfo->tm_year + 1900,
            timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour,
            timeinfo->tm_min, timeinfo->tm_sec);

    return output;
}

const int LOOPS = 10;

double u(int x) { return (double)(x + 1) / 10; }
double exp_time() {
    int x = rand() % 10;
    double sleeptime = (-(log(u(x))) * 1e6);

    return sleeptime;
}

int main(int argc, char *argv[]) {
    int rw_ratio, shm_size, peers;
    ShmData *shmData;
    int shm_id, shm_stat_id;
    int readers_counter_id;
    int *readers_counter_data;
    long *stat_data;
    pid_t pid;
    int read_mutex, write_mutex, counter_mutex, print_mutex;

    if (argc != 4) {
        printf("Error: not enough arguments passed to program: Only %d/3 "
               "arguments\n ",
               argc);
    }

    peers = atoi(argv[1]);
    // For inputs between 1 and 100 -> between 1% and 100%.
    rw_ratio = atoi(argv[2]) - 1;
    shm_size = atoi(argv[3]);

    srand(getpid());

    // Initialize the shared matrix.
    // Allocate shared memory for ShmData.
    shm_id = shm_init(597, sizeof(ShmData) * shm_size);
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
    read_mutex = sem_init((key_t)10001, shm_size);
    write_mutex = sem_init((key_t)20001, shm_size);
    counter_mutex = sem_init((key_t)30001, shm_size);
    print_mutex = sem_init((key_t)40001, shm_size);

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
        printf("%s Parent with pid: %d\n", log_time(), pid);
    } else {
        // child
        printf("%s Child with pid: %d\n", log_time(), getpid());
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
                sem_down(write_mutex, entry);
                printf("%s Child[%d](writer) accessing shared_memory[%d].\n",
                       log_time(), getpid(), entry);

                gettimeofday(&stop, NULL);
                curr_time = (stop.tv_sec - start.tv_sec) * 1e6 + stop.tv_usec -
                            start.tv_usec;
                printf("%s Child[%d](writer) waited for %lf seconds.\n",
                       log_time(), getpid(), (double)curr_time / (double)1e6);

                // Sleep to occupy symaphore.
                double sleeptime = exp_time();
                printf("%s Sleep for %lf seconds.\n", log_time(),
                       (double)sleeptime / 1e6);
                usleep(sleeptime);

                shmData[entry].writes++;

                sem_up(write_mutex, entry);
                printf("%s Child[%d](writer) exited shared_memory[%d].\n",
                       log_time(), getpid(), entry);
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
                sem_down(counter_mutex, entry);
                readers_counter_data[entry]++;
                if (readers_counter_data[entry] == 1) {
                    // Prevent writer from entering critical section.
                    sem_down(write_mutex, entry);
                }
                sem_up(counter_mutex, entry);

                /**
                 * CRITICAL SECTION OF READER
                 */
                sem_down(read_mutex, entry);
                printf("%s Child[%d](reader) accessing shared_memory[%d].\n",
                       log_time(), getpid(), entry);

                gettimeofday(&stop, NULL);
                curr_time = (stop.tv_sec - start.tv_sec) * 1e6 + stop.tv_usec -
                            start.tv_usec;
                printf("%s Child[%d](reader) waited for %lf seconds.\n",
                       log_time(), getpid(), (double)curr_time / 1e6);

                // Sleep to occupy symaphore.
                double sleeptime = exp_time();
                printf("%s Sleep for %lf seconds.\n", log_time(),
                       (double)sleeptime / 1e6);
                usleep(sleeptime);
                shmData[entry].reads++;

                sem_up(read_mutex, entry);
                printf("%s Child[%d](reader) exited shared_memory[%d].\n",
                       log_time(), getpid(), entry);
                /**
                 * EXIT CRITICAL ZONE OF READER.
                 */

                // Update counter.
                sem_down(counter_mutex, entry);
                readers_counter_data[entry]--;
                if (readers_counter_data[entry] == 0) {
                    // Release writer lock.
                    sem_up(write_mutex, entry);
                }
                sem_up(counter_mutex, entry);

                // Update timer.
                total_time_reader += curr_time;
                total_time += curr_time;
            }
        }
    }

    if (pid == 0) {
        // Let parent process print statistics.
        avg_time_writer = (writes) ? ((double)total_time_writer / writes) : 0;
        avg_time_reader = (reads) ? ((double)total_time_reader / reads) : 0;
        avg_time =
            (reads + writes) ? ((double)total_time / (reads + writes)) : 0;

        /**
         * STATISTICS PRINTER CRITICAL ZONE
         */
        sem_down(print_mutex, 0);
        fprintf(log_file, "%s Child[%d]:\n", log_time(), getpid());
        fprintf(
            log_file,
            "Total write time: %lf seconds; average write time: %lf seconds.\n",
            (double)total_time_writer / 1e6, (double)avg_time_writer / 1e6);
        fprintf(log_file, "Total read time: %lf; average read time: %lf\n",
                (double)total_time_reader / 1e6, (double)avg_time_reader / 1e6);
        fprintf(log_file, "Total time: %lf, total average time: %lf\n",
                (double)total_time / 1e6, (double)avg_time / 1e6);
        fprintf(log_file, "\n");

        // Shared statistics
        stat_data[0] += total_time_writer / 10;
        stat_data[1] += total_time_reader / 10;
        stat_data[2] += total_time / 10;

        sem_up(print_mutex, 0);
        /**
         * EXIT STATISTICS PRINTER CRITICAL ZONE
         */
    }

    // Exit processes.
    if (pid != 0) {
        // Parent process,
        // Terminate child process.
        int status;
        pid_t child_terminated_pid;

        // Close all child processes.
        for (size_t i = 0; i < (size_t)peers; i++) {
            child_terminated_pid = waitpid(child_pid[i], &status, 0);
            printf("%s Child[%d] has finished.\n", log_time(),
                   child_terminated_pid);
            if (WIFEXITED(status)) {
                printf("%s Child exited with code %d\n", log_time(), status);
            } else {
                printf("%s Child terminated abnormally %d\n", log_time(),
                       status);
            }
        }

        // Validate results.
        int sum_readers = 0;
        int sum_writers = 0;

        /**
         * ENTER STATISTIC PRINTER CRITICAL ZONE.
         */
        sem_down(print_mutex, 0);
        printf("%s Parent[%d] Writing statistics log.\n", log_time(), pid);
        fprintf(log_file, "\n VALIDATING RESULTS \n");
        for (size_t i = 0; i < (size_t)shm_size; i++) {
            fprintf(log_file, "shared[%zu]: readers[%d], writers[%d]\n", i,
                    shmData[i].reads, shmData[i].writes);
            sum_readers += shmData[i].reads;
            sum_writers += shmData[i].writes;
        }
        fprintf(log_file, "--------------------\n");
        fprintf(log_file, "total: readers[%d], writers[%d]\n", sum_readers,
                sum_writers);
        fprintf(log_file, "Total should be equal to (peers * LOOPS)[%d]\n",
                peers * LOOPS);
        if (peers * LOOPS == sum_writers + sum_readers) {
            fprintf(log_file, "Result is right!\n");
        }

        // Print statistics in log_stat.
        fprintf(log_stat, "%ld, %ld, %ld\n", (long)(stat_data[2] / 1e3),
                (long)(stat_data[1] / 1e3), (long)(stat_data[0] / 1e3));
        sem_up(print_mutex, 0);
        /**
         * EXIT STATISTIC PRINTER CRITICAL ZONE
         */
    } else {
        // Child process,
        // Exit.
        // pid = getpid();
        printf("%s Process with pid %d exitting...\n", log_time(), getpid());
        exit(0);
    }

    // Delete semaphores.
    sem_del(read_mutex);
    sem_del(write_mutex);
    sem_del(counter_mutex);
    sem_del(print_mutex);

    // Free allocated shared memory.
    shm_delete(shm_stat_id);
    shm_detach(stat_data);

    shm_delete(readers_counter_id);
    shm_detach(readers_counter_data);

    shm_delete(shm_id);
    shm_detach((ShmData *)shmData);

    // Close files.
    fclose(log_file);
    fclose(log_stat);

    return 0;
}
