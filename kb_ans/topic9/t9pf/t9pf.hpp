#ifndef _t9pf_20210101_
#define _t9pf_20210101_
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

const int MAXN = 2e5 + 3;
const int MAXM = 1e6 + 3;
int N, M;

vector<int> g[MAXN];

struct Edge {
    int from, to, next;
    bool vis;
} edges[MAXM << 1];
int head[MAXN], edge_cnt;

void add_edge(int u, int v)
{
    Edge &e = edges[edge_cnt];
    e.from = u;
    e.to = v;
    e.next = head[u];
    e.vis = false;
    head[u] = edge_cnt++;
}

char gvis[MAXN];
void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
    for (int i = 0; i <= N; ++i) {
        g[i].clear();
    }
    memset(gvis, 0, sizeof(gvis));
}

int ss[MAXN], ss_cnt;
int belong[MAXN], dfn[MAXN], lowlink[MAXN];
char instack[MAXN];
int dfn_cnt, scc_cnt, bg_cnt;

void dfs(int u)
{
    dfn[u] = lowlink[u] = ++dfn_cnt;
    instack[u] = 1;
    ss[ss_cnt++] = u;

    for (int h = head[u]; h != -1; h = edges[h].next) {
        const Edge &e = edges[h];
        if (e.vis) {
            continue;
        }
        edges[h].vis = true;
        edges[h ^ 0x01].vis = true;
        if (dfn[e.to] == 0) {
            // depth[e.to] = depth[u] + 1;
            dfs(e.to);
            lowlink[u] = min(lowlink[u], lowlink[e.to]);
            if (dfn[u] < lowlink[e.to]) {
                // bridge
                ++bg_cnt;
            }
            else {
                // add_edge(e.to, u);
            }
        }
        else if (instack[e.to]) {
            lowlink[u] = min(lowlink[u], dfn[e.to]);
        }
    }

    if (dfn[u] == lowlink[u]) {
        ++scc_cnt;
        int node;
        do {
            node = ss[--ss_cnt];
            instack[node] = 0;
            belong[node] = scc_cnt;
        } while (node != u);
    }
}
void tarjan()
{
    bg_cnt = 0;
    ss_cnt = 0;
    dfn_cnt = 0;
    scc_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));
    memset(lowlink, 0, sizeof(lowlink));
    // memset(depth, 0, sizeof(depth));
    for (int i = 1; i <= N; ++i) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }
}

int treewidth_dfs(int u, int &dest_node)
{
    int d = -1;
    gvis[u] = 1;
    for (int i = 0; i < g[u].size(); ++i) {
        if (gvis[g[u][i]] == 0) {
            int newdn;
            int newd = treewidth_dfs(g[u][i], newdn);
            if (newd > d) {
                d = newd;
                dest_node = newdn;
            }
        }
    }
    if (d == -1) {
        dest_node = u;
    }
    return d + 1;
}

int main(int argc, char **argv)
{
    int a, b;
    while (~scanf("%d%d", &N, &M) && M + N) {
        init();
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
            add_edge(b, a);
        }
        tarjan();
        _DEBUG_CMD({
            printf("tarjan output, belongs:\n");
            for (int i = 1; i <= N; ++i) {
                printf("%d ", belong[i]);
            }
            puts("");
        });
        for (int i = 1; i <= N; ++i) {
            for (int h = head[i]; h != -1; h = edges[h].next) {
                const Edge &e = edges[h];
                if (belong[i] != belong[e.to]) {
                    g[belong[i]].push_back(belong[e.to]);
                }
            }
        }
        int n1, w1;
        w1 = treewidth_dfs(1, n1);
        int n2, w2;
        memset(gvis, 0, sizeof(gvis));
        w2 = treewidth_dfs(n1, n2);
        printf("%d\n", bg_cnt - w2);
    }
    return 0;
};

#endif
