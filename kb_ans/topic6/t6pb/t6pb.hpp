#ifndef _t6pb_20200110_
#define _t6pb_20200110_
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

const int MAXN = 65536;
int f[MAXN];
int P, R;

struct Edge {
    int u, v, cost;
    bool operator<(const Edge &e) const { return cost < e.cost; }
    Edge(int u = 0, int v = 0, int cost = 0) : u(u), v(v), cost(cost) {}
} edge[MAXN];
int edge_cnt;

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
        return -1;
    }
    return f[yroot] = xroot;
}
void init()
{
    edge_cnt = 0;
    for (int i = 0; i < MAXN; ++i) {
        f[i] = i;
    }
}

int kruskal()
{
    int min_cost = 0;
    sort(edge, edge + edge_cnt);
    for (int i = 0; i < edge_cnt; ++i) {
        const Edge &e = edge[i];
        if (find(e.u) != find(e.v)) {
            union_set(e.u, e.v);
            min_cost += e.cost;
        }
    }
    return min_cost;
}

int main(int argc, char **argv)
{
    while (cin >> P >> R) {
        init();
        for (int i = 0; i < R; ++i, ++edge_cnt) {
            scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].cost);
        }
        int res = kruskal();
        cout << res << endl;
    }
    return 0;
};

#endif
