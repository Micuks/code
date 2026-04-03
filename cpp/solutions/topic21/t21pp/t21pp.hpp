#ifndef _t21pp_20210911_
#define _t21pp_20210911_
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
int T, n, K, ncnt, pcnt;
int maze[MAXN];
double dp[MAXN];
double prob[MAXN], expect[MAXN];

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        int nsum = 0, psum = 0;
        ncnt = pcnt = 0;
        memset(dp, 0, sizeof(dp));
        memset(prob, 0, sizeof(prob));
        memset(expect, 0, sizeof(expect));
        scanf("%d%d", &n, &K);
        for (int i = 0; i < n; ++i) {
            scanf("%d", maze + i);
            if (maze[i] > 0) {
                ++pcnt;
                psum += maze[i];
            }
            else {
                ++ncnt;
                nsum += (-maze[i]);
            }
        }
        double navg = ncnt != 0 ? double(nsum) / ncnt : 0;
        double pavg = pcnt != 0 ? double(psum) / pcnt : 0;

        int ub = min(K, ncnt);
#if 0
        prob[0] = double(pcnt) / n;
        expect[0] = pavg;

        for (int i = 1; i < ub; ++i) {
            prob[i] = (1 - prob[i - 1]) * double(pcnt) / (n - i);
            expect[i] = navg * i + pavg;
        }
        if (K > ub) {
            prob[ub] = 1 - prob[ub - 1];
            expect[ub] = expect[ub - 1] + pavg;
        }
        else {
            prob[ub] = 1 - prob[ub - 1];
            expect[ub] = double(pcnt) / (K - ncnt) * pavg + navg + expect[ub - 1];
        }

        double ans = 0;
        for (int i = 0; i <= ub; ++i) {
            /*
            if (isnan(prob[i]) || isnan(expect[i]) || isinf(prob[i]) || isinf(expect[i])) {
                abort();
            }
            */
            ans += prob[i] * expect[i];
        }
        if (pcnt == 0) {
            ans = -1;
        }
#endif
        if (pcnt == 0) {
            printf("Case %d: -1\n", cc);
            continue;
        }
        dp[ub] = (pcnt * pavg + (ncnt - ub) * navg) / double(n - ncnt);
        for (int i = ub - 1; i >= 0; --i) {
            dp[i] = (pcnt * pavg + (ncnt - i) * (dp[i + 1] + navg)) / double(n - i);
        }
        printf("Case %d: %lf\n", cc, dp[0]);
    }
    return 0;
};

#endif
