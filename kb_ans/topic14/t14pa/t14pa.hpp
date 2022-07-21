#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int max_n = 2000010;
int a[max_n + 5], b[max_n + 5];

void Init() // euler筛法
{
    a[1] = 0;
    for (int i = 2; i <= max_n; i++)
        a[i] = i;
    for (int i = 2; i < max_n; i++) {
        if (a[i] == i) {
            for (int j = i; j < max_n; j += i)
                a[j] = a[j] / i * (i - 1);
        }
    }
}

int main()
{
    int T, n, k;
    long long ans;
    Init();
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= max_n; i++)
        a[i] = max(a[i], a[i - 1]); //不可省略
    for (int i = max_n; i >= 1; i--)
        b[a[i]] = i;
    for (int i = 1; i <= max_n; i++) {
        if (b[i] == 0) {
            int t = i;
            while (b[i] == b[t] && t <= max_n) {
                t++;
            }
            b[i] = b[t];
        }
    }
    b[0] = 0;
    scanf("%d", &T);
    while (T--) {
        static int cnt = 0;
        ans = 0;
        scanf("%d", &n);
        while (n--) {
            scanf("%d", &k);
            ans += b[k];
        }
        printf("Case %d: %lld Xukha\n", ++cnt, ans);
    }
    return 0;
}

#else
#ifndef _t14pa_20200401_
#define _t14pa_20200401_
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

const int MAXP = 1e6 + 3;
const int MAXV = 1e6 + 3;
int prime[MAXP];
char not_prime[MAXV];
int prime_cnt = 0;

void init_prime()
{
    memset(prime, 0, sizeof(prime));
    memset(not_prime, 0, sizeof(not_prime));
    prime_cnt = 0;
    for (int i = 2; i <= MAXV; ++i) {
        if (not_prime[i] == 0) {
            prime[prime_cnt++] = i;
        }
        int idx = 0;
        while (idx < prime_cnt && i * prime[idx] <= MAXV) {
            not_prime[i * prime[idx]] = 1;
            if (i % idx[prime] == 0) {
                break;
            }
            ++idx;
        }
    }
}

const int MAXN = 1e4 + 7;
int T;
int n, luck[MAXN];

int main(int argc, char **argv)
{
    int case_cnt = 0;
    init_prime();
    // cout << "max prime: " << prime[prime_cnt - 1] << endl;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> luck[i];
        }
        long long int res = 0;
        // int res = 0;
        for (int i = 0; i < n; ++i) {
            _DEBUG_CMD({
                printf("i:%d luck[i]+1: %d lower_bound:%d\n", i, luck[i] + 1,
                       *lower_bound(prime, prime + prime_cnt, luck[i] + 1));
            });
            res += *lower_bound(prime, prime + prime_cnt, luck[i] + 1);
        }
        printf("Case %d: %lld Xukha\n", ++case_cnt, res);
        // printf("Case %d: %d Xukha\n", ++case_cnt, res);
    }
    return 0;
};

#endif
#endif
