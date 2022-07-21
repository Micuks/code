#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int inf = 1e9, N = 100003;
int n, k, l, r, i, ans, las, a, b, c, d;
struct node {
    int l, r, h, f;
    bool operator<(node x) const { return h < x.h || h == x.h && f > x.f; }
} s[N];
struct kk {
    int l, r, sum, cnt, len;
} tree[N << 2];
void pushup(int t, int l, int r)
{
    if (tree[t].cnt) {
        tree[t].l = tree[t].r = tree[t].sum = 1;
        tree[t].len = r - l + 1;
    }
    else if (l == r)
        tree[t] = (kk){0, 0, 0, 0, 0};
    else {
        tree[t].l = tree[t << 1].l;
        tree[t].r = tree[t << 1 | 1].r;
        tree[t].len = tree[t << 1].len + tree[t << 1 | 1].len;
        tree[t].sum =
            tree[t << 1].sum + tree[t << 1 | 1].sum - (tree[t << 1].r && tree[t << 1 | 1].l);
    }
}
void add(int t, int l, int r, int x, int y, int v)
{
    if (x <= l && r <= y)
        tree[t].cnt += v;
        int mid = l + r >> 1;
        if (x <= mid)
            add(t << 1, l, mid, x, y, v);
        if (mid < y)
            add(t << 1 | 1, mid + 1, r, x, y, v);
    }
    pushup(t, l, r);
}
int main()
{
    while (~scanf("%d", &n)) {
        k = ans = las = 0;
        l = inf;
        r = -inf;
        for (i = 0; i < n; i++) {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            l = min(l, a);
            r = max(r, c);
            s[k++] = (node){a, c, b, 1};
            s[k++] = (node){a, c, d, -1};
        }
        sort(s, s + k);
        for (i = 0; i < k; i++) {
            if (s[i].l < s[i].r)
                add(1, l, r - 1, s[i].l, s[i].r - 1, s[i].f);
            ans += tree[1].sum * 2 * (s[i + 1].h - s[i].h);
            ans += abs(tree[1].len - las);
            las = tree[1].len;
        }
        printf("%d\n", ans);
    }
}
#else
#ifndef _t7pn_20201130_
#define _t7pn_20201130_
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
const int MAXN = 1e4 + 7;
const int MAXR = 5e3 + 3;

struct Rect {
    int x1, y1;
    int x2, y2;
} rects[MAXR];
int rcnt;

int arrseg[MAXN << 2];
int arrlm[MAXN << 2];
int arrrm[MAXN << 2];
int arrccnt[MAXN << 2];
int lidx[MAXN << 2], ridx[MAXN << 2];

int arrnzcnt[MAXN << 2];
int arrnzlen[MAXN << 2];
int arrhlen[MAXN << 2];

int xbin[MAXN], ybin[MAXN];
int xcnt, ycnt;

struct Event {
    int x1, x2;
    int op;
    bool operator<(const Event &e) const { return op > e.op; }
};
vector<Event> events[MAXR];
int ecnt;

void pushdown(int now, int l, int r)
{
    arrseg[lson] = arrseg[rson] = arrseg[now];
    return;
}

void popup(int now)
{
    int lsid = (now | 0x01);
    int rsid = (lsid ^ 0x01);
    int father = (now >> 1);

    arrlm[father] = arrlm[lsid];
    arrrm[father] = arrrm[rsid];
    // arrccnt[father] = arrccnt[lsid] + arrccnt[rsid];
    arrseg[father] = arrseg[lsid] + arrseg[rsid];

    // arrnzcnt[father] = arrnzcnt[lsid] + arrnzcnt[rsid];
    arrnzlen[father] = arrnzlen[lsid] + arrnzlen[rsid];

    if (arrrm[lsid] && arrlm[rsid]) {
        // arrccnt[father] -= 1;
        // arrnzcnt[father] -= 1;
        arrseg[father] -= 1;
    }
}

void build(int now, int l, int r)
{
    lidx[now] = l;
    ridx[now] = r;
    if (l == r) {
        arrrm[now] = arrlm[now] = arrseg[now] = 0;
        popup(now);
        return;
    }
    build(lson, l, mid);
    build(rson, mid + 1, r);
    popup(now);
}

