#ifndef _t10pm_20210223_
#define _t10pm_20210223_
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

const int MAXN = 1 << 10;
const int MAXM = 1 << 9;
int n, m;
// map<string, int> name_map;
vector<string> name;

char g[MAXN][MAXM];
int visited[MAXN], match[MAXM][MAXN], cap[MAXM];

int dfs(int u, int max_cap)
{
    for (int v = 0; v < m; ++v) {
        if (g[u][v] != 0 && visited[v] == 0) {
            visited[v] = 1;
            if (cap[v] < max_cap) {
                match[v][cap[v]++] = u;
                return 1;
            }
            for (int i = 0; i < cap[v]; ++i) {
                if (dfs(match[v][i], max_cap)) {
                    match[v][i] = u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool hungarian(int max_cap)
{
    memset(cap, 0, sizeof(cap));
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; ++i) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i, max_cap) != 1) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    // string n;
    while (~scanf("%d%d\n", &n, &m) && (n || m)) {
        // name_map.clear();
        name.clear();
        name.resize(n);
        memset(g, 0, sizeof(g));
        _DEBUG_CMD(printf("n:%d m:%d\n", n, m));
        for (int i = 0; i < n; ++i) {
            string line;
            getline(cin, line);
            stringstream ss(line);
            ss >> name[i];
            // name_map[name[i]] = i;
            int gp_id;
            while (ss >> gp_id) {
                g[i][gp_id] = 1;
            }
        }
        int lo = n / m, hi = n;
        // int lo = 1, hi = n;
        int res = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (hungarian(mid)) {
                hi = mid - 1;
                res = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        // assert(res == lo);
        printf("%d\n", res);
        // std::getline(cin, line);
    }
    return 0;
};

#endif
