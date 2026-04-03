#ifndef _t6pn_20200113_
#define _t6pn_20200113_
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

const int MAXN = 256;
int f[MAXN];
int T, C;
int xi[MAXN], yi[MAXN];
double dist[MAXN][MAXN];

#define EUCLIDEAN_DIST(x, y) sqrt((x) * (x) + (y) * (y))
int find(int x)
{
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}
int union_set(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y) {
        return x;
    }
    return f[y] = x;
}

double prim()
{
    double d[MAXN];
    int visited[MAXN];
    fill(d, d + MAXN, 1e10);
    d[0] = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < C; ++i) {
        int min_idx;
        double min_val = 1e11;
        for (int j = 0; j < C; ++j) {
            if (!visited[j] && d[j] < min_val) {
                min_val = d[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int j = 0; j < C; ++j) {
            if (!visited[j] && d[j] > dist[min_idx][j]) {
                d[j] = dist[min_idx][j];
            }
        }
    }
    return accumulate(d, d + C, 0.0L);
}

int main(int argc, char **argv)
{
    cin >> T;
    while (T--) {
        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                dist[i][j] = 1e10;
            }
        }
        scanf("%d", &C);
        for (int i = 0; i <= C; ++i) {
            f[i] = i;
        }
        for (int i = 0; i < C; ++i) {
            scanf("%d%d", &xi[i], &yi[i]);
        }
        for (int i = 0; i < C; ++i) {
            for (int j = 0; j < i; ++j) {
                double d = EUCLIDEAN_DIST(double(xi[i]) - xi[j], double(yi[i]) - yi[j]);
                if (d >= 10 && d <= 1000) {
                    dist[i][j] = dist[j][i] = d * 100;
                }
            }
        }
        double res = prim();
        if (res >= 1e10) {
            printf("oh!\n");
        }
        else {
            printf("%.1lf\n", res);
        }
    }
    return 0;
};

#endif
