#ifndef _t11pf_20210627_
#define _t11pf_20210627_
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
#include <stack>
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

const int INF = 0x3F3F3F3F;
const int MAXN = 1 << 8;
int n, np, nc, m;

struct Edge {
    int to, cap, next;
} edges[MAXN * MAXN + 4];
int head[MAXN], ec;
int g[MAXN][MAXN];

void add_edge(int u, int v, int cap)
{
    edges[ec].to = v;
    edges[ec].cap = cap;
    edges[ec].next = head[u];
    head[u] = ec++;
}
void init_graph()
{
    ec = 0;
    memset(head, -1, sizeof(head));
    memset(g, -1, sizeof(g));
}

int sidx, tidx;
void build_graph() {}

int dfn[MAXN], curr_head[MAXN];
bool bfs()
{
    memset(dfn, -1, sizeof(dfn));

    dfn[sidx] = 0;
    std::queue<int> q;
    q.push(sidx);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        /*
        for (int h = head[u]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            int v = e.to;
            if (e.cap > 0 && dfn[v] == -1) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
            }
        }
        */
        for (int v = 0; v <= tidx; ++v) {
            if (g[u][v] > 0 && dfn[v] == -1) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
            }
        }
    }

    if (dfn[tidx] != -1) {
        memcpy(curr_head, head, sizeof(curr_head));
        return true;
    }
    return false;
}
int dfs(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    /*
    for (int &h = curr_head[u]; h != -1; h = edges[h].next) {
        Edge &e = edges[h];
        Edge &revE = edges[h ^ 0x01];
        int v = e.to;
        if (dfn[v] > dfn[u] && e.cap > 0) {
            int d = dfs(v, t, min(e.cap, f));
            if (d > 0) {
                e.cap -= d;
                revE.cap += d;
                return d;
            }
        }
    }
    */
    for (int v = 0; v <= tidx; ++v) {
        if (dfn[v] > dfn[u] && g[u][v] > 0) {
            int d = dfs(v, t, min(g[u][v], f));
            if (d > 0) {
                g[u][v] -= d;
                g[v][u] += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic()
{
    int flow = 0;
    while (bfs()) {
        flow += dfs(sidx, tidx, INF);
    }
    return flow;
}

int main(int argc, char **argv)
{
    int u, v, z;
    while (~scanf("%d%d%d%d", &n, &np, &nc, &m)) {
        init_graph();
        sidx = n;
        tidx = sidx + 1;
        for (int i = 0; i < m; ++i) {
            //(u,v)z z = lmax(u,v)
            scanf(" (%d,%d)%d", &u, &v, &z);
            // add_edge(u, v, z);
            // add_edge(v, u, 0);
            if (g[u][v] == -1) {
                g[u][v] = z;
                g[v][u] = 0;
            }
            else {
                g[u][v] += z;
            }
        }
        for (int i = 0; i < np; ++i) {
            //(u)z u for power station, z for pmax(u)
            scanf(" (%d)%d", &u, &z);
            // add_edge(sidx, u, z);
            // add_edge(u, sidx, 0);
            g[sidx][u] = z;
            g[u][sidx] = 0;
        }
        for (int i = 0; i < nc; ++i) {
            //(u)z u for consuer, z for cmax(u)
            scanf(" (%d)%d", &u, &z);
            // add_edge(u, tidx, z);
            // add_edge(tidx, u, 0);
            g[u][tidx] = z;
            g[tidx][u] = 0;
        }
        _DEBUG_CMD(printf("get a new round, n:%d np:%d nc:%d m:%d\n", n, np, nc, m));
        build_graph();

        int ret = dinic();
        printf("%d\n", ret);
    };
    return 0;
};

#endif
