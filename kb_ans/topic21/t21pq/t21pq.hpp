#ifndef _t21pq_20210913_
#define _t21pq_20210913_
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

const double eps = 1e-6;
int T, k1, k2;
double p;

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        scanf("%lf%d%d", &p, &k1, &k2);
        if (p < eps) {
            printf("Case %d: %lf\n", cc, 1.0 * k1);
            continue;
        }
        if (1 - p < eps) {
            printf("Case %d: %lf\n", cc, 1.0 * k2);
            continue;
        }
        double a1 = 1 - pow(1 - p, k1 - 1), b1 = a1 / p;
        double a2 = 1 - pow(p, k2 - 1), b2 = a2 / (1 - p);
        double t1 = (a1 * b2 + b1) / (1 - a1 * a2), f1 = a2 * t1 + b2;
        printf("Case %d: %lf\n", cc, (1 - p) * t1 + p * f1 + 1);
    }
    return 0;
};

#endif
