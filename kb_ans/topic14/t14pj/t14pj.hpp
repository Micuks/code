#ifndef _t14pj_20200511_
#define _t14pj_20200511_
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

long T, x;

const int MAXN = 2 << 16 + 1;
bool not_prime[MAXN];
int prime[MAXN];
int pcnt;
void init_prime()
{
    memset(not_prime, 0, sizeof(not_prime));
    pcnt = 0;
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
        }
        for (int j = 0; j < pcnt && prime[j] * i < MAXN; ++j) {
            not_prime[prime[j] * i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

int factor[64];
int powers[64];
int pfcnt;

void get_factor(int n)
{
    pfcnt = 0;
    memset(powers, 0, sizeof(powers));
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n = n / i;
                ++powers[pfcnt];
            }
            factor[pfcnt++] = i;
            _DEBUG_CMD({
                printf("FILE:%s LINE:%d i:%d pfcnt:%d, powers[pfcnt-1]:%d\n", __FILE__, __LINE__, i,
                       pfcnt, powers[pfcnt - 1]);
            });
        }
    }
    if (n != 1) {
        ++powers[pfcnt];
        factor[pfcnt++] = n;
    }
}

void get_factor2(long n)
{
    pfcnt = 0;
    memset(powers, 0, sizeof(powers));
    for (int i = 0; i < pcnt && long(prime[i]) * prime[i] <= n; ++i) {
        if (n % prime[i] == 0) {
            while (n % prime[i] == 0) {
                n = n / prime[i];
                ++powers[pfcnt];
            }
            factor[pfcnt++] = prime[i];
        }
    }
    if (n != 1) {
        ++powers[pfcnt];
        factor[pfcnt++] = n;
    }
}

long gcd(long a, long b) { return b == 0 ? a : gcd(b, a % b); }

int calc(long n)
{
    bool neg = n < 0 ? true : false;
    n = n < 0 ? -n : n;
    get_factor2(n);
    int g = powers[0];
    for (int i = 1; i < pfcnt; ++i) {
        g = gcd(g, powers[i]);
    }
    if (neg) {
        // while (g % 2 == 0) {
        while ((g & 1) == 0) {
            g = g >> 1;
        }
    }
    return g;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    init_prime();
    cin >> T;
    while (T--) {
        cin >> x;
        printf("Case %d: %d\n", ++case_cnt, calc(x));
        _DEBUG_CMD({
            printf("x: %d pfcnt: %d powers[0]:%d factor[0]:%d 6&0x1 = %d\n", x, pfcnt, powers[0],
                   factor[0], 6 & 0x1);
        });
    }
    return 0;
};

#endif
