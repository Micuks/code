#ifndef _t21pi_20210831_
#define _t21pi_20210831_
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

const int MAXN = 1 << 14;
int T, n, s, ycnt, ncnt;
double dp[2][MAXN][2];

int solve()
{
    int pid = 0, lid = 1;
    for (int i = n - 1; i >= 0; --i) {
        int lb = max(0, i - ncnt), ub = min(i, ycnt);
        for (int j = lb; j <= ub; ++j) {
            double pyes = double(ycnt - j) / (n - i);
            double pno = double(ncnt - (i - j)) / (n - i);
            dp[pid][j][0] = dp[lid][j + 1][0] * pyes + (dp[lid][j][1] + 1) * pno;
            dp[pid][j][1] = (dp[lid][j + 1][0] + 1) * pyes + dp[lid][j][1] * pno;
        }
        _DEBUG_CMD(printf("b %d chg, pid:%d lid:%d\n", i, pid, lid));
        swap(pid, lid);
        _DEBUG_CMD(printf("a %d chg, pid:%d lid:%d\n", i, pid, lid));
    }
    // return pid;
    return lid;
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        memset(dp, 0, sizeof(dp));
        scanf("%d%d", &n, &s);
        ycnt = s - 2 * n;
        ncnt = 3 * n - s;
        int u = solve();
        _DEBUG_CMD(printf("ycnt:%d ncnt:%d got %d from solve,\n", ycnt, ncnt, u));
        printf("Case %d: %lf\n", cc, dp[u][0][0]);
    }
    return 0;
};

#endif
