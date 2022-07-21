#ifndef _t11pm_20210707_
#define _t11pm_20210707_
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

const int MAXN = 1e5 + 3;
const int MAXM = 1 << 4;
const int INF = 0x3F3F3F3F;
int n, m;
int match[MAXN][MAXM], pcap[MAXM], mcnt[1 << 10];

struct Edge {
    int to, cap, next;
} edge[MAXN << 2];
int head[MAXN << 1], ec, dfn[MAXN << 1];
const int sidx = 0, tidx = 1;

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

int m2idx(int ma[])
{
    int ret = 0;
    for (int i = 0; i < m; ++i) {
        ret = (ret << 1) + ma[i];
    }
    _DEBUG_CMD({
        for (int i = 0; i < m; ++i) {
            printf("%d", ma[i]);
        }
    });
    return ret;
}
void build_graph()
{
    memset(mcnt, 0, sizeof(mcnt));
    for (int i = 0; i < n; ++i) {
        ++mcnt[m2idx(match[i])];
    }
    for (int i = 0; i < (1 << m); ++i) {
        int pid = i + 2;
        add_edge(sidx, pid, mcnt[i]);
        add_edge(pid, sidx, 0);

        for (int j = 0; j < m; ++j) {
            int sid = j + (1 << m) + 2;
            if (i & (1 << j)) {
                add_edge(pid, sid, mcnt[i]);
                add_edge(sid, pid, 0);
            }
        }
    }

    /*
    for (int i = 0; i < n; ++i) {
        int pid = i + 2;

        add_edge(sidx, pid, 1);
        add_edge(pid, sidx, 0);
        for (int j = 0; j < m; ++j) {
            int sid = j + n + 2;
            add_edge(pid, sid, match[i][j]);
            add_edge(sid, pid, 0);
        }
    }
    */

    for (int i = 0; i < m; ++i) {
        int sid = i + (1 << m) + 2;
        add_edge(sid, tidx, pcap[i]);
        add_edge(tidx, sid, 0);
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
    while (~scanf("%d%d", &n, &m)) {
        init_graph();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &match[i][j]);
            }
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d", &pcap[i]);
        }
        build_graph();
        int ret = dinic();
        if (ret == n) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
};

#endif
