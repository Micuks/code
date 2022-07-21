#ifndef _t21pa_20210824_
#define _t21pa_20210824_
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

const int MAXN = 1 << 7;
int T, n;
int minutes[MAXN];
int gcd(int x, int y)
{
    if (y == 0) {
        return x;
    }
    return gcd(y, x % y);
}
int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int case_cnt = 1; case_cnt <= T; ++case_cnt) {
        scanf("%d", &n);
        int k = 0, b = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &minutes[i]);
            if (minutes[i] < 0) {
                b += (-minutes[i]);
                k += 1;
            }
            else {
                b += minutes[i];
            }
        }
        k = n - k;
        if (k == 0) {
            printf("Case %d: inf\n", case_cnt);
        }
        else {
            int g = gcd(k, b);
            printf("Case %d: %d/%d\n", case_cnt, b / g, k / g);
        }
    }
    return 0;
};

#endif
