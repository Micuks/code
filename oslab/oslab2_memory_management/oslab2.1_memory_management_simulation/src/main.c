#include "schemas.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char ch = 'i'; // Initialize option variable.
    int num_processes = 0, num_blocks = 0;
    Process *p = NULL;
    Block *b = NULL;

    load_config(&p, &b, &num_processes, &num_blocks);

    do {
        print_menu();

        ch = get_valid_option();

        switch (ch) {
        case '0':
            config(&p, &b, &num_processes, &num_blocks);
            assert(p != NULL);
            assert(b != NULL);
            break;

        case '1':
            re_init(p, b, num_processes, num_blocks);
            printf("\nFirst fit.\n");
            first_fit(p, b, num_processes, num_blocks);
            break;

        case '2':
            re_init(p, b, num_processes, num_blocks);
            printf("\nBest fit.\n");
            best_fit(p, b, num_processes, num_blocks);
            break;

        case 'q':
            break;

        default:
            printf("\nInvalid option.");
        }
    } while (valid_option(ch));

    // Free allocated heap memory space.
    if (p != NULL) {
        free(p);
    }
    if (b != NULL) {
        free(b);
    }
    return 0;
}
