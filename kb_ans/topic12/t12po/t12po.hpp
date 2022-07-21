#ifndef _t12po_20200327_
#define _t12po_20200327_
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

const long MAXN = 1 << 11;
long N;
long v[MAXN];
long dp[MAXN][MAXN];
long acc[MAXN][MAXN];
long sum[MAXN];

long get_acc(long s, long e)
{
    if (acc[s][e] != 0) {
        return acc[s][e];
    }
    return acc[s][e] = accumulate(&v[s], &v[e], 0l);
}

long solve(long s, long e, long n)
{
    if (dp[s][e] != 0) {
        return dp[s][e];
    }
    if (s == e) {
        return 0;
    }
    // dp[s][e] = max(solve(s + 1, e, n - 1) + v[s] + accumulate(&v[s + 1], &v[e], 0),
    //               solve(s, e - 1, n - 1) + v[e - 1] + accumulate(&v[s], &v[e - 1], 0));
    // dp[s][e] = max(solve(s + 1, e, n - 1), solve(s, e - 1, n - 1)) + accumulate(&v[s], &v[e], 0);
    // dp[s][e] = max(solve(s + 1, e, n - 1), solve(s, e - 1, n - 1)) + get_acc(s, e);
    dp[s][e] = max(solve(s + 1, e, n - 1), solve(s, e - 1, n - 1)) + sum[e] - sum[s];
    return dp[s][e];
}

int main(int argc, char **argv)
{
    // cin >> N;
    scanf("%ld", &N);
    for (long i = 0; i < N; ++i) {
        scanf("%ld", &v[i]);
    }
    memset(dp, 0, sizeof(dp));
    memset(acc, 0, sizeof(acc));
    memset(sum, 0, sizeof(sum));
    // sum[0] = v[0];
    // sum[0] = 0;
    for (int i = 1; i <= N; ++i) {
        sum[i] = sum[i - 1] + v[i - 1];
    }
    long max_val = solve(0, N, N);
    cout << max_val << endl;
    return 0;
};

#endif
