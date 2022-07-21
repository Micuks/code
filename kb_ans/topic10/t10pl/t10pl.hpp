#ifndef _t10pl_20210221_
#define _t10pl_20210221_
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

int N, M, P;
const int MAXN = 1 << 7;
const int MAXM = 1 << 7;
const int MAXP = 1 << 9;

char g[MAXP][MAXP];
char dlc[MAXP];
int dli[MAXP];
char llc[MAXP];
int lli[MAXP];

int match[MAXP], visited[MAXP];

int dfs(int u)
{
    for (int i = 0; i < P; ++i) {
        if (g[u][i] && visited[i] == 0) {
            visited[i] = 1;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = u;
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
    for (int i = 0; i < P; ++i) {
        memset(visited, 0, sizeof(visited));
        ret += dfs(i);
    }
    return ret;
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d%d\n", &N, &M, &P)) {
        memset(g, 0, sizeof(g));
        for (int i = 0; i < P; ++i) {
            scanf("%c%d %c%d\n", &llc[i], &lli[i], &dlc[i], &dli[i]);
        }
        for (int i = 0; i < P; ++i) {
            for (int j = 0; j < P; ++j) {
                if (llc[i] == dlc[j] && lli[i] == dli[j]) {
                    g[i][j] = 1;
                    g[j][i] = 1;
                    _DEBUG_CMD({ printf("add edge between %d&%d\n", i, j); });
                }
            }
        }
        printf("%d\n", P - hungarian() / 2);
    }
    return 0;
};

#endif
