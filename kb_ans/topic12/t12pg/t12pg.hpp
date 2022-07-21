#if 0
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 99999 + 5;
int dp[maxn][15];

int main()
{
    int n;
    while (cin >> n && n) {
        memset(dp, 0, sizeof dp);
        int a, b, t = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &a, &b);
            dp[b][a + 1]++;
            t = max(t, b);
        }
        for (int i = t - 1; i >= 0; i--) {
            for (int j = 11; j >= 1; j--) { //不能多
                dp[i][j] += max(dp[i + 1][j], max(dp[i + 1][j - 1], dp[i + 1][j + 1]));
            }
        }
        cout << dp[0][6] << endl;
    }
    return 0;
}
#else
#ifndef _t12pg_20200302_
#define _t12pg_20200302_
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

const int MAXN = 1e5 + 3;
const int MAXT = 1e5 + 3;
int n;
int pies[MAXN][16];

int main(int argc, char **argv)
{
    while (cin >> n && n != 0) {
        int x, t;
        int maxt = 0;
        memset(pies, 0, sizeof(pies));
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &x, &t);
            ++pies[t][x];
            maxt = max(t, maxt);
        }
        int dp[16];
        memset(dp, 0, sizeof(dp));
        for (int i = maxt; i >= 0; --i) {
            int cur_state[16];
            memset(cur_state, 0, sizeof(cur_state));
            for (int j = 0; j <= 10; ++j) {
                cur_state[j] = dp[j];
                if (j + 1 <= 10) {
                    cur_state[j] = max(cur_state[j], dp[j + 1]);
                }
                if (j - 1 >= 0) {
                    cur_state[j] = max(cur_state[j], dp[j - 1]);
                }
                cur_state[j] += pies[i][j];
            }
            memcpy(dp, cur_state, sizeof(dp));
        }
        _DEBUG_CMD({
            for (int i = 0; i < 11; ++i) {
                cout << dp[i] << ' ';
            }
            cout << endl;
        });
        cout << dp[5] << endl;
    }
    return 0;
};

#endif
#endif
