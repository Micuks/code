#ifndef _t21pg_20210830_
#define _t21pg_20210830_
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

const int MAXN = 1e5 + 3;
int T, n;
// double dp[MAXN][MAXN];
double dp[MAXN];

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        scanf("%d", &n);
        fill_n(dp, MAXN, 0);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i) {
            dp[i] = dp[i + 1] + n / double(n - i);
        }
        printf("Case %d: %lf\n", cc, dp[0]);
    }
    return 0;
};

#endif
