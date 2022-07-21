#if 0
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
const int MOD = 10007;

int n, m;

/********************************* Segment Tree - st *********************************/
struct Node {
    int l, r;
    int sum1, sum2, sum3;
    int add, mul, alt;
    void Update_Alt(int x)
    {
        x %= MOD;
        sum1 = (r - l + 1) * x % MOD;
        sum2 = (r - l + 1) * x % MOD * x % MOD;
        sum3 = (r - l + 1) * x % MOD * x % MOD * x % MOD;
        alt = x;
        add = 0;
        mul = 1;
    }
    void Update_Mul(int x)
    {
        x %= MOD;
        sum1 = sum1 % MOD * x % MOD;
        sum2 = sum2 % MOD * x % MOD * x % MOD;
        sum3 = sum3 % MOD * x % MOD * x % MOD * x % MOD;
        mul = mul % MOD * x % MOD;
        add = add % MOD * x % MOD;
    }
    void Update_Add(int x)
    {
        x %= MOD;
        sum3 = (sum3 % MOD + 3 * x % MOD * sum2 % MOD + 3 * x % MOD * x % MOD * sum1 % MOD +
                (r - l + 1) * x % MOD * x % MOD * x % MOD) %
               MOD;
        sum2 =
            (sum2 % MOD + 2 * x % MOD * sum1 % MOD + (r - l + 1) % MOD * x % MOD * x % MOD) % MOD;
        sum1 = (sum1 % MOD + (r - l + 1) % MOD * x % MOD) % MOD;
        add = (add % MOD + x) % MOD;
    }
} node[4 * maxn];
void Pushdown(int root)
{
    int ls = root * 2, rs = root * 2 + 1;
    if (node[root].alt != 0) {
        node[ls].Update_Alt(node[root].alt);
        node[rs].Update_Alt(node[root].alt);
        node[root].alt = 0;
    }
    if (node[root].mul != 1) {
        node[ls].Update_Mul(node[root].mul);
        node[rs].Update_Mul(node[root].mul);
        node[root].mul = 1;
    }
    if (node[root].add != 0) {
        node[ls].Update_Add(node[root].add);
        node[rs].Update_Add(node[root].add);
        node[root].add = 0;
    }
}
void Pushup(int root)
{
    int ls = root * 2, rs = root * 2 + 1;
    node[root].sum1 = (node[ls].sum1 + node[rs].sum1) % MOD;
    node[root].sum2 = (node[ls].sum2 + node[rs].sum2) % MOD;
    node[root].sum3 = (node[ls].sum3 + node[rs].sum3) % MOD;
}
void Build(int root, int l, int r) //对区间[l,r]建树
{
    if (l > r)
        return;
    node[root].l = l;
    node[root].r = r;
    node[root].sum1 = 0;
    node[root].sum2 = 0;
    node[root].sum3 = 0;
    node[root].alt = 0;
    node[root].add = 0;
    node[root].mul = 1;

    if (l < r) {
        int mid = l + (r - l) / 2;
        Build(root * 2, l, mid);
        Build(root * 2 + 1, mid + 1, r);
        Pushup(root);
    }
}
void Alt(int root, int st, int ed, ll val) //区间[st,ed]全部改成val
{
    if (st > node[root].r || ed < node[root].l)
        return;
    if (st <= node[root].l && node[root].r <= ed)
        node[root].Update_Alt(val);
    else {
        Pushdown(root);
        Alt(root * 2, st, ed, val);
        Alt(root * 2 + 1, st, ed, val);
        Pushup(root);
    }
}
void Mul(int root, int st, int ed, ll val) //区间[st,ed]全部加上val
{
    if (st > node[root].r || ed < node[root].l)
        return;
    if (st <= node[root].l && node[root].r <= ed)
        node[root].Update_Mul(val);
    else {
        Pushdown(root);
        Mul(root * 2, st, ed, val);
        Mul(root * 2 + 1, st, ed, val);
        Pushup(root);
    }
}
void Add(int root, int st, int ed, ll val) //区间[st,ed]全部加上val
{
    if (st > node[root].r || ed < node[root].l)
        return;
    if (st <= node[root].l && node[root].r <= ed)
        node[root].Update_Add(val);
    else {
        Pushdown(root);
        Add(root * 2, st, ed, val);
        Add(root * 2 + 1, st, ed, val);
        Pushup(root);
    }
}
int Query(int root, int st, int ed, int p) //查询区间[st,ed]的p次方和
{
    if (st > node[root].r || ed < node[root].l)
        return 0;
    if (st <= node[root].l && node[root].r <= ed) {
        if (p == 1)
            return node[root].sum1;
        if (p == 2)
            return node[root].sum2;
        if (p == 3)
            return node[root].sum3;
    }
    else {
        Pushdown(root);
        int ls = Query(root * 2, st, ed, p) % MOD;
        int rs = Query(root * 2 + 1, st, ed, p) % MOD;
        Pushup(root);
        return (ls + rs) % MOD;
    }
}
/********************************* Segment Tree - st *********************************/

