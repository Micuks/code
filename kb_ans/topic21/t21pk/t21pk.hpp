#ifndef _t21pk_20210903_
#define _t21pk_20210903_
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

const int MAXN = 16;
double dp[MAXN][1 << MAXN];
int reachable[MAXN][1 << MAXN];
int g[1 << 7][1 << 7];
int T, n, m, u, v, w;

int dfs(int u, int s)
{
    if (s == ((1 << n) - 1)) {
        dp[u][s] = 0;
        // reachable[u][s] = 1;
        return 1;
    }
    if (reachable[u][s] != -1)
        return reachable[u][s];
    int cnt = 0;
    double weight = 0;
    for (int i = 0; i < n; ++i) {
        int news = (1 << i) | s;
        if (g[u][i] != 0 && ((1 << i) & s) == 0 && dfs(i, news)) {
            ++cnt;
            weight += dp[i][news] + g[u][i];
        }
    }
    if (cnt) {
        weight += 5;
        weight /= cnt;
        dp[u][s] = weight;
        reachable[u][s] = 1;
        return 1;
    }

    dp[u][s] = 0;
    reachable[u][s] = 0;
    return 0;
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        scanf("%d%d", &n, &m);
        memset(g, 0, sizeof(g));
        memset(dp, 0, sizeof(dp));
        memset(reachable, -1, sizeof(reachable));
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = g[v][u] = w;
        }
        dfs(0, 1);
        double ans = dp[0][1];
        printf("Case %d: %lf\n", cc, ans);
    }
    return 0;
};

#endif
