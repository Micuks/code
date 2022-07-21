#ifndef _t15pd_20210713_
#define _t15pd_20210713_
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

typedef unsigned long long ull;
const int MAXD = 1 << 5;
const int BASE10 = 1 << 4;
int t;
ull dp[MAXD][BASE10];
int digits[MAXD], dcnt;
ull n;

void split_number(ull n)
{
    dcnt = 0;
    while (n != 0) {
        digits[dcnt++] = n % 10;
        n /= 10;
    }
}

ull dfs(int pos, int preced, bool limit)
{
    if (pos == -1) {
        return 1;
    }
    if (limit == false && dp[pos][preced] != ull(-1)) {
        return dp[pos][preced];
    }
    ull ret = 0;
    int upper_bound = limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        if (preced == 4 && i == 9) {
            continue;
        }
        ret += dfs(pos - 1, i, limit && i == upper_bound);
    }
    if (limit == false) {
        dp[pos][preced] = ret;
    }
    return ret;
}

ull solve(ull n)
{
    split_number(n);
    ull no49 = dfs(dcnt - 1, 0, true);
    return n + 1 - no49;
}
int main(int argc, char **argv)
{
    memset(dp, -1, sizeof(dp));
    scanf("%d", &t);
    while (t--) {
        scanf("%llu", &n);
        printf("%llu\n", solve(n));
    }
    return 0;
};

#endif
