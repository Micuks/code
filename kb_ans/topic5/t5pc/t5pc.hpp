#ifndef _t5pc_20191230_
#define _t5pc_20191230_
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

int T;
const int MAXN = 1024;
int f[MAXN];
int N, M;

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
bool same_group(int x, int y) { return find(x) == find(y); }

int main(int argc, char **argv)
{
    int a, b;
    cin >> T;
    while (T--) {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; ++i) {
            f[i] = i;
        }
        for (int i = 1; i <= M; ++i) {
            scanf("%d%d", &a, &b);
            union_set(a, b);
        }
        _DEBUG_CMD({
            cerr << "f[]: ";
            for (int i = 1; i <= N; ++i)
        });
        set<int> table_cnt;
        for (int i = 1; i <= N; ++i) {
            table_cnt.insert(find(i));
        }
        cout << table_cnt.size() << endl;
    }
    return 0;
};

#endif
