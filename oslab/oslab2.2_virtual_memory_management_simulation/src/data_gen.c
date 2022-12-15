#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments give.\n");
        printf("Usage: data_gen <start> <end> <number of virtual addresses to "
               "access>.\n");
        printf("Default write to config/input.txt.\n");
    }

    char filename[] = "config/input.txt";
    FILE *fout = fopen(filename, "w");

    srand(time(NULL));

    int low = atoi(argv[1]);
    int high = atoi(argv[2]);
    int num_vaddr = atoi(argv[3]);

    for (int i = 0; i < num_vaddr; i++) {
        int r = (rand() % (high - low + 1) + low);
        fprintf(fout, "%d\n", r);
    }

    return 0;
}
