#ifndef _t11pg_20210627_
#define _t11pg_20210627_
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

int t, n, m;
struct Isle {
    int x, y;
    bool operator<(const Isle &i) const
    {
        if (x < i.x) {
            return true;
        }
        else if (x > i.x) {
            return false;
        }
        return y < i.y;
    }
};
const int MAXN = 1e6 + 5;
Isle isles[MAXN];
int sid, tid;

struct Edge {
    int to, cap, next;
} edges[MAXN << 4];
int head[MAXN], ec, curr_head[MAXN], dfn[MAXN], que[MAXN];
void add_edge(int u, int v, int c)
{
    edges[ec] = Edge{v, c, head[u]};
    head[u] = ec++;
}
void init_graph()
{
    ec = 0;
    memset(head, -1, sizeof(head));
}
void build_graph() {}

bool bfs(int s, int t)
{
    memset(dfn, -1, sizeof(dfn));
    // int qh, qt;
    // qh = qt = 0;
    // que[qt++] = s;
    queue<int> q;
    q.push(s);
    dfn[s] = 0;

    while (!q.empty()) {
        // while (qh < qt) {
        int u = q.front();
        q.pop();
        // int u = que[qh++];
        if (u == t) {
            return true;
        }
        for (int h = head[u]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            int v = e.to;
            if (dfn[v] == -1 && e.cap > 0) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
                // que[qt++] = v;
            }
        }
    }
    if (dfn[t] != -1) {
        memcpy(curr_head, head, sizeof(curr_head));
    }
    return false;
}
int dfs(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    int res = 0;
    // for (int &h = curr_head[u]; h != -1; h = edges[h].next) {
    for (int h = head[u]; h != -1; h = edges[h].next) {
        Edge &e = edges[h];
        Edge &revE = edges[h ^ 0x01];
        int v = e.to;
        if (dfn[v] == dfn[u] + 1 && e.cap > 0) {
            int d = dfs(v, t, min(e.cap, f - res));
            if (d > 0) {
                e.cap -= d;
                revE.cap += d;
                // return d;
                res += d;
                if (res == f) {
                    break;
                }
            }
        }
    }
    if (res == 0) {
        dfn[u] = -1;
    }
    return res;
}
int dinic()
{
    int maxflow = 0;
    while (bfs(sid, tid)) {
        maxflow += dfs(sid, tid, 0x3F3F3F3F);
    }
    return maxflow;
}

int main(int argc, char **argv)
{
    scanf("%d", &t);
    int i1, i2, c;
    for (int case_cnt = 0; case_cnt < t; ++case_cnt) {
        scanf("%d%d", &n, &m);
        sid = tid = 0;
        init_graph();
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &isles[i].x, &isles[i].y);
            if (isles[i] < isles[sid]) {
                sid = i;
            }
            if (isles[tid] < isles[i]) {
                tid = i;
            }
        }
        sid += 1;
        tid += 1;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &i1, &i2, &c);
            add_edge(i1, i2, c);
            add_edge(i2, i1, c);
        }
        _DEBUG_CMD(printf("read n:%d m:%d in, sid:%d tid:%d\n", n, m, sid, tid));
        build_graph();
        int ret = dinic();
        printf("%d\n", ret);
    }
    return 0;
};

#endif
