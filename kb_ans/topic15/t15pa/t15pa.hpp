#ifndef _t15pa_20210709_
#define _t15pa_20210709_
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
const int MOD = 2520;
int digits[20];
int idx[MOD + 3];
ll dp[20][2525][50];
ll t, l, r;
inline ll gcd(ll m, ll n) { return n ? gcd(n, m % n) : m; }
inline ll lcm(ll m, ll n) { return m / gcd(m, n) * n; }

void discretize()
{
    int cnt = 0;
    for (int i = 1; i <= MOD; ++i) {
        if (MOD % i == 0) {
            idx[i] = ++cnt;
        }
    }
}

ll dfs(int pos, int mod, int cur_lcm, bool upper_limit)
{
    if (pos == 0)
        return mod % cur_lcm == 0;
    if (upper_limit == false && dp[pos][mod][idx[cur_lcm]] != -1)
        return dp[pos][mod][idx[cur_lcm]];
    int upper_bound = upper_limit ? digits[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= upper_bound; ++i) {
        if (i == 0) {
            ans += dfs(pos - 1, (mod * 10 + i) % MOD, cur_lcm, upper_limit && i == upper_bound);
        }
        else {
            ans += dfs(pos - 1, (mod * 10 + i) % MOD, lcm(cur_lcm, i),
                       upper_limit && i == upper_bound);
        }
    }
    if (upper_limit == false) {
        dp[pos][mod][idx[cur_lcm]] = ans;
    }
    return ans;
}

ll solve(ll n)
{
    int len = 0;
    while (n) {
        digits[++len] = n % 10;
        n = n / 10;
    }
    return dfs(len, 0, 1, true);
}

int main(int argc, char **argv)
{
    scanf("%lld", &t);
    discretize();
    memset(dp, -1, sizeof(dp));

    while (t--) {
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", solve(r) - solve(l - 1));
    }
    return 0;
};

#endif
