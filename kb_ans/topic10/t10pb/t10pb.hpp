#ifndef _t10pb_20210129_
#define _t10pb_20210129_
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
const int RED = 1;
const int BLACK = 2;
int g[MAXN][MAXN];
int color[MAXN];

int n, m;
int wcnt;

bool dfs(int u, int c)
{
    color[u] = c;
    if (c == BLACK) {
        ++wcnt;
    }
    int nextc = c == RED ? BLACK : RED;
    bool ret = true;
    for (int i = 1; i <= n; ++i) {
        if (g[u][i] != -1) {
            if (color[i] == 0) {
                ret = (ret && dfs(i, nextc));
            }
            else if (color[i] == c) {
                return false;
            }
        }
    }
    return ret;
}

int match[MAXN];
int visited[MAXN];

bool hungarian(int u)
{
    /*
    for (int i = 1; i < u; ++i) {
        if (g[u][i] != -1) {
            if (match[i] == 0 || hungrian(match[i])) {
                match[i] = u;
            }
        }
    }
    */
    for (int i = 1; i <= n; ++i) {
        if (g[u][i] != -1) {
            if (visited[i] == 0) {
                visited[i] = 1;
                if (match[i] == -1 || hungarian(match[i])) {
                    match[i] = u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    int a, b;
    while (~scanf("%d%d", &n, &m)) {
        wcnt = 0;
        memset(g, -1, sizeof(g));
        memset(color, 0, sizeof(color));
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &a, &b);
            g[a][b] = g[b][a] = 1;
        }
        bool bflag = true;
        for (int i = 1; i <= n; ++i) {
            if (color[i] == 0) {
                bflag = (bflag && dfs(i, RED));
            }
        }
        if (bflag) {
            //
            // printf("%d\n", max(wcnt, n - wcnt));
            int ans = 0;
            memset(match, -1, sizeof(match));
            for (int i = 1; i <= n; ++i) {
                memset(visited, 0, sizeof(visited));
                ans += hungarian(i);
            }
            printf("%d\n", ans / 2);
        }
        else {
            printf("No\n");
        }
    }
    return 0;
};

#endif
