#ifndef _t21ph_20210830_
#define _t21ph_20210830_
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

int T;

double solve(int t, int d)
{
    if (t & 1) {
        return 0;
    }
    double ans = 1;
    while (t > 0) {
        ans = ans * (t - 1) / (t + 1);
        t -= 2;
    }
    return ans;
}
int main(int argc, char **argv)
{
    int t, d;
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        scanf("%d%d", &t, &d);
        double ret = solve(t, d);
        printf("Case %d: %lf\n", cc, ret);
    }
    return 0;
};

#endif
