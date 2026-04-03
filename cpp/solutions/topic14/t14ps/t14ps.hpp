#if 0
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#define ll long long
#define ld long double
#define ull unsigned long long
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 100100;
ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0) {
	x = 1;
	y = 0;
	return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
int main(void)
{
    ll A, B, C, K;
    while (1) {
	scanf("%lld%lld%lld%lld", &A, &B, &C, &K);
	if (A == 0 && B == 0 && C == 0 && K == 0)
	    break;
	ll a = C, c = B - A;
	ll b = 1;
	for (ll i = 1; i <= K; i++)
	    b *= 2;
	ll x, y;
	ll g = exgcd(a, b, x, y);
	if (c % g != 0)
	    printf("FOREVER\n");
	else {
	    x = c * x / g;
	    if (x >= 0)
		x = x % (b / g);
	    else
		x = x % (b / g) + b / g;
	    printf("%lld\n", x);
	}
    }
    return 0;
}
#else
#ifndef _t14ps_20200617_
#define _t14ps_20200617_
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
#define DEBUG_CMD(cmd) \
    do {               \
        cmd;           \
    } while (false)
#else
#define DEBUG_CMD(cmd) \
    do {               \
        ;              \
    } while (false)
#endif
#define _DEBUG_CMD(cmd) \
    do {                \
        ;               \
    } while (false)

long long a, b, c, k;

long long get_gcd(long long x, long long two2kthp)
{
    long long gcd = 0;
    while ((x & 0x1) == 0 && gcd <= two2kthp) {
        gcd += 1;
        x = x / 2;
    }
    return gcd;
}

long long ext_gcd(long long a, long long b, long long& x, long long& y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long gcd = ext_gcd(b, a % b, y, x);
    // y = x0
    // x = y0
    // x1 = y0 - [a/b]x0
    // y1 = x0
    y -= (a / b) * x;
    return gcd;
}

int main(int argc, char** argv)
{
    while (cin >> a >> b >> c >> k && k != 0) {
        long long d = b - a;
        long long gcd1 = get_gcd(c, k);
        long long gcd2 = get_gcd(d, k);
        //printf("a: %lld b: %lld c: %lld d(b - a): %lld, k: %lld gcd1(c, k): %lld gcd2(d, k):%lld\n", a, b, c, d, k, gcd1, gcd2);
        if (gcd2 < gcd1) {
            printf("FOREVER\n");
            continue;
        }
        long long x, y;
        long long s = (1LL << (k - gcd1));
        long long g = ext_gcd(c >> gcd1, s, x, y);
        long long rem = (d >> gcd1);
        long long res = (rem * x) % s;
        if (res < 0) {
            res += s;
        }
        //printf("s: %lld g: %lld, x:%lld, y:%lld rem: %lld, res:%lld,\n", s, g, x, y, rem, res);
        printf("%lld\n", res % s);
    }
    return 0;
};

#endif
#endif