void update(int now, int l, int r, int beg, int end, int op)
{
    if (l >= beg && r <= end) {
        // arrseg[now] += op;
        arrccnt[now] += op;
        // if (arrseg[now] > 0) {
        if (arrccnt[now] > 0) {
            arrrm[now] = arrlm[now] = 1;
            arrseg[now] = 1;
            arrnzlen[now] = xbin[r + 1] - xbin[l];
        }
        else {
            arrrm[now] = arrlm[now] = arrseg[now] = 0;
            arrnzlen[now] = 0;
        }
        if (l == r) {
            popup(now);
            return;
        }
    }
    if (mid >= beg) {
        update(lson, l, mid, beg, end, op);
    }
    if (mid < end) {
        update(rson, mid + 1, r, beg, end, op);
    }
    popup(now);
}
void query(int now, int l, int r) {}
int query() { return arrseg[1] * 2; }
void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,len:%d,seg:%d,cnt:%d,%d-%d\n", now, arrnzlen[now], arrseg[now], arrccnt[now],
               l, r);
    }
    else {
        printf("n:%d,len:%d,seg:%d,cnt:%d,%d-%d\n", now, arrnzlen[now], arrseg[now], arrccnt[now],
               l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    int bottom, left, up, right;
    scanf("%d", &rcnt);
    for (int i = 0; i < rcnt; ++i) {
        scanf("%d%d%d%d", &left, &bottom, &right, &up);
        xbin[++xcnt] = left;
        xbin[++xcnt] = right;
        ybin[++ycnt] = bottom;
        ybin[++ycnt] = up;
        rects[i] = Rect{left, bottom, right, up};
    }
    sort(xbin + 1, xbin + 1 + xcnt);
    sort(ybin + 1, ybin + 1 + ycnt);
    xcnt = unique(xbin + 1, xbin + 1 + xcnt) - xbin - 1;
    ycnt = unique(ybin + 1, ybin + 1 + ycnt) - ybin - 1;
    xbin[0] = xbin[1];
    ybin[0] = ybin[1];

    for (int i = 0; i < rcnt; ++i) {
        int x1pos = lower_bound(xbin + 1, xbin + 1 + xcnt, rects[i].x1) - xbin;
        int x2pos = lower_bound(xbin + 1, xbin + 1 + xcnt, rects[i].x2) - xbin;
        int y1pos = lower_bound(ybin + 1, ybin + 1 + ycnt, rects[i].y1) - ybin;
        int y2pos = lower_bound(ybin + 1, ybin + 1 + ycnt, rects[i].y2) - ybin;
        if (x1pos < x2pos) {
            events[y1pos].push_back(Event{x1pos, x2pos, 1});
            events[y2pos].push_back(Event{x1pos, x2pos, -1});
        }
    }
    for (int i = 1; i < ycnt; ++i) {
        sort(events[i].begin(), events[i].end());
    }

    int result = 0;
    int hlen = 0;
    int vlen = 0;
    int last_len = 0;
    const int TREE_LEN = xcnt;

    build(1, 1, TREE_LEN);
    for (int i = 1; i <= ycnt; ++i) {
        int diff = (ybin[i] - ybin[i - 1]) * query();
        vlen += diff;
        _DEBUG_CMD({
            printf("i:%d vlen:%d diff:%d arrseg[1]:%d, ybin[%d]%d-ybin[%d]%d:%d\n", i, vlen, diff,
                   arrseg[1], i, ybin[i], i - 1, ybin[i - 1], ybin[i] - ybin[i - 1]);
        });
        for (unsigned j = 0; j < events[i].size(); ++j) {
            // debug_print(1, 1, TREE_LEN, 0);
            _DEBUG_CMD({
                // if (i == 2 && j == 0) {
                printf("i:%d,j:%d\n", i, j);
                debug_print(1, 1, TREE_LEN, 0);
                //}
            });
            update(1, 1, TREE_LEN, events[i][j].x1, events[i][j].x2 - 1, events[i][j].op);
            // result += abs(arrnzlen[1] - last_len);
            _DEBUG_CMD({
                printf("events[%d][%d]:(%d-%d,%d~%d),op:%d,last_len:%d arrnzlen[1]:%d new gain "
                       "vlen:%d\n",
                       i, j, events[i][j].x1, events[i][j].x2, xbin[events[i][j].x1],
                       xbin[events[i][j].x2], events[i][j].op, last_len, arrnzlen[1],
                       abs(last_len - arrnzlen[1]));
            });
            hlen += abs(arrnzlen[1] - last_len);
            last_len = arrnzlen[1];
        }
        // result += (ybin[i] - ybin[i - 1]) * query();
        _DEBUG_CMD({
            if (i == 3) {
                printf("third run");
                debug_print(1, 1, TREE_LEN, 0);
            }
        });
    }
    // hlen += (ybin[ycnt + 1] - ybin[ycnt]) * query();
    result = hlen + vlen;
    _DEBUG_CMD(printf("hlen:%d vlen:%d, tlen:%d\n", hlen, vlen, result));
    printf("%d\n", result);
    return 0;
};

#endif
#endif
