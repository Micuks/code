#if 0
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int N = 55;
const int M = N * N;
const int INF = 0x3f3f3f3f;

struct mac {
    int q;
    int in[10], out[10];
} m[N];
struct edge {
    int v, next, c;
} e[M];
int p[2 * N], eid;
int n, qn, g[2 * N][2 * N], cnt;

void add(int u, int v, int c)
{
    e[eid] = {v, p[u], c};
    p[u] = eid++;
    e[eid] = {u, p[v], 0};
    p[v] = eid++;
}
int d[N], s, t;
bool bfs()
{
    memset(d, -1, sizeof(d));
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = p[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (e[i].c > 0 && d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[t] != -1;
}
int dfs(int u, int flow)
{
    if (u == t)
        return flow;
    int res = 0;
    for (int i = p[u]; ~i; i = e[i].next) {
        int v = e[i].v;
        if (e[i].c > 0 && d[v] == d[u] + 1) {
            int tmp = dfs(v, min(e[i].c, flow));
            if (u != s && v != t && u > n && v <= n && tmp) {
                if (g[u - n][v] == 0)
                    cnt++;
                g[u - n][v] += tmp;
            }
            res += tmp;
            flow -= tmp;
            e[i].c -= tmp;
            e[i ^ 1].c += tmp;
            if (!flow)
                break;
        }
    }
    if (!res)
        d[u] = -1;
    return res;
}

int main()
{
    while (scanf("%d%d", &qn, &n) != EOF) {
        s = 0, t = 2 * n + 1;
        memset(p, -1, sizeof(p));
        eid = 0;
        memset(g, 0, sizeof(g));
        cnt = 0;
        int flag;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &m[i].q);
            for (int j = 0; j < qn; ++j)
                scanf("%d", &m[i].in[j]);
            for (int j = 0; j < qn; ++j)
                scanf("%d", &m[i].out[j]);
        }
        for (int i = 1; i <= n; ++i)
            add(i, i + n, m[i].q);
        for (int i = 1; i <= n; ++i) {
            int k;
            for (k = 0; k < qn; ++k)
                if (m[i].in[k] == 1)
                    break;
            if (k == qn)
                add(s, i, m[i].q);
            for (k = 0; k < qn; ++k)
                if (m[i].out[k] == 0)
                    break;
            if (k == qn) {
                add(i + n, t, m[i].q);
                continue;
            }
            for (int j = 1; j <= n; ++j) {
                if (i == j)
                    continue;
                flag = 0;
                for (k = 0; k < qn; ++k) {
                    if (m[j].in[k] && m[i].out[k]) {
                        flag = 1;
                    }
                    else if (m[j].in[k] == 1 && !m[i].out[k] || m[j].in[k] == 0 && m[i].out[k]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                    add(i + n, j, m[i].q);
            }
        }
        int ans = 0;
        while (bfs()) {
            ans += dfs(s, INF);
            //      cout<<ans<<endl;
        }
        printf("%d %d\n", ans, cnt);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j)
                    continue;
                if (g[i][j])
                    printf("%d %d %d\n", i, j, g[i][j]);
            }
        }
    }
    return 0;
}

#else
#ifndef _t11pa_20210619_
#define _t11pa_20210619_
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

#define INF 0x3F3F3F3

const int MAXP = 1 << 4;
// const int MAXP = 1 << 5;
// const int MAXN = 1 << 6;
const int MAXN = 1 << 8;

int n, p;
int sp[MAXN][MAXP], dp[MAXN][MAXP], q[MAXN];
int lvl[MAXN];

int a_to_b_available(int pa, int pb)
{
    int ret = 1;
    for (int i = 1; i <= p; ++i) {
        if (((dp[pa][i] ^ sp[pb][i]) == 0) || (sp[pb][i] == 2)) {
            continue;
        }
        else {
            ret = 0;
        }
    }
    return ret;
}

