#ifndef _t6pg_20200111_
#define _t6pg_20200111_
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

const int MAXN = 1024;
int N, S, P, D;
int xi[MAXN], yi[MAXN];
// float dist[MAXN][MAXN];
struct Edge {
    int u, v;
    float cost;
    Edge(int u = 0, int v = 0, float cost = 0) : u(u), v(v), cost(cost) {}
    bool operator<(const Edge &e) const { return cost < e.cost; };
} edge[MAXN * MAXN];
int edge_cnt = 0;
int f[MAXN];

#define EUCLIDEAN_DIST(x, y) sqrt((x) * (x) + (y) * (y))

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

float kruskal()
{
    vector<float> res;
    res.reserve(P);
    sort(edge, edge + edge_cnt);
    for (int i = 0; i <= P; ++i) {
        f[i] = i;
    }
    for (int i = 0; i < edge_cnt; ++i) {
        const Edge &e = edge[i];
        if (find(e.u) != find(e.v)) {
            union_set(e.u, e.v);
            res.push_back(e.cost);
        }
    }
    return res[P - S - 1];
}

int main(int argc, char **argv)
{
    cin >> N;
    while (N--) {
        cin >> S >> P;
        edge_cnt = 0;
        for (int i = 0; i < P; ++i) {
            scanf("%d%d", &xi[i], &yi[i]);
        }
        for (int i = 0; i < P; ++i) {
            for (int j = 0; j < i; ++j) {
                edge[edge_cnt].u = i;
                edge[edge_cnt].v = j;
                edge[edge_cnt].cost = EUCLIDEAN_DIST(float(xi[i]) - xi[j], float(yi[i]) - yi[j]);
                ++edge_cnt;
            }
        }
        float res = kruskal();
        printf("%.2f\n", res);
    }
    return 0;
};

#endif
