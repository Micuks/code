#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments give.\n");
        printf("Usage: data_gen <number of virtual addresses to access> <up "
               "border of number of consistent accesses in the same frame>.\n");
        printf("Default write to config/input.txt.\n");

        exit(-1);
    }

    char filename[] = "config/input.txt";
    FILE *fout = fopen(filename, "w");

    srand(time(NULL));

    int num_vaddr = atoi(argv[1]);
    int in_frame_border = atoi(argv[2]);

    int frame, offset;
    int cnt = num_vaddr;
    int in_frame_cnt;

    // Simulate locality of reference.
    while (cnt >= 0) {
        // Frame index.
        frame = rand() % (1 << 8);
        // Counter of addresses in this frame.
        in_frame_cnt = rand() % (in_frame_border + 1);
        printf("%4d virtual addresses to access in frame[0x%04x]\n",
               in_frame_cnt, (frame & 0xFF));
        while (in_frame_cnt >= 0) {
            offset = rand() % (1 << 8);
            fprintf(fout, "%d\n", ((frame & 0xFF) << 8) | (offset & 0xFF));

            in_frame_cnt--;
            cnt--;
        }
    }

    return 0;
}
