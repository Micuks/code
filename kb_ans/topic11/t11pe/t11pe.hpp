#if 0
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
const int N = 8024;
const int inf = 0x7fffffff;
struct Edge {
    int from, to, cap, flow, cost;
};
vector<Edge> edges;
vector<int> G[N];
int n, m;
int inq[N], p[N], d[N], a[N];

void AddEdge(int from, int to, int cap, int cost)
{
    Edge tp;
    tp.from = from, tp.to = to, tp.cap = cap, tp.flow = 0, tp.cost = cost;
    edges.push_back(tp);

    tp.from = to, tp.to = from, tp.cap = 0, tp.flow = 0, tp.cost = -cost;
    edges.push_back(tp);

    int g = edges.size();
    G[from].push_back(g - 2);
    G[to].push_back(g - 1);
}

int BellmanFord(int s, int t, int &flow, int &cost)
{
    int i, j, u;
    for (i = 0; i <= n + 1; i++)
        d[i] = inf;
    memset(inq, 0, sizeof(inq));
    d[s] = 0;
    inq[s] = 1;
    p[s] = 0;
    a[s] = inf;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        inq[u] = 0;
        for (i = 0; i < G[u].size(); i++) {
            Edge &e = edges[G[u][i]];
            if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                d[e.to] = d[u] + e.cost;
                p[e.to] = G[u][i];
                a[e.to] = min(a[u], e.cap - e.flow);
                if (!inq[e.to]) {
                    Q.push(e.to);
                    inq[e.to] = 1;
                }
            }
        }
    }
    if (d[t] == inf)
        return 0;
    flow += a[t];
    cost += d[t] * a[t];
    u = t;
    while (u != 0) {
        edges[p[u]].flow += a[t];
        edges[p[u] ^ 1].flow -= a[t];
        u = edges[p[u]].from;
    }
    return 1;
}

int Mincost(int s, int t)
{
    int flow = 0, cost = 0;
    while (BellmanFord(s, t, flow, cost))
        ;
    return cost;
}