int main()
{
    while (scanf("%d%d", &n, &m) && n * m != 0) {
        Build(1, 1, n);
        for (int i = 1; i <= m; i++) {
            int op;
            scanf("%d", &op);
            if (op == 1) {
                int x, y, k;
                scanf("%d%d%d", &x, &y, &k);
                Add(1, x, y, k);
            }
            if (op == 2) {
                int x, y, k;
                scanf("%d%d%d", &x, &y, &k);
                Mul(1, x, y, k);
            }
            if (op == 3) {
                int x, y, k;
                scanf("%d%d%d", &x, &y, &k);
                Alt(1, x, y, k);
            }
            if (op == 4) {
                int l, r, p;
                scanf("%d%d%d", &l, &r, &p);
                printf("%d\n", Query(1, l, r, p));
            }
        }
    }
}

#else
#ifndef _t7pk_20201018_
#define _t7pk_20201018_
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
#include <stack>
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

#define mid ((l + r) / 2)
#define lson (now << 1)
#define rson ((now << 1) | 1)

int n, m;
const int mod = 10007;
const int MAXN = 1e5 + 3;
long long arrsum[3][MAXN << 2];
long long asgn[MAXN << 2], add[MAXN << 2], mul[MAXN << 2];

void popup(int now)
{
    int other_son = (now ^ 0x01);
    int father = (now >> 1);
    if (father != 0) {
        arrsum[0][father] = arrsum[0][now] + arrsum[0][other_son];
        arrsum[1][father] = arrsum[1][now] + arrsum[1][other_son];
        arrsum[2][father] = arrsum[2][now] + arrsum[2][other_son];
    }
}
void update_asgn(int now, int l, int r, long long val)
{
    arrsum[0][now] = (val * (r - l + 1)) % mod;
    arrsum[1][now] = (arrsum[0][now] * val) % mod;
    arrsum[2][now] = (arrsum[1][now] * val) % mod;
    asgn[now] = val;
    mul[now] = 1;
    add[now] = 0;
}
void update_mul(int now, int l, int r, long long val)
{
    // val = val % mod;
    arrsum[0][now] = (arrsum[0][now] * val) % mod;
    arrsum[1][now] = (((arrsum[1][now] * val) % mod) * val) % mod;
    arrsum[2][now] = (((((arrsum[2][now] * val) % mod) * val) % mod) * val) % mod;
    mul[now] = (val * mul[now]) % mod;
    add[now] = (add[now] * val) % mod;
}
void update_add(int now, int l, int r, long long val)
{
    // (a+val)^3 = a^3 + 3a^2val + 3aval^2 + val^3
    // val = val % mod;
    arrsum[2][now] = (arrsum[2][now] + (3 * arrsum[1][now] * val) % mod +
                      (((3 * arrsum[0][now] * val) % mod) * val) % mod +
                      ((((((r - l + 1) * val) % mod) * val) % mod) * val) % mod) %
                     mod;
    // (a+val)^2 = a^2 + 2aval + val^2
    arrsum[1][now] = (arrsum[1][now] + (2 * arrsum[0][now] * val) % mod +
                      ((((r - l + 1) * val) % mod) * val % mod)) %
                     mod;
    arrsum[0][now] = (arrsum[0][now] + val * (r - l + 1) % mod) % mod;
    add[now] = (val + add[now]) % mod;
}

