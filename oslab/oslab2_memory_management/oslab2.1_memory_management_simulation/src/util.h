#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#ifndef BOOLEAN
#define TRUE 1
#define FALSE 0
#endif

typedef struct Process {
    int psize;
    int pflag;
} Process;

typedef struct Block {
    int bsize;
    int bflag;
} Block;

typedef uint8_t Boolean;

void print_menu();
Boolean config(Process **p, Block **b, int *n, int *m);
Boolean load_config(Process **p, Block **b, int *num_processes,
                    int *num_blocks);
Boolean valid_option(char ch);

char get_valid_option();
#endif // !UTIL_H
