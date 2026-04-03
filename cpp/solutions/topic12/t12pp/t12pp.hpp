#if 0
#include <iostream>
#include <string.h>
using namespace std;

int maze[101][101], flag[101][101];
int n, k;
int fx[4] = {0, 0, -1, 1};
int fy[4] = {1, -1, 0, 0};

int maxses(int a, int b)
{
    if (a < b)
        return b;
    return a;
}

int bfs(int a, int b)
{
    if (flag[a][b] != -1)
        return flag[a][b];
    int i, x, y, t;
    int sum = 0;
    for (i = 0; i < 4; i++) {
        for (t = 1; t <= k; t++) {
            x = a + t * fx[i];
            y = b + t * fy[i];
            if (x < 0 || x >= n || y < 0 || y >= n)
                continue;
            if (maze[a][b] >= maze[x][y])
                continue;
            flag[x][y] = bfs(x, y);
            sum = maxses(flag[x][y], sum);
        }
    }
    return maze[a][b] + sum;
}

int main()
{
    int i, j;
    while (scanf("%d%d", &n, &k) != EOF) {
        if (n == -1 && k == -1)
            break;
        memset(flag, -1, sizeof(flag));
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                scanf("%d", &maze[i][j]);
            }
        }
        printf("%d\n", bfs(0, 0));
    }
    return 0;
}

#else
#ifndef _t12pp_20200327_
#define _t12pp_20200327_
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

const int MAXN = 128;
int N;
int K;
int dp[MAXN][MAXN];
int tc[MAXN][MAXN];
int maze[MAXN][MAXN];
int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool valid(int x, int y, int oldx, int oldy)
{
    return x >= 0 && x < N && y >= 0 && y < N && maze[x][y] > maze[oldx][oldy];
}

#if 1
int solve(int x, int y)
{
    ++tc[x][y];
    int maxn = -1;
    // if (dp[x][y] < maze[x][y] + c) { // !!TLE
    if (dp[x][y] == -1) {
        // dp[x][y] = maze[x][y] + c;
        for (int step = 1; step <= K; ++step) {
            for (int i = 0; i < 4; ++i) {
                int newx = x + dirs[i][0] * step;
                int newy = y + dirs[i][1] * step;
                if (valid(newx, newy, x, y)) {
                    //&& dp[newx][newy] < dp[x][y] + maze[newx][newy]) {
                    dp[newx][newy] = solve(newx, newy);
                    maxn = max(dp[newx][newy], maxn);
                }
            }
        }
        // return max(dp[x][y], maxn);
        return dp[x][y] = maxn + maze[x][y];
        // return dp[x][y];
    }
    else {
        return dp[x][y];
    }
}

int main(int argc, char **argv)
{
    while (cin >> N >> K && N != -1 && K != -1) {
        memset(dp, -1, sizeof(dp));
        memset(tc, 0, sizeof(tc));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &maze[i][j]);
            }
        }
        // dp[0][0] = maze[0][0];
        int max_n = solve(0, 0);
        _DEBUG_CMD({
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << tc[i][j] << ' ';
                }
                cout << endl;
            }
        });
        cout << max_n + 1 << endl;
    };
    return 0;
};

#else
int solve(int x, int y)
{
    if (dp[x][y] != -1) {
        return dp[x][y];
    }
}

int main(int argc, char **argv)
{
    while (cin >> N >> K && N != -1 && K != -1) {
        memset(dp, -1, sizeof(dp));
        // memset(tc, 0, sizeof(tc));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &maze[i][j]);
            }
        }
        int max_n = solve(0, 0);
        cout << max_n << endl;
    };
    return 0;
};
#endif

#endif
#endif
