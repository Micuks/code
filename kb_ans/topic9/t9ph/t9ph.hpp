#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 2005;
int t;
int n, m, tot;
int match[N], head[N], mylink[N][N], check[N];
stack<int> s;
vector<int> ans;
int T, num;
int scc[N], dfn[N], low[N], vis[N];
struct Edge {
    int u, v, next;
} e[N * N];
void adde(int u, int v)
{
    e[tot].v = v;
    e[tot].u = u;
    e[tot].next = head[u];
    head[u] = tot++;
}
void Tarjan(int u)
{
    dfn[u] = low[u] = ++T;
    vis[u] = 1;
    s.push(u);
    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (!vis[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!scc[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        num++;
        int now;
        do {
            now = s.top();
            s.pop();
            scc[now] = num;
        } while (!s.empty() && now != u);
    }
}
int dfs(int x, int nown)
{
    for (int i = 1; i <= nown; i++) {
        if (!check[i] && mylink[x][i]) {
            check[i] = 1;
            if (match[i] == -1 || dfs(match[i], nown)) {
                match[i] = x;
                return 1;
            }
        }
    }
    return 0;
}
int hungry(int n1, int m1)
{
    memset(match, -1, sizeof(match));
    int ans = 0;
    for (int i = 1; i <= n1; i++) {
        memset(check, 0, sizeof(check));
        ans += dfs(i, m1);
    }
    return ans;
}
void init()
{
    memset(mylink, 0, sizeof(mylink));
    memset(match, -1, sizeof(match));
    memset(head, -1, sizeof(head));
    memset(scc, 0, sizeof(scc));
    memset(dfn, 0, sizeof(dfn));
    memset(vis, 0, sizeof(vis));
    num = 0;
    T = 0;
    tot = 0;
}
int main()
{
    cin >> t;
    int Case = 0;
    while (t--) {
        Case++;
        init();
        scanf("%d%d", &n, &m);
        for (int i = 1, k; i <= n; i++) {
            scanf("%d", &k);
            for (int j = 1, l; j <= k; j++) {
                scanf("%d", &l);
                mylink[i][l] = 1;
            }
        }
        int cnt = hungry(n, m);
        int nown, nowm;
        nown = nowm = n + m - cnt;
        for (int i = n + 1; i <= nown; i++) {
            for (int j = 1; j <= nown; j++) {
                mylink[i][j] = 1;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = m + 1; j <= nowm; j++) {
                mylink[i][j] = 1;
            }
        }
        hungry(nown, nowm);
        for (int i = 1; i <= nown; i++) {
            for (int j = 1; j <= nowm; j++) {
                if (mylink[i][j])
                    adde(i, nown + j);
            }
        }
        for (int i = 1; i <= nown; i++) {
            if (match[i] != -1)
                adde(i + nown, match[i]);
        }
        printf("Case #%d:\n", Case);
        while (!s.empty())
            s.pop();
        for (int i = 1; i <= 2 * nown; i++) {
            if (!vis[i])
                Tarjan(i);
        }
        for (int i = 1; i <= n; i++) {
            ans.clear();
            for (int j = head[i]; j != -1; j = e[j].next) {
                int v = e[j].v;
                v -= nown;
                if (v > m)
                    continue;
                if (scc[i] == scc[v + nown])
                    ans.push_back(v);
            }
            sort(ans.begin(), ans.end());
            printf("%d", (int) ans.size());
            for (int j = 0; j < ans.size(); j++) {
                printf(" %d", ans[j]);
            }
            printf("\n");
        }
    }
    return 0;
}

#else
#ifndef _t9ph_20210104_
#define _t9ph_20210104_
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

const int MAXN = 1 << 11;
int T, n, m;

char g[MAXN][MAXN];
char vis[MAXN];
// int rx[MAXN], ry[MAXN];
int match[MAXN];
int check[MAXN];

int belong[MAXN], scc_cnt;
char instack[MAXN];
int dfn[MAXN], lowlink[MAXN], dfn_clock, ss[MAXN], ss_cnt;

struct Edge {
    int from, to, next;
} edges[MAXN * MAXN];
int edge_cnt;
int head[MAXN];

void add_edge(int u, int v)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].from = u;
    edges[edge_cnt].to = v;
    head[u] = edge_cnt++;
}

