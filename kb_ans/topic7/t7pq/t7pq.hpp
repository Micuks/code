#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAXN 100
#define lc k << 1, l, mid
#define rc k << 1 | 1, mid + 1, r
struct node {
    int l, r, h, f;
    bool operator<(node p) const { return h < p.h; }
} a[MAXN << 1];
struct edge {
    int x, xx, y, yy, z, zz;
} b[MAXN];
int sum1[MAXN << 3], sum2[MAXN << 3], sum3[MAXN << 3], f[MAXN << 3], has[MAXN << 1],
    has2[MAXN << 1];
long long ans;
int n, cnt, opl, opr, w;
void up(int k, int l, int r)
{
    if (f[k] >= 3)
        sum3[k] = has2[r + 1] - has2[l];
    else if (f[k] == 2) {
        sum3[k] = sum1[k << 1] + sum1[k << 1 | 1];
        sum2[k] = has2[r + 1] - has2[l];
    }
    else if (f[k] == 1) {
        sum3[k] = sum2[k << 1] + sum2[k << 1 | 1];
        sum2[k] = sum1[k << 1] + sum1[k << 1 | 1];
        sum1[k] = has2[r + 1] - has2[l];
    }
    else {
        sum3[k] = sum3[k << 1] + sum3[k << 1 | 1];
        sum2[k] = sum2[k << 1] + sum2[k << 1 | 1];
        sum1[k] = sum1[k << 1] + sum1[k << 1 | 1];
    }
}
void change(int k, int l, int r)
{
    if (opl <= l && r <= opr) {
        f[k] += w;
        up(k, l, r);
        return;
    }
    int mid = l + r >> 1;
    if (opl <= mid)
        change(lc);
    if (opr > mid)
        change(rc);
    up(k, l, r);
}
void debug_print(int now, int l, int r, int inc = 0)
{
    int mid = (l + r) / 2;
    int lson = (now << 1);
    int rson = ((now << 1) | 1);
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,cnt:%d,l1:%d,l2:%d,l3:%d,%d-%d\n", now, f[now], sum1[now], sum2[now],
               sum3[now], l, r);
    }
    else {
        printf("n:%d,cnt:%d,l1:%d,l2:%d,l3:%d,%d-%d\n", now, f[now], sum1[now], sum2[now],
               sum3[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        ans = 0;
        cnt = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d%d%d", &b[i].x, &b[i].y, &b[i].z, &b[i].xx, &b[i].yy, &b[i].zz);
            has[i * 2 - 1] = b[i].z;
            has[i * 2] = b[i].zz;
        }
        sort(has + 1, has + 2 * n + 1);
        cnt = unique(has + 1, has + 2 * n + 1) - (has + 1);
        for (int i = 1; i < cnt; i++) {
            int sz = 0;
            for (int j = 1; j <= n; j++)
                if (b[j].z <= has[i] && b[j].zz >= has[i + 1]) {
                    a[++sz].l = b[j].x;
                    a[sz].r = b[j].xx;
                    a[sz].h = b[j].y;
                    a[sz].f = 1;
                    a[++sz].l = b[j].x;
                    a[sz].r = b[j].xx;
                    a[sz].h = b[j].yy;
                    a[sz].f = -1;
                    has2[sz - 1] = b[j].x;
                    has2[sz] = b[j].xx;
                }
            sort(has2 + 1, has2 + sz + 1);
            int m = unique(has2 + 1, has2 + sz + 1) - (has2 + 1);
            sort(a + 1, a + sz + 1);
            memset(sum1, 0, sizeof(sum1));
            memset(sum2, 0, sizeof(sum2));
            memset(sum3, 0, sizeof(sum3));
            for (int j = 1; j <= sz; j++) {
                opl = lower_bound(has2 + 1, has2 + m + 1, a[j].l) - has2;
                opr = lower_bound(has2 + 1, has2 + m + 1, a[j].r) - has2 - 1;
                w = a[j].f;
                change(1, 1, m);
                // debug_print(1, 1, m);
                printf("zlen:%d width:%d height:%d area:%d\n", a[j + 1].h - a[j].h, sum3[1],
                       has[i + 1] - has[i], sum3[1] * (has[i + 1] - has[i]));
                ans += 1ll * sum3[1] * (a[j + 1].h - a[j].h) * (has[i + 1] - has[i]);
            }
        }
        printf("Case %d: %lld\n", t, ans);
    }
}

#else
#ifndef _t7pq_20201208_
#define _t7pq_20201208_
#include <algorithm>
#include <assert.h>
#include <chrono>
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

