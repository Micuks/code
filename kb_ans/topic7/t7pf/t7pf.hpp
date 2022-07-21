#ifndef _t7pf_20200909_
#define _t7pf_20200909_
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

const int MAXN = 1 << 13;
const int SEG_LEN = 8000;
int arr[MAXN];
int arrc[MAXN << 2];
int n;

#define mid ((l + r) / 2)
#define lson (now << 1)
#define rson ((now << 1) | 1)

void popup(int now) {}
void pushdown(int now, int l, int r)
{
    if (arrc[now] != -1) {
        arrc[lson] = arrc[now];
        arrc[rson] = arrc[now];
    }
    arrc[now] = -1;
}

void build(int now, int l, int r)
{
    memset(arrc, -1, sizeof(arrc));
    memset(arr, -1, sizeof(arr));
    // fill_n(arr, n + 1, -1);
}
void update(int now, int l, int r, int beg, int end, int color)
{
    if (l == r) {
        arrc[now] = -1;
        arr[l] = color;
        // popup(now);
        return;
    }
    if (l >= beg && r <= end) {
        arrc[now] = color;
        // popup(now);
        return;
    }
    pushdown(now, l, r);
    if (beg <= mid) {
        update(lson, l, mid, beg, end, color);
    }
    if (end > mid) {
        update(rson, mid + 1, r, beg, end, color);
    }
}
void query(int now, int l, int r)
{
    if (l == r) {
        if (arrc[now] != -1) {
            arr[l] = arrc[now];
        }
        arrc[now] = -1;
        return;
    }
    pushdown(now, l, r);
    query(lson, l, mid);
    query(rson, mid + 1, r);
}
void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    if (l == r) {
        printf("n:%d,c:%d,a:%d,%d-%d\n", now, arrc[now], arr[l], l, r);
    }
    else {
        printf("n:%d,c:%d,%d-%d\n", now, arrc[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    int x1, x2, c;
    while (~scanf("%d", &n)) {
        build(1, 1, SEG_LEN);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &x1, &x2, &c);
            update(1, 1, SEG_LEN, x1 + 1, x2, c);
        }
        query(1, 1, SEG_LEN);
        _DEBUG_CMD(debug_print(1, 1, SEG_LEN, 0));
        int *end = unique(arr + 1, arr + SEG_LEN + 1);
        map<int, int> m;
        for (int *s = arr + 1; s != end; ++s) {
            if (*s == -1) {
                continue;
            }
            if (m.find(*s) == m.end()) {
                m[*s] = 1;
            }
            else {
                ++m[*s];
            }
        }
        for (map<int, int>::iterator iter = m.begin(); iter != m.end(); ++iter) {
            printf("%d %d\n", iter->first, iter->second);
        }
        puts("");
    }
    return 0;
};

#endif
