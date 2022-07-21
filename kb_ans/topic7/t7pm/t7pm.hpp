#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

#define ls l, m, rt << 1
#define rs m + 1, r, rt << 1 | 1
#define defm int m = (l + r) >> 1
const int MAXN = 1e6 + 1000;
int T, t, n, a, b, c;
struct P {
    int lsum, rsum, msum, color;
};
P ds[MAXN << 2], ns[MAXN << 2];
char op[19];

void pushUp(P p[], int rt, int m)
{
    p[rt].lsum = p[rt << 1].lsum;
    if (p[rt << 1].lsum == (m - (m >> 1)))
        p[rt].lsum += p[rt << 1 | 1].lsum;
    p[rt].rsum = p[rt << 1 | 1].rsum;
    if (p[rt << 1 | 1].rsum == (m >> 1))
        p[rt].rsum += p[rt << 1].rsum;
    p[rt].msum =
        max(p[rt << 1].msum, max(p[rt << 1 | 1].msum, p[rt << 1].rsum + p[rt << 1 | 1].lsum));
}

void pushDown(P p[], int rt, int m)
{
    if (p[rt].color != -1) {
        p[rt << 1].color = p[rt << 1 | 1].color = p[rt].color;
        p[rt << 1].lsum = p[rt << 1].msum = p[rt << 1].rsum = p[rt].color ? 0 : m - (m >> 1);
        p[rt << 1 | 1].lsum = p[rt << 1 | 1].msum = p[rt << 1 | 1].rsum =
            p[rt].color ? 0 : (m >> 1);
        p[rt].color = -1;
    }
}

void build(P p[], int l, int r, int rt)
{
    p[rt].color = -1;
    p[rt].lsum = p[rt].msum = p[rt].rsum = r - l + 1;
    if (l == r)
        return;
    defm;
    build(p, ls);
    build(p, rs);
}

int query(P p[], int v, int l, int r, int rt)
{
    if (v > p[rt].msum)
        return 0;
    if (l == r)
        return l;
    pushDown(p, rt, r - l + 1);
    defm;
    if (p[rt << 1].msum >= v)
        return query(p, v, ls);
    if (p[rt << 1].rsum + p[rt << 1 | 1].lsum >= v)
        return m - p[rt << 1].rsum + 1;
    return query(p, v, rs);
}

void update(P p[], int L, int R, int o, int l, int r, int rt)
{
    if (L <= l && r <= R) {
        p[rt].color = o;
        p[rt].lsum = p[rt].msum = p[rt].rsum = o ? 0 : (r - l + 1);
        return;
    }
    if (R < l || r < L)
        return;
    pushDown(p, rt, r - l + 1);
    defm;
    update(p, L, R, o, ls);
    update(p, L, R, o, rs);
    pushUp(p, rt, r - l + 1);
}

int main()
{
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        printf("Case %d:\n", cas);
        scanf("%d%d", &t, &n);
        build(ds, 1, t, 1);
        build(ns, 1, t, 1);
        for (int i = 0; i < n; ++i) {
            scanf("%s%d", op, &a);
            if (op[0] == 'D') {
                b = query(ds, a, 1, t, 1);
                if (b) {
                    printf("%d,let's fly\n", b);
                    update(ds, b, b + a - 1, 1, 1, t, 1);
                }
                else
                    printf("fly with yourself\n");
            }
            else if (op[0] == 'N') {
                b = query(ds, a, 1, t, 1);
                if (b) {
                    printf("%d,don't put my gezi\n", b);
                    update(ds, b, b + a - 1, 1, 1, t, 1);
                    update(ns, b, b + a - 1, 1, 1, t, 1);
                }
                else {
                    c = query(ns, a, 1, t, 1);
                    if (c) {
                        printf("%d,don't put my gezi\n", c);
                        update(ns, c, c + a - 1, 1, 1, t, 1);
                        update(ds, c, c + a - 1, 1, 1, t, 1);
                    }
                    else
                        printf("wait for me\n");
                }
            }
            else {
                scanf("%d", &b);
                update(ds, a, b, 0, 1, t, 1);
                update(ns, a, b, 0, 1, t, 1);
                printf("I am the hope of chinese chengxuyuan!!\n");
            }
        }
    }
    return 0;
}

#else
#ifndef _t7pm_20201120_
#define _t7pm_20201120_
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
// Caleb, DeAngelo,
const int MAXN = 1e5 + 3;
int T, N;

const int MAXTT = 2;
// int arrstart[MAXTT][MAXN << 2];
// int arrlen[MAXTT][MAXN << 2];