void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));

    dfn_clock = 1;
    ss_cnt = 0;
    scc_cnt = 0;

    memset(lowlink, 0, sizeof(lowlink));
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));

    memset(g, 0, sizeof(g));
    // memset(rx, -1, sizeof(rx));
    // memset(ry, -1, sizeof(ry));
    memset(match, -1, sizeof(match));
}

int ha_dfs(int u, int m1)
{
    for (int i = 1; i <= m1; ++i) {
        if (!check[i] && g[u][i]) {
            check[i] = 1;
            if (match[i] == -1 || ha_dfs(match[i], m1)) {
                match[i] = u;
                return 1;
            }
        }
    }
    return 0;
}
int hungarian_algorithm(int n1, int m1)
{
    int ans = 0;
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= n1; ++i) {
        memset(check, 0, sizeof(check));
        ans += ha_dfs(i, m1);
    }
    return ans;
}

// void dfs(int u) {}
void tarjan(int u)
{
    dfn[u] = lowlink[u] = dfn_clock++;
    instack[u] = 1;
    ss[ss_cnt++] = u;

    for (int h = head[u]; h != -1; h = edges[h].next) {
        const Edge &e = edges[h];
        if (dfn[e.to] == 0) {
            tarjan(e.to);
            lowlink[u] = min(lowlink[u], lowlink[e.to]);
        }
        else if (instack[e.to]) {
            lowlink[u] = min(lowlink[u], dfn[e.to]);
        }
    }

    if (lowlink[u] == dfn[u]) {
        ++scc_cnt;
        int node;
        do {
            node = ss[--ss_cnt];
            belong[node] = scc_cnt;
            instack[node] = 0;
        } while (node != u);
    }
}

int main(int argc, char **argv)
{
    int k, p;
    scanf("%d", &T);
    for (int case_cnt = 0; case_cnt < T; ++case_cnt) {
        init();
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &k);
            for (int j = 0; j < k; ++j) {
                scanf("%d", &p);
                g[i + 1][p] = 1;
            }
        }
        int cnt = hungarian_algorithm(n, m);
        int nn, nw;
        nn = nw = n + m - cnt;
        for (int i = n + 1; i <= nn; ++i) {
            for (int j = 1; j <= nn; ++j) {
                g[i][j] = 1;
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = m + 1; j <= nw; ++j) {
                g[i][j] = 1;
            }
        }
        hungarian_algorithm(nn, nw);

        for (int i = 1; i <= nn; ++i) {
            for (int j = 1; j <= nw; ++j) {
                if (g[i][j]) {
                    add_edge(i, nw + j);
                }
            }
        }
        for (int i = 1; i <= nn; ++i) {
            if (match[i] != -1) {
                add_edge(i + nn, match[i]);
            }
        }
        printf("Case #%d:\n", case_cnt + 1);
        // ss_cnt = 0;
        for (int i = 1; i <= 2 * nn; ++i) {
            if (dfn[i] == 0)
                tarjan(i);
        }
        for (int i = 1; i <= n; ++i) {
            vector<int> ans;
            for (int h = head[i]; h != -1; h = edges[h].next) {
                int v = edges[h].to;
                _DEBUG_CMD(printf("u:%d v:%d\n", i, v));
                v -= nn;
                if (v > m)
                    continue;
                if (belong[i] == belong[v + nn])
                    ans.push_back(v);
            }
            sort(ans.begin(), ans.end());
            printf("%d", (int) ans.size());
            for (int j = 0; j < ans.size(); ++j) {
                printf(" %d", ans[j]);
            }
            printf("\n");
        }
    }
    return 0;
};

#endif
#endif
