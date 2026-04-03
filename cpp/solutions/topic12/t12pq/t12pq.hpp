#if 0
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int dp[1010][1010];
char str[1010][1010];

int main()
{
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            scanf("%s", str[i]);
        int ans = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i == 0 || j == n - 1) {
                    dp[i][j] = 1;
                    continue;
                }
                int t1 = i, t2 = j;
                while (t1 >= 0 && t2 < n && str[t1][j] == str[i][t2]) {
                    t1--;
                    t2++;
                }
                t1 = i - t1;
                if (t1 >= dp[i - 1][j + 1] + 1)
                    dp[i][j] = dp[i - 1][j + 1] + 1;
                else
                    dp[i][j] = t1;
                ans = max(ans, dp[i][j]);
            }
        printf("%d\n", ans);
    }
    return 0;
}

#else
#ifndef _t12pq_20200328_
#define _t12pq_20200328_
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

const int MAXN = 1024;
int N;
char maze[MAXN][MAXN];
int dp[MAXN][MAXN];

int solve(int x, int y)
{
    if (x <= 0 || y >= N - 1) {
        dp[x][y] = 1;
    }
    else if (dp[x][y] == 0) {
        int min_dp = maze[x][y + 1] == maze[x - 1][y] ? min(solve(x - 1, y), solve(x, y + 1)) : 1;
        int max_dp = solve(x - 1, y + 1);
        while (maze[x][y + min_dp] == maze[x - min_dp][y] && y + min_dp < N && x - min_dp >= 0 &&
               min_dp <= max_dp) {
            min_dp++;
        }
        dp[x][y] = min_dp;
        /*
        if (min_dp == max_dp && maze[x][y + min_dp] == maze[x - min_dp][y]) {
            dp[x][y] = min_dp + 1;
        }
        else {
            dp[x][y] = min_dp;
        }
        */
    }
    return dp[x][y];
}

int main(int argc, char **argv)
{
    while (~scanf("%d", &N) && N != 0) {
        fgets(maze[0], MAXN, stdin);
        for (int i = 0; i < N; ++i) {
            fgets(maze[i], MAXN, stdin);
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                solve(i, j);
            }
        }
        // solve(N - 1, 0);
        int max_n = 0;
        for (int i = 0; i < N; ++i) {
            max_n = max(max_n, *max_element(dp[i], dp[i] + N));
        }
        _DEBUG_CMD({
            for (int i = 0; i < N; ++i) {
                cout << maze[i];
            }
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << dp[i][j] << ' ';
                }
                cout << endl;
            }
        });
        cout << max_n << endl;
    }
    return 0;
};

#endif
#endif
