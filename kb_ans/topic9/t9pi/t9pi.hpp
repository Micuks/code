#ifndef _t9pi_20210104_
#define _t9pi_20210104_
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

const int MAXN = 1 << 10;
const int INFI = 1e9;
int n, m;
struct E {
    int u, v, w, next;
    bool vis;
} e[MAXN * MAXN * 2];
int ec, head[MAXN];
int mw;

void add_edge(int u, int v, int w)
{
    e[ec].next = head[u];
    e[ec].u = u;
    e[ec].v = v;
    e[ec].w = w;
    e[ec].vis = false;
    head[u] = ec++;
}
void init()
{
    ec = 0;
    mw = INFI;
    memset(head, -1, sizeof(head));
}

int lowlink[MAXN], dfn[MAXN], dfn_clock;
char instack[MAXN];
int ss[MAXN], ss_cnt;
// int scc_cnt;
int cc_cnt;
// int belong[MAXN];

void dfs(int u)
{
    dfn[u] = lowlink[u] = dfn_clock++;
    instack[u] = 1;
    ss[ss_cnt++] = u;

    for (int h = head[u]; h != -1; h = e[h].next) {
        if (e[h].vis == true) {
            continue;
        }
        e[h].vis = true;
        e[h ^ 0x01].vis = true;
        int v = e[h].v;
        int w = e[h].w;
        if (dfn[v] == 0) {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
            if (dfn[u] < lowlink[v]) {
                mw = min(mw, w);
            }
        }
        else if (instack[v]) {
            lowlink[u] = min(lowlink[u], dfn[v]);
        }
    }

    if (lowlink[u] == dfn[u]) {
        int node;
        do {
            node = ss[--ss_cnt];
            instack[node] = 0;
        } while (node != u);
    }
}

void tarjan()
{
    dfn_clock = 1;
    ss_cnt = 0;
    // scc_cnt = 0;
    cc_cnt = 0;
    memset(instack, 0, sizeof(instack));
    memset(dfn, 0, sizeof(dfn));
    for (int i = 1; i <= n; ++i) {
        if (dfn[i] == 0) {
            ++cc_cnt;
            dfs(i);
        }
    }
}

int main(int argc, char **argv)
{
    // scanf("%d", &t);
    int a, b, c;
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        init();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c);
            add_edge(b, a, c);
        }
        tarjan();
        if (cc_cnt > 1) {
            printf("0\n");
        }
        else if (mw == 0) {
            printf("1\n");
        }
        else if (mw == INFI) {
            printf("-1\n");
        }
        else {
            printf("%d\n", mw);
        }
    }
    return 0;
};

#endif
