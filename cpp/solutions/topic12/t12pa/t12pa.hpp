#ifndef _t12pa_20200118_
#define _t12pa_20200118_
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
#include <signal.h>
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

const int MAXN = 1e6 + 3;
int m, n;
int s[MAXN];
long ss[MAXN];

long dp(int m, int n)
{
    long last_maxes[MAXN];
    memset(last_maxes, 0, sizeof(last_maxes));
    memset(ss, 0, sizeof(ss));

    long last_max = -0x7FFFFFFF;
    for (int i = 1; i <= m; ++i) {
        last_max = -0x7FFFFFFF;
        for (int j = i; j <= n; ++j) {
            ss[j] = max(ss[j - 1], last_maxes[j - 1]) + s[j - 1];
            last_maxes[j - 1] = last_max;
            last_max = max(last_max, ss[j]);
        }
    }
    _DEBUG_CMD({
        printf("m:%d, n:%d\n", m, n);
        cout << "ss[idx]: ";
        for (int i = 0; i <= n; ++i) {
            cout << ss[i] << ' ';
        }
        cout << endl << "last_maxes[idx]: ";
        for (int i = 0; i <= n; ++i) {
            cout << last_maxes[i] << " ";
        }
        cout << endl;
    });
    return last_max;
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d", &m, &n)) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &s[i]);
        }
        long res = dp(m, n);
        printf("%ld\n", res);
    }
    return 0;
};

#endif
