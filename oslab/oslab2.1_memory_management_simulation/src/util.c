#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("\n\n MEMORY MANAGEMENT ALLOCATION SIMULATION");
    printf("\n Options:");
    printf("\n 0. Customize configuration");
    printf("\n 1. First Fit");
    printf("\n q. Exit\n");
}

int config(Process *p, Block *b, int *n, int *m) {

    // Free allocated heap memory space.
    if (p != NULL) {
        free(p);
    }
    if (b != NULL) {
        free(b);
    }

    printf("\n Enter number of blocks: ");
    scanf("%d", m);
    b = (Block *)malloc(*m * sizeof(Block));
    if (b == NULL) {
        printf("\n Error: failed to allocate memory for blocks.\n");
        return -1;
    }
    for (int i; i < *m; i++) {
        printf("Enter size of block[%d]: ", i);
        scanf("%d", &b[i].bsize);
    }

    printf("\n Enter number of processes: ");
    scanf("%d", n);
    p = (Process *)malloc(*n * sizeof(Process));
    if (p == NULL) {
        printf("\n Error: failed to allocate memory for processes.\n");
        return -1;
    }
    for (int i; i < *n; i++) {
        printf("Enter size of process[%d]: ", i);
        scanf("%d", &p[i].psize);
    }

    return 0;
}

Boolean valid_option(char ch) {
    switch (ch) {
    case '0':
    case '1':
    case 'q':
    case 'i':
        return TRUE;
    default:
        return FALSE;
    }
}
