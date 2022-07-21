#ifndef _t12ps_20200329_
#define _t12ps_20200329_
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

const int MAXN = 1 << 11;
int N;
int elev[MAXN];
int sorted_elev[MAXN];
int dp[MAXN][MAXN];

// 如果以 dp[i][j] 为从前 i 个元素中, 取队列最后一个值为第 j 个元素的值所需要的最小成本
// 最大的问题就是状态转移方程不好算: 这里会损失无后效性:
// 例如: 1 5 2 3, 如果 dp[0][0] = 0, dp[1][0] = 4, dp[1][1] = 0, dp[2][0] = 4 + 1, dp[2][1] = 3
// 计算 dp[2][2] 的时候就会有问题: 因为 dp[2][2] 无法从之前的最优子结构中推导出来,
// 2 这个元素会降低 5 这个元素的阈值, 必须前向搜索, 查找合适的位置d dp[i-1][k]
// dp[2][2] 不能轻松由 dp[1][0~1] 轻松的出来. 导致这里成为一个复杂的推导.

// 如果将这个第二维度, 按照大小排序, 这个问题会简单很多, 参见:
// https://blog.csdn.net/weixin_45508368/article/details/101215625

int main(int argc, char **argv)
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &elev[i]);
    }
    memcpy(sorted_elev, elev, sizeof(sorted_elev));
    sort(sorted_elev, sorted_elev + N);
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < N; ++i) {
        dp[0][i] = abs(elev[i] - elev[0]);
    }
    for (int i = 1; i < N; ++i) {
        int min_cost = 0x3F3F3F3F;
        for (int j = 0; j < N; ++j) {
            // dp[i][j] = min(dp[i][j])
            min_cost = min(min_cost, dp[i - 1][j]);
            dp[i][j] = abs(elev[i] - sorted_elev[j]) + min_cost;
        }
    }
    _DEBUG_CMD({
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                cout << dp[i][j] << ' ';
            }
            cout << endl;
        }
    });
    cout << *min_element(&dp[N - 1][0], &dp[N - 1][N]) << endl;
    return 0;
};

#endif
