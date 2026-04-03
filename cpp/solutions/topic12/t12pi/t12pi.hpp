#ifndef _t12pi_20200309_
#define _t12pi_20200309_
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

const int MAXN = 3e4 + 11;
int dp[MAXN];
int N;

int main(int argc, char **argv)
{
    int max_e = 0;
    int ele = 0;
    while (cin >> N) {
        fill_n(dp, MAXN, 0);
        max_e = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &ele);
            int *e = upper_bound(dp, dp + max_e, ele);
            if (e == dp + max_e) {
                dp[max_e] = ele;
                max_e++;
            }
            else {
                *e = ele;
            }
        }
        cout << max_e << endl;
    }
    return 0;
};

#endif
