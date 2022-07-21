#if 0
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn0 = 20;
const int maxn1 = (1 << 10) + 5;
const int maxn2 = 15;

LL dp[maxn0][maxn1][maxn2], l, r;
int a[maxn0], store[maxn0], k, t, tail, T;

int cnt1(int x)
{
    int ret = 0;
    while (x) {
        x = x & (x - 1);
        ret += 1;
    }
    return ret;
}
void process(LL x)
{
    tail = 0;
    while (x) {
        a[tail++] = int(x % 10);
        x /= 10;
    }
}
inline void decode(int x)
{
    t = 0;
    for (int i = 0; (x >> i) > 0; ++i) {
        int temp = (x >> i);
        if (temp & 1)
            store[t++] = i;
    }
    store[t] = maxn0;
}
inline int encode()
{
    int ret = 0;
    for (int i = 0; i < t; ++i)
        ret += (1 << store[i]);
    return ret;
}
LL dfs(int pos, int state, bool limit, bool lead, int kk)
{

    if (pos == -1) {
        printf("dfs(%d, %d, %d, %d, %d): %lld\n", pos, state, int(limit), int(lead), kk,
               cnt1(state) == k ? 1ll : 0ll);
        return cnt1(state) == k ? 1 : 0;
    }
    if (!limit && !lead && dp[pos][state][kk] != -1) {
        printf("dfs(%d, %d, %d, %d, %d): %lld\n", pos, state, int(limit), int(lead), kk,
               dp[pos][state][kk]);
        return dp[pos][state][kk];
    }

    int up = limit ? a[pos] : 9;
    LL ret = 0;
    for (int i = 0; i <= up; ++i) {
        decode(state);
        int idx = lower_bound(store, store + t, i) - store;
        if (idx + 1 > k)
            break;

        store[idx] = i;
        t = max(idx + 1, t);

        int nstate = (i == 0 && lead) ? state : encode();
        ret += dfs(pos - 1, nstate, limit && i == up, lead && i == 0, kk);
    }
    if (!limit && !lead)
        dp[pos][state][kk] = ret;
    printf("dfs(%d, %d, %d, %d, %d): %lld\n", pos, state, int(limit), int(lead), kk, ret);
    return ret;
}

int main()
{

    scanf("%d", &T);
    memset(dp, -1, sizeof(dp));
    int cas = 1;
    while (T--) {
        scanf("%lld%lld%d", &l, &r, &k);

        process(l - 1);
        LL ans0 = dfs(tail - 1, 0, true, true, k);

        process(r);
        LL ans1 = dfs(tail - 1, 0, true, true, k);

        printf("k:%d solve(%lld): %lld, solve(%lld): %lld\n", k, l - 1, ans0, r, ans1);
        printf("Case #%d: %lld\n", cas++, ans1 - ans0);
    }
    return 0;
}
#else
#ifndef _t15pb_20210710_
#define _t15pb_20210710_
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
typedef unsigned long long ull;

const int MAXN = 1 << 5;
const int MAXK = 1 << 4;

ull l, r, k, t;

int digits[MAXN], d;
int c[MAXN];
ull dp[MAXN][1 << 10][MAXK];

ull tt;

int split_num(ull n)
{
    d = 0;
    while (n != 0) {
        digits[d++] = (n % 10);
        n = n / 10;
    }
    return d;
}
int get_cardinality(int x)
{
    int ret = 0;
    while (x) {
        ++ret;
        x = (x & (x - 1));
    }
    return ret;
}

int decode(int state)
{
    // int cnt = 0;
    memset(c, 0, sizeof(c));
    tt = 0;
    for (int i = 0; i < MAXN; ++i) {
        if ((1 << i) & state) {
            c[tt++] = i;
        }
    }
    return (int) tt;
}
int encode()
{
    int ret = 0;
    for (int i = 0; i < (int) tt; ++i) {
        ret |= (1 << c[i]);
    }
    return ret;
}

ull dfs(int pos, int state, bool limit, bool lead, int cardinality)
{
    if (pos == -1) {
        _DEBUG_CMD(printf("dfs(%d, %d, %d, %d, %d): %llu\n", pos, state, int(limit), int(lead),
                          cardinality, ull(get_cardinality(state) == cardinality ? 1 : 0)););
        return get_cardinality(state) == cardinality ? 1 : 0;
    }
    if (limit == false && lead == false && dp[pos][state][cardinality] != (ull) -1) {
        _DEBUG_CMD(printf("dfs(%d, %d, %d, %d, %d): %llu\n", pos, state, int(limit), int(lead),
                          cardinality, dp[pos][state][cardinality]););
        return dp[pos][state][cardinality];
    }

    int upper_bound = limit ? digits[pos] : 9;
    ull ret = 0;

    for (int i = 0; i <= upper_bound; ++i) {

        int sd = decode(state);
        int cur_card = lower_bound(c, c + sd, i) - c;
        if (cur_card + 1 > cardinality) {
            break;
        }

        c[cur_card] = i;
        tt = max(cur_card + 1, (int) tt);

        int newstate = (i == 0) && lead ? state : encode();
        ret += dfs(pos - 1, newstate, limit && i == upper_bound, lead && i == 0, cardinality);
    }

    if (limit == false && lead == false)
        dp[pos][state][cardinality] = ret;
    // _DEBUG_CMD(printf("dfs(%d, %d)"));
    _DEBUG_CMD(printf("dfs(%d, %d, %d, %d, %d): %llu\n", pos, state, int(limit), int(lead),
                      cardinality, ret););
    return ret;
}

ull solve(ull n)
{
    split_num(n);
    ull ret = dfs(d - 1, 0, true, true, (int) k);
    _DEBUG_CMD(printf("solve(%llu): %llu card:%d\n", n, ret, (int) k));
    return ret;
}

int main(int argc, char **argv)
{
    scanf("%llu", &t);
    memset(dp, -1, sizeof(dp));
    for (ull case_cnt = 0; case_cnt < t; ++case_cnt) {
        scanf("%llu%llu%llu", &l, &r, &k);
        printf("Case #%llu: %llu\n", case_cnt + 1, solve(r) - solve(l - 1));
    }
    return 0;
};

#endif
#endif
