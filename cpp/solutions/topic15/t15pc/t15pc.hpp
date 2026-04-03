#ifndef _t15pc_20210713_
#define _t15pc_20210713_
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

const int MAXN = 1e6 + 3;
int n, m;
// int dp[1 << 3][1 << 4][1 << 3];
int dp[1 << 3][1 << 4];
int digits[1 << 3], dcnt;

//[pos][state][cardinality]
void split_number(int n)
{
    dcnt = 0;
    while (n) {
        digits[dcnt++] = (n % 10);
        n /= 10;
    }
}

int dfs(int pos, int end, bool limit)
{
    if (pos == -1) {
        // return end != 4 ? 1 : 0;
        return 1;
    }
    if (limit == 0 && dp[pos][end] != -1) {
        return dp[pos][end];
    }
    int ret = 0;
    int upper_bound = limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        if (i == 4) {
            continue;
        }
        if (end == 6 && i == 2) {
            continue;
        }
        ret += dfs(pos - 1, i, limit && i == upper_bound);
    }
    if (limit == 0) {
        dp[pos][end] = ret;
    }
    return ret;
}

int solve(int n)
{
    split_number(n);
    return dfs(dcnt - 1, 0, true);
}
int main(int argc, char **argv)
{
    memset(dp, -1, sizeof(dp));
    while (~scanf("%d%d", &n, &m) && n && m) {
        printf("%d\n", solve(m) - solve(n - 1));
    }
    return 0;
};

#endif
