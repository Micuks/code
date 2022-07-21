#ifndef _t14pe_20200501_
#define _t14pe_20200501_
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

long long n, k;
int T;

int least_3_digits()
{
    long long ret = 1;
    long long mul = n % 1000;
    long long flg = k;
    while (flg) {
        if (flg & 1) {
            ret = (ret * mul) % 1000;
        }
        mul = (mul * mul) % 1000;
        flg = flg / 2;
    }
    return int(ret);
}

int greatest_3_digits()
{
    float x = k * log10(n) - (int) (k * log10(n));
    float m = pow(10, x);
    return int(m * 100);
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &n, &k);
        int g = greatest_3_digits();
        int l = least_3_digits();
        printf("Case %d: %d %03d\n", ++case_cnt, g, l);
    }
    return 0;
};

#endif
