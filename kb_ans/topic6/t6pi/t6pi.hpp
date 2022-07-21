#ifndef _t6pi_20200112_
#define _t6pi_20200112_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define DEBUG
#ifdef DEBUG
#define DEBUG_CMD(cmd)                                                                             \
    do {                                                                                           \
        cmd;                                                                                       \
    } while (false)
#else
#define DEBUG_CMD(cmd)                                                                             \
    do {                                                                                           \
        ;                                                                                          \
    } while (false)
#endif
#define _DEBUG_CMD(cmd)                                                                            \
    do {                                                                                           \
        ;                                                                                          \
    } while (false)

const int MAXN = 128;
int N;
int matrix[MAXN][MAXN];

int prim()
{
    int d[MAXN];
    int visited[MAXN];
    memset(d, 0x3F, sizeof(d));
    memset(visited, 0, sizeof(visited));
    d[0] = 0;
    for (int i = 1; i < N; ++i) {
        int min_val = 1e9;
        int min_idx;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && d[j] < min_val) {
                min_val = d[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && d[j] > matrix[min_idx][j]) {
                d[j] = matrix[min_idx][j];
            }
        }
    }
    return accumulate(d, d + N, 0);
}

int main(int argc, char **argv)
{
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &matrix[i][j]);
            }
        }
        int res = prim();
        cout << res << endl;
    }
    return 0;
};

#endif
