#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 10005;
struct Node {
    int px, dx;
    friend bool operator<(const Node &a, const Node &b) { return a.px > b.px; }
} arr[N];

int f[N], _rank[N], n;
inline void init(int n)
{
    for (int i = 0; i <= n; ++i)
        f[i] = i, _rank[i] = 0;
}
int find(int x)
{
    int i, j = x;
    while (j != f[j])
        j = f[j];
    while (x != j) {
        i = f[x];
        f[x] = j;
        x = i;
    }
    return j;
}

int main()
{
    while (~scanf("%d", &n)) {
        int maxTime = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &arr[i].px, &arr[i].dx);
            if (arr[i].dx > maxTime)
                maxTime = arr[i].dx;
        }
        init(maxTime);
        sort(arr, arr + n);
        bool vis[N];
        int ans = 0, pos = 0;
        for (int i = 0; i < n; ++i) {
            int d = find(arr[i].dx);
            if (d > 0) {
                ans += arr[i].px;
                f[d] = d - 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

#else
#ifndef _t5pg_20200102_
#define _t5pg_20200102_
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
int n;
struct Node {
    int pi;
    int di;
    bool operator<(const Node &n) const { return pi > n.pi; }
} node[MAXN];
int f[MAXN];

int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    return f[x] = find(f[x]);
}
int union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    return f[yroot] = xroot;
}

int main(int argc, char **argv)
{
    while (cin >> n) {
        int max_t = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &node[i].pi, &node[i].di);
            if (max_t < node[i].di)
                max_t = node[i].di;
        }
        for (int i = 0; i <= max_t; ++i) {
            f[i] = i;
        }
        sort(node, node + n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int d = find(node[i].di);
            if (d > 0) {
                ans += node[i].pi;
                f[d] = d - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
};

#endif
#endif
