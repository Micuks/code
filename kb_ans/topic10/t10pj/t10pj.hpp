#ifndef _t10pj_20210213_
#define _t10pj_20210213_
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

int t, n, e;

const int MAXN = 1 << 8;
struct {
    int v;
    int next;
} edges[MAXN * 20];
int head[MAXN], ecnt;

void add_edge(int u, int v)
{
    edges[ecnt].next = head[u];
    edges[ecnt].v = v;
    head[u] = ecnt++;
}

char visited[MAXN], match[MAXN];
int dfs(int u)
{
    for (int h = head[u]; h != -1; h = edges[h].next) {
        const int v = edges[h].v;
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
    for (int i = 1; i <= n; ++i) {
        memset(visited, 0, sizeof(visited));
        ret += dfs(i);
    }
    return ret;
}

int main(int argc, char **argv)
{
    int a, b;
    scanf("%d", &t);
    for (int cc = 1; cc <= t; ++cc) {
        memset(head, -1, sizeof(head));
        ecnt = 0;
        scanf("%d%d", &n, &e);
        for (int i = 0; i < e; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        printf("%d\n", n - hungarian());
    }
    return 0;
};

#endif
