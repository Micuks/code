#ifndef _t21pe_20210829_
#define _t21pe_20210829_
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

int T, n;

int solve(int n)
{
    double prob = 1;
    int k = 0;
    for (k = 1; k < n; ++k) {
        prob = prob * (n - k) / double(n);
        if (1 - prob >= 0.5) {
            break;
        }
    }
    return k;
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int case_cnt = 1; case_cnt <= T; ++case_cnt) {
        scanf("%d", &n);
        int ans = solve(n);
        printf("Case %d: %d\n", case_cnt, ans);
    }
    return 0;
};

#endif
