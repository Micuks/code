#ifndef _t14pi_20200510_
#define _t14pi_20200510_
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

const int MAXN = 1e8 + 3;
const int P = 64;
int T, n;
double table[MAXN / P + 3];
void init_table()
{
    double init = 0;
    int acc = 0;
    table[0] = 0;
    for (int i = 1; i <= MAXN; ++i) {
        init = init + 1 / double(i);
        ++acc;
        if (acc % P == 0) {
            table[i / P] = init;
        }
    }
}

double calc(int n)
{
    double ret = table[n / P];
    int b = int(n / P) * P;
    for (int i = 1; i <= n % P; ++i) {
        ret += 1 / double(i + b);
    }
    return ret;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    init_table();
    cin >> T;
    while (T--) {
        cin >> n;
        printf("Case %d: %.12g\n", ++case_cnt, calc(n));
    }
    return 0;
};

#endif