int arrllen1[MAXN << 2];
int arrllen2[MAXN << 2];
int arrrlen1[MAXN << 2];
int arrrlen2[MAXN << 2];
int arrtlen1[MAXN << 2];
int arrtlen2[MAXN << 2];

int le1[MAXN << 2], le2[MAXN << 2];

int lb[MAXN << 2], rb[MAXN << 2];

int popup(int now, int arrllen[], int arrrlen[], int arrtlen[])
{
    int ridx = (now | 0x01);
    int lidx = (ridx ^ 0x01);
    int father = (now >> 1);

    if (father != 0) {
        arrrlen[father] = arrrlen[ridx] == rb[ridx] - lb[ridx] + 1 ? arrrlen[ridx] + arrrlen[lidx]
                                                                   : arrrlen[ridx];
        arrllen[father] = arrllen[lidx] == rb[lidx] - lb[lidx] + 1 ? arrllen[lidx] + arrllen[ridx]
                                                                   : arrllen[lidx];
        arrtlen[father] = max(arrrlen[lidx] + arrllen[ridx], max(arrtlen[lidx], arrtlen[ridx]));
    }
}

void pushdown(int now, int arrllen[], int arrrlen[], int arrtlen[], int le[])
{
    const int &l = lb[now];
    const int &r = rb[now];
    if (le[now] == 0) {
        return;
    }
    if (l == r) {
        if (le[now] == 1) {
            arrllen[now] = arrrlen[now] = arrtlen[now] = 0;
        }
        else {
            arrllen[now] = arrrlen[now] = arrtlen[now] = 1;
        }
        le[now] = 0;
        return;
    }
    if (lson <= (T << 2)) {
        if (le[now] == 1) {
            // update
            le[lson] = le[now];
            arrllen[lson] = arrrlen[lson] = arrtlen[lson] = 0;
        }
        else {
            // reset
            le[lson] = le[now];
            arrllen[lson] = arrrlen[lson] = arrtlen[lson] = rb[lson] - lb[lson] + 1;
        }
    }
    if (rson <= (T << 2)) {
        if (le[now] == 1) {
            le[rson] = le[now];
            arrllen[rson] = arrrlen[rson] = arrtlen[rson] = 0;
        }
        else {
            le[rson] = le[now];
            arrllen[rson] = arrrlen[rson] = arrtlen[rson] = rb[rson] - lb[rson] + 1;
        }
    }
    le[now] = 0;
}

void build(int now, int l, int r, int arrllen[], int arrrlen[], int arrtlen[])
{
    lb[now] = l;
    rb[now] = r;
    if (l == r) {
        arrllen[now] = arrrlen[now] = arrtlen[now] = 1;
        popup(now, arrllen, arrrlen, arrtlen);
        return;
    }
    build(lson, l, mid, arrllen, arrrlen, arrtlen);
    build(rson, mid + 1, r, arrllen, arrrlen, arrtlen);
    popup(now, arrllen, arrrlen, arrtlen);
}

void update(int now, int l, int r, int beg, int end, int arrllen[], int arrrlen[], int arrtlen[],
            int le[])
{
    pushdown(now, arrllen, arrrlen, arrtlen, le);
    if (l == r || (l >= beg && r <= end)) {
        le[now] = 1;
        arrllen[now] = 0;
        arrrlen[now] = 0;
        arrtlen[now] = 0;
        popup(now, arrllen, arrrlen, arrtlen);
        return;
    }
    if (mid >= beg) {
        update(lson, l, mid, beg, end, arrllen, arrrlen, arrtlen, le);
    }
    if (mid < end) {
        update(rson, mid + 1, r, beg, end, arrllen, arrrlen, arrtlen, le);
    }
    popup(now, arrllen, arrrlen, arrtlen);
}

int query(int now, int l, int r, int timespan, int arrllen[], int arrrlen[], int arrtlen[],
          int le[])
{
    if (arrllen[now] >= timespan) {
        return l;
    }
    pushdown(now, arrllen, arrrlen, arrtlen, le);
    if (arrtlen[now] >= timespan) {
        int lq = query(lson, l, mid, timespan, arrllen, arrrlen, arrtlen, le);
        if (lq != -1) {
            return lq;
        }
        if (arrrlen[lson] + arrllen[rson] >= timespan) {
            return mid - arrrlen[lson] + 1;
        }
        int rq = query(rson, mid + 1, r, timespan, arrllen, arrrlen, arrtlen, le);
        if (rq != -1) {
            return rq;
        }
    }
    if (arrrlen[now] >= timespan) {
        return r - arrrlen[now] + 1;
    }
    return -1;
}

