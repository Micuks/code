#ifndef _t22pd_20210924_
#define _t22pd_20210924_
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

const int MOD = 1000000007;
const int MAXN = 1 << 10;
long long dp[MAXN][MAXN][1 << 2][1 << 2], plen;
char parenthese[MAXN];
int match[MAXN];

void get_match()
{
    stack<int> st;
    for (int i = 0; i < plen; ++i) {
        if (parenthese[i] == '(') {
            st.push(i);
        }
        else {
            int p = st.top();
            st.pop();
            match[i] = p;
            match[p] = i;
        }
    }
    assert(st.size() == 0);
}

void solve(int l, int r)
{
    if (l == r - 1) {
        dp[l][r][0][1] = 1;
        dp[l][r][1][0] = 1;
        dp[l][r][0][2] = 1;
        dp[l][r][2][0] = 1;
        return;
    }
    if (match[l] == r) {
        solve(l + 1, r - 1);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (j != 1)
                    dp[l][r][0][1] = (dp[l][r][0][1] + dp[l + 1][r - 1][i][j]) % MOD;
                if (i != 1)
                    dp[l][r][1][0] = (dp[l][r][1][0] + dp[l + 1][r - 1][i][j]) % MOD;
                if (j != 2)
                    dp[l][r][0][2] = (dp[l][r][0][2] + dp[l + 1][r - 1][i][j]) % MOD;
                if (i != 2)
                    dp[l][r][2][0] = (dp[l][r][2][0] + dp[l + 1][r - 1][i][j]) % MOD;
            }
        }
    }
    else {
        int k = match[l];
        solve(l, k);
        solve(k + 1, r);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int m = 0; m < 3; ++m) {
                    for (int n = 0; n < 3; ++n) {
                        if ((m == 1 || m == 2) && (m == n))
                            continue;
                        dp[l][r][i][j] =
                            (dp[l][r][i][j] + dp[l][k][i][m] * dp[k + 1][r][n][j]) % MOD;
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    scanf("%s", parenthese);
    plen = strlen(parenthese);
    get_match();
    solve(0, plen - 1);
    long long ans = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ans = (ans + dp[0][plen - 1][i][j]) % MOD;
        }
    }
    printf("%lld\n", ans);

    return 0;
};

// https://blog.csdn.net/loy_184548/article/details/65448189
#endif