int main()
{
    int s, t, flag, i, tn, tm, tk, u, v, c, ans, need[100][50], have[100][50], mp[50][100][100];
    int needs[50], haves[50];
    while (~scanf("%d%d%d", &tn, &tm, &tk)) {
        if (tn == 0 && tm == 0 && tk == 0)
            break;
        memset(needs, 0, sizeof(needs));
        memset(haves, 0, sizeof(haves));
        for (int i = 1; i <= tn; i++)
            for (int j = 0; j < tk; j++) {
                scanf("%d", &need[i][j]);
                needs[j] += need[i][j];
            }

        for (int i = 1; i <= tm; i++)
            for (int j = 0; j < tk; j++) {
                scanf("%d", &have[i][j]);
                haves[j] += have[i][j];
            }

        for (int pt = 0; pt < tk; pt++)
            for (int i = 1; i <= tn; i++)
                for (int j = 1; j <= tm; j++)
                    scanf("%d", &mp[pt][i][j]);

        flag = 1;
        for (int j = 0; j < tk; j++) {
            if (needs[j] > haves[j])
                flag = 0;
        }

        if (!flag) {
            printf("-1\n");
        }
        else {
            n = tn + tm + 2;
            s = 0;
            t = tn + tm + 1;
            ans = 0;
            for (int pt = 0; pt < tk; pt++) {
                edges.clear();
                for (int i = 0; i < N; i++)
                    G[i].clear();

                for (int i = 1; i <= tn; i++)
                    AddEdge(s, i, need[i][pt], 0);
                for (int i = 1; i <= tn; i++)
                    for (int j = 1; j <= tm; j++)
                        AddEdge(i, tn + j, need[i][pt], mp[pt][i][j]);

                for (int i = 1; i <= tm; i++)
                    AddEdge(tn + i, t, have[i][pt], 0);
                ans += Mincost(s, t);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
#else
#ifndef _t11pe_20210624_
#define _t11pe_20210624_
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
int price[MAXN][MAXN][MAXN];
int goods[MAXN][MAXN], supply[MAXN][MAXN], tg[MAXN], ts[MAXN];
int n, m, k;
int pred[MAXN], cdist[MAXN];

struct Edge {
    int to, cap, cost, next;
} edges[MAXN * MAXN];
int head[MAXN << 2], edge_cnt;

void add_edge(int u, int v, int cap, int cost)
{
    edges[edge_cnt].to = v;
    edges[edge_cnt].cap = cap;
    edges[edge_cnt].cost = cost;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void init_graph()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
}

const int sidx = 0, tidx = 1;

void print_node(int u)
{
    printf("node %d: to,cap,cost: ", u);
    for (int h = head[u]; h != -1; h = edges[h].next) {
        const Edge &e = edges[h];
        printf("%d,%d,%d ", e.to, e.cap == INF ? -1 : e.cap, e.cost);
    }
    printf("\n");
}
void print_graph()
{
    for (int i = 0; i <= n + m + 2; ++i) {
        print_node(i);
    }
}

void build_graph(int kn)
{
    for (int i = 0; i < n; ++i) {
        int gid = i + 2;
        add_edge(sidx, gid, goods[i][kn], 0);
        add_edge(gid, sidx, 0, 0);
        _DEBUG_CMD(printf("conn start idx(%d) to a merchant(%d)\n", sidx, i + 2));
    }
    for (int i = 0; i < m; ++i) {
        int sid = i + n + 2;
        add_edge(sid, tidx, supply[i][kn], 0);
        add_edge(tidx, sid, 0, 0);
        _DEBUG_CMD(printf("conn target idx(%d) to a supply station(%d)\n", tidx, i + n + 2));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int gid = i + 2;
            int sid = j + n + 2;
            add_edge(gid, sid, INF, price[kn][i][j]);
            add_edge(sid, gid, 0, -price[kn][i][j]);
            _DEBUG_CMD(printf("conn gid(%d) to sid(%d) at price:%d\n", gid, sid, price[kn][i][j]));
        }
    }
    _DEBUG_CMD(print_graph());
}

int inq[MAXN << 2];
bool spfa()
{
    memset(inq, 0, sizeof(inq));
    memset(cdist, 0x3F, sizeof(cdist));
    memset(pred, -1, sizeof(pred));
    queue<int> q;
    inq[sidx] = 1;
    cdist[sidx] = 0;
    q.push(sidx);

    _DEBUG_CMD(printf("enter q loop\n"));
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        _DEBUG_CMD(printf("q.size():%ld\n", q.size()));
        for (int h = head[u]; h != -1; h = edges[h].next) {
            Edge &e = edges[h];
            int v = e.to;
            if (e.cap > 0 && cdist[v] > cdist[u] + e.cost) {
                cdist[v] = cdist[u] + e.cost;
                pred[v] = u;
                if (inq[v] == 0) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    return cdist[tidx] != INF;
}

int find_eid(int u, int v)
{
    int ret = -1;
    for (int h = head[u]; h != -1; h = edges[h].next) {
        if (edges[h].to == v) {
            ret = h;
            break;
        }
    }
    return ret;
}

std::pair<int, int> augment_path()
{
    int maxflow = INF;
    int mincost = cdist[tidx];
    for (int curr_id = tidx, prev_id = pred[curr_id]; prev_id != -1;
         curr_id = prev_id, prev_id = pred[curr_id]) {
        int eid = find_eid(prev_id, curr_id);
        if (eid != -1) {
            maxflow = min(maxflow, edges[eid].cap);
        }
    }
    for (int curr_id = tidx, prev_id = pred[curr_id]; prev_id != -1;
         curr_id = prev_id, prev_id = pred[curr_id]) {
        int eid = find_eid(prev_id, curr_id);
        if (eid != -1) {
            edges[eid].cap -= maxflow;
            edges[eid ^ 0x01].cap += maxflow;
        }
    }

    return std::pair<int, int>(maxflow, mincost);
}
std::pair<int, int> mincost_dinic()
{
    memset(inq, 0, sizeof(inq));
    int maxflow = 0;
    int mincost = 0;
    while (spfa()) {
        _DEBUG_CMD(printf("spfa is done\n"));
        std::pair<int, int> p = augment_path();
        _DEBUG_CMD(printf("augment path is done\n"));
        maxflow += p.first;
        mincost += p.second * p.first;
    }
    return std::pair<int, int>(maxflow, mincost);
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d%d", &n, &m, &k) && n && m && k) {
        memset(tg, 0, sizeof(tg));
        memset(ts, 0, sizeof(ts));
        _DEBUG_CMD(printf("before read input, n:%d m:%d k:%d\n", n, m, k));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                scanf("%d", &goods[i][j]);
                tg[j] += goods[i][j];
            }
        }
        _DEBUG_CMD(printf("get %d goods is done\n", n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < k; ++j) {
                scanf("%d", &supply[i][j]);
                ts[j] += supply[i][j];
            }
        }
        _DEBUG_CMD(printf("get %d supply is done\n", k));
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    scanf("%d", &price[i][j][k]);
                }
            }
        }
        bool skip = false;
        for (int i = 0; i < k; ++i) {
            if (tg[i] > ts[i]) {
                skip = true;
                break;
            }
        }
        if (skip) {
            printf("-1\n");
            continue;
        }
        _DEBUG_CMD(printf("get %d %dx%d matrix is done\n", k, n, m));
        int mc = 0;
        _DEBUG_CMD(printf("get input done, n:%d m:%d k:%d\n", n, m, k));
        for (int i = 0; i < k; ++i) {
            init_graph();
            build_graph(i);
            _DEBUG_CMD(printf("build_graph(%d) is done\n", i));
            std::pair<int, int> p = mincost_dinic();
            _DEBUG_CMD(printf("mincost dinic at k:%d is done\n", i));
            mc += p.second;
        }
        printf("%d\n", mc);
    }
    return 0;
};

#endif
#endif
