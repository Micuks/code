#ifndef _t7pe_20200907_
#define _t7pe_20200907_
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
const int MAXN = 1e5 + 3;
int t, q, n;

long long arr[MAXN];
long long arrsum[MAXN << 2];
long long lazy_eval[MAXN << 2];

void popup(int now)
{
    if (!now) {
        return;
    }
    int father = now >> 1;
    int other_son = (now ^ 0x01);
    long long newfv = arrsum[now] + arrsum[other_son];
    if (newfv != arrsum[father]) {
        arrsum[father] = newfv;
        popup(father);
    }
}

void pushdown(int now, int l, int r)
{
    if (lazy_eval[now] == 0) {
        return;
    }
    if (l == r) {
        arrsum[now] = arr[l] = lazy_eval[now];
        lazy_eval[now] = 0;
        return;
    }
    // maintain both the lazy_eval flag and arrsum value;
    lazy_eval[lson] = lazy_eval[now];
    lazy_eval[rson] = lazy_eval[now];
    arrsum[lson] = (mid - l + 1) * lazy_eval[now];
    arrsum[rson] = (r - mid) * lazy_eval[now];
    //
    arrsum[now] = lazy_eval[now] * (r - l + 1);
    lazy_eval[now] = 0;
    // pushdown(now, l, r);
}

void build(int now, int l, int r)
{
    if (l == r) {
        arrsum[now] = arr[l];
        popup(now);
        return;
    }
    if (l <= mid) {
        build(lson, l, mid);
    }
    if (r > mid) {
        build(rson, mid + 1, r);
    }
}
void update(int now, int l, int r, int begin, int end, int val)
{
    pushdown(now, l, r);
    if (l == r) {
        lazy_eval[now] = 0;
        arrsum[now] = arr[l] = val;
        popup(now);
        return;
    }
    if (l >= begin && r <= end) {
        lazy_eval[now] = val;
        arrsum[now] = lazy_eval[now] * (r - l + 1);
        popup(now);
        return;
    }
    if (begin <= mid) {
        update(lson, l, mid, begin, end, val);
    }
    if (end > mid) {
        update(rson, mid + 1, r, begin, end, val);
    }
}

long long query(int now, int l, int r, int begin, int end)
{
    pushdown(now, l, r);
    if ((l >= begin && r <= end) || l == r) {
        return arrsum[now];
    }
    long long ret = 0;
    if (begin <= mid) {
        ret += query(lson, l, mid, begin, end);
    }
    if (end > mid) {
        ret += query(rson, mid + 1, r, begin, end);
    }
    return ret;
}

void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    if (l != r) {
        printf("n:%d s:%lld le:%lld %d-%d\n", now, arrsum[now], lazy_eval[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
    else {
        printf("n:%d s:%lld le:%lld a:%lld %d-%d\n", now, arrsum[now], lazy_eval[now], arr[now], l,
               r);
    }
}

int main(int argc, char **argv)
{
    int x, y, v;
    int case_cnt = 0;
    scanf("%d", &t);
    while (t--) {
        memset(lazy_eval, 0, sizeof(lazy_eval));
        scanf("%d", &n);
        fill_n(arr + 1, n, 1LL);
        build(1, 1, n);
        _DEBUG_CMD(debug_print(1, 1, n, 0));
        scanf("%d", &q);
        for (int i = 0; i < q; ++i) {
            scanf("%d%d%d", &x, &y, &v);
            update(1, 1, n, x, y, v);
        }
        printf("Case %d: The total value of the hook is %lld.\n", ++case_cnt, query(1, 1, n, 1, n));
        _DEBUG_CMD(debug_print(1, 1, n, 0));
    }
    return 0;
};

#endif
