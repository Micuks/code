#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Not enough arguments give.\n");
        printf("Usage: data_gen <start> <end> <number of blocks> <number of "
               "processes>.\n");
        printf("Default write to config/config.txt.\n");
    }

    char filename[] = "config/config.txt";
    FILE *fout = fopen(filename, "w");

    int low = atoi(argv[1]);
    int high = atoi(argv[2]);
    int num_blockes = atoi(argv[3]);
    int num_processes = atoi(argv[4]);

    srand(time(NULL));

    fprintf(fout, "%d\n", num_blockes);
    for (int i = 0; i < num_blockes; i++) {
        int rnd_num = (rand() % (high - low + 1) + low);
        fprintf(fout, "%d ", rnd_num);
    }

    fprintf(fout, "\n%d\n", num_processes);
    for (int i = 0; i < num_processes; i++) {
        int rnd_num = (rand() % (high - low + 1) + low);
        fprintf(fout, "%d ", rnd_num);
    }
    putchar('\n');

    return 0;
}
