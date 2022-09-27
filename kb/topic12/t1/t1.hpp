#ifndef _t1_20220909_
#define _t1_20220909_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
const int maxn = 1e6 + 10;
ll dp[2][maxn + 10];

int main(int argc, char **argv) {
    int s[maxn + 10];
    int m, n;
    while (scanf("%d%d", &m, &n) == 2) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &s[i + 1]);
        }
        dp[0][0] = 0;
        dp[0][1] = s[1];
        for (int i = 2; i <= m; i++) {
            int prev = i&1;
            int curr = (i+1)&1;

            for (int j = 1; j <= n; j++) {
                dp[curr][j] = max(dp[prev][j], dp[prev][j - 1]) + s[j];
                printf("i[%d],j[%d],dp[%d][%d] = %lld\n", i, j, dp[curr][j]);
            }
        }
        printf("%lld\n", dp[(m+1)&1][n]);
    }
    return 0;
};

#endif
