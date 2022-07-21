#if 0
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define maxn 111
#define inf 99999999
int c[maxn];
int dp[maxn][maxn];
int main()
{
    int T, j = 1;
    scanf("%d", &T);
    while (T--) {
        memset(dp, 0, sizeof(dp));
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);
            dp[i][i] = 1;
        }
        for (int s = n - 1; s >= 1; s--) {
            for (int e = s + 1; e <= n; e++) {
                dp[s][e] = dp[s + 1][e] + 1;
                for (int k = s + 1; k <= e; k++) {
                    if (c[s] == c[k]) {
                        dp[s][e] = min(dp[s][e], dp[s + 1][k - 1] + dp[k][e]);
                        assert(s <= e);
                        assert(s + 1 <= k - 1);
                        assert(k <= e);
                    }
                }
            }
        }
        ///*
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                printf("%2d ", dp[i][j] == inf ? -1 : dp[i][j]);
            }
            printf("\n");
        }
        //*/
        printf("Case %d: %d\n", j++, dp[1][n]);
    }
}
// https://blog.csdn.net/acmer_hades/article/details/48055581
#else
#ifndef _t22pb_20210922_
#define _t22pb_20210922_
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

int T, N, c[MAXN];
int dp[MAXN][MAXN];

int solve(int alpha, int omega)
{
    if (dp[alpha][omega] != INF) {
        return dp[alpha][omega];
    }
    if (alpha == omega) {
        return dp[alpha][omega] = 1;
    }
    // not a key boundry condition
    /*
    if (alpha > omega) {
        return 0;
    }
    */
    int minval = INF;
    // key boundry condition here
    // plz refer to https://www.cnblogs.com/neopenx/p/4050003.html
    if (c[alpha] == c[omega]) {
        minval = min(minval, solve(alpha, omega - 1));
    }
    // interval dp// interval dp
    for (int k = alpha; k < omega; ++k) {
        if (c[alpha] == c[k]) {
            minval = min(minval, solve(alpha, k) + solve(k + 1, omega));
        }
    }
    return dp[alpha][omega] = min(dp[alpha][omega], minval);
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        memset(dp, 0x3F, sizeof(dp));
        memset(c, 0, sizeof(c));
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", c + i);
        }
        for (int i = 0; i < N; ++i) {
            dp[i][i] = 1;
        }
        /*
        for (int k = 1; k <= N; ++k) {
            for (int i = 0; i < N; ++i) {
                // dp[i][i + k] = min(dp[i][i + k], dp[i][i + k - 1] + 1);
                dp[i][i + k] = min(dp[i][i + k], dp[i][i + k - 1] + 1);
                int minval = INF;
                for (int j = 1; j <= k; ++j) {
                    if (c[i] == c[i + j]) {
                        // dp[i][i + k] = min(dp[i][i + k], dp[i][i + j] + dp[i + j + 1][i + k]);
                        minval = min(minval, dp[i][i + j - 1] + dp[i + j][i + k]);
                    }
                }
                dp[i][i + k] = min(dp[i][i + k], minval);
            }
        }
        */
        // int ans = dp[0][N - 1];
        int ans = solve(0, N - 1);
        _DEBUG_CMD({
            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= N; ++j) {
                    printf("%2d ", dp[i][j] == 0x3F3F3F3F ? -1 : dp[i][j]);
                }
                printf("\n");
            }
        });
        printf("Case %d: %d\n", cc, ans);
    }
    return 0;
};

#endif
#endif
