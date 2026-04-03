#ifndef _t10pr_20210618_
#define _t10pr_20210618_
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
int n;
int g[MAXN][MAXN];
int match[MAXN], pre[MAXN], visit[MAXN], fa[MAXN], dfn[MAXN], tim;
int que[MAXN], qhead, qtail;
int pt[MAXN];

int ufind(int x) { return fa[x] == x ? x : fa[x] = ufind(fa[x]); }
int LCA(int x, int y)
{
    ++tim;
    x = ufind(x);
    y = ufind(y);
    while (dfn[x] != tim) {
        dfn[x] = tim;
        x = ufind(pre[match[x]]);
        if (y)
            std::swap(x, y);
    }
    return x;
}

queue<int> Q;
void blossom(int x, int y, int lcaRoot)
{
    while (ufind(x) != lcaRoot) {
        pre[x] = y, y = match[x];
        if (visit[y] == 2)
            visit[y] = 1, Q.push(y);
        if (ufind(x) == x)
            fa[x] = lcaRoot;
        if (ufind(y) == y)
            fa[y] = lcaRoot;
        x = pre[y];
    }
}

bool augment(int s)
{
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    memset(visit, 0, sizeof(visit));
    memset(pre, 0, sizeof(pre));

    // std::swap(Q, std::queue<int>());
    while (!Q.empty())
        Q.pop();
    Q.push(s);
    visit[s] = 1; // black node, 2 denotes white node

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v = 1; v <= n; ++v) {
            if (g[u][v] == 0) {
                continue;
            }
            if (ufind(u) == ufind(v) || visit[v] == 2) {
                continue;
            }
            if (!visit[v]) {
                visit[v] = 2;
                pre[v] = u;
                if (!match[v]) {
                    for (int x = v, lst; x; x = lst) {
                        lst = match[pre[x]], match[x] = pre[x], match[pre[x]] = x;
                    }
                    return true;
                }
                visit[match[v]] = 1, Q.push(match[v]);
            }
            else {
                int root = LCA(u, v);
                blossom(u, v, root);
                blossom(v, u, root);
            }
        }
    }
    return false;
}

int blossom_km()
{
    int ans = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; ++i) {
        if (!match[i]) {
            ans += augment(i);
        }
    }
    return ans;
}

int main(int argc, char **argv)
{
    scanf("%d", &n);
    int u, v;
    while (~scanf("%d%d", &u, &v)) {
        g[u][v] = g[v][u] = 1;
    }
    int c = blossom_km();
    printf("%d\n", c * 2);
    for (int i = 1; i <= n; ++i) {
        if (pt[i] == 0 && match[i] != 0) {
            pt[i] = 1;
            pt[match[i]] = 1;
            printf("%d %d\n", i, match[i]);
        }
    }
    return 0;
};

#endif
