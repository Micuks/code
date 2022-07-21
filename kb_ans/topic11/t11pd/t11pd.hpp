#ifndef _t11pd_20210623_
#define _t11pd_20210623_
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
// const int MAXN = 1 << 7;
const int MAXN = 1 << 13;
const int MAXD = 1 << 8;
int n, m;
int man_cnt = 0;
int house_cnt = 0;
int sid, tid;
char cmap[MAXN][MAXN];

struct Edge {
    int to, cap, cost, next;
} edges[MAXN * MAXN];
int head[MAXN << 2], edge_cnt;
int curr_head[MAXN << 2], dfn[MAXN << 2];
int prev_arr[MAXN << 2], cost_dist[MAXN << 2];

void add_edge(int u, int v, int capacity, int cost)
{
    edges[edge_cnt].to = v;
    edges[edge_cnt].cap = capacity;
    edges[edge_cnt].cost = cost;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void init_graph()
{
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
}

void print_node(int u)
{
    printf("u:%d, to(cap,cost): ", u);
    for (int h = head[u]; h != -1; h = edges[h].next) {
        const Edge &e = edges[h];
        printf("%d(%d,%d) ", e.to, e.cap, e.cost);
    }
    printf("\n");
}
void print_graph()
{
    for (int i = 1; i <= tid; ++i) {
        print_node(i);
    }
}

void build_graph()
{
    init_graph();
    man_cnt = 0;
    house_cnt = 0;
    int mx[MAXN], my[MAXN], hx[MAXN], hy[MAXN];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (cmap[i][j] == 'm') {
                mx[man_cnt] = i;
                my[man_cnt] = j;
                ++man_cnt;
            }
            else if (cmap[i][j] == 'H') {
                hx[house_cnt] = i;
                hy[house_cnt] = j;
                ++house_cnt;
            }
        }
    }
    assert(man_cnt == house_cnt);
    sid = man_cnt + house_cnt + 1;
    tid = sid + 1;
    for (int i = 0; i < man_cnt; ++i) {
        for (int j = 0; j < house_cnt; ++j) {
            int mid = i + 1;
            int hid = j + man_cnt + 1;
            // int cap = MAXD - (abs(mx[i] - hx[j]) + abs(my[i] - hy[j]));
            int cost = (abs(mx[i] - hx[j]) + abs(my[i] - hy[j]));
            _DEBUG_CMD(printf("man[%d](%d,%d) - house[%d](%d,%d) = %d\n", i, mx[i], my[i], j, hx[j],
                              hy[j], cost));
            add_edge(mid, hid, 1, cost);
            add_edge(hid, mid, 0, -cost);
        }
    }
    for (int i = 0; i < man_cnt; ++i) {
        int mid = i + 1;
        add_edge(sid, mid, 1, 0);
        add_edge(mid, sid, 0, 0);
    }
    for (int i = 0; i < house_cnt; ++i) {
        int hid = i + 1 + man_cnt;
        add_edge(hid, tid, 1, 0);
        add_edge(tid, hid, 0, 0);
    }
}

bool bfs(int sidx, int tidx)
{
    memset(dfn, -1, sizeof(dfn));
    dfn[sidx] = 0;
    queue<int> q;
    q.push(sidx);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int h = head[u]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            int v = e.to;
            if (dfn[v] < 0 && e.cap > 0) {
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
char inq[MAXN << 2];
bool spfa(int sidx, int tidx)
{
    memset(cost_dist, 0x3F, sizeof(cost_dist));
    memset(prev_arr, -1, sizeof(prev_arr));
    prev_arr[sidx] = 0;
    queue<int> q;
    q.push(sidx);
    cost_dist[sidx] = 0;

    inq[sidx] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int h = head[u]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            int v = e.to;
            if (e.cap > 0 && cost_dist[v] > cost_dist[u] + e.cost) {
                cost_dist[v] = cost_dist[u] + e.cost;
                prev_arr[v] = u;
                if (inq[v] == 0) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    if (cost_dist[tidx] != INF) {
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
    return 0;
}
int visit[MAXN << 2];
int dfs2(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    visit[u] = 1;
    int total_flow = 0;
    // for (int &h = curr_head[u]; h != -1; h = edges[h].next) {
    for (int h = curr_head[u]; h != -1; h = edges[h].next) {
        Edge &e = edges[h];
        Edge &revE = edges[h ^ 0x01];
        int v = e.to;
        if (e.cap > 0 && visit[v] == 0 && cost_dist[v] == cost_dist[u] + e.cost) {
            int d = dfs2(v, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                revE.cap += d;
                total_flow += d;
                // return d;
            }
        }
    }
    visit[u] = 0;
    return total_flow;
}

int dfs3(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
}

int dinic()
{
    int flow = 0;
    while (bfs(sid, tid)) {
        flow += dfs(sid, tid, 0x3F3F3F3F);
    }
    return man_cnt * (MAXD + 2) - flow;
}

int find_edge(int u, int v)
{
    int ret = -1;
    for (int h = head[u]; h != -1; h = edges[h].next) {
        Edge &e = edges[h];
        if (e.to == v) {
            ret = h;
            break;
        }
    }
    return ret;
}
int mincost_dinic()
{
    static int scnt = 0;
    int maxflow = 0;
    int mincost = 0;
    memset(visit, 0, sizeof(visit));
    memset(inq, 0, sizeof(inq));
    while (spfa(sid, tid)) {

        // int flow = dfs2(sid, tid, INF);
        int fee = cost_dist[tid];
        //*
        int flow = INF;
        for (int this_id = tid, prev_id = prev_arr[this_id]; prev_id != -1;
             this_id = prev_id, prev_id = prev_arr[this_id]) {
            int eid = find_edge(prev_id, this_id);
            if (eid != -1) {
                flow = min(flow, edges[eid].cap);
            }
        }
        for (int this_id = tid, prev_id = prev_arr[this_id]; prev_id != -1;
             this_id = prev_id, prev_id = prev_arr[this_id]) {
            int eid = find_edge(prev_id, this_id);
            if (eid != -1) {
                edges[eid].cap -= flow;
                edges[eid ^ 0x01].cap += flow;
            }
        }
        //*/
        maxflow += flow;
        mincost += fee * flow;
        _DEBUG_CMD(printf("scnt:%d flow:%d fee:%d\n", scnt++, flow, fee));
    }
    return mincost;
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d", &n, &m) && n && m) {
        for (int i = 0; i < n; ++i) {
            scanf("%s", cmap[i]);
        }
        build_graph();
        // int res = dinic();
        int res = mincost_dinic();
        printf("%d\n", res);
    }
    return 0;
};

#endif
