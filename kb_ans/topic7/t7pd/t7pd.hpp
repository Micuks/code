#ifndef _t7pd_20200904_
#define _t7pd_20200904_
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
const int MAXN = 1e7 + 19;
const int MAXM = 1e4 + 7;
int le[MAXM], rt[MAXM];
int arr[MAXM << 2];
int postmap[MAXM << 2], pmidx;
int visited[MAXM << 2];
int arrc[MAXM << 4];
int c, n;
size_t ans;

void pushdown(int now, int l, int r)
{
    if (l == r) {
        arr[l] = arrc[now];
        arrc[now] = 0;
        return;
    }
    if (arrc[now]) {
        arrc[lson] = arrc[now];
        arrc[rson] = arrc[now];
        arrc[now] = 0;
    }
}
void popup(int now) {}

void build(int now, int l, int r)
{
    memset(arr, 0, sizeof(arr));
    memset(arrc, 0, sizeof(arrc));
}
void paint(int now, int l, int r, int start, int end, int color_idx)
{
    if ((l >= start && r <= end) || l == r) {
        arrc[now] = arr[l] = color_idx;
        popup(now);
        return;
    }
    pushdown(now, l, r);
    if (start <= mid) {
        paint(lson, l, mid, start, end, color_idx);
    }
    if (end > mid) {
        paint(rson, mid + 1, r, start, end, color_idx);
    }
}
void pa(int now, int l, int r)
{
    pushdown(now, l, r);
    if (l == r) {
        if (arr[l] != 0 && visited[arr[l]] == 0) {
            visited[arr[l]] = 1;
            _DEBUG_CMD(printf("%d is visited\n", arr[l]));
            ++ans;
        }
        return;
    }
    pa(lson, l, mid);
    pa(rson, mid + 1, r);
}
void query(int now, int l, int r, int start, int end)
{
    pa(now, l, r);
    // set<int> set(arr + start, arr + end + 1);
    // return set.size();
    // sort(arr, arr + end + 1);
    // int *dest = unique(arr + start, arr + end + 1);
    // return dest - arr - start;
}
void dfs(int now, int l, int r)
{
    if (arrc[now] != 0 || l == r) {
        if (!visited[arrc[now]]) {
            visited[arrc[now]] = 1;
            _DEBUG_CMD(printf("LINE:%d %d is visited\n", __LINE__, arrc[now]));
            ++ans;
        }
        return;
    }
    dfs(lson, l, mid);
    dfs(rson, mid + 1, r);
}

void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    printf("n:%d,c:%d %d-%d\n", now, arrc[now], l, r);
    if (l != r) {
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)

{
    scanf("%d", &c);
    while (c--) {
        scanf("%d", &n);
        memset(visited, 0, sizeof(visited));
        visited[0] = 1;
        pmidx = 0;
        ans = 0;
        build(1, 1, n);
        // int s, e;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &le[i], &rt[i]);
            postmap[pmidx++] = le[i];
            postmap[pmidx++] = rt[i];
        }
        sort(postmap, postmap + pmidx);
        _DEBUG_CMD(printf("n:%d pmidx before sort insert & unique: %d\n", n, pmidx););
        for (int i = 0; i < 2 * n; ++i) {
            if (postmap[i] < postmap[i + 1] - 1) {
                postmap[pmidx++] = postmap[i + 1] - 1;
            }
        }
        sort(postmap, postmap + pmidx);
        _DEBUG_CMD(printf("n:%d pmidx before unique: %d\n", n, pmidx););
        pmidx = unique(postmap, postmap + pmidx) - postmap;
        _DEBUG_CMD({
            printf("n:%d pmidx after unique: %d\n", n, pmidx);
            for (int i = 0; i < pmidx; ++i) {
                printf("%d ", postmap[i]);
            }
            puts("");
        });
        int max_node = pmidx;
        for (int i = 0; i < n; ++i) {
            int s = lower_bound(postmap, postmap + pmidx, le[i]) - postmap + 1;
            int e = lower_bound(postmap, postmap + pmidx, rt[i]) - postmap + 1;
            _DEBUG_CMD(printf("i:%d le:%d, rt:%d s:%d, e:%d\n", i, le[i], rt[i], s, e));
            paint(1, 1, pmidx, s, e, i + 1);
        }
        // query(1, 1, n, 1, n);
        dfs(1, 1, max_node);
        _DEBUG_CMD({
            printf("max_node:%d\n", max_node);
            debug_print(1, 1, max_node, 0);
        });
        printf("%lu\n", ans);
    }
    return 0;
};

#endif
