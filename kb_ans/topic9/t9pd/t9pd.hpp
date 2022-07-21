#if 0
/*************************************************************************
> File Name: 3694.cpp
> Author: jiangyuzhu
> Mail: 834138558@qq.com
> Created Time: 2016/9/14 13:37:27
************************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int maxn = 1e5 + 5, maxm = 2e5 + 5;
int head[maxn], dfn[maxn], low[maxn];
struct EDGE {
    int to, next;
    bool vis;
};
EDGE edge[maxm * 2];
int tot, dfnum;
int btot;
int pa[maxn], fa[maxn];
int dep[maxn];
void init(int n)
{
    tot = 0;
    btot = 0;
    dfnum = 1;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    for (int i = 1; i <= n; i++)
        pa[i] = i;
}
int _find(int x)
{
    if (x == pa[x])
        return x;
    return pa[x] = _find(pa[x]);
}
void unit(int x, int y)
{
    int rx = _find(x), ry = _find(y);
    if (rx == ry)
        return;
    pa[rx] = ry;
}
void addedge(int u, int v)
{
    edge[tot].vis = false;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
void dfs(int u, int depth)
{
    dfn[u] = low[u] = dfnum++;
    dep[u] = depth;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        if (edge[i].vis)
            continue;
        edge[i].vis = edge[i ^ 1].vis = true;
        int v = edge[i].to;
        if (!dfn[v]) {
            fa[v] = u;
            dfs(v, depth + 1);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], dfn[v]);
        if (low[v] <= dfn[u])
            unit(v, u);
        else
            btot++;
    }
}
int LCA(int u, int v)
{
    int cnt = 0;
    while (dep[u] > dep[v]) {
        if (_find(u) != _find(fa[u]))
            cnt++;
        unit(u, fa[u]);
        u = fa[u];
    }
    while (dep[v] > dep[u]) {
        if (_find(v) != _find(fa[v]))
            cnt++;
        unit(v, fa[v]);
        v = fa[v];
    }
    while (u != v) {
        if (_find(u) != _find(fa[u]))
            cnt++;
        unit(u, fa[u]);
        if (_find(v) != _find(fa[v]))
            cnt++;
        unit(v, fa[v]);
        u = fa[u];
        v = fa[v];
    }
    return cnt;
}
int main(void)
{
    int n, m;
    int a, b;
    int kas = 1;
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        init(n);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }
        fa[1] = 1;
        dfs(1, 1);
        int q;
        scanf("%d", &q);
        printf("Case %d:\n", kas++);
        for (int i = 0; i < q; i++) {
            scanf("%d%d", &a, &b);
            if (_find(a) != _find(b))
                btot -= LCA(a, b);
            printf("%d\n", btot);
        }
        puts("");
    }
    return 0;
}

#else
#ifndef _t9pd_20201230_
#define _t9pd_20201230_
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
const int MAXM = 2e5 + 3;

int n, m, q;
int uarr[MAXN];

struct Edge {
    int from, to, next;
    bool vis;
} edges[MAXM << 1];

int head[MAXM], edge_cnt;

void add_edge(int u, int v)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].from = u;
    edges[edge_cnt].to = v;
    edges[edge_cnt].vis = false;
    head[u] = edge_cnt++;
}

void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
    for (int i = 0; i <= n; ++i) {
        uarr[i] = i;
    }
}

int scc[MAXN], scc_cnt, dfn[MAXN], lowlink[MAXN], depth[MAXN], dfs_cnt;
int ss[MAXN], ss_cnt;
char instack[MAXN];
int bcnt;
int fa[MAXN];

typedef pair<int, int> pii;
vector<pii> cuts;

int ufind(int u)
{
    if (uarr[u] == u) {
        return u;
    }
    return uarr[u] = ufind(uarr[u]);
}
void uadd(int x, int y)
{
    int px = ufind(x);
    int py = ufind(y);
    if (px == py) {
        return;
    }
    uarr[px] = py;
}

void dfs(int v, int u)
{
    depth[v] = depth[u] + 1;
    dfn[v] = lowlink[v] = ++dfs_cnt;
    instack[v] = 1;
    ss[ss_cnt++] = v;

    int h = head[v];
    while (h != -1) {
        const Edge &e = edges[h];
        if (e.vis) {
            h = e.next;
            continue;
        }
        edges[h].vis = edges[h ^ 1].vis = true;
        if (dfn[e.to] == 0) {
            fa[e.to] = v;
            dfs(e.to, v);
            lowlink[v] = min(lowlink[v], lowlink[e.to]);
        }
        else if (instack[e.to]) {
            lowlink[v] = min(lowlink[v], dfn[e.to]);
        }
        if (dfn[v] < lowlink[e.to]) {
            ++bcnt;
            cuts.push_back(pair<int, int>(v, e.to));
        }
        else {
            uadd(e.to, v);
        }
        h = e.next;
    }

    if (dfn[v] == lowlink[v]) {
        ++scc_cnt;
        int node;
        do {
            node = ss[--ss_cnt];
            instack[node] = 0;
            scc[node] = scc_cnt;
        } while (node != v);
    }
}
void tarjan()
{
    bcnt = 0;
    ss_cnt = 0;
    scc_cnt = 0;
    dfs_cnt = 1;
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));
    cuts.clear();

    for (int i = 1; i <= n; ++i) {
        if (dfn[i] == 0) {
            // dfn[i] = 1;
            depth[i] = 1;
            fa[i] = i;
            dfs(i, -1);
        }
    }
}

int LCA(int u, int v)
{
    int cnt = 0;
    while (depth[u] > depth[v]) {
        if (ufind(u) != ufind(fa[u])) {
            ++cnt;
        }
        uadd(u, fa[u]);
        u = fa[u];
    }
    while (depth[v] > depth[u]) {
        if (ufind(v) != ufind(fa[v])) {
            ++cnt;
        }
        uadd(v, fa[v]);
        v = fa[v];
    }
    while (u != v) {
        if (ufind(u) != ufind(fa[u])) {
            ++cnt;
        }
        uadd(u, fa[u]);
        u = fa[u];
        if (ufind(v) != ufind(fa[v])) {
            ++cnt;
        }
        uadd(v, fa[v]);
        v = fa[v];
    }
    return cnt;
}

int main(int argc, char **argv)
{
    int a, b;
    int case_cnt = 0;
    while (~scanf("%d%d", &n, &m) && (n != 0 || m != 0)) {
        init();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
            add_edge(b, a);
        }
        tarjan();
        _DEBUG_CMD({
            printf("tarjan bcnt: %d\n", bcnt);
            printf("cuts:\n");
            for (auto k : cuts) {
                printf("%d-%d\n", k.first, k.second);
            }
        });
        scanf("%d", &q);
        printf("Case %d:\n", ++case_cnt);
        for (int i = 0; i < q; ++i) {
            scanf("%d%d", &a, &b);
            if (ufind(a) != ufind(b)) {
                bcnt -= LCA(a, b);
            }
            printf("%d\n", bcnt);
        }
        puts("");
    }
    return 0;
};

#endif
#endif
