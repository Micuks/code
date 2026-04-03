#if 0
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 100000 + 5;
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
typedef long long LL;
LL sum[maxn << 2], add[maxn];
int a[maxn];
struct node {
    int l, r, m;
    LL sum, mark;
} tree[maxn << 2];

void BuildTree(int l, int r, int k)
{
    tree[k].l = l;
    tree[k].r = r;
    tree[k].m = (l + r) >> 1;
    tree[k].mark = 0;
    if (l == r) {
        tree[k].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(l, mid, k << 1);
    BuildTree(mid + 1, r, k << 1 | 1);

    tree[k].sum = (tree[k << 1].sum + tree[k << 1 | 1].sum);
}
void UpdateTree(int l, int r, int k, int x)
{
    if (tree[k].l == l && tree[k].r == r) {
        tree[k].mark += x;
        return;
    }
    tree[k].sum += (LL) x * (r - l + 1);
    // int mid=(tree[k].l+tree[k].r)>>1;
    int mid = tree[k].m;
    if (r <= mid)
        UpdateTree(l, r, k << 1, x);
    else if (mid < l)
        UpdateTree(l, r, k << 1 | 1, x);
    else {
        UpdateTree(l, mid, k << 1, x);
        UpdateTree(mid + 1, r, k << 1 | 1, x);
    }
}
LL QueryTree(int l, int r, int k)
{
    // cout<<l<<","<<r<<","<<k<<endl;
    if (tree[k].l == l && tree[k].r == r)
        return tree[k].sum + tree[k].mark * (LL)(r - l + 1);

    if (tree[k].mark != 0) {
        tree[k << 1].mark += tree[k].mark;
        tree[k << 1 | 1].mark += tree[k].mark;

        tree[k].sum += (LL)(tree[k].r - tree[k].l + 1) * tree[k].mark; //记得+1
        tree[k].mark = 0;
    }

    // int mid=(tree[k].l+tree[k].r)>>1;
    int mid = tree[k].m;
    if (mid >= r)
        return QueryTree(l, r, k << 1);
    else if (l > mid)
        return QueryTree(l, r, k << 1 | 1);
    else
        return QueryTree(l, mid, k << 1) + QueryTree(mid + 1, r, k << 1 | 1);
}
int main()
{
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        BuildTree(1, n, 1);
        char ch[2];
        int x, y, z;
        while (m--) {
            scanf("%s", ch);
            if (ch[0] == 'Q') {
                scanf("%d%d", &x, &y);
                printf("%lld\n", QueryTree(x, y, 1));
            }
            else if (ch[0] == 'C') {
                scanf("%d%d%d", &x, &y, &z);
                UpdateTree(x, y, 1, z);
            }
        }
    }
    return 0;
}

#else
#ifndef _t7pc_20200902_
#define _t7pc_20200902_
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
int N, Q;
long long arr[MAXN];
long long arrsum[MAXN << 2];
long long lazy_update[MAXN << 2];

void pushdown(int now, int l, int r)
{
    // arrsum[now] += (l - r + 1) * lazy_update[now];
    if (l != r) {
        lazy_update[lson] += lazy_update[now] / (r - l + 1) * (mid - l + 1);
        lazy_update[rson] += lazy_update[now] / (r - l + 1) * (r - mid);
    }
    arrsum[now] += lazy_update[now];
    lazy_update[now] = 0;
}
void popup(int now)
{
    int father = now >> 1;
    if (father == 0) {
        return;
    }
    int other_son = (now ^ 0x01);
    assert(other_son != now);
    assert(other_son / 2 == now / 2);
    assert((other_son & now) == (father << 1));
    long long newfv = arrsum[now] + lazy_update[now] + arrsum[other_son] + lazy_update[other_son];
    if (newfv != arrsum[father]) {
        arrsum[father] = newfv;
        popup(father);
    }
}

long long build(int now, int l, int r)
{
    if (l == r) {
        return arrsum[now] = arr[l];
    }
    return arrsum[now] = build(lson, l, mid) + build(rson, mid + 1, r);
}

long long query(int now, int l, int r, int start, int end);
void update(int now, int l, int r, const int &start, const int &end, const long long &val)
{
    pushdown(now, l, r);
    if (l >= start && r <= end) {
        lazy_update[now] += val * (r - l + 1);
        popup(now);
        return;
    }
    if (start <= mid) {
        update(lson, l, mid, start, end, val);
    }
    if (end > mid) {
        update(rson, mid + 1, r, start, end, val);
    }
}

long long query(int now, int l, int r, int start, int end)
{
    pushdown(now, l, r);
    if (l >= start && r <= end) {
        return arrsum[now];
    }
    if (l == r) {
        return arrsum[now];
    }
    long long newsum = 0;
    if (start <= mid) {
        newsum += query(lson, l, mid, start, end);
        _DEBUG_CMD(
            printf("query(%d, %d, %d, %d, %d): newsum:%lld\n", lson, l, mid, start, end, newsum));
        // newsum += lazy_update[now] * (min(end, mid) - start + 1);
        _DEBUG_CMD(
            printf("lazy_update[%d]:%lld min(%d, %d):%d - start:%d + 1 add_val:%lld newsum:%lld\n",
                   now, lazy_update[now], end, mid, min(end, mid), start,
                   lazy_update[now] * (min(end, mid) - start + 1), newsum));
    }
    if (end > mid) {
        newsum += query(rson, mid + 1, r, start, end);
        // newsum += lazy_update[now] * (end - max(mid + 1, start) + 1);
    }
    return newsum;
}

void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    printf("n:%d,s:%lld,le:%lld %d-%d\n", now, arrsum[now], lazy_update[now], l, r);
    if (l != r) {
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

char ins[1 << 4];
int main(int argc, char **argv)
{
    int a, b;
    long long c;
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &arr[i]);
    }
    memset(lazy_update, 0, sizeof(lazy_update));
    build(1, 1, N);
    for (int i = 0; i < Q; ++i) {
        scanf("%s", ins);
        if (ins[0] == 'C') {

            scanf("%d%d%lld", &a, &b, &c);
            long long s1 = query(1, 1, N, 1, N);
            update(1, 1, N, a, b, c);
            long long s2 = query(1, 1, N, 1, N);
            assert(s2 == s1 + (b - a + 1) * c);
        }
        else {
            assert(ins[0] == 'Q');
            _DEBUG_CMD(debug_print(1, 1, N, 0));
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(1, 1, N, a, b));
        }
    }
    return 0;
};

#endif
#endif
