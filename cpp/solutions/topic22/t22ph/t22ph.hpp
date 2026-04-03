#if 0
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char a[150];
char b[150];
int dp[150][150];
int f[150];
int judge(int i, int j)
{
    if (b[i] != b[j])
        return 1;
    else
        return 0;
}
int main()
{
    while (~scanf("%s%s", a + 1, b + 1)) {
        int n = strlen(a + 1);
        memset(dp, 0, sizeof(dp));
        memset(f, 0, sizeof(f));
        for (int len = 0; len <= n; len++) {
            for (int i = 1; i <= n; i++) {
                int j = i + len;
                if (len == 0) {
                    dp[i][j] = 1;
                }
                else if (j <= n) {
                    dp[i][j] = 0x3f3f3f3f;
                    if (i + 1 <= n)
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + judge(i, i + 1));
                    if (i + 1 <= n)
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + judge(i, j));
                    if (j - 1 >= 1)
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + judge(j - 1, j));
                    if (j - 1 >= 1)
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + judge(i, j));
                    for (int k = i; k < j; k++) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            f[i] = dp[1][i];
            if (a[i] == b[i])
                f[i] = min(f[i - 1], f[i]);
            else {
                for (int j = 0; j < i; j++) {
                    f[i] = min(f[i], f[j] + dp[j + 1][i]);
                }
            }
        }
        printf("%d\n", f[n]);
    }
}
// https://blog.csdn.net/mengxiang000000/article/details/73505936
#else
#ifndef _t22ph_20210927_
#define _t22ph_20210927_
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
const int INF = 0x3F3F3F3F;
char A[MAXN], B[MAXN];
int dp[MAXN][MAXN], alen, blen;

int check(int i, int j)
{
    _DEBUG_CMD(printf("A[%d]:%c B[%d]:%c return %d\n", i, B[i], j, B[j], B[i] == B[j] ? 0 : 1););
    return B[i] == B[j] ? 0 : 1;
}
int solve(int l, int r)
{
    if (dp[l][r] != INF) {
        return dp[l][r];
    }
    if (l == r) {
        return dp[l][r] = 1;
    }
    if (l > r) {
        return INF;
    }
    int lineno = 0;
    int olddp = dp[l][r];

    if (l + 1 < alen && l + 1 < r) {
        dp[l][r] = min(dp[l][r], solve(l + 1, r) + check(l, l + 1));
        if (dp[l][r] != olddp) {
            lineno = __LINE__, olddp = dp[l][r];
        }
        dp[l][r] = min(dp[l][r], solve(l + 1, r) + check(l, r));
        if (dp[l][r] != olddp) {
            lineno = __LINE__, olddp = dp[l][r];
        }
    }
    if (r - 1 >= 0 && r - 1 >= l) {
        dp[l][r] = min(dp[l][r], solve(l, r - 1) + check(r - 1, r));
        if (dp[l][r] != olddp) {
            lineno = __LINE__, olddp = dp[l][r];
        }
        dp[l][r] = min(dp[l][r], solve(l, r - 1) + check(l, r));
        if (dp[l][r] != olddp) {
            lineno = __LINE__, olddp = dp[l][r];
        }
    }
    for (int k = l; k < r; ++k) {
        dp[l][r] = min(dp[l][r], solve(l, k) + solve(k + 1, r));
        if (dp[l][r] != olddp) {
            lineno = __LINE__, olddp = dp[l][r];
        }
    }
    _DEBUG_CMD({
        if (l == 0 && r == 3) {
            printf("l:%d r:%d dp:%d lineno:%d\n", l, r, dp[l][r] == INF ? -1 : dp[l][r], lineno);
        }
    });
    return dp[l][r];
}
int solve0(int l, int r)
{
    if (dp[l][r] != INF) {
        return dp[l][r];
    }
    if (l == r) {
        if (A[l] == B[l]) {
            DEBUG_CMD(printf("A[%d]:%c B[%d]:%c return 0\n", l, A[l], l, B[l]));
            return dp[l][r] = 0;
        }
        else {
            DEBUG_CMD(printf("A[%d]:%c B[%d]:%c return 1\n", l, A[l], l, B[l]));
            return dp[l][r] = 1;
        }
    }
    if (l > r) {
        return INF;
    }
    int lineno = 0;
    int olddp = dp[l][r];

    dp[l][r] = min(dp[l][r], solve(l + 1, r) + (A[l] == B[l] ? 0 : 1));
    if (dp[l][r] != olddp) {
        lineno = __LINE__, olddp = dp[l][r];
    }
    dp[l][r] = min(dp[l][r], solve(l, r - 1) + (A[r] == B[r] ? 0 : 1));
    if (dp[l][r] != olddp) {
        lineno = __LINE__, olddp = dp[l][r];
    }
    if (B[l] == B[r]) {
        int newl = l, newr = r;
        while (newl <= r) {
            if (B[newl] == B[r]) {
                ++newl;
            }
            else {
                break;
            }
        }
        while (newr >= newl) {
            if (B[newr] == B[l]) {
                --newr;
            }
            else {
                break;
            }
        }
        dp[l][r] = min(dp[l][r], solve(l + 1, r - 1) + ((A[l] != B[l] || A[r] != B[r]) ? 1 : 0));
        if (dp[l][r] != olddp) {
            lineno = __LINE__, olddp = dp[l][r];
        }
    }
    DEBUG_CMD({
        if (l == 0 && r == 2) {
            printf("l:%d r:%d dp:%d lineno:%d\n", l, r, dp[l][r] == INF ? -1 : dp[l][r], lineno);
        }
    });
    return dp[l][r];
}

int f[MAXN];

int main(int argc, char **argv)
{
    while (~scanf("%s%s", A, B) && strcmp(A, "") != 0) {
        alen = strlen(A), blen = strlen(B);
        assert(alen == blen);
        memset(dp, 0x3F, sizeof(dp));
        solve(0, alen - 1);

        memset(f, 0x3F, sizeof(f));
        for (int i = 0; i < alen; ++i) {
            f[i] = dp[0][i];
        }
        f[0] = (A[0] == B[0] ? 0 : 1);

        for (int i = 1; i < alen; ++i) {
            if (A[i] == B[i]) {
                f[i] = min(f[i], f[i - 1]);
            }
            for (int j = 0; j < i; ++j) {
                f[i] = min(f[i], f[j] + dp[j + 1][i]);
            }
        }
        int ans = f[alen - 1];
        printf("%d\n", ans);
        _DEBUG_CMD({
            for (int i = 0; i < alen; ++i) {
                for (int j = 0; j < alen; ++j) {
                    printf("%2d ", dp[i][j] == INF ? -1 : dp[i][j]);
                }
                printf("\n");
            }
        });
    }
    return 0;
};

#endif
#endif
