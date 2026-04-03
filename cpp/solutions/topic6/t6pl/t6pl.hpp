#ifndef _t6pl_20200113_
#define _t6pl_20200113_
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
int f[MAXN];

struct Edge {
    int u, v, cost;
    bool operator<(const Edge &e) const { return cost < e.cost; };
    Edge(int u = 0, int v = 0, int cost = 0) : u(u), v(v), cost(cost){};
} edge[MAXN * MAXN / 2];
int edge_cnt = 0;

int find(int x)
{
    if (f[x] == x)
        return f[x];
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

int kruskal()
{
    int res = 0;
    sort(edge, edge + edge_cnt);
    for (int i = 0; i < edge_cnt; ++i) {
        const Edge &e = edge[i];
        if (find(e.u) != find(e.v)) {
            union_set(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}

int main(int argc, char **argv)
{
    int a, b, w;
    while (cin >> N && N != 0) {
        edge_cnt = 0;
        for (int i = 0; i <= N; ++i) {
            f[i] = i;
        }
        for (int i = 0; i < N * (N - 1) / 2; ++i) {
            scanf("%d%d%d", &a, &b, &w);
            edge[edge_cnt].u = a - 1;
            edge[edge_cnt].v = b - 1;
            edge[edge_cnt].cost = w;
            edge_cnt++;
        }
        int res = kruskal();
        cout << res << endl;
    }
    return 0;
};

#endif
