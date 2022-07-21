#ifndef _t7pb_20200830_
#define _t7pb_20200830_
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

const int MAXN = 2e5 + 3;
int arr[MAXN];
int arrmax[MAXN << 2];
int N, M;

int build(int now, int l, int r)
{
    if (l == r) {
        return arrmax[now] = arr[l];
    }
    int mid = (l + r) / 2;
    int lson = now << 1;
    int rson = (now << 1) | 1;
    return arrmax[now] = max(build(lson, l, mid), build(rson, mid + 1, r));
}
void popup(int now)
{
    int father = now >> 1;
    int other_son = (now ^ 0x1);
    assert(other_son != now);
    assert(other_son / 2 == now / 2);
    assert((other_son & now) == (father << 1));
    int newfv = max(arrmax[now], arrmax[other_son]);
    if (newfv != arrmax[father]) {
        arrmax[father] = newfv;
        popup(father);
    }
}

void update(int now, int l, int r, const int &idx, const int &val)
{
    if (l == r) {
        arrmax[now] = arr[l] = val;
        popup(now);
        return;
    }
    int mid = (l + r) / 2;
    int lson = now << 1;
    int rson = (now << 1) | 1;
    if (idx <= mid) {
        update(lson, l, mid, idx, val);
    }
    else {
        update(rson, mid + 1, r, idx, val);
    }
}
int query(int now, int l, int r, int beg, int end)
{
    if (beg <= l && end >= r) {
        return arrmax[now];
    }
    int mid = (l + r) / 2;
    int lson = now << 1;
    int rson = (now << 1) | 1;
    int res = -1;
    if (beg <= mid) {
        res = max(res, query(lson, l, mid, beg, end));
    }
    if (end > mid) {
        res = max(res, query(rson, mid + 1, r, beg, end));
    }
    return res;
}
int debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    printf("n:%d,v:%d,%d-%d\n", now, arrmax[now], l, r);
    if (l != r) {
        int mid = (l + r) / 2;
        int lson = now << 1;
        int rson = (now << 1) | 1;
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    char op[1 << 4];
    int val1, val2;
    while (~scanf("%d%d", &N, &M)) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &arr[i]);
        }
        _DEBUG_CMD({
            printf("arr[]:\n");
            for (int i = 1; i <= N; ++i) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        });
        build(1, 1, N);
        for (int i = 0; i < M; ++i) {
            scanf("%s%d%d", op, &val1, &val2);
            if (op[0] == 'Q') {
                _DEBUG_CMD(debug_print(1, 1, N, 0););
                printf("%d\n", query(1, 1, N, val1, val2));
            }
            else {
                update(1, 1, N, val1, val2);
            }
        }
    }
    return 0;
};

#endif
