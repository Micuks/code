#if 0
#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#define lson k * 2
#define rson k * 2 + 1
#define M (t[k].l + t[k].r) / 2
#define INF 1008611111
#define ll long long
#define eps 1e-15
struct node {
    int l, r;
    double len1; //覆盖一次的长度
    double len2; //覆盖两次长度
    int v;       //记录覆盖次数
} t[2005 * 4];
double xx[2005]; //离散化后的数组
void Build(int l, int r, int k)
{
    t[k].l = l;
    t[k].r = r;
    t[k].len1 = 0;
    t[k].len2 = 0;
    t[k].v = 0;
    if (l == r)
        return;
    int mid = M;
    Build(l, mid, lson);
    Build(mid + 1, r, rson);
}
void pushup1(int k) //更新len1
{
    if (t[k].v > 0) {
        t[k].len1 = xx[t[k].r + 1] - xx[t[k].l];
        return;
    }
    else if (t[k].l == t[k].r) {
        t[k].len1 = 0;
    }
    else {
        t[k].len1 = t[lson].len1 + t[rson].len1;
    }
}
void pushup2(int k) //更新len2
{
    if (t[k].v > 1) {
        t[k].len2 = xx[t[k].r + 1] - xx[t[k].l];
        return;
    }
    if (t[k].l == t[k].r) {
        t[k].len2 = 0;
    }
    else if (t[k].v == 1) {
        t[k].len2 = t[lson].len1 + t[rson].len1;
    }
    else {
        t[k].len2 = t[lson].len2 + t[rson].len2;
    }
}
void update(int l, int r, int k, int d)
{
    if (l == t[k].l && t[k].r == r) {
        t[k].v += d;
        pushup1(k);
        pushup2(k);
        return;
    }
    int mid = M;
    if (r <= mid)
        update(l, r, lson, d);
    else if (l > mid)
        update(l, r, rson, d);
    else {
        update(l, mid, lson, d);
        update(mid + 1, r, rson, d);
    }
    pushup1(k);
    pushup2(k);
}
struct edge //存扫描线
{
    double l, r;
    double h;
    int d; //存扫描线性质，1为下底，-1为上底
} a[2005];
int cmp(edge x, edge y) //按高度从小到大排序
{
    if (x.h != y.h)
        return x.h < y.h;
    return x.d < y.d;
}
int main()
{
    int i, j, k, n, tot, l, r, test, ans;
    double x1, x2, y1, y2;
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &n);
        tot = 0;
        for (i = 0; i < n; i++) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            a[tot].l = x1;
            a[tot].r = x2;
            a[tot].h = y1;
            a[tot].d = 1;
            a[tot + 1].l = x1;
            a[tot + 1].r = x2;
            a[tot + 1].h = y2;
            a[tot + 1].d = -1;
            xx[tot] = x1;
            xx[tot + 1] = x2;
            tot += 2;
        }
        sort(xx, xx + tot);
        sort(a, a + tot, cmp);
        ans = unique(xx, xx + tot) - xx; //离散化去重
        Build(0, ans - 1, 1);
        double s = 0.0;
        int l = lower_bound(xx, xx + ans, a[0].l) - xx;
        int r = lower_bound(xx, xx + ans, a[0].r) - xx - 1;
        update(l, r, 1, a[0].d);
        for (i = 1; i < tot; i++) {
            s += (t[1].len2 * (a[i].h - a[i - 1].h));
            l = lower_bound(xx, xx + ans, a[i].l) - xx;
            r = lower_bound(xx, xx + ans, a[i].r) - xx - 1;
            update(l, r, 1, a[i].d);
        }
        printf("%.2lf\n", s + eps); //玄学
    }
    return 0;
}
#else
#ifndef _t7po_20201205_
#define _t7po_20201205_
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
#define eps 1e-15

// const int MAXN = 1e3 + 9;
const int MAXN = 4e3 + 1;
int T, N;
int arrcnt[MAXN << 2];
double arrlen[MAXN << 2];

struct Rect {
    double x1, y1, x2, y2;
} rects[MAXN];

struct Event {
    int x1, x2;
    int op;
    bool operator<(const Event &e) const { return op > e.op || (op == e.op && x1 < e.x1); }
};
vector<Event> events[MAXN << 1];

double xbin[MAXN << 1], ybin[MAXN << 1];
int xcnt, ycnt;

