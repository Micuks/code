#ifndef _t11pj_20210704_
#define _t11pj_20210704_
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
const int MAXN = 1 << 6;
const int MAXM = 1 << 9;
const ll INF = 0x3F3F3F3F3F3F3F3F;
int n, m;

struct Edge {
    int from, to, cap, next;
} edge[MAXM * 10];
int head[MAXN], ec, dfn[MAXN], iscut[MAXN];
int sidx, tidx;

void init_graph()
{
    memset(head, -1, sizeof(head));
    ec = 0;
}
void build_graph()
{
    sidx = 1;
    tidx = 2;
}
void add_edge(int u, int v, int cap)
{
    edge[ec] = Edge{u, v, cap, head[u]};
    head[u] = ec++;
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
            int v = e.to;
            if (e.cap > 0 && dfn[v] == -1) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
            }
        }
    }
    return dfn[t] != -1;
}
ll min_cost;
int eidx;
ll dfs(int u, int t, ll f)
{
    if (u == t) {
        return f;
    }
    ll ret = 0;
    for (int h = head[u]; h != -1; h = edge[h].next) {
        Edge &e = edge[h];
        Edge &revE = edge[h ^ 0x01];
        int v = e.to;
        if (e.cap > 0 && dfn[v] == dfn[u] + 1) {
            int d = dfs(v, t, min(f - ret, (ll) e.cap));
            if (d > 0) {
                e.cap -= d;
                revE.cap += d;
                ret += d;
                if (e.cap == 0) {
                    ll this_cost = revE.cap / 2;
                    if (this_cost < min_cost) {
                        min_cost = this_cost;
                        eidx = h;
                    }
                }
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
ll dinic()
{
    ll maxflow = 0;
    memset(iscut, 0, sizeof(iscut));
    while (bfs(sidx, tidx)) {
        min_cost = INF;
        maxflow += dfs(sidx, tidx, INF);
        iscut[eidx] = 1;
    }
    return maxflow;
}
void bfs_group(int s)
{
    memset(dfn, 0, sizeof(dfn));
    std::queue<int> q;
    q.push(s);
    dfn[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int h = head[u]; h != -1; h = edge[h].next) {
            Edge &e = edge[h];
            int v = e.to;
            if (e.cap == 0) {
                continue;
            }
            if (dfn[v] == 0) {
                dfn[v] = 1;
                q.push(v);
            }
        }
    }
}
void bfs_print(int s)
{
    for (int i = 0; i <= m * 2; ++i) {
        Edge &e = edge[i];
        int u = e.from;
        int v = e.to;
        if (dfn[u] != dfn[v] && e.cap == 0) {
            printf("%d %d\n", u, v);
        }
    }
}
void debug_print(int u)
{
    printf("u:%d v,cap:", u);
    for (int h = head[u]; h != -1; h = edge[h].next) {
        printf("(%d,%d) ", edge[h].to, edge[h].cap);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int a, b, c;
    while (~scanf("%d%d", &n, &m) && n && m) {
        init_graph();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c);
            add_edge(b, a, c);
        }
        build_graph();
        ll ret = dinic();
        // printf("%lld\n", ret);
        bfs_group(sidx);
        bfs_print(sidx);
        /*
        for (int u = 1; u <= n; ++u) {
            for (int h = head[u]; h != -1; h = edge[h].next) {
                Edge &e = edge[h];
                int v = e.to;
                if (e.cap == 0) {
                    // an edge cannot be augmented belongs to minimum cut
                    printf("%d %d\n", u, v);
                }
            }
        }

        //*/
        /*
        for (int i = 0; i < m * 2; ++i) {
            if (iscut[i]) {
                printf("%d %d\n", edge[i].from, edge[i].to);
            }
        }
        */

        printf("\n");
    }
    return 0;
};

#endif
