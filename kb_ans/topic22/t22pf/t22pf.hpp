#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define L(i) i << 1
#define R(i) i << 1 | 1
#define INF 0x3f3f3f3f
#define pi acos(-1.0)
#define eps 1e-3
#define maxn 100010
#define MOD 1000000007
struct node {
    int x, v;
    bool operator<(const node &a) const { return x < a.x; }
} a[1010];
int n, v, x;
int dp[1010][1010][2];
int sum[1010];

int main()
{
    int t, C = 1;
    while (scanf("%d%d%d", &n, &v, &x) != EOF) {
        memset(dp, INF, sizeof(dp));
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &a[i].x, &a[i].v);
        a[++n].x = x;
        a[n].v = 0;
        sort(a + 1, a + n + 1);
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + a[i].v;
        int tmp = 0;
        for (int i = 1; i <= n; i++)
            if (a[i].x == x)
                tmp = i;
        dp[tmp][tmp][0] = dp[tmp][tmp][1] = 0;
        for (int i = tmp; i > 0; i--)
            for (int j = tmp; j <= n; j++) {
                if (i == j)
                    continue;
                printf("l:%d r:%d dir:0 sentinal:%d di_multi:%d=sum[%d]:%d - sum[%d]:%d + "
                       "sum[%d]:%d ld:%d lsub:%d rd:%d rsub:%d new "
                       "lstate:%d rstate:%d\n",
                       i, j, tmp, sum[n] - sum[j] + sum[i], n, sum[n], j, sum[j], i, sum[i],
                       a[i + 1].x - a[i].x, dp[i + 1][j][0], a[j].x - a[i].x, dp[i + 1][j][1],
                       (sum[n] - sum[j] + sum[i]) * (a[i + 1].x - a[i].x) + dp[i + 1][j][0],
                       (sum[n] - sum[j] + sum[i]) * (a[j].x - a[i].x) + dp[i + 1][j][1]);
                dp[i][j][0] = min(dp[i][j][0], dp[i + 1][j][0] + (a[i + 1].x - a[i].x) *
                                                                     (sum[n] - sum[j] + sum[i]));
                dp[i][j][0] = min(dp[i][j][0],
                                  dp[i + 1][j][1] + (a[j].x - a[i].x) * (sum[n] - sum[j] + sum[i]));
                printf("l:%d r:%d dir:1 sentinal:%d di_multi:%d=sum[%d]:%d - sum[%d]:%d + "
                       "sum[%d]:%d ld:%d lsub:%d rd:%d rsub:%d new "
                       "lstate:%d rstate:%d\n",
                       i, j, tmp, sum[n] - sum[j - 1] + sum[i - 1], n, sum[n], j - 1, sum[j - 1],
                       i - 1, sum[i - 1], a[j].x - a[i].x, dp[i][j - 1][0], a[j].x - a[j - 1].x,
                       dp[i][j - 1][1],
                       (sum[n] - sum[j - 1] + sum[i - 1]) * (a[j].x - a[i].x) + dp[i][j - 1][0],
                       (sum[n] - sum[j - 1] + sum[i - 1]) * (a[j].x - a[j - 1].x) +
                           dp[i][j - 1][1]);
                dp[i][j][1] =
                    min(dp[i][j][1],
                        dp[i][j - 1][0] + (a[j].x - a[i].x) * (sum[n] - sum[j - 1] + sum[i - 1]));
                dp[i][j][1] =
                    min(dp[i][j][1], dp[i][j - 1][1] + (a[j].x - a[j - 1].x) *
                                                           (sum[n] - sum[j - 1] + sum[i - 1]));
            }
        printf("sums:\n");
        for (int i = 0; i <= n; ++i) {
            printf("%2d ", sum[i]);
        }
        printf("\n");
        printf("dp[0]:\n");
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                printf("%2d ", dp[i][j][0] == INF ? -1 : dp[i][j][0]);
            }
            printf("\n");
        }
        printf("dp[1]:\n");
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                printf("%2d ", dp[i][j][1] == INF ? -1 : dp[i][j][1]);
            }
            printf("\n");
        }
        printf("%d\n", v * min(dp[1][n][0], dp[1][n][1]));
    }
    return 0;
}
// https://blog.csdn.net/weixin_37517391/article/details/73801443
#else
#ifndef _t22pf_20210924_
#define _t22pf_20210924_
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