struct Edge {
    int to, cap, next;
} edges[MAXN * MAXN];
int head[MAXN], edge_cnt = 0, curr_head[MAXN];

void init_graph()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
}

void add_edge(int u, int v, int cap)
{
    edges[edge_cnt].to = v;
    edges[edge_cnt].cap = cap;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

// void add_rev(int eid1, int revid) { edges[eid1].revid = revid; }

int sidx, tidx;
void add_source_and_target()
{
    sidx = 2 * n + 1;
    tidx = 2 * n + 2;
    //_DEBUG_CMD(printf("before build graph\n"));
    for (int j = 1; j <= p; ++j) {
        sp[sidx][j] = 0;
        dp[sidx][j] = 0;
    }
    for (int j = 1; j <= p; ++j) {
        sp[tidx][j] = 1;
        dp[tidx][j] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        int ini = (i << 1) - 1;
        int outi = (i << 1);

        if (a_to_b_available(sidx, i)) {
            add_edge(sidx, ini, INF);
            add_edge(ini, sidx, 0);
        }
        if (a_to_b_available(i, tidx)) {
            add_edge(outi, tidx, INF);
            add_edge(tidx, outi, 0);
        }
    }
}

void build_graph()
{
    init_graph();
    for (int i = 1; i <= n; ++i) {
        int ini = (i << 1) - 1;
        int outi = (i << 1);
        add_edge(ini, outi, q[i]);
        add_edge(outi, ini, 0);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j) {
                int ini = (i << 1) - 1;
                int outi = (i << 1);
                int inj = (j << 1) - 1;
                int outj = (j << 1);

                if (a_to_b_available(i, j)) {
                    add_edge(outi, inj, max(q[i], q[j]));
                    add_edge(inj, outi, 0);
                }
            }
        }
    }
    add_source_and_target();
}

// void bfs(int s)
bool bfs(int s, int t)
{
    // int s = sidx;
    memset(lvl, -1, sizeof(lvl));
    queue<int> q;
    lvl[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int h = head[u]; h != -1; h = edges[h].next) {
            Edge &e = edges[h];
            if (e.cap > 0 && lvl[e.to] < 0) {
                lvl[e.to] = lvl[u] + 1;
                q.push(e.to);
            }
        }
    }
    if (lvl[t] != -1) {
        memcpy(curr_head, head, sizeof(curr_head));
        return true;
    }
    return false;
}

const int N = MAXN;
struct mac {
    int q;
    int in[10], out[10];
} m[N];
int pa[2 * N], eid;
// int n;
int qn, g[2 * N][2 * N], cnt;
int d[N], s, t;
int dfs(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    for (int &h = curr_head[u]; h != -1; h = edges[h].next) {
        Edge &e = edges[h];
        int v = e.to;
        if (e.cap > 0 && lvl[u] < lvl[v]) {
            int d = dfs(v, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                if (u != s && v != t && u > n && v <= n) {
                    if (g[u - n][v] == 0) {
                        ++cnt;
                    }
                    g[u - n][v] += d;
                }
                edges[h ^ 0x01].cap += d;
                return d;
            }
        }
    }
}

int max_flow()
{
    int run_cnt = 0;
    int flow = 0;
    while (true) {
        bfs(sidx, tidx);
        if (lvl[tidx] < 0) {
            return flow;
        }
        _DEBUG_CMD(printf("run_cnt:%d lvl[%d]:%d\n", run_cnt++, tidx, lvl[tidx]));
        // flow += dfs(sidx, tidx, INF);
        //*
        int f = 0;
        while ((f = dfs(sidx, tidx, INF)) > 0) {
            _DEBUG_CMD(printf("dfs(%d, %d, INF): %d\n", sidx, tidx, f));
            flow += f;
        }
        //*/
    }
    return flow;
}

