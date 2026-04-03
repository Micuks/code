#include <cstdio>
#include <string>
#include <sys/time.h>
class timer {
    struct timeval start;
    struct timeval end;
    const char *s;

  public:
    timer(const char *s_) : s(s_) { gettimeofday(&start, NULL); }

    ~timer()
    {
        gettimeofday(&end, NULL);
        unsigned long long timer =
            (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
        printf("%s time cost: %lld\n", s, timer);
    }
};
#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define max_n 1000050
typedef long long LL;
using namespace std;
LL p[max_n], a[max_n]; //注意p数组大小，虽然用不了，但init里可能会RE
int k = 0;

void init()
{
    memset(p, 0, sizeof(p));
    memset(a, 0, sizeof(a));
    a[0] = a[1] = 1;
    for (int i = 2; i * i <= max_n - 5; i++) {
        if (!a[i]) {
            for (int j = i + i; j <= max_n - 5; j += i)
                a[j] = 1;
        }
    }
    for (int i = 1; i <= max_n - 5; i++) {
        if (!a[i])
            p[k++] = i;
    }
}

LL nop(LL n)
{
    LL ans = 1;
    for (int i = 0; i < k; i++) {
        if (p[i] > n)
            break;
        LL res = 0;
        while (n % p[i] == 0) {
            res++;
            n /= p[i];
        }
        ans = ans * (res + 1);
    }
    if (n > 1)
        ans *= 2; //注意这一步
    return ans;
}

int main()
{
    init();
    LL n, m, t;
    scanf("%lld", &t);
    while (t--) {
        LL num = 0, ans, res = 0;
        scanf("%lld %lld", &n, &m);
        ans = nop(n) / 2;
        // printf("%lld\n",ans);
        if (m * m > n)
            ans = 0;
        else {
            num = 0;
            for (int i = 1; i < m; i++) {
                if (n % i == 0)
                    num++;
            }
            ans -= num;
        }
        static int p = 1;
        printf("Case %d: %lld\n", p++, ans);
    }
    return 0;
}
#else
#ifndef _t14pc_20200427_
#define _t14pc_20200427_
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

const long long MAXN = 1e12;
const int MAXP = 1e6 + 3;

long long area;
long long min_side;
int T;
bool not_prime[MAXP];
// int prime[MAXP]; // 2020年04月28日01:12:26
long long prime[MAXP];
int pcnt = 0;

void init_prime()
{
    memset(not_prime, 0, sizeof(not_prime));
    memset(prime, 0, sizeof(prime));
    for (int i = 2; i < MAXP; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
        }
        for (int j = 0; j < pcnt && prime[j] * i < MAXP; ++j) {
            not_prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

void init_prime2()
{
    memset(not_prime, 0, sizeof(not_prime));
    memset(prime, 0, sizeof(prime));
    not_prime[0] = not_prime[1] = true;
    for (int i = 1; i < MAXP; ++i) {
        if (!not_prime[i]) {
            for (int j = i + i; j < MAXP; j += i) {
                not_prime[j] = true;
            }
        }
    }

    for (int i = 0; i < MAXP; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
        }
    }
}

int prime_divisors[64];
int ppower[64];
int pd_cnt = 0;

int find_prime_divisors(long long k)
{
    pd_cnt = 0;
    int pi = 0;
    int total_power = 0;
    memset(prime_divisors, 0, sizeof(prime_divisors));
    memset(ppower, 0, sizeof(ppower));
    // while (k != 1 && pi < pcnt) {
    while (pi < pcnt && prime[pi] * prime[pi] <= k) {
        const int p = prime[pi];
        if (k % p == 0) {
            while (k % p == 0) {
                k = k / p;
                ppower[pd_cnt] += 1;
                total_power += 1;
            }
            prime_divisors[pd_cnt++] = p;
        }
        pi += 1;
    }
    if (k != 1) {
        ppower[pd_cnt] += 1;
        total_power += 1;
        prime_divisors[pd_cnt++] = k;
        pi += 1;
    }
    return total_power;
}

int find_prime_divisors2(long long k)
{
    pd_cnt = 0;
    long long pi = 2;
    int total_power = 0;
    memset(prime_divisors, 0, sizeof(prime_divisors));
    memset(ppower, 0, sizeof(ppower));
    while (k / pi >= pi) {
        if (k % pi == 0) {
            while (k % pi == 0) {
                k = k / pi;
                ppower[pd_cnt] += 1;
                total_power += 1;
            }
            prime_divisors[pd_cnt++] = pi;
        }
        pi += 1;
    }
    if (k != 1) {
        ppower[pd_cnt] += 1;
        total_power += 1;
        prime_divisors[pd_cnt++] = pi;
        pi += 1;
    }
    return total_power;
}

int combination(int pd_end, long long rem = 1)
{
    int pd_idx = pd_end - 1;
    long long new_rem = rem;
    int new_pp = ppower[pd_idx];
    int success_cnt = 0;
    if (area / rem <= rem) {
        return 0;
    }
    if (pd_idx >= 0) {
        while (new_pp > 0) {
            new_rem = new_rem * prime_divisors[pd_idx];
            new_pp -= 1;
            _DEBUG_CMD({ printf("new_rem: %ld, \n", new_rem); });
            // if (new_rem * new_rem < area && new_rem >= min_side) {
            //++success_cnt;
            success_cnt += combination(pd_idx, new_rem);
            //}
        }
        success_cnt += combination(pd_idx, rem);
    }
    else {
        if (area / rem > rem && rem >= min_side) {
            _DEBUG_CMD({
                printf("rem: %lld success on short edge, min_side: %lld. rem * rem: %lld < area: "
                       "%lld \n",
                       rem, min_side, rem * rem, area);
            });
            success_cnt = 1;
        }
    }
    return success_cnt;
}

int combination2()
{
    long long cnt = 1;
    for (int i = 0; i < pd_cnt; ++i) {
        cnt = cnt * (ppower[i] + 1);
    }
    cnt /= 2;
    long long min_factor_cnt = 1;
    find_prime_divisors2(min_side);
    for (int i = 0; i < pd_cnt; ++i) {
        min_factor_cnt = min_factor_cnt * (ppower[i] + 1);
    }
    return cnt - min_factor_cnt + 1;
}

#define max_n 1000050
typedef long long LL;
using namespace std;
LL p[max_n], a[max_n]; //注意p数组大小，虽然用不了，但init里可能会RE
int k = 0;

void init()
{
    memset(p, 0, sizeof(p));
    memset(a, 0, sizeof(a));
    a[0] = a[1] = 1;
    for (int i = 2; i * i <= max_n - 5; i++) {
        if (!a[i]) {
            for (int j = i + i; j <= max_n - 5; j += i)
                a[j] = 1;
        }
    }
    for (int i = 1; i <= max_n - 5; i++) {
        if (!a[i])
            p[k++] = i;
    }
}

void init2()
{
    memset(p, 0, sizeof(p));
    memset(a, 0, sizeof(a));
    for (int i = 2; i < MAXP; ++i) {
        if (!a[i]) {
            p[k++] = i;
        }
        for (int j = 0; j < k && long(p[j]) * i < MAXP; ++j) {
            a[p[j] * i] = 1;
            if (i % p[j] == 0) {
                break;
            }
        }
    }
}

LL nop(LL n)
{
    LL ans = 1;
    for (int i = 0; i < k; i++) {
        if (p[i] > n)
            break;
        LL res = 0;
        while (n % p[i] == 0) {
            res++;
            n /= p[i];
        }
        ans = ans * (res + 1);
    }
    if (n > 1)
        ans *= 2; //注意这一步
    return ans;
}
LL nop2(LL n)
{
    find_prime_divisors2(n);
    LL res = 1;
    for (int i = 0; i < pd_cnt; ++i) {
        res *= (ppower[i] + 1);
    }
    return res;
}

LL calc(LL n)
{
    int ans = 1;
    for (int i = 0; i < pcnt; ++i) {
        int res = 0;
        while (n % prime[i] == 0) {
            ++res;
            n = n / prime[i];
        }
        ans = ans * (res + 1);
    }
    if (n > 1)
        ans = ans * 2;
    return ans;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    {
        // timer t("init prime");
        // init_prime2();
    }
    init2();
    // cin >> T;
    scanf("%d", &T);
    while (T--) {
        int case_num = 0;
        // cin >> area >> min_side;
        {
            // timer t("find prime divisors");
            scanf("%lld%lld", &area, &min_side);
            // int ttp = find_prime_divisors2(area);
        }
        _DEBUG_CMD({
            for (int i = 0; i < pd_cnt; ++i) {
                printf("divisor[%d]: %d, ppf: %d\n", i, prime_divisors[i], ppower[i]);
            }
        });
        _DEBUG_CMD({
            // timer("calculate combinations");
            if (area / min_side <= min_side) {
                printf("Case %d: 0\n", ++case_cnt);
            }
            else {
                printf("Case %d: %d\n", ++case_cnt, combination2());
            }
        });
        {
            // timer("use nop");
            LL num = 0, ans, res = 0;
            LL n = area, m = min_side;
            // scanf("%lld %lld", &n, &m);
            {
                // timer t("ans nop operation");
                ans = nop(n) / 2;
            }
            // printf("%lld\n",ans);
            if (m * m > n)
                ans = 0;
            else {
                num = 0;
                for (int i = 1; i < m; i++) {
                    if (n % i == 0)
                        num++;
                }
                ans -= num;
            }
            static int p = 1;
            printf("Case %d: %lld\n", p++, ans);
        };

        /*
        if (area / min_side <= min_side) {
            printf("Case %d: 0\n", ++case_cnt);
        }
        else {
            printf("Case %d: %d\n", ++case_cnt, combination(pd_cnt, 1));
        }
        */
        // printf("Case %d: %d\n", ++case_cnt, 1);
    }
    return 0;
};

#endif
#endif