void reset(int now, int l, int r, int beg, int end, int arrllen[], int arrrlen[], int arrtlen[],
           int le[])
{
    if (l == r || (l >= beg && r <= end)) {
        le[now] = 2;
        arrllen[now] = arrrlen[now] = arrtlen[now] = r - l + 1;
        popup(now, arrllen, arrrlen, arrtlen);
        return;
    }
    pushdown(now, arrllen, arrrlen, arrtlen, le);
    if (mid >= beg) {
        reset(lson, l, mid, beg, end, arrllen, arrrlen, arrtlen, le);
    }
    if (mid < end) {
        reset(rson, mid + 1, r, beg, end, arrllen, arrrlen, arrtlen, le);
    }
    popup(now, arrllen, arrrlen, arrtlen);
}

void debug_print(int now, int l, int r, int inc, int arrllen[], int arrrlen[], int arrtlen[],
                 int le[])
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,lrt:%d-%d-%d,le:%d,%d-%d\n", now, arrllen[now], arrrlen[now], arrtlen[now],
               le[now], l, r);
    }
    else {
        // printf("n:%d,%d-%d\n", now, l, r);
        // printf("n:%d,lrt:%d-%d-%d,%d-%d\n", now, arrllen[now], arrrlen[now], arrtlen[now], l, r);
        printf("n:%d,lrt:%d-%d-%d,le:%d,%d-%d\n", now, arrllen[now], arrrlen[now], arrtlen[now],
               le[now], l, r);
        debug_print(lson, l, mid, inc + 1, arrllen, arrrlen, arrtlen, le);
        debug_print(rson, mid + 1, r, inc + 1, arrllen, arrrlen, arrtlen, le);
    }
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    int c;
    scanf("%d", &c);
    char ii[128];
    int op1, op2;
    while (c--) {
        scanf("%d%d", &T, &N);
        memset(le1, 0, sizeof(le1));
        memset(le2, 0, sizeof(le2));
        build(1, 1, T, arrllen1, arrrlen1, arrtlen1);
        build(1, 1, T, arrllen2, arrrlen2, arrtlen2);
        printf("Case %d:\n", ++case_cnt);
        for (int i = 0; i < N; ++i) {
            scanf("%s", ii);
            if (ii[0] == 'D') {
                scanf("%d", &op1);
                int res = query(1, 1, T, op1, arrllen1, arrrlen1, arrtlen1, le1);
                if (res != -1) {
                    update(1, 1, T, res, op1 + res - 1, arrllen1, arrrlen1, arrtlen1, le1);
                    _DEBUG_CMD({
                        printf("after update 1, 1, %d %d\n", res, op1 + res - 1);
                        debug_print(1, 1, T, 0, arrllen1, arrrlen1, arrtlen1, le1);
                    });
                    printf("%d,let's fly\n", res);
                }
                else {
                    printf("fly with yourself\n");
                }
            }
            else if (ii[0] == 'N') {
                scanf("%d", &op1);
                int res = query(1, 1, T, op1, arrllen1, arrrlen1, arrtlen1, le1);
                if (res != -1) {
                    update(1, 1, T, res, op1 + res - 1, arrllen1, arrrlen1, arrtlen1, le1);
                    update(1, 1, T, res, op1 + res - 1, arrllen2, arrrlen2, arrtlen2, le2);
                    printf("%d,don't put my gezi\n", res);
                }
                else {
                    int res2 = query(1, 1, T, op1, arrllen2, arrrlen2, arrtlen2, le2);
                    if (res2 != -1) {
                        update(1, 1, T, res2, op1 + res2 - 1, arrllen1, arrrlen1, arrtlen1, le1);
                        update(1, 1, T, res2, op1 + res2 - 1, arrllen2, arrrlen2, arrtlen2, le2);
                        printf("%d,don't put my gezi\n", res2);
                    }
                    else {
                        printf("wait for me\n");
                    }
                    _DEBUG_CMD({
                        printf("after update ns and ds 1, 1, %d, %d %d:\n", T, res, op1 + res - 1);
                        debug_print(1, 1, T, 0, arrllen2, arrrlen2, arrtlen2, le2);
                    });
                }
                _DEBUG_CMD(debug_print(1, 1, T, 0, arrllen1, arrrlen1, arrtlen1, le1));
            }
            else {
                scanf("%d%d", &op1, &op2);
                reset(1, 1, T, op1, op2, arrllen1, arrrlen1, arrtlen1, le1);
                reset(1, 1, T, op1, op2, arrllen2, arrrlen2, arrtlen2, le2);
                printf("I am the hope of chinese chengxuyuan!!\n");
                _DEBUG_CMD({
                    printf("reset between %d and %d\n", op1, op2);
                    debug_print(1, 1, T, 0, arrllen1, arrrlen1, arrtlen1, le1);
                });
            }
        }
    }
    return 0;
};

#endif
#endif
