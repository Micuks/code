#ifndef _t22pg_20210926_
#define _t22pg_20210926_
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
int dp[MAXN][MAXN], boys[MAXN], acc[MAXN], T, n;

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        scanf("%d", &n);
        memset(acc, 0, sizeof(acc));
        for (int i = 0; i < n; ++i) {
            scanf("%d", boys + i);
            acc[i + 1] = acc[i] + boys[i];
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 0;
        }
        // DEBUG_CMD({ printf("n:%d\n", n); });
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                dp[i][j] = INF;
                for (int k = 1; k <= len; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i + 1][i + k - 1] + (k - 1) * boys[i] +
                                                 dp[i + k][j] + k * (acc[j + 1] - acc[i + k]));
                }
            }
        }

        int ans = dp[0][n - 1];
        printf("Case #%d: %d\n", cc, ans);
        _DEBUG_CMD({
            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j <= n; ++j) {
                    printf("%2d ", dp[i][j] == INF ? -1 : dp[i][j]);
                }
                printf("\n");
            }
        });
    }
    return 0;
};

#endif
