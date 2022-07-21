#if 0
#include <bits/stdc++.h>
#define lc lp, s, mid
#define rc rp, mid + 1, e
#define lp p << 1
#define rp p << 1 | 1
#define mid ((s + e) >> 1)
using namespace std;
const int N = 50005;
int len[N * 4], lr[N * 4], ll[N * 4];
int n, m;

void pushup(int p, int s, int e)
{
    len[p] = max(len[lp], len[rp]);
    len[p] = max(len[p], lr[lp] + ll[rp]);
    ll[p] = ll[lp], lr[p] = lr[rp];
    if (ll[p] == mid - s + 1)
        ll[p] += ll[rp];
    if (lr[p] == e - mid)
        lr[p] += lr[lp];
}

void build(int p, int s, int e)
{
    if (s == e) {
        len[p] = ll[p] = lr[p] = 1;
        return;
    }
    build(lc);
    build(rc);
    pushup(p, s, e);
}

void update(int p, int s, int e, int x, int v)
{
    if (s == e && e == x) {
        len[p] = ll[p] = lr[p] = v;
        return;
    }
    if (x <= mid)
        update(lc, x, v);
    else
        update(rc, x, v);
    pushup(p, s, e);
}

int query(int p, int s, int e, int x)
{
    if (len[p] == 0 || len[p] == e - s + 1)
        return len[p];
    if (x <= mid)
        return x > mid - lr[lp] ? lr[lp] + ll[rp] : query(lc, x);
    return x <= ll[rp] + mid ? ll[rp] + lr[lp] : query(rc, x);
}

int main()
{
    char op[10];
    int p;
    while (~scanf("%d%d", &n, &m)) {
        stack<int> s;
        build(1, 1, n);
        while (m--) {
            scanf("%s", op);
            if (op[0] == 'R' && !s.empty()) {
                p = s.top(), s.pop();
                update(1, 1, n, p, 1);
            }
            else if (op[0] == 'D') {
                scanf("%d", &p);
                update(1, 1, n, p, 0);
                s.push(p);
            }
            else {
                scanf("%d", &p);
                printf("%d\n", query(1, 1, n, p));
            }
        }
    }
    return 0;
}

#else

#ifndef _t7pi_20201006_
#define _t7pi_20201006_
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
//#define DEBUG
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

const int MAXN = 5e4 + 21;
int n, m;
stack<int> dq;
// int arr[MAXN];
int lidx[MAXN << 2], ridx[MAXN << 2];
int alen[MAXN << 2];
int all[MAXN << 2], alr[MAXN << 2];

// int checkfull(int now, int l, int r) { return }

void popup(int now)
{
    int rc = (now | 0x01);
    int lc = (rc ^ 0x01);
    // int rc = (lc ^ 0x01);
    int father = (now >> 1);
    if (father != 0) {
        alen[father] = max(max(alen[lc], alen[rc]), alr[lc] + all[rc]);
        if (alr[rc] == ridx[rc] - lidx[rc] + 1) {
            alr[father] = alr[rc] + alr[lc];
        }
        else {
            alr[father] = alr[rc];
        }
        if (all[lc] == ridx[lc] - lidx[lc] + 1) {
            all[father] = all[lc] + all[rc];
        }
        else {
            all[father] = all[lc];
        }
        popup(father);
    }
}

void build(int now, int l, int r)
{
    lidx[now] = l;
    ridx[now] = r;
    if (l == r) {
        all[now] = 1;
        alr[now] = 1;
        alen[now] = 1;
        popup(now);
        return;
    }
    build(lson, l, mid);
    build(rson, mid + 1, r);
}
void update(int now, int l, int r) {}

int query(int now, int l, int r, int node)
{
    if (l == r) {
        DEBUG_CMD(
            printf("FILE:%s LINE:%u Fun:%s return on l == r\n", __FILE__, __LINE__, __func__));
        return alen[now];
    }
    if (alen[now] == r - l + 1) {
        DEBUG_CMD(printf("FILE:%s LINE:%u Fun:%s return on alen[now] cover r - l + 1\n", __FILE__,
                         __LINE__, __func__));
        return alen[now];
    }
    int ll = all[rson];
    int lr = alr[lson];

    if (node > mid - lr && node <= mid + ll) {
        DEBUG_CMD(printf("FILE:%s LINE:%u Fun:%s return on combine both side answer, now:%d, "
                         "mid:%d l:%d, r:%d lson:%d rson:%d ll:%d lr:%d\n",
                         __FILE__, __LINE__, __func__, now, mid, l, r, lson, rson, ll, lr));
        return ll + lr;
    }

    if (node <= mid) {
        DEBUG_CMD(
            printf("FILE:%s LINE:%u Fun:%s return on left part\n", __FILE__, __LINE__, __func__));
        return query(lson, l, mid, node);
    }
    else {
        DEBUG_CMD(
            printf("FILE:%s LINE:%u Fun:%s return on right part\n", __FILE__, __LINE__, __func__));
        return query(rson, mid + 1, r, node);
    }
}

void destroy(int now, int l, int r, int node)
{
    if (l == r) {
        assert(l == node);
        all[now] = alr[now] = alen[now] = 0;
        popup(now);
        return;
    }
    if (node <= mid) {
        destroy(lson, l, mid, node);
    }
    else {
        destroy(rson, mid + 1, r, node);
    }
}
void recover(int now, int l, int r, int node)
{
    if (l == r) {
        assert(l == node);
        alr[now] = all[now] = alen[now] = 1;
        popup(now);
        return;
    }
    if (node <= mid) {
        recover(lson, l, mid, node);
    }
    else {
        recover(rson, mid + 1, r, node);
    }
}

void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        // printf("\t");
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,alen:%d,ll:%d,lr:%d,%d-%d\n", now, alen[now], all[now], alr[now], l, r);
    }
    else {
        printf("n:%d,alen:%d,ll:%d,lr:%d,%d-%d\n", now, alen[now], all[now], alr[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    char cmd;
    int key;
    while (~scanf("%d%d", &n, &m)) {
        // dq.clear();
        DEBUG_CMD(printf("get a new test case: n:%d m:%d\n", n, m));
        dq = stack<int>();
        /*
        for (int i = 1; i <= n; ++i) {
            arr[i] = i;
        }
        */
        // memset(alen, n, sizeof(alen));
        memset(alen, 0, sizeof(alen));
        memset(lidx, 0, sizeof(lidx));
        memset(ridx, 0, sizeof(ridx));
        // fill_n(alen + 1, n, n);
        build(1, 1, n);
        for (int i = 0; i < m; ++i) {
            // scanf("%c", &cmd);
            cin >> cmd;
            if (cmd == 'D' || cmd == 'Q') {
                // scanf("%d", &key);
                cin >> key;
                if (cmd == 'D') {
                    destroy(1, 1, n, key);
                    dq.push(key);
                }
                else {
                    printf("%d\n", query(1, 1, n, key));
                }
            }
            else {
                if (!dq.empty()) {
                    int last_destroy = dq.top();
                    dq.pop();
                    recover(1, 1, n, last_destroy);
                }
            }
            DEBUG_CMD({
                if (i == 3) {
                    debug_print(1, 1, n, 0);
                }
            });
        }
    }
    return 0;
};

#endif
#endif
