#ifndef _t11pn_20210708_
#define _t11pn_20210708_
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

const int MAXN = 1 << 7;
const int INF = 0x3F3F3F3F;
int conn[MAXN][MAXN];
int t, n, m, f;

int fa[MAXN];

void join_conn(int root, int son)
{
    for (int i = 1; i <= n; ++i) {
        conn[root][i] |= conn[son][i];
    }
}
int find_union(int x)
{
    if (fa[x] == x) {
        return x;
    }
    int res = find_union(fa[x]);
    fa[x] = res;
    join_conn(fa[x], x);
    return res;
    // return fa[x] == x ? x : fa[x] = find_union(fa[x]);
}
void union_set(int x, int y)
{
    int px = find_union(x);
    int py = find_union(y);
    if (px != py) {
        join_conn(px, fa[py]);
        fa[py] = px;
    }
}

struct Edge {
    int to, cap, next;
} edge[MAXN * MAXN * 10];
int head[MAXN * MAXN], dfn[MAXN * MAXN], ec, sidx, tidx;
void add_edge(int u, int v, int cap)
{
    edge[ec] = Edge{v, cap, head[u]};
    head[u] = ec++;
}
void init_graph()
{
    ec = 0;
    memset(head, -1, sizeof(head));
}
void build_graph(int k)
{
    sidx = 0, tidx = 1;
    for (int i = 0; i < n; ++i) {
        int gid = i + 2;
        int bid = i + n + 2;
        int guid = find_union(i + 1);
        _DEBUG_CMD(printf("gid: %d, guid: %d bid: ", i + 1, guid));
        for (int j = 0; j < n; ++j) {
            int bid = j + n + 2;
            if (conn[guid][j + 1]) {
                _DEBUG_CMD(printf("%d ", j + 1));
                add_edge(gid, bid, 1);
                add_edge(bid, gid, 0);
            }
        }
        _DEBUG_CMD(printf("\n"));
        add_edge(sidx, gid, k);
        add_edge(gid, sidx, 0);
        add_edge(bid, tidx, k);
        add_edge(tidx, bid, 0);
    }
}
void init()
{
    // init_graph();
    memset(conn, 0, sizeof(conn));
    // memset(fa, -1, sizeof(fa));
    for (int i = 0; i < MAXN; ++i) {
        fa[i] = i;
    }
}

void debug_node(int u)
{
    printf("u:%d ", u);
    for (int h = head[u]; h != -1; h = edge[h].next) {
        printf("(%d,%d) ", edge[h].to, edge[h].cap);
    }
    printf("\n");
}
void debug_graph()
{
    for (int i = 0; i < n + (1 << m) + 2; ++i) {
        if (head[i] != -1) {
            debug_node(i);
        }
    }
}

bool bfs(int s, int t)
{
    memset(dfn, -1, sizeof(dfn));
    std::queue<int> q;
    dfn[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int h = head[u]; h != -1; h = edge[h].next) {
            Edge &e = edge[h];
            int v = edge[h].to;
            if (dfn[v] == -1 && e.cap > 0) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
            }
        }
    }
    return dfn[t] != -1;
}
int dfs(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    int ret = 0;
    for (int h = head[u]; h != -1; h = edge[h].next) {
        Edge &e = edge[h];
        Edge &revE = edge[h ^ 0x01];
        int v = e.to;
        if (dfn[v] == dfn[u] + 1 && e.cap > 0) {
            int d = dfs(v, t, min(e.cap, f - ret));
            if (d > 0) {
                e.cap -= d;
                revE.cap += d;
                ret += d;
                if (ret == f) {
                    break;
                }
            }
        }
    }
    if (ret == 0) {
        dfn[u] = -1;
    }
    return ret;
}
int dinic()
{
    int maxflow = 0;
    while (bfs(sidx, tidx)) {
        maxflow += dfs(sidx, tidx, INF);
    }
    return maxflow;
}

int main(int argc, char **argv)
{
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d%d%d", &n, &m, &f);
        int a, b;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &a, &b);
            conn[a][b] = 1;
        }
        for (int i = 0; i < f; ++i) {
            scanf("%d%d", &a, &b);
            union_set(a, b);
        }
        int k_ub = n + 1, k_lb = 0, k = (k_ub + k_lb) / 2;
        while (k_ub > k_lb) {
            k = (k_ub + k_lb) / 2 + 1;
            init_graph();
            build_graph(k);
            int ret = dinic();
            if (ret == k * n) {
                k_lb = k;
            }
            else {
                k_ub = k - 1;
                k -= 1;
            }
            _DEBUG_CMD(printf("ub:%d lb:%d k:%d n:%d ret:%d succ:%d\n", k_ub, k_lb, k, n, ret,
                              (int) (ret == k * n)));
        }
        printf("%d\n", k_lb);
    }
    return 0;
};

#endif