void update_from_child(int now, int l, int r) { arrlen[now] = arrlen[lson] + arrlen[rson]; }
void build(int now, int l, int r) {}
void update(int now, int l, int r, int beg, int end, int op)
{
    if (l >= beg && r <= end) {
        arrcnt[now] += op;
        if (arrcnt[now] >= 2) {
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
        update(lson, l, mid, beg, end, op);
    }
    if (mid < end) {
        update(rson, mid + 1, r, beg, end, op);
    }
    update_from_child(now, l, r);
}
void query(int now, int l, int r) {}
double query() { return arrlen[1]; }
void debug_print(int now, int l, int r, int inc = 0)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,cnt:%d,len:%.2f,%d-%d\n", now, arrcnt[now], arrlen[now], l, r);
    }
    else {
        // printf("n:%d,%d-%d\n", now, l, r);
        printf("n:%d,cnt:%d,len:%.2f,%d-%d\n", now, arrcnt[now], arrlen[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

void init()
{
    xcnt = ycnt = 0;
    memset(arrcnt, 0, sizeof(arrcnt));
    memset(arrlen, 0, sizeof(arrlen));
    for (int i = 0; i < (MAXN << 1); ++i) {
        events[i].clear();
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        init();
        scanf("%d", &N);
        for (int j = 0; j < N; ++j) {
            Rect &r = rects[j];
            scanf("%lf%lf%lf%lf", &r.x1, &r.y1, &r.x2, &r.y2);
            xbin[++xcnt] = r.x1;
            xbin[++xcnt] = r.x2;
            ybin[++ycnt] = r.y1;
            ybin[++ycnt] = r.y2;
        }
        sort(xbin + 1, xbin + 1 + xcnt);
        sort(ybin + 1, ybin + 1 + ycnt);
        xcnt = unique(xbin + 1, xbin + 1 + xcnt) - xbin - 1;
        ycnt = unique(ybin + 1, ybin + 1 + ycnt) - ybin - 1;
        for (int j = 0; j < N; ++j) {
            Rect &r = rects[j];
            int x1pos = find(xbin + 1, xbin + 1 + xcnt, r.x1) - xbin;
            int y1pos = find(ybin + 1, ybin + 1 + ycnt, r.y1) - ybin;
            int x2pos = find(xbin + 1, xbin + 1 + xcnt, r.x2) - xbin;
            int y2pos = find(ybin + 1, ybin + 1 + ycnt, r.y2) - ybin;
            if (x1pos < x2pos) {
                _DEBUG_CMD({
                    printf("push events[%d] %d, %d, %d\tevents[%d] %d, %d, %d\n", y1pos, x1pos,
                           x2pos - 1, 1, y2pos, x1pos, x2pos - 1, -1);
                });
                events[y1pos].push_back(Event{x1pos, x2pos - 1, 1});
                events[y2pos].push_back(Event{x1pos, x2pos - 1, -1});
            }
        }
        xbin[0] = xbin[1];
        ybin[0] = ybin[1];
        _DEBUG_CMD({
            printf("xbin[%d]:\n", xcnt);
            for (int j = 0; j <= xcnt; ++j) {
                printf("%.2f ", xbin[j]);
            }
            printf("\nybin[%d]:\n", ycnt);
            for (int j = 0; j <= ycnt; ++j) {
                printf("%.2f ", ybin[j]);
            }
            printf("\n");
        });
        const int TREE_CNT = xcnt;
        double res = 0.0;
        // build(1, 1, TREE_CNT);
        for (int j = 1; j < ycnt; ++j) {
            sort(events[j].begin(), events[j].end());
            _DEBUG_CMD(printf("sort events[%d] len:%u\n", j, events[j].size()));
        }
        for (int j = 1; j <= ycnt; ++j) {
            // sort(events[j].begin(), events[j].end());
            _DEBUG_CMD({
                printf("events[%d] ops:\n", j);
                for (int k = 0; k < events[j].size(); ++k) {
                    printf("op:%d x1:%d, x2:%d ", events[j][k].op, events[j][k].x1,
                           events[j][k].x2);
                }
                printf("\n");
            });
            // _DEBUG_CMD({ debug_print(1, 1, TREE_CNT); });
            double ydiff = ybin[j] - ybin[j - 1];
            _DEBUG_CMD({
                printf("ydiff:%.2f=ybin[%d]%.2f-ybin[%d]%.2f, query:%.2f old res:%.2f\n", ydiff, j,
                       ybin[j], j - 1, ybin[j - 1], query(), res);
            });
            res += query() * ydiff;
            _DEBUG_CMD({
                if (j == 4 || j == 3) {
                    debug_print(1, 1, TREE_CNT);
                }
            });
            for (int k = 0; k < events[j].size(); ++k) {
                Event &e = events[j][k];
                _DEBUG_CMD(
                    { printf("events[%d][%d] x1:%d x2-1:%d, e.op:%d\n", j, k, e.x1, e.x2, e.op); });
                update(1, 1, TREE_CNT, e.x1, e.x2, e.op);
            }
        }
        printf("%.2lf\n", ((double) res + eps));
    }
    return 0;
};

#endif
#endif
