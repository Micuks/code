#ifndef _cpt1_20220721_
#define _cpt1_20220721_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
const int maxn = 10;

int g_flag[maxn][maxn];
int c_avai[maxn];
int r_avai[maxn];
int n, k, ans = 0;
int cnt = 0;

int unitprocess(int i, int j) {
    if (cnt == k) {
        return 0;
    }
    if (g_flag[i][j] != 0 && c_avai[j] != 0 && r_avai[i] != 0) {
        c_avai[j] = 0;
        r_avai[i] = 0;
        cnt++;
    }
    return 1;
}

void process() {
    int ibgn = 0;
    int jbgn = 0;
    for (ibgn = 0; ibgn < n; ibgn++) {
        for (jbgn = 0; jbgn < n; jbgn++) {
            for(int i = 0; i < n; i++) {
                c_avai[i] = 1;
                r_avai[i] = 1;
            }
            cnt = 0;

            if (g_flag[ibgn][jbgn] == 0) {
                continue;
            }
            for (int i = ibgn; i < n; i++) {
                if (cnt == k) {
                    break;
                }
                if (i == ibgn) {
                    for (int j = jbgn; j < n; j++) {
                        if (unitprocess(i, j) == 0) {
                            break;
                        }
                    }
                } else {
                    for (int j = 0; j < n; j++) {
                        if (unitprocess(i, j) == 0) {
                            break;
                        }
                    }
                }
            }
            if (cnt == k) {
                ans++;
            }
        }
    }
};

void printMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", g_flag[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    scanf("%d%d", &n, &k);
    // printf("%d %d\n", n, k);
    while (n != -1 || k != -1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char tmp;
                if ((tmp = getchar()) == '\n') {
                    tmp = getchar();
                }
                if (tmp == '#') {
                    g_flag[i][j] = 1;
                } else {
                    g_flag[i][j] = 0;
                }
            }
        }
        // printMatrix();
        for(int i = 0; i < n; i++) {
            c_avai[i] = 0;
            r_avai[i] = 0;
        }
        ans = 0;
        process();
        printf("%d\n", ans);
        scanf("%d%d", &n, &k);
        // printf("%d %d\n", n, k);
    }
    putchar('\n');
    return 0;
};

#endif
