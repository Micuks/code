#ifndef _t6ph_20200112_
#define _t6ph_20200112_
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
int N, M;
int xi[MAXN], yi[MAXN];
int f[MAXN];
struct Edge {
    int u, v;
    float cost;
    bool operator<(const Edge &e) const { return cost < e.cost; };
    Edge(int u = 0, int v = 0, float cost = 0) : u(u), v(v), cost(cost) {}
} edge[MAXN * MAXN / 2];
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
        return 0;
    }
    f[yroot] = xroot;
    return 1;
}

int gp_cnt = 0;

void kruskal(vector<int> &ori, vector<int> &dst)
{
    ori.clear();
    ori.reserve(N);
    dst.clear();
    dst.reserve(N);
    sort(edge, edge + edge_cnt);
    for (int i = 0; i < edge_cnt && gp_cnt < N - 1; ++i) {
        const Edge &e = edge[i];
        if (find(e.u) != find(e.v)) {
            ori.push_back(e.u);
            dst.push_back(e.v);
            union_set(e.u, e.v);
            ++gp_cnt;
        }
    }
}

#define EUCLIDEAN_DIST(x, y) sqrt((x) * (x) + (y) * (y))

int main(int argc, char **argv)
{
    int a, b;
    cin >> N;
    for (int i = 0; i <= N; ++i) {
        f[i] = i;
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d%d", &xi[i], &yi[i]);
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j < i; ++j) {
            edge[edge_cnt].u = i;
            edge[edge_cnt].v = j;
            edge[edge_cnt].cost =
                EUCLIDEAN_DIST(float(xi[i - 1]) - xi[j - 1], float(yi[i - 1]) - yi[j - 1]);
            ++edge_cnt;
        }
    }
    cin >> M;
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &a, &b);
        if (union_set(a, b)) {
            ++gp_cnt;
        }
    }
    vector<int> ori;
    vector<int> dst;
    kruskal(ori, dst);
    for (int i = 0; i < ori.size(); ++i) {
        printf("%d %d\n", ori[i], dst[i]);
    }

    return 0;
};

#endif
