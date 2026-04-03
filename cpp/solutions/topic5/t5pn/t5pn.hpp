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
int in_degree[MAXN];

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
    ++in_degree[y];
    f[yroot] = xroot;
    return true;
}

void init()
{
    memset(in_degree, 0, sizeof(in_degree));
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
    int case_cnt = 1;
    init();
    while (cin >> x >> y && x != -1 && y != -1) {
        max_cnt = max(max(x, y), max_cnt);
        if (x == 0 || y == 0) {
            set<int> connectivity;
            bool in_degree_logic = true;
            bool root_found = false;
            for (int i = 1; i <= max_cnt; ++i) {
                find(i);
            }
            for (int i = 1; i <= max_cnt; ++i) {
                if (rooms.find(i) != rooms.end()) {
                    if (in_degree[i] > 1) {
                        in_degree_logic = false;
                    }
                    if (!root_found && in_degree[i] == 0) {
                        root_found = true;
                    }
                    else if (root_found && in_degree[i] == 0) {
                        in_degree_logic = false;
                    }
                    connectivity.insert(f[i]);
                }
            }
            if (!success || connectivity.size() > 1 || !in_degree_logic) {
                printf("Case %d is not a tree.\n", case_cnt++);
            }
            else {
                printf("Case %d is a tree.\n", case_cnt++);
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
