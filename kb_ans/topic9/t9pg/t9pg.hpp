#ifndef _t9pg_20210102_
#define _t9pg_20210102_
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
const int MAXM = 1e5 + 3;
int T, M, N;

struct Edge {
    int from, to, next;
} edges[MAXM];
int edge_cnt;
int head[MAXN];

void add_edge(int u, int v)
{
    edges[edge_cnt].from = u;
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}
void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
}

char instack[MAXN];
int ss[MAXN], ss_cnt;
int belong[MAXN], scc_pt_cnt[MAXN], scc_cnt;
int lowlink[MAXN], dfn[MAXN], dfn_cnt;

void dfs(int u)
{
    lowlink[u] = dfn[u] = ++dfn_cnt;
    instack[u] = 1;
    ss[ss_cnt++] = u;

    for (int h = head[u]; h != -1; h = edges[h].next) {
        const Edge &e = edges[h];
        if (dfn[e.to] == 0) {
            dfs(e.to);
            lowlink[u] = min(lowlink[u], lowlink[e.to]);
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
            belong[node] = scc_cnt;
            ++scc_pt_cnt[scc_cnt];
            instack[node] = 0;
        } while (node != u);
    }
}

void tarjan()
{
    scc_cnt = 0;
    ss_cnt = 0;
    dfn_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));
    memset(scc_pt_cnt, 0, sizeof(scc_pt_cnt));

    for (int i = 1; i <= N; ++i) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }
}

int main(int argc, char **argv)
{
    int a, b;
    scanf("%d", &T);
    for (int case_cnt = 1; case_cnt <= T; ++case_cnt) {
        init();
        scanf("%d%d", &N, &M);
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        tarjan();
        long long xy = 1e8;
        int indeg[MAXN], outdeg[MAXN];
        memset(indeg, 0, sizeof(indeg));
        memset(outdeg, 0, sizeof(outdeg));
        for (int i = 1; i <= N; ++i) {
            int scci = belong[i];
            for (int h = head[i]; h != -1; h = edges[h].next) {
                int sccj = belong[edges[h].to];
                if (scci != sccj) {
                    ++indeg[sccj];
                    ++outdeg[scci];
                }
            }
        }
        for (int i = 1; i <= scc_cnt; ++i) {
            if (indeg[i] == 0 || outdeg[i] == 0) {
                xy = min(xy, (long long) (scc_pt_cnt[i]) * (N - scc_pt_cnt[i]));
            }
        }
        long long ans = (long long) (N) * (N - 1) - M - xy;
        if (scc_cnt == 1) {
            ans = -1;
        }
        printf("Case %d: %lld\n", case_cnt, ans);
    }
    return 0;
};

#endif
