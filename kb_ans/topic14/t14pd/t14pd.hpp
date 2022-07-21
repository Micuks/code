#ifndef _t14pd_20200501_
#define _t14pd_20200501_
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

int main(int argc, char **argv)
{
    long long T, N;
    int case_cnt = 0;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &N);
        printf("Case %d: %lld\n", ++case_cnt, N - (long long) sqrt(N) - (long long) sqrt(N / 2));
    }
    return 0;
};

#endif
