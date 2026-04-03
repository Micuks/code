#if 0
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#define MAXC 20
#define MAXK 110
#define limit 10000
#define LL long long
using namespace std;
set<LL> values[MAXC];
LL C, m[MAXC], k[MAXC], Y[MAXC][MAXK];
inline LL read()
{
    LL x = 0, f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
    return x * f;
}
void solve(LL S, LL bc)
{
    for (register LL i = 1; i <= C; ++i)
        if (i != bc) {
            values[i].clear();
            for (register LL j = 0; j < k[i]; ++j)
                values[i].insert(Y[i][j]);
        }
    for (register LL t = 0;; ++t)
        for (register LL i = 0; i < k[bc]; ++i) {
            LL n = m[bc] * t + Y[bc][i];
            if (n == 0)
                continue;
            bool bj = true;
            for (register LL i = 1; i <= C; ++i)
                if (i != bc)
                    if (!values[i].count(n % m[i])) {
                        bj = false;
                        break;
                    }
            if (bj) {
                cout << n << "\n";
                if (--S == 0)
                    return;
            }
        }
}
LL x, y, M;
vector<LL> sol;
void exgcd(LL a, LL b)
{
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b);
    LL t = x;
    x = y;
    y = t - a / b * y;
    return;
}
LL tmp[MAXC];
LL llchina()
{
    LL ans = 0;
    for (register LL i = 1; i <= C; ++i) {
        LL Mi = M / m[i];
        exgcd(Mi, m[i]);
        ans = ((ans + Mi * x * tmp[i]) % M + M) % M;
    }
    return ans;
}
void dfs(LL deep)
{
    if (deep == C + 1) {
        sol.push_back(llchina());
    }
    else
        for (register LL i = 0; i < k[deep]; ++i) {
            tmp[deep] = Y[deep][i];
            dfs(deep + 1);
        }
}
void crt(LL S)
{
    M = 1;
    for (register LL i = 1; i <= C; ++i)
        M *= m[i];
    sol.clear();
    dfs(1);
    sort(sol.begin(), sol.end());
    for (register LL i = 0;; ++i)
        for (register LL j = 0; j < sol.size(); ++j) {
            LL n = M * i + sol[j];
            if (n > 0) {
                printf("%lld\n", n);
                if (--S == 0)
                    return;
            }
        }
}
int main()
{
    LL t;
    for (;;) {
        C = read(), t = read();
        if (!C && !t)
            return 0;
        LL tot = 1;
        LL bestc = 0;
        for (register LL i = 1; i <= C; ++i) {
            m[i] = read(), k[i] = read();
            tot *= k[i];
            for (register LL j = 0; j < k[i]; ++j)
                Y[i][j] = read();
            sort(Y[i], Y[i] + k[i]);
            if (m[bestc] * k[i] <= k[bestc] * m[i])
                bestc = i;
        }
        if (tot > limit)
            solve(t, bestc);
        else
            crt(t);
        putchar('\n');
    }
}

#else
#ifndef _t14pp_20200515_
#define _t14pp_20200515_
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

const int MAXK = 128;
const int MAXC = 16;
int C, S, X[MAXC], k[MAXC];
int y[MAXC][MAXK];
long long Mx[MAXC];
long long M;
long long ti[MAXC];
int best_kox;

long long ex_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b != 0) {
        long long res = ex_gcd(b, a % b, x, y);
        long long y1 = x - (a / b) * y;
        long long x1 = y;
        x = x1;
        y = y1;
        return res;
    }
    else {
        x = 1;
        y = 0;
        return a;
    }
}

// Chinese Remainder Theorem
vector<long long> res;
void dfs(int idx, long long rem)
{
    if (idx == C) {
        while (rem <= 0) {
            rem += M;
        }
        res.push_back(rem);
        return;
    }
    for (int j = 0; j < k[idx]; ++j) {
        long long new_rem = rem + y[idx][j] * ti[idx] * Mx[idx];
        _DEBUG_CMD({
            printf("new_rem: %lld, y[%d][%d]: %lld ti[%d]: %lld Mx[%d] %lld\n", new_rem, idx, j,
                   y[idx][j], idx, ti[idx], idx, Mx[idx]);
        });
        dfs(idx + 1, new_rem % M);
    }
}

void crt()
{
    res.clear();
    res.reserve(S);
    dfs(0, 0);
    sort(res.begin(), res.end());
    _DEBUG_CMD({
        for (int i = 0; i < res.size(); ++i) {
            printf("res[%d]:%lld\n", i, res[i]);
        }
    });
    for (int j = 0;; ++j) {
        for (int k = 0; k < res.size(); ++k) {
            long long n = M * j + res[k];
            if (n > 0) {
                printf("%lld\n", n);
                if (--S == 0)
                    return;
            }
        }
    }
}

/*
bool dfs2(int idx, long long n)
{
    if (idx == C) {
        return true;
    }
    long long rem = n % X[idx];
    int offset = lower_bound(&y[idx][0], &y[idx][k[idx]], rem) - &y[idx][0];
    return binary_search(&y[idx][0], &y[idx][k[idx]], rem) && dfs2(idx + 1, n);
}
*/

