#ifndef _t21pc_20210829_
#define _t21pc_20210829_
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
double dp[MAXN];
int T, N;

int main(int argc, char **argv)
{
    scanf("%d", &T);
    dp[1] = 0;
    for (int i = 2; i < MAXN; ++i) {
        int divisor_cnt = 0;
        double val = 0;
        for (int j = 1; j * j <= i; ++j) {
            if (i % j == 0) {
                divisor_cnt++;
                val += dp[j];
                if (j != i / j) {
                    divisor_cnt++;
                    val += dp[i / j];
                }
            }
        }
        dp[i] = (divisor_cnt + val) / (divisor_cnt - 1);
    }

    // printf("dp[2]:%lf\n", dp[2]);
    for (int case_cnt = 1; case_cnt <= T; ++case_cnt) {
        scanf("%d", &N);
        printf("Case %d: %.7lf\n", case_cnt, dp[N]);
    }
    return 0;
};

#endif