const int MAXN = 1e3 + 9;
int arrcnt[4];
int lzev[MAXN << 3];
int arrlen[4];
int arr1len[MAXN << 3], arr2len[MAXN << 3], arr3len[MAXN << 3];
int T, N;

void debug_print(int now, int l, int r, int inc);
long long check_tree(int now, int l, int r, int inc);
struct Cube {
    int x1, y1, z1;
    int x2, y2, z2;
};
Cube Cubes[MAXN];
vector<Cube> icv[MAXN];
// vector<Cube> ocv[1 << 9];
int TREE_CNT = 0;

struct Event {
    int x1, x2, op;
    bool operator<(const Event &e) { return op > e.op; }
};
vector<Event> events[MAXN << 1];

int xbin[MAXN << 1], ybin[MAXN << 1], zbin[MAXN << 1];
int xcnt, ycnt, zcnt;

int update_from_child1(int now, int l, int r) { arrlen[now] = arrlen[lson] + arrlen[rson]; }
int update_from_child(int now, int l, int r)
{
    arr1len[now] = arr1len[lson] + arr1len[rson];
    arr2len[now] = arr2len[lson] + arr2len[rson];
    arr3len[now] = arr3len[lson] + arr3len[rson];
}
void build(int now, int l, int r) {}
void update1(int now, int l, int r, int beg, int end, int op)
{
    if (l >= beg && r <= end) {
        arrcnt[now] += op;
        if (arrcnt[now] > 2) {
            arrlen[now] = xbin[r + 1] - xbin[l];
        }
        else {
            arrlen[now] = 0;
        }
        if (l == r) {
            return;
        }
    }
    if (mid >= beg) {
        update1(lson, l, mid, beg, end, op);
    }
    if (mid < end) {
        update1(rson, mid + 1, r, beg, end, op);
    }
    update_from_child1(now, l, r);
}
// void popup() {}
void popup(int now) {}

