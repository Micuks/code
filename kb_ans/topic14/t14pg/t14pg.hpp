#ifndef _t14pg_20200502_
#define _t14pg_20200502_
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

long long T, n;

long long calc(long long n)
{
    long long ret = 0;
    long long i = 1;
    long long m = sqrt(n);
    for (i = 1; i <= m; ++i) {
        // long long k = n / i;
        ret += n / i;
        // ret += k * (n / k - n / (k + 1));
    }

    for (i = 1; i <= m; ++i) {
        ret += i * (n / i - n / (i + 1));
    }
    if (n / m == m) {
        ret -= m;
    }
    return ret;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    cin >> T;
    while (T--) {
        cin >> n;
        printf("Case %d: %lld\n", ++case_cnt, calc(n));
    }
    return 0;
};

#endif
