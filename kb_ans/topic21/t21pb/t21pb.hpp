#if 0
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int v[maxn];
double dp[maxn];

int main()
{
    int T;
    scanf("%d", &T);
    int kase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &v[i]);
        }
        memset(dp, 0, sizeof(dp));
        dp[1] = 1.0;
        for (int i = 1; i <= n; ++i) {
            int k = min(6, n - i);
            for (int j = 1; j <= k; ++j) {
                dp[i + j] += dp[i] * 1.0 / k;
            }
        }
        double ans = 0.0;
        for (int i = 1; i <= n; ++i) {
            ans += dp[i] * v[i];
        }
        printf("prob: ");
        for (int i = 0; i <= n; ++i) {
            printf("%.7f ", dp[i]);
        }
        printf("\n");
        printf("dt: ");
        for (int i = 0; i <= n; ++i) {
            printf("%.7f ", dp[i] * v[i]);
        }
        printf("\n");
        printf("Case %d: %.7lf\n", ++kase, ans);
    }
    return 0;
}
// https://wutao18.github.io/2019/10/13/LightOJ-1030-Discovering-Gold-%E6%A6%82%E7%8E%87-%E6%9C%9F%E6%9C%9BDP/
#elif 0
#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <math.h>
#include <memory.h>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;

double Dp[110];
int a[110];
int n;

int main()
{
    int t, cnt = 0;
    scanf("%d", &t);
    while (t--) {
        memset(Dp, 0, sizeof(Dp));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        Dp[n] = a[n];
        for (int i = n - 1; i >= 1; i--) {
            Dp[i] += a[i];
            int step = min(6, n - i);
            for (int j = 1; j <= step; j++)
                Dp[i] += (1.0 / step) * Dp[i + j];
        }
        printf("dp: ");
        for (int i = 1; i < n; ++i) {
            printf("%.3lf ", Dp[i]);
        }
        printf("\n");
        printf("Case %d: %.7lf\n", ++cnt, Dp[1]);
    }

    return 0;
}

#else
#ifndef _t21pb_20210824_
#define _t21pb_20210824_
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
int T, N;
int cave[MAXN];
double dp[MAXN];
double prob[MAXN];

pair<double, double> solve(int k)
{
    if (dp[k] != -1.0f) {
        _DEBUG_CMD(printf("dp[%d]:%lf\n", k, dp[k]));
        return pair<double, double>(dp[k], prob[k]);
    }
    int source = k >= 6 ? 6 : k;
    double r = 0;
    double pk = 0;
    for (int i = k - 1; i >= k - source; --i) {
        int ul = (N - i - 1) > 6 ? 6 : (N - i - 1);
        double f = 1.0l / ul;
        _DEBUG_CMD(
            printf("to k:%d, cave[%d]:%d oldr:%lf from: solve(%d):%lf, f:%lf, gain:%lf ul:%d\n", k,
                   k, cave[k], r, i, solve(i), f, solve(i) * f, ul));
        // r += solve(i) * f;
        pair<double, double> pi = solve(i);
        // P(D) = P(D|A) * P(A) + P(D|B) * P(B) + P(D|C) * P(C)
        // f: P(D|A), pi.second: P(A)
        pk += f * pi.second;
        // r += pi.second * pi.first; // G(A) = P(A) * W(A)

        // r += solve(i);
    }
    // dp[k] = r / source + cave[k];
    dp[k] = pk * cave[k];
    prob[k] = pk;
    _DEBUG_CMD(printf("k:%d r:%lf source:%d dp[k]:%lf\n", k, r, source, dp[k]););
    return pair<double, double>(dp[k], prob[k]);
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int case_cnt = 1; case_cnt <= T; ++case_cnt) {
        scanf("%d", &N);
        // memset(dp, -1, sizeof(dp));
        fill_n(dp, MAXN, -1.0f);
        fill_n(prob, MAXN, 0);
        fill_n(cave, MAXN, 0);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &cave[i]);
        }
        dp[0] = cave[0];
        prob[0] = 1;
        // double ans = solve(N - 1);
        solve(N - 1);
        double r = 0;
        for (int i = 0; i < N; ++i) {
            r += dp[i];
        }
        printf("Case %d: %.6lf\n", case_cnt, r);
        _DEBUG_CMD({
            if (case_cnt == 11 || case_cnt == 48 || case_cnt == 63 || case_cnt == 64) {
                printf("case:%d\n", case_cnt);
                printf("%d\n", N);
                for (int k = 0; k < N; ++k) {
                    printf("%d ", cave[k]);
                }
                printf("\n");
            }
        });
        _DEBUG_CMD({
            /*
            printf("cave: ");
            for (int i = 0; i <= N; ++i) {
                printf("%d ", cave[i]);
            }
            printf("\n");
            */
            printf("dp: ");
            for (int i = 0; i <= N; ++i) {
                printf("%lf ", dp[i]);
            }
            printf("\n");
        });
    }
    return 0;
};

#endif
#endif
