#ifndef _t5pa_20191229_
#define _t5pa_20191229_
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

const int MAXN = 1024;
int N, D;
int c[MAXN];
// int repaired[MAXN];
set<int> repaired;
int xi[MAXN];
int yi[MAXN];
int dist[MAXN][MAXN];

int find(int x)
{
    if (c[x] == x) {
        return x;
    }
    return c[x] = find(c[x]);
}

int union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    c[yroot] = xroot;
    return xroot;
}

bool same_group(int x, int y) { return find(x) == find(y); }

bool dist_less(int x1, int y1, int x2, int y2, int dis)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= dis * dis;
}

int main(int argc, char **argv)
{
    cin >> N >> D;
    for (int i = 1; i <= N; ++i) {
        c[i] = i;
        // repaired[i] = 0;
    }
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &xi[i], &yi[i]);
        /*
        for (int j = 0; j < i; ++j) {
            if (dist_less(xi[j], yi[j], xi[i], yi[i], D)) {
                union_set(i, j);
            }
        }
        */
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= i; ++j) {
            dist[i][j] = dist[j][i] =
                (xi[i] - xi[j]) * (xi[i] - xi[j]) + (yi[i] - yi[j]) * (yi[i] - yi[j]);
        }
    }
    string s;
    char buf[1024];
    int ori, dst, d;
    while (~scanf("%s", buf)) {
        if (buf[0] == 'O') {
            scanf("%d", &d);
            repaired.insert(d);
            for (set<int>::iterator iter = repaired.begin(); iter != repaired.end(); ++iter) {
                if (d != *iter && !same_group(*iter, d) && dist[*iter][d] <= D * D) {
                    union_set(*iter, d);
                }
            }
        }
        else if (buf[0] == 'S') {
            scanf("%d%d", &ori, &dst);
            if (same_group(ori, dst)) {
                printf("SUCCESS\n");
            }
            else {
                printf("FAIL\n");
            }
        }
    }
    return 0;
};

#endif