// not a dfs actually
bool dfs2(const vector<set<int>> &rs, long long n)
{
    for (int i = 1; i < C; ++i) {
        if (rs[i - 1].find(n % X[i]) == rs[i - 1].end()) {
            return false;
        }
    }
    return true;
}
// search by largest gap
void search()
{
    if (best_kox != 0) {
        swap(X[0], X[best_kox]);
        swap(k[0], k[best_kox]);
        swap(Mx[0], Mx[best_kox]);

        int yt[MAXK];
        memcpy(yt, y[0], sizeof(yt));
        memcpy(y[0], y[best_kox], sizeof(y[0]));
        memcpy(y[best_kox], yt, sizeof(yt));
    }
    for (int i = 0; i < C; ++i) {
        sort(&y[i][0], &y[i][k[i]]);
    }
    _DEBUG_CMD({
        for (int i = 0; i < C; ++i) {
            printf("rule %d: k:%d x:%d ", i, k[i], X[i]);
            for (int j = 0; j < k[i]; ++j) {
                printf("y[%d][%d]: %d ", i, j, y[i][j]);
            }
            printf("Mx[%d]: %lld\n", i, Mx[i]);
        }
    });
    vector<set<int>> rem_set(C);
    for (int i = 1; i < C; ++i) {
        for (int j = 0; j < k[i]; ++j) {
            rem_set[i - 1].insert(y[i][j]);
        }
    }
    long long b = 0;
    while (true) {
        for (int i = 0; i < k[0]; ++i) {
            long long rem = y[0][i] + b * X[0];
            // here is a WA, x is positive
            if (rem == 0) {
                continue;
            }
            if (dfs2(rem_set, rem)) {
                printf("%lld\n", rem);
                --S;
                if (S == 0) {
                    return;
                }
            }
            else {
                _DEBUG_CMD({
                    printf("rem = %lld y[0][%d] = %d b = %d Mx[0]: %d has found not answer!\n", rem,
                           b, i, y[0][i], b, Mx[0]);
                });
            }
        }
        ++b;
    }
}

int main(int argc, char **argv)
{
    _DEBUG_CMD({
        long long a1 = 8;
        long long b1 = 5;
        long long x1 = 0;
        long long y1 = 0;
        long long gcd_ab1 = ex_gcd(a1, b1, x1, y1);
        printf("gcd(%lld, %lld) = %lld, %lld * %lld + %lld * %lld = %lld(gcd)\n", a1, b1, gcd_ab1,
               a1, x1, b1, y1, gcd_ab1);
        if (gcd_ab1 == 1) {
            printf("gcd == 1 thus %lld is perpendicular to %lld\n", a1, b1);
            printf("a*a^-1 = 1 (mod b): %lld*%lld = 1 (mod %lld)\n", a1, x1, b1);
        }
    });
    _DEBUG_CMD({
        long long a1 = 5;
        long long b1 = 8;
        long long x1 = 0;
        long long y1 = 0;
        long long gcd_ab1 = ex_gcd(a1, b1, x1, y1);
        printf("gcd(%lld, %lld) = %lld, %lld * %lld + %lld * %lld = %lld(gcd)\n", a1, b1, gcd_ab1,
               a1, x1, b1, y1, gcd_ab1);
        if (gcd_ab1 == 1) {
            printf("gcd == 1 thus %lld is perpendicular to %lld\n", a1, b1);
            printf("a*a^-1 = 1 (mod b): %lld*%lld = 1 (mod %lld)\n", a1, x1, b1);
        }
    });
    while (cin >> C >> S && C != 0 && S != 0) {
        long long sp = 1;
        M = 1;
        best_kox = 0;
        for (int i = 0; i < C; ++i) {
            cin >> X[i] >> k[i];
            M = M * X[i];
            sp = sp * k[i];
            for (int j = 0; j < k[i]; ++j) {
                cin >> y[i][j];
            }
            if (k[best_kox] * X[i] > k[i] * X[best_kox]) {
                best_kox = i;
            }
        }
        for (int i = 0; i < C; ++i) {
            Mx[i] = M / X[i];
            long long x, y;
            ex_gcd(Mx[i], X[i], x, y);
            /*
            while (x < 0) {
                x = x + X[i];
            }
            */
            ti[i] = x;
        }
        _DEBUG_CMD({
            for (int i = 0; i < C; ++i) {
                printf("ti[%d]: %lld Mx[%d]:%lld, X[%d]:%d %lld * %lld = %lld (mod %d)\n", i, ti[i],
                       i, Mx[i], i, X[i], ti[i], Mx[i], Mx[i] * ti[i] % X[i], X[i]);
            }
        });
        // search();
        // crt();
        // here is a WA if (sp > S)
        if (sp > S) {
            // cout << "do search" << endl;
            search();
        }
        else {
            // cout << "do crt" << endl;
            crt();
        }
        printf("\n");
    }
    return 0;
};

#endif
#endif
