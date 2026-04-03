#ifndef _t11pc_20210622_
#define _t11pc_20210622_
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

#define INF 0x3F3F3F3F
const int MAXN = 1 << 8;
const int MAXM = 1 << 8;
const int MAXK = 1 << 8;
const int MAXLEN = 1 << 5;
int n, m, k;

typedef char dtype[MAXN][MAXLEN];
dtype plugs, devices, device_plugs, adaptorA, adaptorB;

struct Edge {
    int to, cap, next;
} edges[MAXN * MAXN * MAXN];
int head[MAXN * 4], edge_cnt;
int curr_head[MAXN * 4], dfn[MAXN * 4];
void add_edge(int u, int v, int c)
{
    edges[edge_cnt].cap = c;
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}
void init_graph()
{
    memset(head, -1, sizeof(head));
    memset(curr_head, -1, sizeof(curr_head));
    edge_cnt = 0;
}

int get_sidx() { return n + m + k + 1; }
int get_tidx() { return get_sidx() + 1; }
int get_device_idx(int didx) { return didx; }
int get_adaptor_idx(int aidx) { return aidx + m; }
int get_plug_idx(int pidx) { return pidx + m + k; }

void debug_print()
{
    printf("(%d) idx for plugs:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d(%d),", i, get_plug_idx(i + 1));
    }
    printf("\n(%d) idx for devices:\n", m);
    for (int i = 0; i < m; ++i) {
        printf("%d(%d),", i, get_device_idx(i + 1));
    }
    printf("\n(%d) idx for adaptors:\n", k);
    for (int i = 0; i < k; ++i) {
        printf("%d(%d),", i, get_adaptor_idx(i + 1));
    }
    printf("\nidx for sidx, tidx:\n");
    printf("%d, %d\n", get_sidx(), get_tidx());
    for (int u = 0; u <= get_tidx(); ++u) {
        printf("%d(u) to: ", u);
        for (int h = head[u]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            printf("%d(%d) ", e.to, e.cap);
        }
        printf("\n");
    }
}
void connect_device2plug()
{
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (string(device_plugs[i]) == plugs[j]) {
                int plug_idx = get_plug_idx(j + 1);
                int device_idx = get_device_idx(i + 1);
                add_edge(device_idx, plug_idx, 1);
                add_edge(plug_idx, device_idx, 0);
            }
        }
    }
}
void connect_device2adaptor()
{
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            if (string(device_plugs[i]) == adaptorA[j]) {
                int device_idx = get_device_idx(i + 1);
                int adaptor_idx = get_adaptor_idx(j + 1);
                add_edge(device_idx, adaptor_idx, 1);
                add_edge(adaptor_idx, device_idx, 0);
            }
        }
    }
}
void connect_adaptor2adaptor()
{
    for (int i = 0; i < k; ++i) {
        for (int j = i + 1; j < k; ++j) {
            if (string(adaptorB[i]) == adaptorA[j] || string(adaptorA[i]) == adaptorB[j]) {
                int a1idx = get_adaptor_idx(i + 1);
                int a2idx = get_adaptor_idx(j + 1);
                add_edge(a1idx, a2idx, INF);
                add_edge(a2idx, a1idx, INF);
            }
        }
    }
}
void connect_adaptor2plug()
{
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            if (string(adaptorB[i]) == plugs[j]) {
                int plug_idx = get_plug_idx(j + 1);
                int adaptor_idx = get_adaptor_idx(i + 1);
                add_edge(plug_idx, adaptor_idx, INF);
                add_edge(adaptor_idx, plug_idx, INF);
            }
        }
    }
}

void connect_st_point()
{
    int sidx = get_sidx();
    int tidx = get_tidx();
    for (int i = 0; i < n; ++i) {
        int plug_idx = get_plug_idx(i + 1);
        add_edge(plug_idx, tidx, 1);
        add_edge(tidx, plug_idx, 0);
    }
    for (int i = 0; i < m; ++i) {
        int device_idx = get_device_idx(i + 1);
        add_edge(sidx, device_idx, 1);
        add_edge(device_idx, sidx, 0);
    }
}

void build_graph()
{
    init_graph();
    _DEBUG_CMD(printf("after init_graph\n"));
    connect_device2plug();
    _DEBUG_CMD(printf("after d2p\n"));
    connect_device2adaptor();
    _DEBUG_CMD(printf("after d2a\n"));
    connect_adaptor2adaptor();
    _DEBUG_CMD(printf("after a2a\n"));
    connect_adaptor2plug();
    _DEBUG_CMD(printf("after a2p\n"));
    connect_st_point();
    _DEBUG_CMD(printf("after st point\n"));
    _DEBUG_CMD(debug_print());
}

bool bfs(int s, int t)
{
    memset(dfn, -1, sizeof(dfn));
    queue<int> q;
    dfn[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int h = head[u]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            int v = e.to;
            if (dfn[v] == -1 && e.cap > 0) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
            }
        }
    }

    if (dfn[t] != -1) {
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
    for (int &h = curr_head[u]; h != -1; h = edges[h].next) {
        int v = edges[h].to;
        Edge &e = edges[h];
        Edge &revE = edges[h ^ 0x01];
        if (dfn[v] > dfn[u] && e.cap > 0) {
            int d = dfs(v, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                revE.cap += d;
                return d;
            }
        }
    }
    return 0;
}
int dinic()
{
    int flow = 0;
    int sidx = get_sidx();
    int tidx = get_tidx();
    while (bfs(sidx, tidx)) {
        _DEBUG_CMD(printf("get bfs done\n"));
        flow += dfs(sidx, tidx, INF);
    }
    return m - flow;
}

int main(int argc, char **argv)
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", plugs[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%s %s", devices[i], device_plugs[i]);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        scanf("%s %s", adaptorA[i], adaptorB[i]);
        _DEBUG_CMD(printf("aa:%s ab:%s\n", adaptorA[i], adaptorB[i]););
    }
    _DEBUG_CMD(printf("after getting input\n"));
    build_graph();
    _DEBUG_CMD(printf("after building graph\n"));
    int ret = dinic();
    _DEBUG_CMD(printf("after running dinic\n"));
    printf("%d\n", ret);
    return 0;
};

#endif
