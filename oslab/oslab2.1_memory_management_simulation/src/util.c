#include "util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("\n\nMEMORY MANAGEMENT ALLOCATION SIMULATION");
    printf("\nOptions:");
    printf("\n0. Customize configuration");
    printf("\n1. First Fit");
    printf("\n2. Best Fit");
    printf("\nq. Exit\n");
}

Boolean config(Process **p, Block **b, int *n, int *m) {

    // Free allocated heap memory space.
    if (*p != NULL) {
        free(*p);
    }
    if (*b != NULL) {
        free(*b);
    }

    printf("\nEnter number of blocks: ");
    scanf("%d", m);
    *b = (Block *)malloc((*m) * sizeof(Block));
    if (b == NULL) {
        printf("\nError: failed to allocate memory for blocks.\n");
        return FALSE;
    }
    for (int i = 0; i < *m; i++) {
        printf("Enter size of block[%d]: ", i);
        scanf("%d", &(*b)[i].bsize);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", n);
    *p = (Process *)malloc((*n) * sizeof(Process));
    if (p == NULL) {
        printf("\nError: failed to allocate memory for processes.\n");
        return FALSE;
    }
    for (int i = 0; i < *n; i++) {
        printf("Enter size of process[%d]: ", i);
        scanf("%d", &(*p)[i].psize);
    }

    return TRUE;
}

Boolean load_config(Process **p, Block **b, int *n, int *m) {
    char filename[] = "config/config.txt";
    FILE *config_file = fopen(filename, "r");
    if (config_file == NULL) {
        printf("\nError: failed to load config from file.");
        return FALSE;
    }
    printf("\nLoad config from %s.", filename);

    // Read config from file.
    fscanf(config_file, "%d", m);
    *b = (Block *)malloc(*m * sizeof(Block));
    if (b == NULL) {
        printf("\nError: failed to allocate memory for blocks.\n");
        return FALSE;
    }
    for (int i = 0; i < *m; i++) {
        fscanf(config_file, "%d", &(*b)[i].bsize);
    }

    fscanf(config_file, "%d", n);
    *p = (Process *)malloc(*n * sizeof(Process));
    if (p == NULL) {
        printf("\nError: failed to allocate memory for processes.\n");
        return FALSE;
    }
    for (int i = 0; i < *n; i++) {
        fscanf(config_file, "%d", &(*p)[i].psize);
    }

    return TRUE;
}

Boolean valid_option(char ch) {
    switch (ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case 'i':
        return TRUE;
    case 'q':
    default:
        return FALSE;
    }
}

char get_valid_option() {
    char ch;
    ch = getchar();
    while (ch == '\n' || ch == ' ') {
        ch = getchar();
    }
    return ch;
}
