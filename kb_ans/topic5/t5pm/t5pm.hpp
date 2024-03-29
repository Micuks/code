#ifndef _t5pm_20200106_
#define _t5pm_20200106_
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
int f[MAXN];
int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    return f[x] = find(f[x]);
}

bool union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        return false;
    }
    f[yroot] = xroot;
    return true;
}

void init()
{
    for (int i = 0; i < MAXN; ++i) {
        f[i] = i;
    }
}

int main(int argc, char **argv)
{
    int x, y;
    int max_cnt = 0;
    bool success = true;
    set<int> rooms;
    init();
    while (cin >> x >> y && x != -1 && y != -1) {
        max_cnt = max(max(x, y), max_cnt);
        if (x == 0 || y == 0) {
            set<int> connectivity;
            for (int i = 1; i <= max_cnt; ++i) {
                find(i);
            }
            for (int i = 1; i <= max_cnt; ++i) {
                if (rooms.find(i) != rooms.end())
                    connectivity.insert(f[i]);
            }
            if (!success || connectivity.size() > 1) {

                printf("No\n");
            }
            else {
                printf("Yes\n");
            }
            init();
            success = true;
            max_cnt = 0;
            rooms.clear();
            continue;
        }
        rooms.insert(x);
        rooms.insert(y);
        if (!union_set(x, y)) {
            success = false;
        }
    }
    return 0;
};

#endif
