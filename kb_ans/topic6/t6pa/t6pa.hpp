#ifndef _t6pa_20200108_
#define _t6pa_20200108_
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

const int MAXN = 1024;
int n;
int f[MAXN];
int r[MAXN];
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
    if (xroot == yroot) {
        return xroot;
    }
    if (r[xroot] > r[yroot])
        return f[yroot] = xroot;
    else {
        f[xroot] = yroot;
        if (r[xroot] == r[yroot])
            r[yroot]++;
        return yroot;
    }
}
struct Edge {
    int ori, dst;
    int val;
    bool operator<(const Edge &e) const { return val < e.val; };
    Edge(int ori = 0, int dst = 0, int val = 0) : ori(ori), dst(dst), val(val) {}
} edges[MAXN];
int edge_cnt;
int roads[MAXN][MAXN];

int main(int argc, char **argv)
{
    char s[32], e[32];
    int k, val;
    while (cin >> n && n != 0) {
        memset(roads, 0x3F, sizeof(roads));
        memset(r, 0, sizeof(r));
        for (int i = 0; i < 256; ++i) {
            f[i] = i;
        }
        edge_cnt = 0;
        for (int i = 1; i < n; ++i) {
            scanf("%s%d", s, &k);
            for (int j = 0; j < k; ++j) {
                scanf("%s%d", e, &val);
                edges[edge_cnt].ori = s[0];
                edges[edge_cnt].dst = e[0];
                edges[edge_cnt].val = val;
                edge_cnt++;
            }
        }
        _DEBUG_CMD({
            cout << "edges[i]: ";
            for (int i = 0; i < edge_cnt; ++i) {
                cout << edges[i].ori << ' ' << edges[i].dst << ' ' << edges[i].val << '\t';
            }
            cout << endl;
        });
        int res = 0;
        sort(edges, edges + edge_cnt);
        for (int i = 0; i < edge_cnt; ++i) {
            const Edge &e = edges[i];
            if (find(e.ori) != find(e.dst)) {
                union_set(e.ori, e.dst);
                res += e.val;
            }
        }
        _DEBUG_CMD({
            cout << "f[i]: ";
            for (int i = 'A'; i <= 'Z'; ++i) {
                cout << f[i] - 'A' << ' ';
            }
            cout << endl;
        });
        cout << res << endl;
    }
    return 0;
};

#endif