void pushdown(int now, int l, int r)
{
    if (asgn[now] != 0) {
        update_asgn(lson, l, mid, asgn[now]);
        update_asgn(rson, mid + 1, r, asgn[now]);
        asgn[now] = 0;
    }
    if (mul[now] != 1) {
        update_mul(lson, l, mid, mul[now]);
        update_mul(rson, mid + 1, r, mul[now]);
        mul[now] = 1;
    }
    if (add[now] != 0) {
        update_add(lson, l, mid, add[now]);
        update_add(rson, mid + 1, r, add[now]);
        add[now] = 0;
    }
}

void build(int now, int l, int r)
{
    if (l == r) {
        asgn[now] = add[now] = 0;
        mul[now] = 1;
        arrsum[0][now] = arrsum[1][now] = arrsum[2][now] = 0;
        return;
    }
    build(lson, l, mid);
    build(rson, mid + 1, r);
    popup(now);
}
void update(int now, int l, int r, int s, int e, int op, int val)
{
    if (l >= s && r <= e) {
        switch (op) {
            case 1:
                update_add(now, l, r, val);
                break;
            case 2:
                update_mul(now, l, r, val);
                break;
            case 3:
                update_asgn(now, l, r, val);
                break;
        }
        popup(now);
        return;
    }
    pushdown(now, l, r);
    if (s <= mid) {
        update(lson, l, mid, s, e, op, val);
    }
    if (e > mid) {
        update(rson, mid + 1, r, s, e, op, val);
    }
    popup(now);
}
long long query(int now, int l, int r, int s, int e, int lev)
{
    if (l >= s && r <= e) {
        return arrsum[lev - 1][now];
    }
    pushdown(now, l, r);
    long long ret = 0;
    if (s <= mid) {
        ret += query(lson, l, mid, s, e, lev);
        ret %= mod;
    }
    if (e > mid) {
        ret += query(rson, mid + 1, r, s, e, lev);
        ret %= mod;
    }
    return ret % mod;
}

void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,a2:%d,m:%d,a:%d,%d-%d\n", now, (int) arrsum[1][now], (int) mul[now],
               (int) asgn[now], l, r);
    }
    else {
        printf("n:%d,a2:%d,m:%d,a:%d,%d-%d\n", now, (int) arrsum[1][now], (int) mul[now],
               (int) asgn[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    int op, x, y, c;
    while (~scanf("%d%d", &n, &m) && n && m) {
        memset(asgn, 0, sizeof(asgn));
        fill_n(mul, MAXN << 2, 1);
        memset(add, 0, sizeof(add));
        memset(arrsum, 0, sizeof(arrsum));
        build(1, 1, n);
        _DEBUG_CMD({
            printf("init query\n");
            printf("query(1, 1, n, 1, n, 3):%d\n", int(query(1, 1, n, 1, n, 3)));
            printf("query(1, 1, n, 1, n, 2):%d\n", int(query(1, 1, n, 1, n, 2)));
            printf("query(1, 1, n, 1, n, 1):%d\n", int(query(1, 1, n, 1, n, 1)));
            debug_print(1, 1, n, 0);
        });

        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d%d", &op, &x, &y, &c);
            switch (op) {
                case 1:
                case 2:
                case 3:
                    update(1, 1, n, x, y, op, c);
                    break;
                case 4:
                    printf("%d\n", int(query(1, 1, n, x, y, c)));
                    break;
            }
            _DEBUG_CMD({
                printf("i=%d, debugPrint\n", i);
                debug_print(1, 1, n, 0);
            });
            _DEBUG_CMD({
                if (i == 2) {
                    debug_print(1, 1, n, 0);
                }
            });
        }
    }
    return 0;
};

#endif
#endif
