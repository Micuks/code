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
ll dp[maxn + 10][maxn + 10];

int main(int argc, char **argv) {
    int s[maxn + 10];
    int m, n;
    while (scanf("%d%d", &m, &n) == 2) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &s[i + 1]);
        }
        dp[1][0] = 0;
        dp[1][1] = s[1];
        for (int i = 2; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + s[j];
            }
        }
        printf("%64lld\n", dp[m][n]);
    }
    return 0;
};

#endif
