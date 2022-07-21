#ifndef _t11po_20210708_
#define _t11po_20210708_
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

const int MAXN = 1 << 10;
const int MAXM = 1 << 17;
const int INF = 0x3F3F3F3F;
int t, n, m, A, B, a[MAXM], b[MAXM], c[MAXM];

struct Edge {
    int to, cap, next;
} edge[MAXM << 1];
int head[MAXN], dfn[MAXN], ec, sidx, tidx, dist_adv[MAXN], dist_rev[MAXN];
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
void build_graph() {}

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

struct Node {
    int u, dist;
    bool operator<(const Node &n) const { return dist > n.dist; }
};
void dijkstra(int s, int *dist_arr)
{
    int vis[MAXN];
    memset(vis, 0, sizeof(vis));
    memset(dist_arr, 0x3F, sizeof(dist_adv));
    Node start = Node{s, 0};
    dist_arr[s] = 0;
    std::priority_queue<Node> pq;
    pq.push(start);

    while (!pq.empty()) {
        Node n = pq.top();
        pq.pop();
        int u = n.u;
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int h = head[u]; h != -1; h = edge[h].next) {
            Edge &e = edge[h];
            int v = e.to;
            if (vis[v] == 0 && dist_arr[v] > dist_arr[u] + e.cap) { // use cap as dist
                dist_arr[v] = dist_arr[u] + e.cap;
                pq.push(Node{v, dist_arr[v]});
            }
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

void build_graph_fwd()
{
    init_graph();
    for (int i = 0; i < m; ++i) {
        add_edge(a[i], b[i], c[i]);
    }
}
void build_graph_bckwd()
{
    init_graph();
    for (int i = 0; i < m; ++i) {
        add_edge(b[i], a[i], c[i]);
    }
}
void build_graph_dinic()
{
    init_graph();

    sidx = 0, tidx = n + 1;
    add_edge(sidx, A, INF);
    add_edge(A, sidx, 0);

    for (int i = 0; i < m; ++i) {
        if (dist_adv[a[i]] + dist_rev[b[i]] + c[i] == dist_adv[B]) {
            add_edge(a[i], b[i], 1);
            add_edge(b[i], a[i], 0);
        }
    }

    add_edge(B, tidx, INF);
    add_edge(tidx, B, 0);
}
int main(int argc, char **argv)
{
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", a + i, b + i, c + i);
        }
        scanf("%d%d", &A, &B);
        _DEBUG_CMD(printf("get input done\n"));
        build_graph_fwd();
        dijkstra(A, dist_adv);
        _DEBUG_CMD(printf("dijkstra fwd done\n"));
        build_graph_bckwd();
        dijkstra(B, dist_rev);
        _DEBUG_CMD(printf("dijkstra bckwd done\n"));
        build_graph_dinic();
        int ret = dinic();
        _DEBUG_CMD(printf("dinic done\n"));
        printf("%d\n", ret);
    }
    return 0;
};

#endif
