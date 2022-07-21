#if 0
#include <algorithm>
#include <map>
#include <math.h>
#include <set>
#include <stdio.h>
#include <string.h>
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y)
{
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

long long inv(long long a, long long n)
{
    long long x, y;
    exgcd(a, n, x, y);
    return (x + n) % n;
}

long long pow_mod(long long x, long long k, long long n)
{
    if (k == 0)
        return 1;
    long long ans = pow_mod(x * x % n, k >> 1, n);
    if (k & 1)
        ans = ans * x % n;
    return ans;
}

long long log_mod(long long a, long long b, long long n)
{
    long long m = (long long) sqrt(n + 0.5), v, e = 1, i;
    v = inv(pow_mod(a, m, n), n);
    map<long long, long long> x;
    x[1] = 0;
    for (long long i = 1; i < m; i++) {
        e = e * a % n;
        if (!x.count(e))
            x[e] = i;
    }
    for (long long i = 0; i < m; i++) {
        if (x.count(b))
            return i * m + x[b];
        b = b * v % n;
    }
    return -1;
}

const long long MOD = 100000007;
long long t, n, k, b, r, Max, x[505], y[505];
typedef pair<long long, long long> pii;

set<pii> beats;

long long cal()
{
    long long ans = 0;
    for (long long i = 0; i < b; i++) {
        if (x[i] != Max && !beats.count(make_pair(x[i] + 1, y[i])))
            ans++;
    }
    ans += n;
    for (long long i = 0; i < b; i++)
        if (x[i] == 1)
            ans--;
    return pow_mod(k, ans, MOD) * pow_mod(k - 1, Max * n - b - ans, MOD) % MOD;
}

long long solve()
{
    long long m = cal();
    if (m == r)
        return Max;
    long long tmp = n;
    for (long long i = 0; i < b; i++)
        if (x[i] == Max)
            tmp--;
    long long ans = pow_mod(k - 1, tmp, MOD) * pow_mod(k, n - tmp, MOD) % MOD;
    m = m * ans % MOD;
    if (m == r)
        return Max + 1;
    return log_mod(pow_mod(k - 1, n, MOD), r * inv(m, MOD) % MOD, MOD) + Max + 1;
}

int main()
{
    long long cas = 0;
    scanf("%lld", &t);
    while (t--) {
        beats.clear();
        Max = 1;
        scanf("%lld%lld%lld%lld", &n, &k, &b, &r);
        for (long long i = 0; i < b; i++) {
            scanf("%lld%lld", &x[i], &y[i]);
            beats.insert(make_pair(x[i], y[i]));
            Max = max(Max, x[i]);
        }
        printf("Case %lld: %lld\n", ++cas, solve());
    }
    return 0;
}

#else
#ifndef _t14pq_20200517_
#define _t14pq_20200517_
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

// const long long mod = 1e8 + 7;
const long long mod = 100000007;
int T, N, K, B, R;
struct Point {
    int x;
    int y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point &operator=(const Point &) = default;
    Point() = default;
    ~Point() = default;
    bool operator<(const Point &p) const
    {
        if (x == p.x) {
            return y < p.y;
        }
        return x < p.x;
    }
} pts[1 << 9];
int pts_cnt = 0;

ostream &operator<<(ostream &oss, const Point &p)
{
    oss << "(" << p.x << ", " << p.y << ")";
    return oss;
}

long long fast_power(long long x, long long y)
{
    long long ret = 1;
    long long mul = x;
    while (y != 0) {
        if (y & 0x1) {
            ret = (ret * mul) % mod;
        }
        mul = (mul * mul) % mod;
        y = y / 2;
    }
    return ret;
}

long long fast_power_multi(long long res, long long x, long long y)
{
    return (res * fast_power(x, y)) % mod;
}

set<int> neg_set(const set<int> &s)
{
    set<int> ret_set;
    for (int i = 1; i < N; ++i) {
        if (s.find(i) == s.end()) {
        }
    }
}

set<int> set_multi(const set<int> &s1, const set<int> s2) {}

set<int> compliment_set(const set<int> &s1, const set<int> &s2)
{
    // return s1 - s2
    set<int> ret;
    for (set<int>::iterator it = s1.begin(); it != s1.end(); ++it) {
        if (s2.find(*it) == s2.end()) {
            ret.insert(*it);
        }
    }
    return ret;
}

long long exgcd(long long a, long long b, long long &x, long long &y)
{
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

long long inv(long long a, long long n)
{
    long long x, y;
    exgcd(a, n, x, y);
    return (x + n) % n;
}

long long pow_mod(long long x, long long k, long long n)
{
    if (k == 0)
        return 1;
    long long ans = pow_mod(x * x % n, k >> 1, n);
    if (k & 1)
        ans = ans * x % n;
    return ans;
}

long long log_mod(long long a, long long b, long long n)
{
    long long m = (long long) sqrt(n + 0.5), v, e = 1, i;
    v = inv(pow_mod(a, m, n), n);
    map<long long, long long> x;
    x[1] = 0;
    for (long long i = 1; i < m; i++) {
        e = e * a % n;
        if (!x.count(e))
            x[e] = i;
    }
    for (long long i = 0; i < m; i++) {
        if (x.count(b))
            return i * m + x[b];
        b = b * v % n;
    }
    return -1;
}

const long long MOD = 100000007;
long long t, n, k, b, r, Max, x[505], y[505];
typedef pair<long long, long long> pii;

set<pii> beats;

long long cal(long long Max, long long n, long long b, long long MOD)
{
    long long ans = 0;
    for (long long i = 0; i < b; i++) {
        if (x[i] != Max && !beats.count(make_pair(x[i] + 1, y[i])))
            ans++;
    }
    ans += n;
    for (long long i = 0; i < b; i++)
        if (x[i] == 1)
            ans--;
    return pow_mod(k, ans, MOD) * pow_mod(k - 1, Max * n - b - ans, MOD) % MOD;
}

long long cal()
{
    long long ans = 0;
    for (long long i = 0; i < b; i++) {
        if (x[i] != Max && !beats.count(make_pair(x[i] + 1, y[i])))
            ans++;
    }
    ans += n;
    for (long long i = 0; i < b; i++)
        if (x[i] == 1)
            ans--;
    return pow_mod(k, ans, MOD) * pow_mod(k - 1, Max * n - b - ans, MOD) % MOD;
}

long long solve()
{
    // long long min_y = 1;
    // long long m = cal(Max, N, B, mod);
    long long m = cal();
    if (m == r)
        return Max;
    long long tmp = n;
    for (long long i = 0; i < b; i++)
        if (x[i] == Max)
            tmp--;
    long long ans = pow_mod(k - 1, tmp, MOD) * pow_mod(k, n - tmp, MOD) % MOD;
    m = m * ans % MOD;
    if (m == r)
        return Max + 1;
    return log_mod(pow_mod(k - 1, n, MOD), r * inv(m, MOD) % MOD, MOD) + Max + 1;
}

#define lb(x, y) lower_bound(&pts[0], &pts[pts_cnt], Point((x), (y)))
#define bs(v) binary_search(&pts[0], &pts[pts_cnt], (v))
long long solve(int min_x)
{
    long long rem = 1;
    long long res = 1;
    long long ans = 0;

    for (int i = 0; i < B; ++i) {
        if (pts[i].x != min_x && !bs(Point(pts[i].x + 1, pts[i].y))) {
            // if (pts[i].x != min_x && !beats.count(make_pair(pts[i].x + 1, pts[i].y))) {
            ++ans;
        }
    }
    ans += N;
    for (int i = 0; i < B; ++i) {
        if (pts[i].x == 1) {
            --ans;
        }
    }
    long long kp = ans;
    long long km1p = (long long) (min_x) *N - B - ans;

    rem = fast_power_multi(fast_power_multi(1, K - 1, km1p), K, kp);
    // rem = pow_mod(K - 1, km1p, mod) * pow_mod(K, kp, mod) % mod;
    // rem = pow_mod(k, ans, MOD) * pow_mod(k - 1, Max * n - b - ans, MOD) % MOD;
    // rem = cal(min_x, N, B, mod);

    _DEBUG_CMD({ printf("rem after min_Y: %lld\n", rem); });
    if (rem == R) {
        _DEBUG_CMD("extact min_x row!\n");
        return min_x;
    }
    long long tmp = N;
    for (int i = 0; i < B; ++i) {
        if (pts[i].x == min_x) {
            tmp--;
        }
    }
    rem = fast_power_multi(fast_power_multi(rem, K - 1, tmp), K, N - tmp);
    kp += N - tmp;
    km1p += tmp;

    res = min_x + 1;
    if (rem == R) {
        _DEBUG_CMD({ printf("min_x row add one line more! kp: %lld km1p: %lld\n", kp, km1p); });
        return res;
    }
#define MY 1
#ifdef MY
    // important !!! not sqrt + 1!!!
    const long long m = (long long) (sqrtl(mod));

    const long long row_mul = fast_power_multi(1, K - 1, N);

    const long long row_mul_rev = fast_power_multi(1, row_mul, mod - 2);
    _DEBUG_CMD({
        printf("row_mul:%lld row_mul_rev:%lld (%lld*%lld)mod(%lld)=%lld\n", row_mul, row_mul_rev,
               row_mul, row_mul_rev, mod, (row_mul * row_mul_rev) % mod);
    });
    long long rev = fast_power_multi(R, rem, mod - 2);
    _DEBUG_CMD({
        printf("hifi reconstruciton: R:%lld rev: %lld * rem: %lld %% mod %lld: %lld\n", R, rev, rem,
               mod, rev * rem % mod);
    });

    // return log_mod(pow_mod(k - 1, n, MOD), r * inv(m, MOD) % MOD, MOD) + Max + 1;
    // long long lm_ret = log_mod(row_mul, (row_mul_rev * rev) % mod, mod);
    // return lm_ret + res;
    // return log_mod(pow_mod(K - 1, N, mod), R * inv(res, mod) % mod, mod) + min_y + 1;

    map<long long, long long> dl_res;
    for (int i = 0; i <= m; ++i) {
        // WA3: save the minor resukt
        if (!dl_res.count(rev)) {
            dl_res[rev] = i;
        }
        rev = (rev * row_mul_rev) % mod;
        // rev = (rev * row_mul) % mod;
    }

    long long lr = 1;
    long long key;

    _DEBUG_CMD({
        for (int i = 0; i < 10; ++i) {
            printf("dl_res.count(%d): %ld\n", i, dl_res.count(i));
        }
        long long k = fast_power_multi(fast_power_multi(R, rem, mod - 2), row_mul, 4);
        key = k;
        printf("dl_res specific search, rev^-4: %lld dl_res.count(rev^-4): %ld, dl_res[rev^-4]: "
               "%lld\n",
               k, dl_res.count(k), dl_res[k]);
    });
    for (int i = 0; i < m; ++i) {
        map<long long, long long>::iterator iter = dl_res.find(lr);
        if (iter != dl_res.end()) {
            _DEBUG_CMD({ printf("discrete logrithm would suffice!\n"); });
            // WA2: missing modular operation
            // return (res + iter->second + i * m) % (mod - 1);
            _DEBUG_CMD({
                printf("get a answer in discrete logarithm step, res:%lld, i: %d, m: %lld kp:%lld "
                       "km1p: "
                       "%lld \n",
                       res, i, m, kp, km1p + (i * m + iter->second) * N);
                printf(
                    "(rev: %lld* row_mul_rev %lld ^%lld) %%mod: (((%lld))), row_mul:%lld ^ i:%lld "
                    "%%mod: (((%lld)))\n",
                    fast_power_multi(R, rem, mod - 2), row_mul_rev, iter->second, iter->first,
                    row_mul, i, lr);
                printf("return value: res:%lld + iter->second:%lld + i: %d * m : %lld res + "
                       "iter->second + i*m: %lld\n",
                       res, iter->second, i, m, res + iter->second + i * m);
            });
            return (res + iter->second + i * m) % (mod - 1);
        }
        // WA1: implementation error
        // lr = fast_power_multi(lr, K - 1, m);

        // seems good
        // lr = (lr * row_mul) % mod;
        // let's have a try
        // lr = (lr * row_mul_rev) % mod;

        lr = fast_power_multi(lr, row_mul, m);
        // lr = fast_power_multi(lr, row_mul_rev, m);
        _DEBUG_CMD({
            if (lr == key)
                printf("lr: %lld\n", lr);
        });
    }
    _DEBUG_CMD({ printf("all cases have failed!\n"); });
    return -1 + res;
#else
    rem = log_mod(pow_mod(K - 1, N, mod), R * inv(rem, mod) % mod, mod) + Max + 1;
    _DEBUG_CMD({ printf("discrete logarithm matches!\n"); });
    return rem;
#endif
}

int main2()
{
    long long cas = 0;
    scanf("%lld", &t);
    while (t--) {
        beats.clear();
        Max = 1;
        scanf("%lld%lld%lld%lld", &n, &k, &b, &r);
        for (long long i = 0; i < b; i++) {
            scanf("%lld%lld", &x[i], &y[i]);
            beats.insert(make_pair(x[i], y[i]));
            Max = max(Max, x[i]);
        }
        printf("Case %lld: %lld\n", ++cas, solve());
    }
    return 0;
}
int main(int argc, char **argv)
{
    int case_cnt = 0;
    int max_x = 1;
    cin >> T;
    while (T--) {
        beats.clear();
        pts_cnt = 0;
        max_x = 1;
        Max = 1;
        cin >> N >> K >> B >> R;
        n = N;
        k = K;
        b = B;
        r = R;
        for (int i = 0; i < B; ++i) {
            int xx, yy;
            cin >> xx >> yy;
            x[pts_cnt] = xx;
            y[pts_cnt] = yy;
            pts[pts_cnt++] = Point(xx, yy);
            beats.insert(make_pair(xx, yy));
            max_x = max(max_x, xx);
            Max = max_x;
        }
        sort(&pts[0], &pts[pts_cnt]);
        assert(pts_cnt == B);
        printf("Case %d: %lld\n", ++case_cnt, solve(max_x));
    }
    return 0;
};

#endif
#endif
