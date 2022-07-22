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
int n, k;

void printMatrix(int mtx[][maxn]) {
    for (int i = 0; i < n; i++) {
        putchar('-');
    }
    putchar('\n');
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mtx[i][j]);
        }
        putchar('\n');
    }
}

int process(int ns, int iter_depth, int mtx[][maxn]) {
    int flag[maxn][maxn];
    memcpy(flag, mtx, maxn * maxn * sizeof(int));
    // printMatrix(flag);
    int sum = 0;

    if (iter_depth == k) {
        // printf("1\n");
        return 1;
    }
    if (iter_depth + n - ns < k) {
        // printf("0\n");
        return 0;
    }
    // printf("ns[%d]\n", ns);
    int i = ns;
    for (int j = 0; j < n; j++) {
        if (flag[i][j] == 1) {
            // printf("%d, %d\n", i, j);
            memset(flag[i], 0, maxn * sizeof(int));
            for (int l = 0; l < maxn; l++) {
                flag[l][j] = 0;
            }
            sum += process(i + 1, iter_depth + 1, flag);
            memcpy(flag[i], mtx[i], maxn * sizeof(int));
            for (int l = 0; l < maxn; l++) {
                flag[l][j] = mtx[l][j];
            }
        }
    }
    sum += process(i + 1, iter_depth, flag);
    return sum;
}

int main(int argc, char **argv) {
    while (scanf("%d%d", &n, &k) == 2 && n != -1 && k != -1) {
        memset(g_flag, 0, sizeof(g_flag));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char tmp = getchar();
                while (tmp == '\n') {
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
        printf("%d\n", process(0, 0, g_flag));
    }
    putchar('\n');
    return 0;
};

#endif
