#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;
#define inf 0x3f3f3f3f
#define maxv 10005
#define maxe 100005

int nume = 0, head[maxv], e[maxe][3];

void inline adde(int i, int j, int c)
{
    e[nume][0] = j;
    e[nume][1] = head[i];
    head[i] = nume;
    e[nume++][2] = c;
    e[nume][0] = i;
    e[nume][1] = head[j];
    head[j] = nume;
    e[nume++][2] = 0;
}

int ss, tt, n, m, f, d;
int vis[maxv], lev[maxv];

bool bfs()
{
    for (int i = 0; i < maxv; i++)
        vis[i] = lev[i] = 0;
    queue<int> q;
    q.push(ss);
    vis[ss] = 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = head[cur]; i != -1; i = e[i][1]) {
            int v = e[i][0];
            if (!vis[v] && e[i][2] > 0) {
                lev[v] = lev[cur] + 1;
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    return vis[tt];
}
int dfs(int u, int minf)
{
    if (u == tt || minf == 0)
        return minf;
    int sumf = 0, f;
    for (int i = head[u]; i != -1 && minf; i = e[i][1]) {
        int v = e[i][0];
        if (lev[v] == lev[u] + 1 && e[i][2] > 0) {
            f = dfs(v, minf < e[i][2] ? minf : e[i][2]);
            e[i][2] -= f;
            e[i ^ 1][2] += f;
            sumf += f;
            minf -= f;
        }
    }
    if (!sumf)
        lev[u] = -1;
    return sumf;
}
int Dinic()
{
    int sum = 0;
    while (bfs())
        sum += dfs(ss, inf);
    return sum;
}
int main()
{
    while (scanf("%d%d%d", &n, &f, &d) != EOF) {
        ss = 0, tt = 505;
        memset(head, -1, sizeof(head));
        for (int i = 1; i <= f; ++i)
            adde(ss, i + 200, 1);
        for (int i = 1; i <= d; ++i)
            adde(i + 300, tt, 1);
        for (int i = 1; i <= n; ++i) {
            adde(i, i + 100, 1);
            int F, D;
            scanf("%d%d", &F, &D);
            for (int j = 1; j <= F; ++j) {
                int food;
                scanf("%d", &food);
                adde(food + 200, i, 1);
            }
            for (int j = 1; j <= D; ++j) {
                int drink;
                scanf("%d", &drink);
                adde(i + 100, drink + 300, 1);
            }
        }
        printf("%d\n", Dinic());
    }
    return 0;
}
#else
#ifndef _t11pb_20210620_
#define _t11pb_20210620_
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
const int MAXF = 1 << 7;
const int MAXD = 1 << 7;
int N, F, D;
int fi[MAXF], di[MAXF];
int foods[MAXN][MAXF], drinks[MAXN][MAXF];

struct Edge {
    int to, c, next;
} edges[MAXN * MAXF * MAXD * 2];
int dfn[4 * MAXN];
int head[4 * MAXN], curr_head[4 * MAXN], edge_cnt;

void init_graph()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
    memset(curr_head, -1, sizeof(curr_head));
}
void add_edge(int u, int v, int c)
{
    edges[edge_cnt].to = v;
    edges[edge_cnt].c = c;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}
bool bfs(int s, int t)
{
    _DEBUG_CMD(printf("bfs on s:%d t%d\n", s, t));
    memset(dfn, -1, sizeof(dfn));
    dfn[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        _DEBUG_CMD(printf("q.size():%d u:%d\n", q.size(), u));
        for (int h = head[u]; h != -1; h = edges[h].next) {
            _DEBUG_CMD(printf("h:%d\n", h));
            const Edge &e = edges[h];
            if (dfn[e.to] < 0 && e.c > 0) {
                dfn[e.to] = dfn[u] + 1;
                q.push(e.to);
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
        Edge &e = edges[h];
        Edge &revE = edges[h ^ 0x01];
        const int v = e.to;
        if (dfn[v] > dfn[u] && e.c > 0) {
            int d = dfs(v, t, min(f, e.c));
            if (d > 0) {
                e.c -= d;
                revE.c += d;
                return d;
            }
        }
    }
    return 0;
}

inline int get_sid() { return F + D + N + N + 1; }
inline int get_tid() { return get_sid() + 1; }
inline int get_food_vid(int food_id) { return food_id; }
inline int get_drink_vid(int drink_id) { return drink_id + F + N + N; }
inline int get_cow_vid(int cow_id, int offset) { return ((cow_id << 1) - offset) + F; }

int dinic()
{
    int flow = 0;
    int svid = get_sid();
    int tvid = get_tid();
    while (bfs(svid, tvid)) {
        // int d = 0;
        // while ((d = dfs(svid, tvid, 0x3F3F3F3F)) > 0) {
        //    flow += d;
        //}
        flow += dfs(svid, tvid, 0x3F3F3F3F);
    }
    return flow;
}

int build_graph()
{
    init_graph();
    int svid = get_sid();
    int tvid = get_tid();
    for (int i = 1; i <= N; ++i) {
        int fcnt = fi[i];
        int cvid1 = get_cow_vid(i, 1);
        int cvid2 = get_cow_vid(i, 0);
        add_edge(cvid1, cvid2, 1);
        add_edge(cvid2, cvid1, 0);
        for (int j = 1; j <= fcnt; ++j) {
            int fvid = get_food_vid(foods[i][j]);
            add_edge(fvid, cvid1, 1);
            add_edge(cvid1, fvid, 0);
        }
        int dcnt = di[i];
        for (int j = 1; j <= dcnt; ++j) {
            int dvid = get_drink_vid(drinks[i][j]);
            add_edge(cvid2, dvid, 1);
            add_edge(dvid, cvid2, 0);
        }
    }
    for (int i = 1; i <= F; ++i) {
        int fvid = get_food_vid(i);
        add_edge(svid, fvid, 1);
        add_edge(fvid, svid, 0);
    }
    for (int i = 1; i <= D; ++i) {
        int dvid = get_drink_vid(i);
        add_edge(dvid, tvid, 1);
        add_edge(tvid, dvid, 0);
    }
}

void print_graph()
{
    for (int i = 1; i <= get_tid(); ++i) {
        printf("edges from %d\n", i);
        for (int h = head[i]; h != -1; h = edges[h].next) {
            printf("%d(%d) ", edges[h].to, edges[h].c);
        }
        printf("\n");
    }
}
int main(int argc, char **argv)
{
    scanf("%d%d%d", &N, &F, &D);
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &fi[i], &di[i]);
        for (int j = 1; j <= fi[i]; ++j) {
            scanf("%d", &foods[i][j]);
        }
        for (int j = 1; j <= di[i]; ++j) {
            scanf("%d", &drinks[i][j]);
        }
    }
    _DEBUG_CMD(printf("reading-input done n:%d, f:%d, d:%d\n", N, F, D));
    build_graph();
    _DEBUG_CMD({
        printf("graph before dinic\n");
        print_graph();
    });
    _DEBUG_CMD(printf("building-graph done ecnt:%d\n", edge_cnt));
    int ret = dinic();
    _DEBUG_CMD(printf("doing-dinic done\n"));
    printf("%d\n", ret);
    _DEBUG_CMD({
        printf("graph after dinic\n");
        print_graph();
    });
    return 0;
};

#endif
#endif