const int MAXN = 1 << 10;
int N, V, X;
struct Customer {
    int meter;
    int di;
    bool operator<(const Customer &c) const { return meter < c.meter; }
} cs[MAXN];

// int meters[MAXN], di[MAXN];

long long dp[MAXN][MAXN][2], sum[MAXN];

int sentinal;
const long long INF = 0x3F3F3F3F3F3F3F3F;
long long solve(int l, int r, int dir, int len = 0)
{
    _DEBUG_CMD({
        for (int i = 0; i < len; ++i) {
            printf(" ");
        }
        printf("solve(%d,%d,%d):%2lld\n", l, r, dir, dp[l][r][dir] == INF ? -1 : dp[l][r][dir]);
    });
    if (dp[l][r][dir] != INF) {
        return dp[l][r][dir];
    }
    if (l == r) {
        // if (cs[l].meter == X) {
        if (l == sentinal) {
            _DEBUG_CMD(printf("sentinal:%d return zero!\n", sentinal););
            return dp[l][r][0] = dp[l][r][1] = 0;
        }
        else {
            _DEBUG_CMD({ printf("not expected: l:%d r:%d\n", l, r); });
            return INF;
        }
    }
    if (l < sentinal) {
        // long long di_multi = sum[N + 1] - (sum[r + 1] - sum[l + 2]);

        long long di_multi = sum[N + 1] - (sum[r + 1] - sum[l + 1]);
        long long left_sub = solve(l + 1, r, 0, len + 1);
        long long right_sub = solve(l + 1, r, 1, len + 1);
        long long left_delta = cs[l + 1].meter - cs[l].meter;
        long long right_delta = cs[r].meter - cs[l].meter;
        _DEBUG_CMD(
            printf("l:%d r:%d dir:%d sentinal:%d di_multi:%lld, sum[%d]:%lld - (sum[%d]:%lld "
                   "- sum[%d]:%lld) = %lld ld:%lld lsub:%lld lstate:%lld rd:%lld rsub:%lld "
                   "rstate:%lld lineno:%d\n",
                   l, r, dir, sentinal, di_multi, N + 1, sum[N + 1], r + 1, sum[r + 1], l + 1,
                   sum[l + 1], sum[N + 1] - (sum[r] - sum[l + 1]), left_delta, left_sub,
                   left_sub + left_delta * di_multi, right_delta, right_sub,
                   right_sub + right_delta * di_multi, __LINE__););
        // assert(left_sub != INF);
        // assert(right_sub != INF);
        assert(left_delta >= 0);
        assert(left_sub >= 0);
        assert(right_delta >= 0);
        assert(right_sub >= 0);
        assert(di_multi >= 0);
        dp[l][r][0] = min(dp[l][r][0], left_sub + left_delta * di_multi);
        dp[l][r][0] = min(dp[l][r][0], right_sub + right_delta * di_multi);
    }
    if (r > sentinal) {
        long long di_multi = sum[N + 1] - (sum[r] - sum[l]);
        _DEBUG_CMD(
            printf("l:%d r:%d dir:%d sentinal:%d di_multi:%lld, sum[%d]:%lld - (sum[%d]:%lld "
                   "- sum[%d]:%lld) = %lld lineno:%d\n",
                   l, r, dir, sentinal, di_multi, N + 1, sum[N + 1], r - 1, sum[r - 1], l, sum[l],
                   sum[N + 1] - (sum[r - 1] - sum[l]), __LINE__););
        // long long di_multi = sum[N] - (sum[r - 1] - sum[l + 1]);
        long long left_sub = solve(l, r - 1, 0, len + 1);
        long long right_sub = solve(l, r - 1, 1, len + 1);
        long long left_delta = cs[r].meter - cs[l].meter;
        long long right_delta = cs[r].meter - cs[r - 1].meter;
        _DEBUG_CMD(
            printf("l:%d r:%d dir:%d sentinal:%d di_multi:%lld, sum[%d]:%lld - (sum[%d]:%lld "
                   "- sum[%d]:%lld) = %lld lineno:%d\n",
                   l, r, dir, sentinal, di_multi, N + 1, sum[N + 1], r - 1, sum[r - 1], l, sum[l],
                   sum[N + 1] - (sum[r - 1] - sum[l]), __LINE__););
        _DEBUG_CMD(printf("l:%d r:%d dir:%d sentinal:%d di_multi:%lld in r > sentinal. "
                          "ld:%lld lsub:%lld, rd:%lld, rsub:%lld lineno:%d\n",
                          l, r, dir, sentinal, di_multi, left_delta, left_sub, right_delta,
                          right_sub, __LINE__););
        _DEBUG_CMD(printf(
            "l:%d r:%d dir:%d sentinal:%d di_multi:%lld new lstate:%lld rstate:%lld lineno:%d\n", l,
            r, dir, sentinal, di_multi, left_sub + left_delta * di_multi,
            right_sub + right_delta * di_multi, __LINE__));
        // assert(left_sub != INF);
        // assert(right_sub != INF);
        assert(left_delta >= 0);
        assert(left_sub >= 0);
        assert(right_delta >= 0);
        assert(right_sub >= 0);
        assert(di_multi >= 0);
        dp[l][r][1] = min(dp[l][r][1], left_sub + left_delta * di_multi);
        dp[l][r][1] = min(dp[l][r][1], right_sub + right_delta * di_multi);
    }
    _DEBUG_CMD({
        printf("expected: l:%d r:%d, dir:%d val:%lld\n", l, r, dir,
               dp[l][r][dir] == INF ? -1 : dp[l][r][dir]);
    });
    return dp[l][r][dir];
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d%d", &N, &V, &X)) {
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &cs[i].meter, &cs[i].di);
        }
        memset(dp, 0x3F, sizeof(dp));
        memset(sum, 0, sizeof(sum));

        cs[N].meter = X;
        cs[N].di = 0;
        sort(cs, cs + N + 1);
        for (int i = 0; i <= N; ++i) {
            if (cs[i].meter == X) {
                sentinal = i;
                break;
            }
        }

        sum[0] = 0;
        for (int i = 1; i <= N + 1; ++i) {
            sum[i] = sum[i - 1] + cs[i - 1].di;
        }
        long long ans = min(solve(0, N, 0), solve(0, N, 1));
        _DEBUG_CMD({
            printf("sentinal: %d\n", sentinal);
            printf("cs:\n");
            for (int i = 0; i <= N; ++i) {
                printf("%d,%d ", cs[i].meter, cs[i].di);
            }
            printf("\n");
            printf("sums:\n");
            for (int i = 0; i <= N + 1; ++i) {
                printf("%2lld ", sum[i]);
            }
            printf("\n");
            printf("dir:0\n");
            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= N; ++j) {
                    printf("%2lld ", dp[i][j][0] == INF ? -1 : dp[i][j][0]);
                }
                printf("\n");
            }
            printf("dir:1\n");
            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= N; ++j) {
                    printf("%2lld ", dp[i][j][1] == INF ? -1 : dp[i][j][1]);
                }
                printf("\n");
            }
        });
        printf("%lld\n", ans * V);
    }
    return 0;
};

// 24/Sep/2021 - 10:13 pm 26/Sep/2021 total time consuming: 08:24
#endif
#endif
