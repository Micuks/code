#ifndef _t6pd_20200111_
#define _t6pd_20200111_
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
int N, Q;
int f[MAXN];
int road[MAXN][MAXN];
struct Edge {
    int u, v, cost;
    bool operator<(const Edge &e) const { return cost < e.cost; };
    Edge(int u = 0, int v = 0, int cost = 0) : u(u), v(v), cost(cost) {}
} edge[MAXN * MAXN];
int edge_cnt = 0;

int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    return f[x] = find(f[x]);
}
int union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        return xroot;
    }
    return f[yroot] = xroot;
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
    int a, b;
    edge_cnt = 0;
    cin >> N;
    for (int i = 0; i <= N; ++i) {
        f[i] = i;
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            scanf("%d", &road[i][j]);
            if (j > i) {
                edge[edge_cnt].u = i;
                edge[edge_cnt].v = j;
                edge[edge_cnt].cost = road[i][j];
                ++edge_cnt;
            }
        }
    }
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        scanf("%d%d", &a, &b);
        union_set(a, b);
    }
    int res = kruskal();
    cout << res << endl;
    return 0;
};

#endif
