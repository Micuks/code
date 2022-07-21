#ifndef _t14pf_20200501_
#define _t14pf_20200501_
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

const int MAXN = (1e7 + 10);
bool not_prime[MAXN];
int prime[MAXN / 10];
int pcnt = 0;

void init_prime1()
{
    pcnt = 0;
    memset(not_prime, 0, sizeof(not_prime));
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
        }
        for (int j = 0; j < pcnt && (long long) prime[j] * i < MAXN; ++j) {
            not_prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
void init_prime2()
{
    pcnt = 0;
    memset(not_prime, 0, sizeof(not_prime));
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
            for (int j = i + i; j < MAXN; j = j + i) {
                not_prime[j] = 1;
            }
        }
    }
}

int T;
int n;

int big_num_prime(int n)
{
    bool ret = true;
    int i = 0;
    for (int i = 0; prime[i] * prime[i] < n; ++i) {
        if (n % prime[i] == 0) {
            ret = false;
            break;
        }
    }
    return ret;
}

int find_match_cnt(int n)
{
    int ret = 0;
    int idx = 0;
    int s = prime[idx];
    while (s + s <= n) {
        if (n - s < MAXN) {
            if (!not_prime[n - s]) {
                ++ret;
            }
        }
        else if (big_num_prime(n - s)) {
            ++ret;
        }
        s = prime[++idx];
    }
    return ret;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    cin >> T;
    init_prime1();
    while (T--) {
        cin >> n;
        printf("Case %d: %d\n", ++case_cnt, find_match_cnt(n));
    }
    return 0;
};

#endif
