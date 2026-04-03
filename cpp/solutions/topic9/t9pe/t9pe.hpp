#ifndef _t9pe_20201231_
#define _t9pe_20201231_
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

const int MAXF = 5e3 + 3;
const int MAXR = 1e4 + 3;
int F, R;

struct Edge {
    int from, to, next;
    bool vis;
} edges[MAXR << 1];
int edge_cnt, head[MAXF];

void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
}
void add_edge(int u, int v)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].from = u;
    edges[edge_cnt].to = v;
    edges[edge_cnt].vis = false;
    head[u] = edge_cnt++;
}

int dfn_cnt, scc_cnt;
int belong[MAXF], instack[MAXF], ss[MAXF], dfn[MAXF], lowlink[MAXF];
int ss_cnt;

void dfs(int u)
{
    lowlink[u] = dfn[u] = dfn_cnt++;
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
            dfs(e.to);
            lowlink[u] = min(lowlink[u], lowlink[e.to]);
        }
        else if (instack[e.to]) {
            lowlink[u] = min(lowlink[u], dfn[e.to]);
        }
    }

    if (dfn[u] == lowlink[u]) {
        int node;
        ++scc_cnt;
        do {
            node = ss[--ss_cnt];
            belong[node] = scc_cnt;
            instack[node] = 0;
        } while (node != u);
    }
}
void tarjan()
{
    dfn_cnt = 1;
    scc_cnt = 0;
    ss_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));
    for (int i = 1; i <= F; ++i) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }
}

int main(int argc, char **argv)
{
    int a, b;
    scanf("%d%d", &F, &R);
    init();
    for (int i = 0; i < R; ++i) {
        scanf("%d%d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    tarjan();
    int odeg[MAXF];
    int ideg[MAXF];
    memset(odeg, 0, sizeof(odeg));
    memset(ideg, 0, sizeof(ideg));
    for (int i = 1; i <= F; ++i) {
        int s1 = belong[i];
        for (int h = head[i]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            int s2 = belong[e.to];
            if (s1 != s2) {
                ++odeg[s1];
                ++ideg[s2];
            }
        }
    }

    int ans = 0;
    _DEBUG_CMD({
        printf("belongs:\n");
        for (int i = 1; i <= F; ++i) {
            printf("%d ", belong[i]);
        }
        puts("");
    });
    _DEBUG_CMD(printf("scc_cnt:%d odegs:\n", scc_cnt));
    for (int i = 1; i <= scc_cnt; ++i) {
        _DEBUG_CMD({ printf("%d ", odeg[i]); });
        if (odeg[i] == 1 || ideg[i] == 1) {
            ++ans;
        }
    }
    _DEBUG_CMD(puts(""));
    printf("%d\n", (ans + 1) / 2);
    return 0;
};

#endif
