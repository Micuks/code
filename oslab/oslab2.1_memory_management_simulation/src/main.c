#include "schemas.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char ch = 'i'; // Initialize option variable.
    int num_processes = 0, num_blocks = 0;
    Process *p = NULL;
    Block *b = NULL;

    do {
        print_menu();
        scanf("%c", &ch);
        switch (ch) {
        case '0':
            config(p, b, &num_processes, &num_blocks);
            break;
        case '1':
            re_init(p, b, num_processes, num_blocks);
            first_fit(p, b, num_processes, num_blocks);
            break;
        default:
            printf("\n Invalid option.");
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
