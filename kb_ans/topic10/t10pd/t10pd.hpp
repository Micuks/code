#ifndef _t10pd_20210130_
#define _t10pd_20210130_
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

const int MAXN = 1 << 7;
int g[MAXN][MAXN];
int N, M, K;

int visited[MAXN], match[MAXN], match_record[MAXN];

int dfs(int u)
{
    for (int v = 1; v <= M; ++v) {
        if (g[u][v] != 0 && visited[v] == 0) {
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
    memset(match, -1, sizeof(match));
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        ans += dfs(i);
    }
    return ans;
}

int main(int argc, char **argv)
{
    int a, b;
    int case_cnt = 0;
    while (~scanf("%d%d%d", &N, &M, &K)) {
        memset(g, 0, sizeof(g));
        for (int i = 0; i < K; ++i) {
            scanf("%d%d", &a, &b);
            g[a][b] = 1;
        }
        int mm = hungarian();
        memcpy(match_record, match, sizeof(match_record));
        int kpcnt = 0;
        for (int i = 1; i <= M; ++i) {
            if (match_record[i] != -1) {
                g[match_record[i]][i] = 0;
                int newmm = hungarian();
                g[match_record[i]][i] = 1;
                if (newmm < mm) {
                    ++kpcnt;
                }
            }
        }

        printf("Board %d have %d important blanks for %d chessmen.\n", ++case_cnt, kpcnt, mm);
    }
    return 0;
};

#endif
