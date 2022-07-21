#ifndef _t21pj_20210902_
#define _t21pj_20210902_
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

int T, x, y, z, r;

double get_prob(int i, int x)
{
    double denominator = double(x) * double(x);
    double acc1 = double(i - 1) * double(i - 1);
    double acc2 = double(x - i) * double(x - i);
    return (denominator - acc1 - acc2) / denominator;
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        double ans = 0;
        scanf("%d%d%d%d", &x, &y, &z, &r);
        for (int i = 1; i <= x; ++i) {
            for (int j = 1; j <= y; ++j) {
                for (int k = 1; k <= z; ++k) {
                    double p = get_prob(i, x) * get_prob(j, y) * get_prob(k, z);
                    ans += 0.5 * (1 - pow(1 - 2 * p, r));
                }
            }
        }
        printf("Case %d: %lf\n", cc, ans);
    }
    return 0;
};

#endif
