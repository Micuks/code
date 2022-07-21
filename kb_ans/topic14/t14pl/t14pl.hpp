#ifndef _t14pl_20200512_
#define _t14pl_20200512_
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

long long n, K, MOD;
int A[10001];
int T;

int fast_power()
{
    long long res = 1;
    long long power = n;
    int num = K - 1;
    while (num) {
        if (num & 0x01) {
            res = (res * power) % MOD;
        }
        power = (power * power) % MOD;
        num = num >> 1;
    }
    return int(res);
}

int solve(long long sum)
{
    _DEBUG_CMD(
        { printf("fast_power %d^%d %% %d = %d sum:%d\n", n, K - 1, MOD, fast_power(), sum); });
    long long res = sum;
    res = (res * fast_power()) % MOD;
    res = (res * K) % MOD;
    return int(res);
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    cin >> T;
    while (T--) {
        long long sum = 0;
        cin >> n >> K >> MOD;
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
            sum += A[i];
            sum = sum % MOD;
        }
        printf("Case %d: %d\n", ++case_cnt, solve(sum));
    }
    return 0;
};

#endif
