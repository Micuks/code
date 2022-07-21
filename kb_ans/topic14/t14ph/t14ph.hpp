#ifndef _t14ph_20200509_
#define _t14ph_20200509_
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

int T;
long long n;

const int MAXN = 1e7 + 19;
bool not_prime[MAXN];
int prime[MAXN / 10];
int pcnt = 0;

void init_prime()
{
    memset(not_prime, 0, sizeof(not_prime));
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
        }
        for (int j = 0; j < pcnt && long(prime[j]) * i < MAXN; ++j) {
            not_prime[prime[j] * i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

const int MAXPF = 64;
int prime_factor[MAXPF];
int powers[MAXPF];
int pfcnt;

void factor_out(long long x)
{
    pfcnt = 0;
    memset(powers, 0, sizeof(powers));
    for (int i = 0; i < pcnt; ++i) {
        const int p = prime[i];
        if (x % p == 0) {
            while (x % p == 0) {
                x = x / p;
                ++powers[pfcnt];
            }
            prime_factor[pfcnt++] = p;
        }
    }
    if (x != 1) {
        ++powers[pfcnt];
        prime_factor[pfcnt++] = x;
    }
}

long long pairsFormLCM(long long n)
{
    factor_out(n);
    long long ans = 1;
    for (int i = 0; i < pfcnt; ++i) {
        ans = ans * (2 * powers[i] + 1);
    }
    ans = ans / 2 + 1;
    return ans;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    init_prime();
    cin >> T;
    while (T--) {
        cin >> n;
        printf("Case %d: %lld\n", ++case_cnt, pairsFormLCM(n));
    }
    return 0;
};

#endif
