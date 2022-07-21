#ifndef _t14po_20200514_
#define _t14po_20200514_
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

const int MAXN = 4e6 + 37;
bool not_prime[MAXN];
int phi[MAXN];
int prime[MAXN];
int pcnt;
void init_prime()
{
    pcnt = 0;
    memset(not_prime, 0, sizeof(not_prime));
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
            phi[i] = i - 1;
        }
        else {
            // else phi[i] must be set in previous for(j) loop
            // do nothing
        }
        for (int j = 0; j < pcnt && long(prime[j]) * i < MAXN; ++j) {
            not_prime[prime[j] * i] = true;
            phi[prime[j] * i] = phi[i] * (prime[j] - 1);
            if (i % prime[j] == 0) {
                phi[prime[j] * i] = phi[i] * prime[j];
                break;
            }
        }
    }
}

// lg(2^64) = 64
int ppower[64];
int factor[64];
int pfcnt;

void get_pfactor(int N)
{
    pfcnt = 0;
    memset(ppower, 0, sizeof(ppower));
    for (int i = 0; i < pcnt && long(prime[i]) * prime[i] <= N; ++i) {
        if (N % prime[i] == 0) {
            while (N % prime[i] == 0) {
                N = N / prime[i];
                ++ppower[pfcnt];
            }
            factor[pfcnt++] = prime[i];
        }
    }
    if (N != 1) {
        ++ppower[pfcnt];
        factor[pfcnt++] = N;
    }
}

int N;

bool visited[MAXN];
long long psum[64];
void solve(int N)
{
    long long ret = N - 1;
    memset(visited, 0, sizeof(visited));
    for (int i = 2; i < N; ++i) {
        /*
        if (visited[i]) {
            continue;
        }
        visited[i] = true;
        */
        long long res = 1;
        get_pfactor(i);
        // memset(psum, 0, sizeof(psum));
        for (int j = 0; j < pfcnt; ++j) {
            long long pf = 1;
            long long f = 0;
            for (int k = 0; k <= ppower[j]; ++k) {
                f = f + pf;
                pf = pf * factor[j];
            }
            // psum[i] = f;
            res = res * f;
            DEBUG_CMD({
                printf("i: %d, factor[%d]: %d, ppower: %d, f:%lld\n", i, j, factor[j], ppower[j],
                       f);
            });
        }
        long long sxn = (long long) (N - i) / i * res;
        DEBUG_CMD({ printf("N:%d i: %d, res:%lld sxn:%lld\n", N, i, res, sxn); });
        // ret += (long long) (N - i) / i * res;
        ret += sxn;
        /*
        for (int j = 0; j < factor[0] && long(prime[j]) * i < N; ++j) {
            visited[prime[j] * i] = true;
            res += ;
        }
        */
    }
    printf("case answer: %lld\n", ret);
}

long s[MAXN], f[MAXN];

void init_s()
{
    memset(f, 0, sizeof(f));
    memset(s, 0, sizeof(s));
    for (int i = 1; i < MAXN; ++i) {
        for (int j = 2 * i; j < MAXN; j += i) {
            f[j] += phi[j / i] * i;
        }
    }
    s[1] = f[1];
    s[2] = f[2];
    for (int i = 2; i <= MAXN; ++i) {
        s[i] = s[i - 1] + f[i];
    }
}

int main(int argc, char **argv)
{
    init_prime();
    init_s();
    _DEBUG_CMD({
        cout << "phi: ";
        for (int i = 0; i < 100; ++i) {
            cout << phi[i] << ' ';
        }
        cout << endl;
        cout << "f: ";
        for (int i = 0; i < 100; ++i) {
            cout << f[i] << ' ';
        }
        cout << endl;
        cout << "s: ";
        for (int i = 0; i < 100; ++i) {
            cout << s[i] << ' ';
        }
        cout << endl;
    });
    while (cin >> N && N != 0) {
        printf("%ld\n", s[N]);
    }
    return 0;
};

#endif
