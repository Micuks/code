#ifndef _t14px_20200619_
#define _t14px_20200619_
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

const int MAXN = 1e6 + 3;
long long phi[MAXN];
bool not_prime[MAXN];
int prime[MAXN];
int pcnt;

void init_phi()
{
    pcnt = 0;
    memset(not_prime, 0, sizeof(not_prime));
    memset(phi, 0, sizeof(phi));
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            phi[i] = i - 1;
            prime[pcnt++] = i;
        }

        for (int j = 0; j < pcnt && prime[j] - 1 < MAXN / i; ++j) {
            not_prime[prime[j] * i] = true;
            if (i % prime[j] == 0) {
                phi[prime[j] * i] = phi[i] * prime[j];
                break;
            }
            else {
                phi[prime[j] * i] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

long long f[MAXN];
int n;

void init_f()
{
    f[2] = 1;
    for (int i = 3; i < MAXN; ++i) {
        f[i] = f[i - 1] + phi[i];
    }
}

int main(int argc, char **argv)
{
    init_phi();
    init_f();
    while (cin >> n && n != 0) {
        printf("%lld\n", f[n]);
    }
    return 0;
};

#endif
