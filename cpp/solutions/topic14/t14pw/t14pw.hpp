#ifndef _t14pw_20200619_
#define _t14pw_20200619_
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

const int MAXN = 1e4 + 7;
int pcnt;
bool not_prime[MAXN];
int prime[MAXN];

void init_prime()
{
    pcnt = 0;
    memset(not_prime, 0, sizeof(not_prime));
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

bool is_prime(int x)
{
    bool ret = true;
    for (int i = 0; i < pcnt; ++i) {
        int factor = prime[i];
        if (factor * factor > x) {
            break;
        }
        if (x % factor == 0) {
            ret = false;
        }
    }
    return ret;
}

bool euler_prime[MAXN];
void init_euler_prime()
{
    for (int i = 0; i < MAXN; ++i) {
        int x = i * i + i + 41;
        euler_prime[i] = is_prime(x);
    }
}
int a, b;

int main(int argc, char **argv)
{
    init_prime();
    init_euler_prime();
    while (cin >> a >> b) {
        int total = b - a + 1;
        // int prime = count_if(euler_prime + a, euler_prime + b + 1);
        int prime = count_if(euler_prime + a, euler_prime + b + 1, [](bool b) { return b; });
        printf("%.2lf\n", roundf(float(prime * 100 * 100) / total) / 100);
    }
    return 0;
};

#endif
