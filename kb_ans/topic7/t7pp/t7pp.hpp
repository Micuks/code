#ifndef _t7pp_20201208_
#define _t7pp_20201208_
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

int n;
const int MAXN = 1e3 + 9;
int arrcnt[MAXN << 2];
double arrlen[MAXN << 2];

double xbin[MAXN], ybin[MAXN];
int xcnt, ycnt;

struct Rect {
    double x1, y1, x2, y2;
};
Rect rects[MAXN];

struct Event {
    int x1, x2;
    int op;
    bool operator<(const Event &e) const
    {
        return op > e.op || (op == e.op && x1 < e.x1) || (op == e.op && x1 == e.x1 && x2 < e.x2);
    }
};
vector<Event> events[MAXN];

void update_from_child(int now, int l, int r) { arrlen[now] = arrlen[lson] + arrlen[rson]; }
void build(int now, int l, int r) {}
void update(int now, int l, int r, int beg, int end, int op)
{
    if (l >= beg && r <= end) {
        arrcnt[now] += op;
        if (arrcnt[now] > 0) {
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
        printf("n:%d,cnt:%d,len:%.2lf,%d-%d\n", now, arrcnt[now], arrlen[now], l, r);
    }
    else {
        printf("n:%d,cnt:%d,len:%.2lf,%d-%d\n", now, arrcnt[now], arrlen[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

void init()
{
    xcnt = ycnt = 0;
    for (int i = 0; i < MAXN; ++i) {
        events[i].clear();
    }
    memset(arrcnt, 0, sizeof(arrcnt));
    memset(arrlen, 0, sizeof(arrlen));
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    while (~scanf("%d", &n) && n != 0) {
        init();
        for (int i = 0; i < n; ++i) {
            Rect &r = rects[i];
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
        xbin[0] = xbin[1];
        ybin[0] = ybin[1];
        for (int i = 0; i < n; ++i) {
            Rect &r = rects[i];
            int x1pos = lower_bound(xbin + 1, xbin + 1 + xcnt, r.x1) - xbin;
            int x2pos = lower_bound(xbin + 1, xbin + 1 + xcnt, r.x2) - xbin;
            int y1pos = lower_bound(ybin + 1, ybin + 1 + ycnt, r.y1) - ybin;
            int y2pos = lower_bound(ybin + 1, ybin + 1 + ycnt, r.y2) - ybin;
            if (x2pos > x1pos) {
                events[y1pos].push_back(Event{x1pos, x2pos - 1, +1});
                events[y2pos].push_back(Event{x1pos, x2pos - 1, -1});
            }
        }
        for (int i = 1; i <= ycnt; ++i) {
            sort(events[i].begin(), events[i].end());
        }
        double res = 0.0f;
        const int TREE_CNT = xcnt;
        for (int i = 1; i <= ycnt; ++i) {
            double width = query();
            double height = ybin[i] - ybin[i - 1];
            const vector<Event> &eves = events[i];
            for (int j = 0; j < eves.size(); ++j) {
                const Event &e = eves[j];
                update(1, 1, TREE_CNT, e.x1, e.x2, e.op);
                _DEBUG_CMD(printf("update(1, 1, %d, %d, %d, %d)\n", TREE_CNT, e.x1, e.x2, e.op));
            }
            _DEBUG_CMD({
                printf("i:%d width:%.2lf, height:%.2lf=ybin[%d]:%.2lf-ybin[%d]:%.2lf\n", i, width,
                       height, i, ybin[i], i - 1, ybin[i - 1]);
                debug_print(1, 1, TREE_CNT);
            });
            res += width * height;
        }
        printf("Test case #%d\n", ++case_cnt);
        printf("Total explored area: %.2lf\n\n", res);
    }
    return 0;
};

#endif
