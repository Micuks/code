#ifndef _t6pk_20200112_
#define _t6pk_20200112_
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
int t, n, m;
int path[MAXN][MAXN];
int conn[MAXN][MAXN];
int used[MAXN][MAXN];

int prim()
{
    // int res = 0;
    int d[MAXN];
    int visited[MAXN];
    int prev[MAXN];
    memset(prev, 0, sizeof(prev));
    memset(d, 0x3F, sizeof(d));
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; ++i) {
        prev[i] = 1;
    }
    d[0] = 0;
    for (int i = 0; i < n; ++i) {
        int min_idx, min_val = 1e9;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && d[j] < min_val) {
                min_val = d[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        used[min_idx][prev[min_idx]] = used[prev[min_idx]][min_idx] = 1;
        for (int j = 0; j < n; ++j) {
            if (visited[j] && j != min_idx) {
                path[j][min_idx] = path[min_idx][j] = max(d[min_idx], path[j][prev[min_idx]]);
            }
            if (!visited[j] && d[j] > conn[min_idx][j]) {
                d[j] = conn[min_idx][j];
                prev[j] = min_idx;
            }
        }
    }
    return accumulate(d, d + n, 0);
}

int main(int argc, char **argv)
{
    int a, b, w;
    cin >> t;
    while (t--) {
        memset(path, 0, sizeof(path));
        memset(conn, 0x3F, sizeof(conn));
        memset(used, 0, sizeof(used));
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &w);
            conn[a - 1][b - 1] = conn[b - 1][a - 1] = w;
        }
        int res = prim();
        int ans = 0x3F3F3F3F;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j & used[i][j] == 0) {
                    ans = min(ans, res + conn[i][j] - path[i][j]);
                }
            }
        }
        if (ans == res) {
            printf("Not Unique!\n");
        }
        else {
            printf("%d\n", res);
        }
    }
    return 0;
};

#endif
