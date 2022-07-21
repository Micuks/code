#ifndef _t7pg_20200917_
#define _t7pg_20200917_
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

const int MAXN = 5e4 + 21;
int arr[MAXN];
int arrmax[MAXN << 2];
int arrmin[MAXN << 2];
int n, q;
int s, e;
#define mid ((l + r) / 2)
#define lson (now << 1)
#define rson ((now << 1) | 1)

void popup(int now, int pop_flag = 3)
{
    int father = now / 2;
    if (father == 0) {
        return;
    }
    int other_son = (now ^ 0x01);
    int pf = 0;
    if ((pop_flag & 0x01) && arrmax[father] < max(arrmax[now], arrmax[other_son])) {
        arrmax[father] = max(arrmax[now], arrmax[other_son]);
        pf |= 0x01;
    }
    if ((pop_flag & 0x02) && arrmin[father] > min(arrmin[now], arrmin[other_son])) {
        arrmin[father] = min(arrmin[now], arrmin[other_son]);
        pf |= 0x02;
    }
    if (pf != 0) {
        popup(father, pf);
    }
}

void build(int now, int l, int r)
{
    if (l == r) {
        arrmax[now] = arrmin[now] = arr[l];
        popup(now);
        return;
    }
    build(lson, l, mid);
    build(rson, mid + 1, r);
}
void update(int now, int l, int r) {}
int query_max(int now, int l, int r, int s, int e)
{
    if (l >= s && r <= e) {
        return arrmax[now];
    }
    assert(l != r);
    int mret = -1;
    if (s <= mid) {
        mret = max(mret, query_max(lson, l, mid, s, e));
    }
    if (e > mid) {
        mret = max(mret, query_max(rson, mid + 1, r, s, e));
    }
    return mret;
}
int query_min(int now, int l, int r, int s, int e)
{
    if (l >= s && r <= e) {
        return arrmin[now];
    }
    int mret = 0x3F3F3F3F;
    if (s <= mid) {
        mret = min(mret, query_min(lson, l, mid, s, e));
    }
    if (e > mid) {
        mret = min(mret, query_min(rson, mid + 1, r, s, e));
    }
    return mret;
}
void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    if (l == r) {
        printf("n:%d,max:%d,min:%d,%d-%d\n", now, arrmax[now], arrmin[now], l, r);
    }
    else {
        printf("n:%d,max:%d,min:%d,%d-%d\n", now, arrmax[now], arrmin[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    memset(arrmin, 0x3F, sizeof(arrmin));
    build(1, 1, n);
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &s, &e);
        _DEBUG_CMD({
            printf("s:%d,e:%d\n", s, e);
            debug_print(1, 1, n, 0);
        });
        printf("%d\n", query_max(1, 1, n, s, e) - query_min(1, 1, n, s, e));
    }
    return 0;
};

#endif
