#ifndef _t14pv_20200619_
#define _t14pv_20200619_
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

const int MAXN = (1 << 7);
int number[MAXN];
int nc;
int N;

int gcd(int x, int y)
{
    if (y == 0) {
        return x;
    }
    return gcd(y, x % y);
}

int main(int argc, char **argv)
{
    string input;
    cin >> N;
    getline(cin, input);
    while (N--) {
        nc = 0;
        getline(cin, input);
        stringstream ss(input);
        while (ss >> number[nc])
            nc++;
        // printf("l:%s nc in case: %d: %d", input.c_str(), N, nc);
        int maxgcd = 1;
        for (int i = 0; i < nc; ++i) {
            for (int j = i + 1; j < nc; ++j) {
                maxgcd = max(maxgcd, gcd(number[i], number[j]));
            }
        }
        printf("%d\n", maxgcd);
    }
    return 0;
};

#endif
