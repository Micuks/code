#ifndef _t12pn_20200327_
#define _t12pn_20200327_
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

const int MAXN = 1 << 10;
int N;
int num[MAXN];
int dp[MAXN];
int max_cnt = 0;
int main(int argc, char **argv)
{
    cin >> N;
    fill_n(dp, MAXN, 0);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &num[i]);
        int *max_n = lower_bound(dp, dp + max_cnt, num[i]);
        *max_n = num[i];
        if (max_n == dp + max_cnt) {
            ++max_cnt;
        }
    }
    cout << max_cnt << endl;
    return 0;
};

#endif
