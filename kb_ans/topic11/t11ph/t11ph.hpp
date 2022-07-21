#ifndef _t11ph_20210704_
#define _t11ph_20210704_
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
int n, f, d;
int food_cnt[MAXN], drink_cnt[MAXN];
char fa[MAXN][MAXN], da[MAXN][MAXN];
int sidx, tidx;
int g[MAXN << 2][MAXN << 2], dfn[MAXN << 2];

void debug_print()
{
    printf("n:%d f:%d d:%d sidx:%d tidx:%d\n", n, f, d, sidx, tidx);
    for (int u = 0; u <= tidx; ++u) {
        printf("from: %d to, cap: ", u);
        for (int v = 0; v <= tidx; ++v) {
            if (g[u][v] != -1) {
                printf("(%d,%d) ", v, g[u][v]);
            }
        }
        printf("\n");
    }
}
void init_graph() { memset(g, -1, sizeof(g)); }
void build_graph()
{
    sidx = n + n + f + d;
    tidx = sidx + 1;

    for (int i = 0; i < n; ++i) {
        int in_id = 2 * i;
        int out_id = 2 * i + 1;
        g[in_id][out_id] = 1;
        g[out_id][in_id] = 0;

        for (int j = 0; j < f; ++j) {
            int fid = j + n + n;
            if (fa[i][j] == 'Y') {
                g[fid][in_id] = 1;
                g[in_id][fid] = 0;
            }
        }
        for (int j = 0; j < d; ++j) {
            int did = j + n + n + f;
            if (da[i][j] == 'Y') {
                g[out_id][did] = 1;
                g[did][out_id] = 0;
            }
        }
    }
    for (int i = 0; i < f; ++i) {
        int fid = i + n + n;
        g[sidx][fid] = food_cnt[i];
        g[fid][sidx] = 0;
    }
    for (int i = 0; i < d; ++i) {
        int did = i + n + n + f;
        g[did][tidx] = drink_cnt[i];
        g[tidx][did] = 0;
    }
}

bool bfs(int s, int t)
{
    memset(dfn, -1, sizeof(dfn));
    dfn[s] = 0;
    std::queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v <= tidx; ++v) {
            if (g[u][v] > 0 && dfn[v] == -1) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
            }
        }
    }

    return dfn[t] != -1;
}
int dfs(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    int res = 0;
    for (int v = 0; v <= tidx; ++v) {
        if (g[u][v] > 0 && dfn[v] == dfn[u] + 1) {
            int d = dfs(v, t, min(g[u][v], f - res));
            g[u][v] -= d;
            g[v][u] += d;
            res += d;
            if (res == f) {
                break;
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
    while (bfs(sidx, tidx)) {
        maxflow += dfs(sidx, tidx, 0x3F3F3F3F);
        _DEBUG_CMD(printf("new maxflow: %d\n", maxflow));
    }
    return maxflow;
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d%d", &n, &f, &d)) {
        init_graph();
        for (int i = 0; i < f; ++i) {
            scanf("%d", &food_cnt[i]);
        }
        for (int i = 0; i < d; ++i) {
            scanf("%d", &drink_cnt[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s", fa[i]);
            _DEBUG_CMD(printf("fa[%d]:%s\n", i, fa[i]));
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s", da[i]);
            _DEBUG_CMD(printf("da[%d]:%s\n", i, da[i]));
        }
        build_graph();
        _DEBUG_CMD(debug_print());
        int res = dinic();
        printf("%d\n", res);
    }
    return 0;
};

#endif
