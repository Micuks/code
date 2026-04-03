#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

struct EuclidReturn {
    long long u, v, d;

    EuclidReturn(long long _u, long long _v, long long _d)
    {
        u = _u;
        v = _v;
        d = _d;
    }
};

EuclidReturn Extended_Euclid(long long a, long long b)
{
    if (b == 0)
        return EuclidReturn(1, 0, a);
    EuclidReturn aux = Extended_Euclid(b, a % b);
    long long v = aux.u - (a / b) * aux.v;
    return EuclidReturn(aux.v, v, aux.d);
}

long long modular_inverse(int a, int n)
{
    EuclidReturn aux = Extended_Euclid(a, n);
    return ((aux.u / aux.d) % n + n) % n;
}

long long solve(int a, int b, int c, int x1, int x2, int Y1, int Y2)
{
    if (x1 > x2 || Y1 > Y2)
        return 0;

    if (a == 0 && b == 0) {
        if (c == 0)
            return (long long) (x2 - x1 + 1) * (Y2 - Y1 + 1);
        return 0;
    }

    if (a == 0) {
        if (c % b == 0 && Y1 <= -c / b && -c / b <= Y2)
            return x2 - x1 + 1;
        return 0;
    }

    if (b == 0) {
        if (c % a == 0 && x1 <= -c / a && -c / a <= x2)
            return Y2 - Y1 + 1;
        return 0;
    }

    int g = __gcd(abs(a), abs(b));

    if (c % g != 0)
        return 0;

    a /= g;
    b /= g;
    c /= g;

    if (b < 0) {
        a = -a;
        b = -b;
        c = -c;
    }

    long long k = modular_inverse((a % b + b) % b, b) * ((-c % b + b) % b) % b;
    long long k2 = (a * k + c) / b;
    long long L1 = ceil((double) (x1 - k) / b), U1 = floor((double) (x2 - k) / b), L2, U2;

    if (a < 0) {
        L2 = ceil((double) (Y1 + k2) / (-a));
        U2 = floor((double) (Y2 + k2) / (-a));
    }
    else {
        L2 = ceil((double) (-k2 - Y2) / a);
        U2 = floor((double) (-k2 - Y1) / a);
    }

    return max(0LL, min(U1, U2) - max(L1, L2) + 1);
}

int main()
{
    int a, b, c, x1, x2, Y1, Y2;

    scanf("%d %d %d %d %d %d %d", &a, &b, &c, &x1, &x2, &Y1, &Y2);
    printf("%lld\n", solve(a, b, c, x1, x2, Y1, Y2));

    return 0;
}

#else
#ifndef _t14pnx_20200619_
#define _t14pnx_20200619_
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

long long a, b, c, x1, x2, Y1, Y2;

long long ext_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long r = ext_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}