#if 1
int main(int argc, char **argv)
{
    while (scanf("%d%d", &p, &n) != EOF) {
        _DEBUG_CMD(printf("get p&n done p:%d n:%d\n", p, n));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &q[i]);
            _DEBUG_CMD(printf("get q[%d]: %d done\n", i, q[i]));
            for (int j = 1; j <= p; ++j) {
                scanf("%d", &sp[i][j]);
            }
            for (int j = 1; j <= p; ++j) {
                scanf("%d", &dp[i][j]);
                _DEBUG_CMD(printf("\tget dp[%d][%d]: %d done\n", i, j, dp[i][j]));
            }
        }

        build_graph();
        _DEBUG_CMD(printf("before build max flow sidx:%d tidx:%d\n", sidx, tidx));
        _DEBUG_CMD({
            printf("graph show:\n");
            for (int i = 1; i <= 2 * n + 2; ++i) {
                for (int h = head[i]; h != -1; h = edges[h].next) {
                    Edge &e = edges[h];
                    printf("from:%d to:%d c:%d\n", i, e.to, e.cap);
                }
            }
        });
        int flow = max_flow();
        _DEBUG_CMD(printf("after get max flow\n"););
        int ecnt = 0;
        vector<int> sv;
        vector<int> ev;
        vector<int> cv;
        for (int i = 2; i <= 2 * n; i += 2) {
            for (int h = head[i]; h != -1; h = edges[h].next) {
                Edge &e = edges[h];
                Edge &revE = edges[h ^ 0x01];
                if (i == sidx || i == tidx || e.to == sidx || e.to == tidx) {
                    continue;
                }
                const int u = i / 2;
                const int v = e.to / 2 + 1;
                if (u == v) {
                    continue;
                }
                if (revE.cap != 0) {
                    ++ecnt;
                    sv.push_back(u);
                    ev.push_back(v);
                    cv.push_back(revE.cap);
                }
            }
        }
        printf("%d %d\n", flow, ecnt);
        for (int i = 0; i < ecnt; ++i) {
            printf("%d %d %d\n", sv[i], ev[i], cv[i]);
        }
    }
    return 0;
};
#endif

#if 0
int main()
{
    while (scanf("%d%d", &qn, &n) != EOF) {
        init_graph();
        s = 0, t = 2 * n + 1;
        memset(pa, -1, sizeof(pa));
        eid = 0;
        memset(g, 0, sizeof(g));
        cnt = 0;
        int flag;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &m[i].q);
            for (int j = 0; j < qn; ++j)
                scanf("%d", &m[i].in[j]);
            for (int j = 0; j < qn; ++j)
                scanf("%d", &m[i].out[j]);
        }
        for (int i = 1; i <= n; ++i)
            add_edge(i, i + n, m[i].q);
        for (int i = 1; i <= n; ++i) {
            int k;
            for (k = 0; k < qn; ++k)
                if (m[i].in[k] == 1)
                    break;
            if (k == qn)
                add_edge(s, i, m[i].q);
            for (k = 0; k < qn; ++k)
                if (m[i].out[k] == 0)
                    break;
            if (k == qn) {
                add_edge(i + n, t, m[i].q);
                continue;
            }
            for (int j = 1; j <= n; ++j) {
                if (i == j)
                    continue;
                flag = 0;
                for (k = 0; k < qn; ++k) {
                    if (m[j].in[k] && m[i].out[k]) {
                        flag = 1;
                    }
                    else if (m[j].in[k] == 1 && !m[i].out[k] || m[j].in[k] == 0 && m[i].out[k]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                    add_edge(i + n, j, m[i].q);
            }
        }
        int ans = 0;
        while (bfs(s, t)) {
            ans += dfs(s, t, INF);
            cout << ans << endl;
        }
        printf("%d %d\n", ans, cnt);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j)
                    continue;
                if (g[i][j]) {
                    printf("%d %d %d\n", i, j, g[i][j]);
                }
            }
        }
    }
    return 0;
}
#endif

#endif
#endif
