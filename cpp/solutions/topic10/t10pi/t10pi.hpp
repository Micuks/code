#ifndef _t10pi_20210212_
#define _t10pi_20210212_
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

const int MAXN = 1 << 11;
int n, t;

int head[MAXN], ecnt;
struct Edge {
    int v;
    int next;
} edges[MAXN * 20];

void add_edge(int u, int v)
{
    edges[ecnt].next = head[u];
    edges[ecnt].v = v;
    head[u] = ecnt++;
}

int visited[MAXN], match[MAXN];
int dfs(int u)
{
    for (int h = head[u]; h != -1; h = edges[h].next) {
        int v = edges[h].v;
        if (visited[v] == 0) {
            visited[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
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
    for (int i = 0; i < n; ++i) {
        memset(visited, 0, sizeof(visited));
        ret += dfs(i);
    }
    return ret;
}

int main(int argc, char **argv)
{
    // scanf("%d", &t);
    int node, ncnt, to;
    while (~scanf("%d", &n)) {
        // for (int cc = 1; cc <= t; ++cc) {
        // scanf("%d", &n);
        memset(head, -1, sizeof(head));
        ecnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d:(%d)", &node, &ncnt);
            for (int j = 0; j < ncnt; ++j) {
                scanf("%d", &to);
                add_edge(node, to);
                add_edge(to, node);
            }
        }
        printf("%d\n", hungarian() / 2);
    }
    return 0;
};

#endif