int main(int argc, char **argv)
{
    using ::Y1;
    long long min_x, min_y;
    cin >> a >> b >> c >> x1 >> x2 >> Y1 >> Y2;
    if (Y1 > Y2 || x1 > x2) {
        // printf("line:%d 0\n", __LINE__);
        cout << 0 << endl;
        return 0;
    }
    if (a == 0 && b == 0) {
        if (c == 0) {
            printf("%lld\n", (long long) (x2 - x1 + 1) * (Y2 - Y1 + 1));
        }
        else {
            // printf("line:%d 0\n", __LINE__);
            cout << 0 << endl;
        }
        return 0;
    }
    if (a == 0) {
        if (c % b == 0 && -c / b >= Y1 && -c / b <= Y2) {
            printf("%lld\n", x2 - x1 + 1);
        }
        else {
            // printf("line:%d 0\n", __LINE__);
            cout << 0 << endl;
        }
        return 0;
    }
    if (b == 0) {
        if (c % a == 0 && -c / a >= x1 && -c / a <= x2) {
            printf("%lld\n", Y2 - Y1 + 1);
        }
        else {
            // printf("line:%d 0\n", __LINE__);
            cout << 0 << endl;
        }
        return 0;
    }
    /*
    using ll = long long;
    ll tmp = c / gcd;
    double adx = b / gcd, ady = a / gcd;
    ll x = min_x;
    ll y = min_y;
    x *= tmp;
    y *= tmp;
    ll l = max(ceil((x1 - x) / adx), ceil((y - Y2) / ady));
    ll r = min(floor((x2 - x) / adx), floor((y - Y1) / ady));
    if (r >= l)
        cout << r - l + 1 << endl;
    else
        cout << "0" << endl;
    */
    c = -c;
    if (c < 0) {
        c = -c;
        a = -a;
        b = -b;
    }
    if (a < 0) {
        a = -a;
        swap(x1, x2);
        x1 = -x1;
        x2 = -x2;
    }
    if (b < 0) {
        b = -b;
        swap(Y1, Y2);
        Y1 = -Y1;
        Y2 = -Y2;
    }
    long long gcd = ext_gcd(a, b, min_x, min_y);
    if (c % gcd != 0) {
        // printf("line:%d 0\n", __LINE__);
        cout << 0 << endl;
        return 0;
    }
    // printf("a: %d b: %d x: %d y: %d c: %d gcd: %d\n", a, b, min_x, min_y, c, gcd);
    min_x = min_x * c / gcd;
    min_y = min_y * c / gcd;
    long long xl = (x1 - min_x) / (b / gcd) + (((x1 - min_x) % (b / gcd)) == 0 ? 0 : 1);
    long long xu = (x2 - min_x) / (b / gcd);

    // long long yl = (Y2 - min_y) / (a / gcd) + (((Y2 - min_y) % (a / gcd)) == 0 ? 0 : 1);
    // long long yu = (Y1 - min_y) / (a / gcd);
    // swap(yl, yu);
    // yl = -yl;
    // yu = -yu;
    long long yl = (min_y - Y2) / (a / gcd) + (((min_y - Y2) % (a / gcd)) == 0 ? 0 : 1);
    long long yu = (min_y - Y1) / (a / gcd);

    xl = (long long) ceil((double) (x1 - min_x) / (double) (b / gcd));
    xu = (long long) floor((double) (x2 - min_x) / (double) (b / gcd));
    yl = (long long) ceil((double) (min_y - Y2) / (double) (a / gcd));
    yu = (long long) floor((double) (min_y - Y1) / (double) (a / gcd));

    long long res = min(xu, yu) - max(xl, yl) + 1;
    _DEBUG_CMD({
        printf("a:%lld b:%lld c:%lld gcd:%lld minx:%lld miny:%lld xl:%lld xu:%lld yl:%lld yu:%lld "
               "min(xu, yu):%lld max(xl, yl):%lld\n",
               a, b, c, gcd, min_x, min_y, xl, xu, yl, yu, min(xu, yu), max(xl, yl));
    });
    if (res > 0) {
        cout << res << endl;
    }
    else {
        cout << 0 << endl;
        // printf("line:%d 0\n", __LINE__);
    }
    /*
    int res = 0;
    int xstep = b;
    int ystep = a;
    int ts = (x1 - min_x) / xstep + (((x1 - min_x) % xstep) == 0 ? 0 : 1);
    // int te = (x2 - min_x) / xstep + (((x2 - min_x) % xstep) == 0 ? 1 : 0);
    int te = (x2 - min_x) / xstep;

    printf("x1:%d x2:%d y1:%d y2:%d ts: %d, te: %d min_x: %d\n", x1, x2, Y1, Y2, ts, te, min_x);

    for (int t = ts; t <= te; ++t) {
        int y_ans = (min_y - t * ystep);
        int newx = (t * xstep + min_x);
        int newy = (-t * ystep + min_y);
        printf("get an answer: xstep:%d xatts:%d xatte:%d a:%d x:%d b:%d y:%d c:%d, ax+by:%d "
               "y_ans:%d\n",
               xstep, min_x + ts * xstep, min_x + te * xstep, a * gcd, newx, b * gcd, newy, c *
    gcd, (a * newx + b * newy) * gcd, y_ans); if (y_ans >= Y1 && y_ans <= Y2) {
            ++res;
        }
    }
    printf("%d\n", res);
    */
    return 0;
};

#endif
#endif
