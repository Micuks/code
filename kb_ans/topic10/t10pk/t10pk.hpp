#ifndef _t10pk_20210219_
#define _t10pk_20210219_
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

const int MAXN = 1 << 9;
const int MAXM = MAXN * 10;
int n, m;

struct Edge {
    int u, v, next;
} edges[MAXM * 100];

int ecnt = 0;
int head[MAXN];

void add_edge(int u, int v)
{
    edges[ecnt].next = head[u];
    edges[ecnt].u = u;
    edges[ecnt].v = v;
    head[u] = ecnt++;
}

void floyd_wrong()
{
    int oecnt = ecnt;
    for (int i = 0; i < oecnt; ++i) {
        const Edge &e = edges[i];
        // for (int j = head[e.v]; j != -1; j = edges[j].next) {
        for (int j = 0; j < oecnt; ++j) {
            if (edges[j].u != e.v) {
                continue;
            }
            for (int k = 0; k < oecnt; ++k) {
                if (edges[k].v == e.u) {
                    add_edge(edges[k].u, edges[j].v);
                }
            }
        }
    }
}

char g[MAXN][MAXN];
void floyd()
{
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                g[i][j] = g[i][j] || (g[i][k] && g[k][j]);
            }
        }
    }
}

int match[MAXN];
char visited[MAXN];
int dfs(int u)
{
    for (int i = 1; i <= n; ++i) {
        if (g[u][i] != 0 && visited[i] == 0) {
            visited[i] = 1;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = u;
                return 1;
            }
        }
    }
    return 0;
}
int dfs_wrong(int u)
{
    for (int h = head[u]; h != -1; h = edges[h].next) {
        const Edge &e = edges[h];
        if (visited[e.v] == 0) {
            visited[e.v] = 1;
            if (match[e.v] == -1 || dfs(match[e.v])) {
                match[e.v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int hungarian()
{
    int ret = 0;
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= n; ++i) {
        memset(visited, 0, sizeof(visited));
        ret += dfs(i);
    }
    return ret;
}

int main(int argc, char **argv)
{
    int a, b;
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        memset(head, -1, sizeof(head));
        ecnt = 0;
        memset(g, 0, sizeof(g));
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &a, &b);
            // add_edge(a, b);
            g[a][b] = 1;
        }
        _DEBUG_CMD(printf("after adding edges: ecnt:%d\n", ecnt));
        floyd();
        _DEBUG_CMD(printf("after floyd: ecnt:%d\n", ecnt));
        printf("%d\n", n - hungarian());
    }
    return 0;
};

#endif
