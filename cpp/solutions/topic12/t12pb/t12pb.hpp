#ifndef _t12pb_20200120_
#define _t12pb_20200120_
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
    int n, max_cnt, max_val;
    while (~scanf("%d", &n)) {
        int in;
        max_cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &in);
            if (max_cnt == 0) {
                ++max_cnt;
                max_val = in;
            }
            else {
                max_cnt += in == max_val ? 1 : -1;
            }
        }
        printf("%d\n", max_val);
    }
    return 0;
};

#endif
