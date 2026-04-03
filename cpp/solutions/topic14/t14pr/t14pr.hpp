#ifndef _t14pr_20200613_
#define _t14pr_20200613_
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

long long ext_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long r = ext_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}

long long x, y, m, n, L;

int main(int argc, char **argv)
{
    while (cin >> x >> y >> m >> n >> L) {
        long long r = x - y;
        long long a = ((n - m) % L) + L;
        long long x1, y1;
        long long gcd = ext_gcd(a, L, x1, y1);
        // printf("gcd:%lld a:%lld r:%lld L:%lld x1:%lld, y1:%lld\n", gcd, a, r, L, x1, y1);
        if (r % gcd != 0) {
            printf("Impossible\n");
        }
        else {
            // x1 = x1 / gcd;
            // y1 = y1 / gcd;
            a = a / gcd;
            r = r / gcd;
            L = L / gcd;
            x1 = ((x1 * r) % L + L) % L;
            /*
            if (x1 < 0) {
                printf("x1: %lld L: %lld r: %lld gcd:%lld\n", x1, L, r, gcd);
            }
            */
            printf("%lld\n", x1);
            // printf("-3 % 5 = %d\n", -3 % 5); // -3 % 5 = -3
        }
    }
    return 0;
};

#endif
