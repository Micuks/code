#ifndef _t9pa_20201216_
#define _t9pa_20201216_
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

const int MAXN = 1 << 8;

int N;
char g[MAXN][MAXN];
char vis[MAXN];
int dfn[MAXN];
int lowlink[MAXN];
stack<int> ts;
int instack[MAXN];

int scc_cnt;
int belong[MAXN];
int in_cnt[MAXN], out_cnt[MAXN];

char ng[MAXN][MAXN];

void dfs(int u, int idx)
{
    dfn[u] = idx;
    lowlink[u] = idx;
    vis[u] = 1;
    ts.push(u);
    instack[u] = 1;

    for (int i = 1; i <= N; ++i) {
        if (g[u][i] != 0) {
            if (vis[i] == 0) {
                dfs(i, idx + 1);
                lowlink[u] = min(lowlink[u], lowlink[i]);
            }
            else if (instack[i] != 0) {
                lowlink[u] = min(lowlink[u], dfn[i]);
            }
        }
    }
    if (lowlink[u] == dfn[u]) {
        ++scc_cnt;
        int node = 0;
        do {
            node = ts.top();
            ts.pop();
            belong[node] = scc_cnt;
            instack[node] = 0;
            // num[scc]++;
        } while (node != u);
    }
}
void tarjan()
{
    memset(vis, 0, sizeof(vis));
    memset(dfn, -1, sizeof(dfn));
    memset(belong, -1, sizeof(belong));
    memset(lowlink, -1, sizeof(lowlink));
    memset(instack, 0, sizeof(instack));
    scc_cnt = 0;
    ts = stack<int>();
    for (int i = 1; i <= N; ++i) {
        if (dfn[i] == -1) {
            dfs(i, 1);
        }
    }
}

int main(int argc, char **argv)
{
    int dest;
    scanf("%d", &N);
    memset(g, 0, sizeof(g));
    for (int i = 0; i < N; ++i) {
        while ((~scanf("%d", &dest)) && dest != 0) {
            g[i + 1][dest] = 1;
        }
    }
    tarjan();
    if (scc_cnt == 1) {
        printf("1\n0\n");
    }
    else {
        memset(in_cnt, 0, sizeof(in_cnt));
        memset(out_cnt, 0, sizeof(out_cnt));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (g[i][j] != 0 && belong[i] != belong[j]) {
                    ++in_cnt[belong[j]];
                    ++out_cnt[belong[i]];
                }
            }
        }
        int zi = 0;
        int zo = 0;
        for (int i = 1; i <= scc_cnt; ++i) {
            if (in_cnt[i] == 0) {
                zi++;
            }
            if (out_cnt[i] == 0) {
                zo++;
            }
        }
        _DEBUG_CMD({
            for (int i = 1; i <= scc_cnt; ++i) {
                printf("zi[%d]:%d zo[%d]:%d ", i, in_cnt[i], i, out_cnt[i]);
            }
            printf("\n");
        });
        printf("%d\n%d\n", zi, max(zi, zo));
    }
    return 0;
};

#endif
