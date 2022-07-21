#ifndef _t10pc_20210129_
#define _t10pc_20210129_
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

const int MAXN = 1 << 9;
int g[MAXN][MAXN];
int case_cnt;
int N, P;

int visited[MAXN], match[MAXN];

int hungarian(int u)
{
    // visited[u] = 1;
    for (int i = 1; i <= P + N; ++i) {
        if (g[u][i] != 0 && visited[i] == 0) {
            visited[i] = 1;
            if (match[i] == 0 || hungarian(match[i])) {
                match[i] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    int cnt, sid;
    scanf("%d", &case_cnt);
    for (int i = 0; i < case_cnt; ++i) {
        memset(g, 0, sizeof(g));
        memset(match, 0, sizeof(match));
        scanf("%d%d", &P, &N);
        for (int j = 1; j <= P; ++j) {
            scanf("%d", &cnt);
            for (int k = 0; k < cnt; ++k) {
                scanf("%d", &sid);
                g[j][P + sid] = g[P + sid][j] = 1;
            }
        }
        int ans = 0;
        for (int j = 1; j <= P; ++j) {
            memset(visited, 0, sizeof(visited));
            ans += hungarian(j);
        }
        if (ans == P) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
};

#endif
