#if 0
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int dig[12];
ll dp[12][13][10][2];
ll N;

ll dfs(int pos, int mod, int pre, bool have13, bool limit)
{
    if (pos == 0)
        return have13 && mod == 0;

    if (!limit && dp[pos][mod][pre][have13] != -1)
        return dp[pos][mod][pre][have13];

    int up = limit ? dig[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= up; i++) {
        if (pre == 1 && i == 3)
            ans += dfs(pos - 1, (mod * 10 + i) % 13, i, 1, limit && i == up);
        else
            ans += dfs(pos - 1, (mod * 10 + i) % 13, i, have13, limit && i == up);
    }

    if (!limit)
        dp[pos][mod][pre][have13] = ans;

    return ans;
}
ll solve(ll x)
{
    int len = 0;
    while (x) {
        dig[++len] = x % 10;
        x /= 10;
    }
    return dfs(len, 0, 0, 0, 1);
}

int main()
{
    while (scanf("%lld", &N) != EOF) {
        memset(dp, -1, sizeof(dp));
        printf("%lld\n", solve(N));
    }
}
#else
#ifndef _t15pg_20210715_
#define _t15pg_20210715_
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
const int MOD = 13;
const int MAXD = 1 << 4;
ll n;
int digits[MAXD], dcnt;

void split_number(ll x)
{
    dcnt = 0;
    while (x) {
        digits[dcnt++] = x % 10;
        x /= 10;
    }
}

/*
int dp[MAXD][MAXD][MAXD];
// tle
int dfs(int pos, int mod, bool upper_limit, bool leading1, bool contain13);
{
    if (pos == -1) {
        return (contain13 && mod == 0) ? 1 : 0;
    }
    if (upper_limit == false && contain13 == true && dp[pos][mod] != -1) {
        return dp[pos][mod];
    }
    int ret = 0;
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        ret += dfs(pos - 1, (mod * 10 + i) % MOD, upper_limit && i == upper_bound, i == 1,
                   contain13 || (leading1 && i == 3));
    }
    if (upper_limit == false && contain13 == true) {
        dp[pos][mod] = ret;
    }
    return ret;
}
*/

const int CONTAIN13FLAG_LEN = 2;
ll dp[MAXD][MAXD][MAXD][CONTAIN13FLAG_LEN];
ll dfs(int pos, int mod, bool upper_limit, int prev, int contain13)
{
    if (pos == -1) {
        return (mod == 0 && contain13 == 1) ? 1 : 0;
    }
    if (upper_limit == false && dp[pos][prev][mod][contain13] != -1ll) {
        return dp[pos][prev][mod][contain13];
    }
    ll ret = 0;
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        if (prev == 1 && i == 3) {
            ret += dfs(pos - 1, (mod * 10 + i) % MOD, upper_limit && i == upper_bound, i, 1);
        }
        else {
            ret +=
                dfs(pos - 1, (mod * 10 + i) % MOD, upper_limit && i == upper_bound, i, contain13);
        }
    }
    if (upper_limit == false) {
        dp[pos][prev][mod][contain13] = ret;
    }
    return ret;
}

ll solve(ll x)
{
    split_number(x);
    return dfs(dcnt - 1, 0, true, 0, 0);
}
int main(int argc, char **argv)
{
    memset(dp, -1, sizeof(dp));
    while (~scanf("%lld", &n)) {
        printf("%lld\n", solve(n));
    }
    return 0;
};

#endif
#endif
