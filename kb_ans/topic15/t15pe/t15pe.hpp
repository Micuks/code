#if 0
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define LL long long
int dp[33][33][33];
int dis[33];

int dfs(int len, int cnt0, int cnt1, bool first, bool flag)
{
    if (len < 0)
        return (first || cnt0 > cnt1);
    if (!flag && !first && dp[len][cnt0][cnt1] != -1)
        return dp[len][cnt0][cnt1];
    int end = flag ? dis[len] : 1;
    int ans = 0;
    for (int i = 0; i <= end; i++) {
        if (first) {
            if (i)
                ans += dfs(len - 1, 0, 0, 0, flag && i == end);
            else
                ans += dfs(len - 1, 0, 0, 1, flag && i == end);
        }
        else {
            if (i)
                ans += dfs(len - 1, cnt0, cnt1 + 1, 0, flag && i == end);
            else
                ans += dfs(len - 1, cnt0 + 1, cnt1, 0, flag && i == end);
        }
    }
    if (!flag && !first)
        dp[len][cnt0][cnt1] = ans;
    return ans;
}

int solve(int n)
{
    int len = 0;
    while (n) {
        dis[len++] = n & 1;
        n >>= 1;
    }
    return dfs(len - 1, 0, 0, 1, 1);
}

int main()
{
    int l, r;
    memset(dp, -1, sizeof(dp));
    while (cin >> l >> r)
        cout << solve(r) - solve(l - 1) << endl;
    return 0;
}
// https://blog.csdn.net/to_be_better/article/details/50664561
#else
#ifndef _t15pe_20210713_
#define _t15pe_20210713_
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

typedef long long ll;
const int MAXN = 1 << 4;
const int MAXD = 1 << 7;
const int MIDD = 1 << 6;

int s, f;
int digits[MAXD], dcnt;
int dp[MAXD][MAXD];

void split_number(int n)
{
    dcnt = 0;
    while (n) {
        digits[dcnt++] = n % 2;
        n /= 2;
    }
}

int get_cardinality(int x)
{
    int ret = 0;
    while (x) {
        if (x & 0x01) {
            --ret;
        }
        else {
            ++ret;
        }
        x = x / 2;
    }
    return ret;
}

int dfs(int pos, int state, bool limit, bool preceding_zero)
{
    if (pos == -1) {
        return state >= 0 ? 1 : 0;
    }
    if (limit == false && preceding_zero == false && dp[pos][state + MIDD] != -1) {
        return dp[pos][state + MIDD];
    }
    int ret = 0;
    int upper_bound = limit ? digits[pos] : 1;
    for (int i = 0; i <= upper_bound; ++i) {
        if (preceding_zero == true && i == 0) {
            ret += dfs(pos - 1, state, limit && i == upper_bound, true);
        }
        else {
            ret += dfs(pos - 1, state + 1 - i * 2, limit && i == upper_bound, false);
        }
    }
    if (limit == false && preceding_zero == false) {
        dp[pos][state + MIDD] = ret;
    }
    return ret;
}

int solve(int n)
{
    split_number(n);
    _DEBUG_CMD(printf("split: %d dcnt:%d\n", n, dcnt));
    return dfs(dcnt - 1, 0, true, true);
}
int main(int argc, char **argv)
{
    memset(dp, -1, sizeof(dp));
    while (~scanf("%d%d", &s, &f)) {
        printf("%d\n", solve(f) - solve(s - 1));
        _DEBUG_CMD({
            printf("dcnt:%d\n", dcnt);
            for (int i = 0; i < dcnt; ++i) {
                printf("dp[%d]: ", i);
                for (int j = 0; j < MAXD; ++j) {
                    if (dp[i][j] != -1) {
                        printf("(%d,%d,%d) ", j - MIDD, j, dp[i][j]);
                    }
                }
                printf("\n");
            }
        });
    }
    return 0;
};

#endif
#endif
