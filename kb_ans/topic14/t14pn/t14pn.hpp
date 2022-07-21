#ifndef _t14pn_20200513_
#define _t14pn_20200513_
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

int T, Q;

long long calc(long long k)
{
    long long ret = k;
    while (k != 0) {
        k = k / 5;
        ret += k;
    }
    return ret;
}

long long solve()
{
    long long begin = Q * 4 / 5;
    long long end = Q + 1;
    while (end > begin) {
        long long mid = (begin + end) / 2;
        long long res = calc(mid);
        if (res < Q) {
            begin = mid + 1;
            continue;
        }
        else if (res > Q) {
            end = mid;
            continue;
        }
        else {
            return mid * 5;
        }
    }
    // DEBUG_CMD({ printf("begin:%lld end:%lld cannot get a solution\n", begin, end); });
    return -1;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    cin >> T;
    while (T--) {
        cin >> Q;
        long long ret = solve();
        if (ret < 0) {
            printf("Case %d: impossible\n", ++case_cnt);
        }
        else {
            printf("Case %d: %lld\n", ++case_cnt, ret);
        }
    }
    return 0;
};

#endif
