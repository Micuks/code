#ifndef _t4pf_20191220_
#define _t4pf_20191220_
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

const int MAXE = 1e5 + 5;
const int MAXV = 512;
struct Edge {
    int u, v, next, val;
    Edge(int u, int v, int next, int val) : u(u), v(v), next(next), val(val) {}
    Edge() {}
} edge[MAXE];
int edge_cnt = 0;
int head[MAXV];
int F, N, M, W;
void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(int) * MAXV);
}
void add_edge(int u, int v, int val)
{
    edge[edge_cnt].next = head[u];
    edge[edge_cnt].u = u;
    edge[edge_cnt].v = v;
    edge[edge_cnt].val = val;
    head[u] = edge_cnt++;
}

bool bellman_ford()
{
    int d[MAXV];
    memset(d, 0x3F, sizeof(int) * MAXV);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < edge_cnt; ++j) {
            const Edge &e = edge[j];
            if (d[e.v] > d[e.u] + e.val) {
                d[e.v] = d[e.u] + e.val;
                if (i == N - 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    cin >> F;
    for (int i = 0; i < F; ++i) {
        int s, e, t;
        init();
        cin >> N >> M >> W;
        for (int j = 0; j < M; ++j) {
            scanf("%d%d%d", &s, &e, &t);
            add_edge(s, e, t);
            add_edge(e, s, t);
        }
        for (int j = 0; j < W; ++j) {
            scanf("%d%d%d", &s, &e, &t);
            add_edge(s, e, -1 * t);
        }
        bool res = bellman_ford();
        if (res) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
};

#endif
