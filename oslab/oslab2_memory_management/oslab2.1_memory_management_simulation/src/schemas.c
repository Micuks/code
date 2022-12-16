#include "schemas.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

void re_init(Process *p, Block *b, int n, int m) {
    assert(p != NULL);
    assert(b != NULL);
    for (int i = 0; i < n; i++) {
        p[i].pflag = 0;
    }

    for (int i = 0; i < m; i++) {
        b[i].bflag = 0;
    }
}

void fragmentation_statistics(int in_frag, Block *b, int m) {
    int ex_frag = 0;
    printf("\n\n ------FRAGMENTATION STATISTICS------");
    printf("\n\n Total internal fragmentation: %d", in_frag);
    for (int j = 0; j < m; j++) {
        if (b[j].bflag == 0) {
            ex_frag += b[j].bsize;
        }
    }

    printf("\n Total external fragmentation: %d", ex_frag);
}

void first_fit(Process *p, Block *b, int n, int m) {
    int in_frag = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (p[i].psize <= b[j].bsize && b[j].bflag == 0 &&
                p[i].pflag == 0) {
                b[j].bflag = p[i].pflag = 1;
                in_frag += b[j].bsize - p[i].psize;
                printf("\n process[%d] in block[%d] %d/%d", i, j, p[i].psize,
                       b[j].bsize);

                break;
            }
        }

        if (p[i].pflag == 0) {
            printf("\n process[%d] is not assigned.", i);
        }
    }

    fragmentation_statistics(in_frag, b, m);
}

void best_fit(Process *p, Block *b, int n, int m) {
    int in_frag = 0;
    int min_frag = INT_MAX;
    int bid = INT_MAX;
    for (int i = 0; i < n; i++) {
        min_frag = INT_MAX;
        bid = INT_MAX;
        for (int j = 0; j < m; j++) {
            int tmp_in_frag = b[j].bsize - p[i].psize;
            if (tmp_in_frag >= 0 && b[j].bflag == 0 && min_frag > tmp_in_frag) {
                min_frag = tmp_in_frag;
                bid = j;
            }
        }

        if (min_frag != INT_MAX) {
            b[bid].bflag = 1;
            p[i].pflag = 1;
            in_frag += b[bid].bsize - p[i].psize;
            printf("\n process[%d] in block[%d] %d/%d", i, bid, p[i].psize,
                   b[bid].bsize);
        }

        if (p[i].pflag == 0) {
            printf("\n process[%d] is not assigned.", i);
        }
    }

    fragmentation_statistics(in_frag, b, m);
}
