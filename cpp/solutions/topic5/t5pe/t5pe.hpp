#ifndef _t5pe_20191231_
#define _t5pe_20191231_
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

const int MAXN = 50001;
int f[MAXN];
int v[MAXN];
int N, K;

int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    // v[x] += v[f[x]];
    int fid = find(f[x]);
    v[x] += v[f[x]];
    v[x] %= 3;
    return f[x] = fid;
}
int union_set(int x, int y, int d)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        if (d == 1 && v[x] != v[y])
            return 1;
        if (d == 2 && (v[x] + 1) % 3 != v[y])
            return 1;
    }
    f[yroot] = xroot;
    v[yroot] = (v[x] - v[y] + 3 + d - 1) % 3;
    return 0;
    // return 1 == (v[xroot] - v[yroot] + 3) % 3;
}
bool same_group(int x, int y) {}

int main(int argc, char **argv)
{
    int ans = 0;
    int d, x, y;
    cin >> N >> K;
    for (int i = 0; i <= N; ++i) {
        f[i] = i;
        v[i] = 0;
    }
    for (int i = 0; i < K; ++i) {
        scanf("%d%d%d", &d, &x, &y);
        if (x > N || y > N || (x == y && d == 2)) {
            ans++;
            DEBUG_CMD({ cerr << "N: " << N << " x: " << x << " y: " << y << " d: " << d << endl; });
            continue;
        }
        int tmp = union_set(x, y, d);
        DEBUG_CMD({
            if (tmp)
                cerr << "N: " << N << " x: " << x << " y: " << y << " d: " << d << " tmp: " << tmp
                     << endl;
        });
        ans += tmp;
    }
    cout << ans << endl;
    return 0;
};

#endif
