#ifndef _t21po_20210910_
#define _t21po_20210910_
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

const int MAXN = 1 << 4;
double dp[8][8][MAXN][MAXN][MAXN][MAXN];
// int b3[] = {1, 3, 27, 81};
int req[8], cur[8];
int T, C, D, H, S;

void solve(int c, int d, int h, int s, int jc, int jd, int jh, int js, int jcnt, int ccnt)
{
    if (ccnt == 0 || c == 0 || d == 0 || h == 0 || s == 0) {
        return;
    }
    double den = 52 - ccnt;
    if (c < C) {

        if (jcnt < 2) {
        }
    }
}

bool check_valid(int c, int d, int h, int s, int p, int q)
{
    memset(cur, 0, sizeof(cur));
    cur[0] = 0;
    cur[1] = c;
    cur[2] = d;
    cur[3] = h;
    cur[4] = s;
    ++cur[p], ++cur[q];
    for (int i = 1; i <= 4; ++i) {
        if (cur[i] < req[i]) {
            return false;
        }
    }
    return true;
}

double dfs(int c, int d, int h, int s, int p, int q)
{
    if (check_valid(c, d, h, s, p, q)) {
        return dp[p][q][c][d][h][s] = 0;
    }
    if (dp[p][q][c][d][h][s] != -1.0) {
        return dp[p][q][c][d][h][s];
    }
    int cnum = 13 - c;
    int dnum = 13 - d;
    int hnum = 13 - h;
    int snum = 13 - s;
    // double denom = cnum + dnum + hnum + snum + (p ? 0 : 1) + (q ? 0 : 1);
    double denom = 54 - c - d - h - s - (p ? 1 : 0) - (q ? 1 : 0);
    double ap = 0;
    double ans = 0;
    if (denom == 0) {
        return 0;
    }

    if (cnum > 0) {
        double prob = cnum / denom;
        double acc = prob * (dfs(c + 1, d, h, s, p, q) + 1);
        ap += prob;
        ans += acc;
    }
    if (dnum > 0) {
        double prob = dnum / denom;
        double acc = prob * (dfs(c, d + 1, h, s, p, q) + 1);
        ap += prob;
        ans += acc;
    }
    if (hnum > 0) {
        double prob = hnum / denom;
        double acc = prob * (dfs(c, d, h + 1, s, p, q) + 1);
        ap += prob;
        ans += acc;
    }
    if (snum > 0) {
        double prob = snum / denom;
        double acc = prob * (dfs(c, d, h, s + 1, p, q) + 1);
        ap += prob;
        ans += acc;
    }
    int arr[] = {0, c, d, h, s};
    if (p == 0) {
        double prob = 1 / denom;
        double min_acc = 1e9;
        ap += prob;
        for (int i = 1; i <= 4; ++i) {
            double acc = prob * (dfs(c, d, h, s, i, q) + 1);
            min_acc = min(acc, min_acc);
        }
        ans += min_acc;
    }
    if (q == 0) {
        double prob = 1 / denom;
        double min_acc = 1e9;
        ap += prob;
        for (int i = 1; i <= 4; ++i) {
            double acc = prob * (dfs(c, d, h, s, p, i) + 1);
            min_acc = min(acc, min_acc);
        }
        ans += min_acc;
    }
    assert(abs(ap - 1.0) < 1e-6);
    /*
    if (std::isnan(ans)) {
        abort();
    }
    */

    // dp[p][q][c][d][h][s] = ans + 1;
    dp[p][q][c][d][h][s] = ans;
    return dp[p][q][c][d][h][s];
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        scanf("%d%d%d%d", &C, &D, &H, &S);
        fill_n(*****dp, sizeof(dp) / sizeof(double), -1.0);

        // int ccnt = C + D + H + S;
        req[0] = 0;
        req[1] = C;
        req[2] = D;
        req[3] = H;
        req[4] = S;

        int red = 0;
        for (int i = 1; i <= 4; ++i) {
            red += max(0, req[i] - 13);
        }
        if (red > 2) {
            printf("Case %d: -1\n", cc);
            continue;
        }
        /*
        for (int i = 0; i < 2; ++i) {
            solve(C, D, H, S, 0, 0, 0, 0, 0, ccnt);
        }
        */

        double ans = dfs(0, 0, 0, 0, 0, 0);
        // ans = ans > 54 ? -1 : ans;
        printf("Case %d: %lf\n", cc, ans);
    }
    return 0;
};

#endif
