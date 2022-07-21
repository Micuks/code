#ifndef _t22pe_20210924_
#define _t22pe_20210924_
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
const int INF = 0x3F3F3F3F;
int dp[MAXN][MAXN], num[MAXN], N;

int solve(int l, int r)
{
    if (dp[l][r] != INF) {
        return dp[l][r];
    }
    if (l == r) {
        return dp[l][r] = num[l] * num[l + 1] * num[l - 1];
    }
    if (l > r) {
        return 0;
    }
    int minval = INF, minidx = INF;
    for (int i = l; i <= r; ++i) {
        int lval = num[l - 1];
        int rval = num[r + 1];
        int thisval = lval * num[i] * rval + solve(l, i - 1) + solve(i + 1, r);
        if (thisval < dp[l][r]) {
            dp[l][r] = thisval;
        }
    }
    return dp[l][r];
}

int main(int argc, char **argv)
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", num + i);
    }
    memset(dp, 0x3F, sizeof(dp));
    int ans = solve(1, N - 2);
    printf("%d\n", ans);
    return 0;
};

#endif
