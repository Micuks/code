#ifndef _t14pm_20200512_
#define _t14pm_20200512_
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

const int MAXN = 1 << 16 + 3;
bool not_prime[MAXN];
int prime[MAXN];
int pcnt;

void init_prime()
{
    pcnt = 0;
    memset(prime, 0, sizeof(prime));
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
        }
        for (int j = 0; j < pcnt && long(prime[j]) * i < MAXN; ++j) {
            not_prime[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

int T, a, b;

bool is_prime(int x)
{
    if (x == 1) {
        return false;
    }
    for (int i = 0; i < pcnt && long(prime[i]) * prime[i] <= x; ++i) {
        if (x % prime[i] == 0) {
            return false;
        }
    }
    return true;
}

int solve()
{
    vector<bool> chart(b - a + 2);
    fill(chart.begin(), chart.end(), true);
    for (int i = 0; i < pcnt && long(prime[i]) * prime[i] <= b; ++i) {
        long base = a / prime[i] + 1;
        base = base > 1 ? base : 2;
        for (long j = base * prime[i]; j <= b; j += prime[i]) {
            chart[j - a] = false;
        }
    }
    int res = is_prime(a) ? 1 : 0;
    _DEBUG_CMD({
        for (int i = 0; i <= b - a; ++i) {
            printf("char[%d], %d: %d\n", i, i + a, int(chart[i]));
        }
    });
    for (int i = 1; i <= b - a; ++i) {
        if (chart[i]) {
            ++res;
        }
    }
    return res;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    init_prime();
    cin >> T;
    while (T--) {
        cin >> a >> b;
        printf("Case %d: %d\n", ++case_cnt, solve());
    }
    return 0;
};

#endif
