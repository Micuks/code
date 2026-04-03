#ifndef _t12ph_20200307_
#define _t12ph_20200307_
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

int N;
int K;
const int MAXN = 2048;
int tc[MAXN];
int ctc[MAXN];
int dp[MAXN];

int main(int argc, char **argv)
{
    cin >> N;
    while (N--) {
        cin >> K;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= K; ++i) {
            scanf("%d", &tc[i]);
        }
        for (int i = 1; i <= K - 1; ++i) {
            scanf("%d", &ctc[i]);
        }
        dp[1] = tc[1];
        for (int i = 2; i <= K; ++i) {
            dp[i] = min(dp[i - 1] + tc[i], dp[i - 2] + ctc[i - 1]);
        }
        int ts = dp[K];
        // DEBUG_CMD({ cerr << "dp[K]: " << ts << endl; });
        int h = ts / 3600;
        int m = (ts / 60) % 60;
        int s = ts % 60;
        const char *ampm = (h < 4 || (h == 4 && m == 0 && s == 0)) ? "am" : "pm";
        printf("%02d:%02d:%02d %s\n", h + 8, m, s, ampm);
    }
    return 0;
};

#endif
