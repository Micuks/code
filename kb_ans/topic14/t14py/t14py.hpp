#if 0

#include <algorithm>
#include <math.h>
#include <set>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef unsigned long long ll;
const int N = 105;
int g, v[N], a[N];

void init()
{
    g = 0;
    memset(v, 0, sizeof(v));

    for (int i = 2; i <= 64; i++) {
        if (v[i]) {
            a[g++] = i;
            continue;
        }

        for (int j = i * 2; j <= 64; j += i)
            v[j] = 1;
    }
}

void solve()
{
    set<ll> ans;
    ans.insert(1);

    ll MaxT = 1 << 16;
    for (ll i = 2; i < MaxT; i++) {
        int ti = ceil(64 * log(2) / log(i)) - 1;
        ll now = i * i * i * i;
        ans.insert(now);
        for (int j = 1; a[j] <= ti; j++) {
            now *= (a[j] - a[j - 1] == 1 ? i : i * i);
            ans.insert(now);
        }
    }

    for (set<ll>::iterator i = ans.begin(); i != ans.end(); i++)
        printf("%llu\n", *i);
}

int main()
{
    init();
    solve();
    return 0;
}
#else

#ifndef _t14py_20200619_
#define _t14py_20200619_
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

using ull = unsigned long long;
const ull MAXN = (ull)(-1LL);
const ull MAXP = (1 << 16);

ull gcd(ull x, ull y)
{
    if (y == 0) {
        return x;
    }
    return gcd(y, x % y);
}

int pfcnt;
ull prime_factors[64];
ull factor_power[64];
void get_factor(ull x)
{
    pfcnt = 0;
    memset(factor_power, 0, sizeof(factor_power));
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            prime_factors[pfcnt] = i;
            while (x % i == 0) {
                x = x / i;
                factor_power[pfcnt]++;
            }
            pfcnt++;
        }
    }
    if (x != 1) {
        prime_factors[pfcnt] = x;
        factor_power[pfcnt]++;
        pfcnt++;
    }
}

bool perfect_power(ull x)
{
    get_factor(x);
    if (pfcnt == 1) {
        return factor_power[0] != 1;
    }
    ull min_gcd = gcd(factor_power[0], factor_power[1]);
    for (int i = 2; i < pfcnt; ++i) {
        min_gcd = min(min_gcd, gcd(factor_power[i], factor_power[i - 1]));
    }
    return min_gcd != 1;
}
vector<ull> sp_vec;

ull fast_power(ull b, ull e)
{
    ull ret = 1;
    ull p = b;
    while (e != 0) {
        if (e & 0x1ULL) {
            ret = ret * p;
        }
        p = p * p;
        e = e / 2;
    }
    return ret;
}
ull fast_power2(ull b, ull e)
{
    ull ret = 1;
    for (int i = 0; i < e; ++i) {
        ret = ret * b;
    }
    return ret;
}

bool power_under_limit(ull b, ull exp)
{
    ull minor_p = fast_power(b, (exp / 2));
    ull major_p = fast_power(b, (exp - exp / 2));
    return MAXN / major_p >= minor_p;
    // return power_under_limit(b, exp - 1) && MAXN / major_p >= minor_p;
}

const int CNUSZ = 128;
ull cnu128[CNUSZ];
ull pu128[CNUSZ];
int cnu128_cnt;

void get_cnu128()
{
    cnu128_cnt = 0;
    memset(cnu128, 0, sizeof(cnu128));
    for (int i = 2; i < CNUSZ; ++i) {
        if (!cnu128[i]) {
            pu128[cnu128_cnt++] = i;
        }
        for (int j = 0; j < cnu128_cnt && pu128[j] * i < CNUSZ; ++j) {
            cnu128[pu128[j] * i] = true;
            if (i % pu128[j] == 0) {
                break;
            }
        }
    }
}

int main(int argc, char **argv)
{
    // printf("MAXN:%llu\n", MAXN);
    // printf("fast_power(56, 64): %llu\n", fast_power1(56, 64));
    sp_vec.push_back(1);
    get_cnu128();
    for (int i = 2; i < MAXP; ++i) {
        if (perfect_power(i)) {
            continue;
        }
        for (int j = 4; j <= 64; ++j) {
            bool pul = power_under_limit(i, j);
            if (pul) {
                if (cnu128[j]) {
                    ull fp = fast_power(i, j);
                    /*
                    if (fp == 4096) {
                        printf(
                            "get a number:%d composite power: %d, fp:%lld power is under limit\n",
                            i, j, fp);
                    }
                    */
                    sp_vec.push_back(fast_power(i, j));
                }
            }
            else {
                break;
            }
        }
    }
    sort(sp_vec.begin(), sp_vec.end());
    // auto it = unique(sp_vec.begin(), sp_vec.end());
    // sp_vec.resize(distance(sp_vec.begin(), it));
    for (auto i : sp_vec) {
        cout << i << endl;
    }
    return 0;
};

#endif
#endif