void refresh_node_from_lazy_tag(int now, int l, int r)
{
    _DEBUG_CMD({
        if (lzev[now] < 0) {
            printf("warning, lzev[%d]:%d\n", now, lzev[now]);
            debug_print(1, 1, TREE_CNT, 0);
        }
    });
    if (lzev[now] >= 3) {
        arr1len[now] = arr2len[now] = 0;
        arr3len[now] = xbin[r + 1] - xbin[l];
    }
    else if (lzev[now] == 2) {
        if (l == r) {
            arr3len[now] = 0;
            arr2len[now] = xbin[r + 1] - xbin[l];
            arr1len[now] = 0;
            return;
        }
        else {
            arr3len[now] = arr1len[lson] + arr1len[rson] + arr2len[lson] + arr2len[rson] +
                           arr3len[lson] + arr3len[rson];
            // arr2len[now] = xbin[r + 1] - xbin[l];
            arr2len[now] = xbin[r + 1] - xbin[l] - arr1len[lson] - arr1len[rson] - arr2len[lson] -
                           arr2len[rson] - arr3len[lson] - arr3len[rson];
            arr1len[now] = 0;
        }
    }
    else if (lzev[now] == 1) {
        if (l == r) {
            arr3len[now] = arr2len[now] = 0;
            arr1len[now] = xbin[r + 1] - xbin[l];
        }
        else {
            arr3len[now] = arr2len[lson] + arr2len[rson] + arr3len[lson] + arr3len[rson];
            arr2len[now] = arr1len[lson] + arr1len[rson];
            arr1len[now] = xbin[r + 1] - xbin[l] - arr3len[now] - arr2len[now];
        }
    }
    else {
        if (l == r) {
            arr3len[now] = arr2len[now] = arr1len[now] = 0;
        }
        else {
            arr3len[now] = arr3len[lson] + arr3len[rson];
            arr2len[now] = arr2len[lson] + arr2len[rson];
            arr1len[now] = arr1len[lson] + arr1len[rson];
        }
    }
}
void refresh_node_from_lazy_tag1(int now, int l, int r)
{
    long long new1len, new2len, new3len;
    if (l == r) {
        if (lzev[now] >= 3) {
            new1len = 0;
            new2len = 0;
            new3len = xbin[r + 1] - xbin[l];
        }
        else if (lzev[now] == 2) {
            new1len = 0;
            new2len = xbin[r + 1] - xbin[l];
            new3len = 0;
        }
        else if (lzev[now] == 1) {
            new1len = xbin[r + 1] - xbin[l];
            new2len = 0;
            new3len = 0;
        }
        else if (lzev[now] == 0) {
            new1len = new2len = new3len = 0;
        }
        else {
            new1len = new2len = new3len = 0;
            DEBUG_CMD(printf("error; __LINE__:%d\n", __LINE__));
        }
        new1len = new2len = new3len = 0;
    }
    else {
        /*
        if (lzev[now] >= 3) {
            new1len = new2len = 0;
            new3len = xbin[r + 1] - xbin[l];
        }
        else if (lzev[now] == 2) {
            new1len = 0;
            new2len = xbin[r + 1] - xbin[l] - arr3len[now] - arr2len[now] - arr1len[now];
            new3len = arr3len[now] + arr2len[now] + arr1len[now];
        }
        else if (lzev[now] == 1) {
            new1len = xbin[r + 1] - xbin[l] - arr3len[now] - arr2len[now] - arr1len[now];
            new2len = arr1len[now];
            new3len = arr3len[now] + arr2len[now];
        }
        else if (lzev[now] == 0) {
            // return;
            new1len = arr1len[lson] + arr1len[rson];
            new2len = arr2len[lson] + arr2len[rson];
            new3len = arr3len[lson] + arr3len[rson];
        }
        else if (lzev[now] <= -1) {
            new1len = arr1len[lson] + arr1len[rson];
            new2len = arr2len[lson] + arr2len[rson];
            new3len = arr3len[lson] + arr3len[rson];
            DEBUG_CMD(printf("error; __LINE__:%d\n", __LINE__));

            // new1len = xbin[r + 1] - xbin[l] - arr2len[now] - arr3len[now];
            // new2len = arr1len[now];
            // new3len = arrlen;

            //
            // coredump();
        }
        else {
            DEBUG_CMD(printf("error; __LINE__:%d\n", __LINE__));
        }
        */
        if (lzev[now] >= 3) {
            // new1len = new2len = 0;
            new1len = arr1len[now];
            new2len = arr2len[now];
            new3len = xbin[r + 1] - xbin[l];
        }
        else if (lzev[now] == 2) {
            new3len = arr1len[lson] + arr1len[rson];
            new2len = xbin[r + 1] - xbin[l];
            new1len = arr1len[now];
        }
        else if (lzev[now] == 1) {
            new3len = arr2len[lson] + arr2len[rson];
            new2len = arr1len[lson] + arr1len[rson];
            new1len = xbin[r + 1] - xbin[l];
        }
        else {
            new3len = arr3len[lson] + arr3len[rson];
            new2len = arr2len[lson] + arr2len[rson];
            new1len = arr1len[lson] + arr1len[rson];
        }
    }
    arr1len[now] = new1len;
    arr2len[now] = new2len;
    arr3len[now] = new3len;
}
void pushdown_obsoleted(int now, int l, int r)
{
    int &opc = lzev[now];
    if (opc == 0) {
        return;
    }
    lzev[lson] += opc;
    lzev[rson] += opc;

    if (lzev[lson] < 0) {
        // pushdown(lson, l, mid);
    }
    if (lzev[rson] < 0) {
        // pushdown(rson, mid + 1, r);
    }
    refresh_node_from_lazy_tag(lson, l, mid);
    refresh_node_from_lazy_tag(rson, mid + 1, r);

    opc = 0;
}
void update(int now, int l, int r, int beg, int end, int op)
{
    if (l >= beg && r <= end) {
        lzev[now] += op;
        if (lzev[now] < 0) {
            // pushdown(now, l, r);
        }
        refresh_node_from_lazy_tag(now, l, r);
        return;
    }
    // pushdown(now, l, r);
    if (mid >= beg) {
        update(lson, l, mid, beg, end, op);
    }
    if (mid < end) {
        update(rson, mid + 1, r, beg, end, op);
    }
    // arr3len[now] = arr3len[lson] + arr3len[rson];
    // update_from_child(now, l, r);
    refresh_node_from_lazy_tag(now, l, r);
}
void query(int now, int l, int r) {}
long long query1() { return arrlen[1]; }
long long query() { return arr3len[1]; }
void debug_print1(int now, int l, int r, int inc = 0)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,cnt:%d,len:%lld,%d-%d\n", now, arrcnt[now], arrlen[now], l, r);
    }
    else {
        printf("n:%d,cnt:%d,len:%lld,%d-%d\n", now, arrcnt[now], arrlen[now], l, r);
        debug_print1(lson, l, mid, inc + 1);
        debug_print1(rson, mid + 1, r, inc + 1);
    }
}
void debug_print(int now, int l, int r, int inc = 0)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,cnt:%d,l1:%lld,l2:%lld,l3:%lld,%d-%d\n", now, lzev[now], arr1len[now],
               arr2len[now], arr3len[now], l, r);
    }
    else {
        printf("n:%d,cnt:%d,l1:%lld,l2:%lld,l3:%lld,%d-%d\n", now, lzev[now], arr1len[now],
               arr2len[now], arr3len[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}
long long check_tree(int now, int l, int r, int inc = 0)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (arr1len[now] + arr2len[now] + arr3len[now] > xbin[r + 1] - xbin[l]) {
        printf("n:%d,cnt:%d,l1:%lld,l2:%lld,l3:%lld,%d-%d fail on sum\n", now, lzev[now],
               arr1len[now], arr2len[now], arr3len[now], l, r);
        return 1ll;
    }
    if (l == r) {
        printf("n:%d,cnt:%d,l1:%lld,l2:%lld,l3:%lld,%d-%d\n", now, lzev[now], arr1len[now],
               arr2len[now], arr3len[now], l, r);
    }
    else {
        printf("n:%d,cnt:%d,l1:%lld,l2:%lld,l3:%lld,%d-%d\n", now, lzev[now], arr1len[now],
               arr2len[now], arr3len[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
    return 0ll;
}

void init()
{
    xcnt = ycnt = zcnt = 0;
    memset(arr1len, 0, sizeof(arr1len));
    memset(arr2len, 0, sizeof(arr2len));
    memset(arr3len, 0, sizeof(arr3len));
    memset(lzev, 0, sizeof(lzev));
}

long long scan_line1(const vector<Cube> &c, const vector<int> &f)
{
    if (c.size() == 0) {
        return 0;
    }
    long long ret = 0;
    for (int i = 0; i < (MAXN << 1); ++i) {
        events[i].clear();
    }
    memset(arrcnt, 0, sizeof(arrcnt));
    memset(arrlen, 0, sizeof(arrlen));
    // memset(arr1len, 0, sizeof(arr1len));
    // memset(arr2len, 0, sizeof(arr2len));
    // memset(arr3len, 0, sizeof(arr3len));
    // memset(lzev, 0, sizeof(lzev));
    vector<int> ys;
    for (size_t i = 0; i < c.size(); ++i) {
        int x1pos = lower_bound(xbin + 1, xbin + 1 + xcnt, c[i].x1) - xbin;
        int x2pos = lower_bound(xbin + 1, xbin + 1 + xcnt, c[i].x2) - xbin;
        int y1pos = lower_bound(ybin + 1, ybin + 1 + ycnt, c[i].y1) - ybin;
        int y2pos = lower_bound(ybin + 1, ybin + 1 + ycnt, c[i].y2) - ybin;
        events[y1pos].push_back(Event{x1pos, x2pos - 1, +1 * f[i]});
        events[y2pos].push_back(Event{x1pos, x2pos - 1, -1 * f[i]});
        ys.push_back(y1pos);
        ys.push_back(y2pos);
    }

    _DEBUG_CMD({
        printf("before sort ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    sort(ys.begin(), ys.end());
    _DEBUG_CMD({
        printf("after sort, before push_back ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    ys.push_back(ys[0]);
    _DEBUG_CMD({
        printf("after push_back, before sort ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    sort(ys.begin(), ys.end());
    _DEBUG_CMD({
        printf("after sort, before unique ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    ys.erase(unique(ys.begin() + 1, ys.end()), ys.end());
    _DEBUG_CMD({
        printf("after unqiue at begin() + 1 ys.len:%lu: ", ys.size());
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });

    TREE_CNT = xcnt - 1;
    _DEBUG_CMD({
        printf("xbin: ");
        for (int i = 0; i <= xcnt; ++i) {
            printf("%lld ", xbin[i]);
        }
        printf("\n");
    });
    int debug_cnt = 0;

    for (size_t i = 1; i < ys.size(); ++i) {
        long long width = query();
        // long long width = query1();
        long long height = ybin[ys[i]] - ybin[ys[i - 1]];
        _DEBUG_CMD({
            printf("i:%lu, ys:%d, width:%lld, height:%lld det(area):%lld\n", i, ys[i], width,
                   height, width * height);
            if (c.size() == 3 && false) {
                printf("zbin[3] == 5, debug_print map\n");
                debug_print(1, 1, TREE_CNT);
            }
            if (false && i == 3 && ys[i] == 3 && width == 9 && height == 3) {
                debug_print(1, 1, TREE_CNT);
            }
        });
        const vector<Event> &eves = events[ys[i]];
        for (size_t j = 0; j < eves.size(); ++j) {
            const Event &e = eves[j];
            update(1, 1, TREE_CNT, e.x1, e.x2, e.op);
            // update1(1, 1, TREE_CNT, e.x1, e.x2, e.op);
            debug_cnt += e.op;
            _DEBUG_CMD({
                printf("update(1, 1, %d, %d, %d, %d)\n", TREE_CNT, e.x1, e.x2, e.op);
                debug_print(1, 1, TREE_CNT);
                if (c.size() == 3) {
                }
            });
        }
        ret += width * height;
    }
    _DEBUG_CMD({ printf("c.size():%lu debug_cnt:%d\n", c.size(), debug_cnt); });
    return ret;
}

long long scan_line(const vector<Cube> &c)
{
    if (c.size() == 0) {
        return 0;
    }
    long long ret = 0;
    for (int i = 0; i < (MAXN << 1); ++i) {
        events[i].clear();
    }
    memset(arrcnt, 0, sizeof(arrcnt));
    memset(arrlen, 0, sizeof(arrlen));
    memset(arr1len, 0, sizeof(arr1len));
    memset(arr2len, 0, sizeof(arr2len));
    memset(arr3len, 0, sizeof(arr3len));
    memset(lzev, 0, sizeof(lzev));
    vector<int> ys;
    for (size_t i = 0; i < c.size(); ++i) {
        int x1pos = lower_bound(xbin + 1, xbin + 1 + xcnt, c[i].x1) - xbin;
        int x2pos = lower_bound(xbin + 1, xbin + 1 + xcnt, c[i].x2) - xbin;
        int y1pos = lower_bound(ybin + 1, ybin + 1 + ycnt, c[i].y1) - ybin;
        int y2pos = lower_bound(ybin + 1, ybin + 1 + ycnt, c[i].y2) - ybin;
        events[y1pos].push_back(Event{x1pos, x2pos - 1, +1});
        events[y2pos].push_back(Event{x1pos, x2pos - 1, -1});
        ys.push_back(y1pos);
        ys.push_back(y2pos);
    }

    _DEBUG_CMD({
        printf("before sort ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    sort(ys.begin(), ys.end());
    _DEBUG_CMD({
        printf("after sort, before push_back ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    ys.push_back(ys[0]);
    _DEBUG_CMD({
        printf("after push_back, before sort ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    sort(ys.begin(), ys.end());
    _DEBUG_CMD({
        printf("after sort, before unique ys: ");
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });
    ys.erase(unique(ys.begin() + 1, ys.end()), ys.end());
    _DEBUG_CMD({
        printf("after unqiue at begin() + 1 ys.len:%lu: ", ys.size());
        for (auto iter = ys.begin(); iter != ys.end(); ++iter) {
            printf("%d ", *iter);
        }
        printf("\n");
    });

    TREE_CNT = xcnt - 1;
    _DEBUG_CMD({
        printf("xbin: ");
        for (int i = 0; i <= xcnt; ++i) {
            printf("%lld ", xbin[i]);
        }
        printf("\n");
    });
    int debug_cnt = 0;

    for (size_t i = 1; i < ys.size(); ++i) {
        long long width = query();
        // long long width = query1();
        long long height = ybin[ys[i]] - ybin[ys[i - 1]];
        _DEBUG_CMD({
            printf("i:%lu, ys:%d, width:%lld, height:%lld det(area):%lld\n", i, ys[i], width,
                   height, width * height);
            if (c.size() == 3 && false) {
                printf("zbin[3] == 5, debug_print map\n");
                debug_print(1, 1, TREE_CNT);
            }
            // if (false && i == 3 && ys[i] == 3 && width == 9 && height == 3) {
            // if (i == 4 && width == 7 && height == 1) {
            // if (i == 4 && width == 9 && height == 1) {
            if (1) {
                debug_print(1, 1, TREE_CNT);
            }
        });
        const vector<Event> &eves = events[ys[i]];
        for (size_t j = 0; j < eves.size(); ++j) {
            const Event &e = eves[j];
            update(1, 1, TREE_CNT, e.x1, e.x2, e.op);
            // update1(1, 1, TREE_CNT, e.x1, e.x2, e.op);
            debug_cnt += e.op;
            _DEBUG_CMD({
                printf("update(1, 1, %d, %d, %d, %d)\n", TREE_CNT, e.x1, e.x2, e.op);
                // debug_print(1, 1, TREE_CNT);
                if (c.size() == 3) {
                }
            });
        }
        ret += width * height;
    }
    _DEBUG_CMD({ printf("c.size():%lu debug_cnt:%d\n", c.size(), debug_cnt); });
    return ret;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    scanf("%d", &T);
    while (T--) {
        auto start = chrono::steady_clock::now();
        _DEBUG_CMD({ cout << "timer: " << endl; });
        long long res = 0;
        scanf("%d", &N);
        init();
        for (int i = 0; i < N; ++i) {
            Cube &c = Cubes[i];
            // scanf("%lld%lld%lld%lld%lld%lld", &c.x1, &c.y1, &c.z1, &c.x2, &c.y2, &c.z2);
            scanf("%d%d%d%d%d%d", &c.x1, &c.y1, &c.z1, &c.x2, &c.y2, &c.z2);
            xbin[++xcnt] = c.x1;
            xbin[++xcnt] = c.x2;
            ybin[++ycnt] = c.y1;
            ybin[++ycnt] = c.y2;
            zbin[++zcnt] = c.z1;
            zbin[++zcnt] = c.z2;
        }
        sort(xbin + 1, xbin + 1 + xcnt);
        sort(ybin + 1, ybin + 1 + ycnt);
        sort(zbin + 1, zbin + 1 + zcnt);
        xcnt = unique(xbin + 1, xbin + 1 + xcnt) - xbin - 1;
        ycnt = unique(ybin + 1, ybin + 1 + ycnt) - ybin - 1;
        zcnt = unique(zbin + 1, zbin + 1 + zcnt) - zbin - 1;
        xbin[0] = xbin[1];
        ybin[0] = ybin[1];
        zbin[0] = zbin[1];

        _DEBUG_CMD({
            auto end = chrono::steady_clock::now();
            cout << "Elapsed time in reading input: "
                 << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms\n";
            start = end;
        });
        _DEBUG_CMD({
            printf("xbin: ");
            for (int i = 0; i <= xcnt; ++i) {
                printf("%lld ", xbin[i]);
            }
            printf("\n");
        });
        for (size_t i = 0; i < N; ++i) {
            Cube &c = Cubes[i];
            int fz = lower_bound(zbin + 1, zbin + 1 + zcnt, c.z1) - zbin - 1;
            int lz = lower_bound(zbin + 1, zbin + 1 + zcnt, c.z2) - zbin - 1;
            for (int j = fz + 1; j <= lz; ++j) {
                icv[j].push_back(c);
            }
            // ocv[Cubes[i].z2].push_back(Cubes[i]);
        }
        _DEBUG_CMD({
            auto end = chrono::steady_clock::now();
            cout << "Elapsed time in calculating z-axis:"
                 << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms\n";
            start = end;
        });

        for (size_t i = 1; i <= zcnt; ++i) {
            // vector<Cube> &cs = icv[i];
            vector<Cube> cs;
            // vector<int> flags;
            long long zlen = zbin[i] - zbin[i - 1];
            for (int j = 0; j < N; ++j) {
                // if (Cubes[i].z1 >= zbin[i - 1] && Cubes[i].z2 <= zbin[i]) {
                if (Cubes[j].z1 < zbin[i] && Cubes[j].z2 >= zbin[i]) {
                    // if (Cubes[j].z1 <= zbin[i] && Cubes[j].z2 > zbin[i]) {
                    cs.push_back(Cubes[j]);
                    _DEBUG_CMD({
                        printf("zbin[%lu]:%lld C[%d].z1:%lld C[%d].z2:%lld\n", i, zbin[i], j,
                               Cubes[j].z1, j, Cubes[j].z2);
                    });
                }
            }
            // long long area = scan_line1(cs, flags);
            long long area = scan_line(cs);
            _DEBUG_CMD({
                printf("zbin[%lu]:%lld zlen:%lld, area:%lld, cs.size():%lu\n\n", i, zbin[i], zlen,
                       area, cs.size());
            });
            res += zlen * area;
        }
        //*/
        _DEBUG_CMD({
            auto end = chrono::steady_clock::now();
            cout << "Elapsed time in calculating seg-tree:"
                 << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms\n";
            start = end;
        });

        printf("Case %d: %lld\n", ++case_cnt, res);
    }
    return 0;
};

#endif
#endif
