#ifndef _t11pi_20210704_
#define _t11pi_20210704_
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

typedef long long ll;
const int MAXN = 1 << 9;
const int MAXM = 1e5 + 3;
const int INF = 0x3F3F3F3F;

struct Edge {
    int to, cap, next;
} edge[MAXM];
int head[MAXN], ec, dfn[MAXN];
int price[MAXN];
int n, m, s, d;
int sidx, tidx;

void init_graph()
{
    ec = 0;
    memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, int cap)
{
    edge[ec] = Edge{v, cap, head[u]};
    head[u] = ec++;
}
void build_graph()
{
    sidx = 2 * s;
    tidx = 2 * d + 1;
}

bool bfs(int s, int t)
{
    std::queue<int> q;
    memset(dfn, -1, sizeof(dfn));
    q.push(s);
    dfn[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int h = head[u]; h != -1; h = edge[h].next) {
            int v = edge[h].to;
            Edge e = edge[h];
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
    int res = 0;
    for (int h = head[u]; h != -1; h = edge[h].next) {
        int v = edge[h].to;
        Edge &e = edge[h];
        Edge &revE = edge[h ^ 0x01];
        if (dfn[v] == dfn[u] + 1 && e.cap > 0) {
            int d = dfs(v, t, min(f - res, e.cap));
            e.cap -= d;
            revE.cap += d;
            res += d;
            if (res == f) {
                break;
            }
        }
    }
    if (res == 0) {
        dfn[u] = -1;
    }
    return res;
}

ll dinic()
{
    ll maxflow = 0;
    while (bfs(sidx, tidx)) {
        maxflow += dfs(sidx, tidx, INF);
    }
    return maxflow;
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d", &n, &m)) {
        scanf("%d%d", &s, &d);
        init_graph();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &price[i]);
            add_edge(i * 2, i * 2 + 1, price[i]);
            add_edge(i * 2 + 1, i * 2, 0);
        }
        int from, to;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &from, &to);
            int fin = 2 * from, fout = 2 * from + 1;
            int tin = 2 * to, tout = 2 * to + 1;
            // add_edge(2 * from + 1, 2 * to, INF);
            // add_edge(2 * to, 2 * from + 1, 0);
            // add_edge(2 * to + 1, 2 * from, INF);
            // add_edge(2 * from, 2 * to + 1, 0);
            add_edge(fout, tin, INF);
            add_edge(tin, fout, 0);
            add_edge(tout, fin, INF);
            add_edge(fin, tout, 0);
        }
        build_graph();
        ll res = dinic();
        printf("%lld\n", res);
    }
    return 0;
};

#endif
