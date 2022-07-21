#ifndef _t21pn_20210905_
#define _t21pn_20210905_
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

const int MAXN = 1 << 14;
int T, dcnt, udcnt, n;
int w[MAXN], type[MAXN];
double f[MAXN];

int main(int argc, char **argv)
{
    for (int i = 1; i < MAXN; ++i) {
        f[i] = 1.0 / i + f[i - 1];
    }
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        double ans = 0;
        dcnt = udcnt = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", w + i, type + i);
            if (type[i] == 1) {
                ++dcnt;
                ans += w[i];
            }
            else {
                ++udcnt;
                ans += w[i] * f[n];
            }
        }
        printf("Case %d: %lf\n", cc, ans);
    }
    return 0;
};

#endif
