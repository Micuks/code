#ifndef _t10pf_20210130_
#define _t10pf_20210130_
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

const int MAXN = 1 << 12;
int xarr[MAXN], yarr[MAXN], spd[MAXN];
int case_cnt, rt, m, n, s;

char g[MAXN][MAXN], visited[MAXN];
int mx[MAXN], my[MAXN];
int lx[MAXN], ly[MAXN];

bool dist_in(int x1, int y1, int x2, int y2, long d)
{
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= d * d;
}

int dist;

bool bfs()
{
    queue<int> q;
    dist = 1e8;
    memset(lx, -1, sizeof(lx));
    memset(ly, -1, sizeof(ly));
    for (int i = 1; i <= m; ++i) {
        if (mx[i] == -1) {
            q.push(i);
            lx[i] = 0;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (lx[u] > dist) {
            break;
        }
        for (int v = 1; v <= n; ++v) {
            if (g[u][v] != 0 && ly[v] == -1) {
                ly[v] = lx[u] + 1;
                if (my[v] == -1) {
                    dist = ly[v];
                }
                else {
                    lx[my[v]] = ly[v] + 1;
                    q.push(my[v]);
                }
            }
        }
    }

    return dist != 1e8;
}

int dfs(int u)
{
    /*
    for (int v = 1; v <= n; ++v) {
        if (g[u][v] && visited[v] == 0) {
            visited[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
    */
    for (int v = 1; v <= n; ++v) {
        if (g[u][v] != 0) {
            if (visited[v] == 0 && ly[v] == lx[u] + 1) {
                visited[v] = 1;
                if (my[v] != -1 && ly[v] == dist) {
                    continue;
                }
                if (my[v] == -1 || dfs(my[v])) {
                    my[v] = u;
                    mx[u] = v;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int hungarian()
{
    int ans = 0;
    /*
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= m; ++i) {
        memset(visited, 0, sizeof(visited));
        ans += dfs(i);
    }
    */
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    while (bfs()) {
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= m; ++i) {
            if (mx[i] == -1 && dfs(i)) {
                ans += 1;
            }
        }
    }
    return ans;
}

int main(int argc, char **argv)
{
    int xpos, ypos;
    scanf("%d", &case_cnt);
    for (int i = 0; i < case_cnt; ++i) {
        memset(g, 0, sizeof(g));
        scanf("%d%d", &rt, &m);
        for (int j = 0; j < m; ++j) {
            scanf("%d%d%d", &xarr[j], &yarr[j], &spd[j]);
        }
        scanf("%d", &n);
        for (int j = 0; j < n; ++j) {
            scanf("%d%d", &xpos, &ypos);
            for (int k = 0; k < m; ++k) {
                if (dist_in(xarr[k], yarr[k], xpos, ypos, rt * spd[k])) {
                    g[k + 1][j + 1] = 1;
                }
            }
        }
        int ans = hungarian();
        printf("Scenario #%d:\n%d\n\n", i + 1, ans);
    }
    return 0;
};

#endif
