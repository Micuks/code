#if 0
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 50000 + 5;
int sum[4 * maxn];

// i节点收集子节点的统计结果
void PushUp(int i) { sum[i] = sum[i * 2] + sum[i * 2 + 1]; }
//递归建立线段树
void build(int i, int l, int r)
{
    if (l == r) {
        scanf("%d", &sum[i]);
        return;
    }
    int m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m + 1, r);
    PushUp(i); //收集子节点的结果
    //要时刻记住维护节点统计信息的正确性!!
}
//在当前区间[l,r]内查询区间[ql,qr]间的目标值
//且能执行这个函数的前提是：[l,r]与[ql,qr]的交集不为空
//其实本函数返回的结果也是 它们交集的目标值
int query(int ql, int qr, int i, int l, int r)
{
    if (ql <= l && r <= qr)
        return sum[i];
    int m = (l + r) / 2;
    int ans = 0;
    if (ql <= m)
        ans += query(ql, qr, i * 2, l, m);
    if (qr > m) //特别注意此处，不是else!!!!!
        ans += query(ql, qr, i * 2 + 1, m + 1, r);
    return ans;
}
// update这个函数就有点定制的意味了
//本题是单点更新，所以实在区间[l,r]内使得第id数的值+val
//如果是区间更新，可以将函数的id参数变为ql,qr
void update(int id, int val, int i, int l, int r)
{
    if (l == r) {
        sum[i] += val;
        return;
    }
    int m = (l + r) / 2;
    if (id <= m)
        update(id, val, i * 2, l, m);
    else
        update(id, val, i * 2 + 1, m + 1, r);
    PushUp(i); //要时刻记住维护节点统计信息的正确性!!
}
int main()
{
    int T, n, kase = 0;
    ;
    cin >> T;
    while (T--) {
        cin >> n;
        build(1, 1, n);
        char str[10];
        int x, y;
        printf("Case %d:\n", ++kase);
        while (cin >> str) {
            if (str[0] == 'E')
                break;
            scanf("%d%d", &x, &y);
            if (str[0] == 'A')
                update(x, y, 1, 1, n);
            else if (str[0] == 'Q')
                printf("%d\n", query(x, y, 1, 1, n));
            else if (str[0] == 'S')
                update(x, -y, 1, 1, n);
        }
    }
    return 0;
}

#else
#ifndef _t7pa_20200829_
#define _t7pa_20200829_
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
int arrsum[MAXN << 2];
int arr[MAXN];
int T, N;
int build(int node, int l, int r)
{
    if (l == r) {
        return arrsum[node] = arr[l];
    }
    int mid = (l + r) / 2;
    int lson = node << 1;
    int rson = (node << 1) | 1;
    return arrsum[node] = build(lson, l, mid) + build(rson, mid + 1, r);
}
int update(int node, int l, int r, const int &newval, const int &newvalidx)
{
    if (l == r) {
        return arrsum[node] = arr[l] = newval;
    }
    int mid = (l + r) / 2;
    int lson = node << 1;
    int rson = (node << 1) | 1;
    if (newvalidx <= mid) {
        return arrsum[node] = arrsum[node] - arrsum[lson] + update(lson, l, mid, newval, newvalidx);
    }
    else {
        return arrsum[node] =
                   arrsum[node] - arrsum[rson] + update(rson, mid + 1, r, newval, newvalidx);
    }
}
int query(int beg, int end, int node, int l, int r)
{
    if (beg <= l && end >= r) {
        return arrsum[node];
    }
    int mid = (l + r) / 2;
    int lson = node << 1;
    int rson = (node << 1) | 1;
    int res = 0;
    if (beg <= mid) {
        res += query(beg, end, lson, l, mid);
    }
    if (end > mid) {
        res += query(beg, end, rson, mid + 1, r);
    }
    return res;
}
int debug_print(int node, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    printf("n:%d,val:%d:%d-%d\n", node, arrsum[node], l, r);
    if (l != r) {
        int mid = (l + r) / 2;
        int lson = node << 1;
        int rson = (node << 1) | 1;
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &arr[i]);
        }
        build(1, 1, N);
        _DEBUG_CMD({
            printf("arr:\n");
            for (int i = 1; i <= N; ++i) {
                printf("%d ", arr[i]);
            }
            printf("\n");
            printf("tree:\n");
            // debug_print(1, 1, N, 0);
        });
        printf("Case %d:\n", ++case_cnt);
        int idx, val;
        string cmd;
        while (cin >> cmd && cmd != "End") {
            cin >> idx >> val;
            if (cmd == "Add") {
                update(1, 1, N, arr[idx] + val, idx);
            }
            else if (cmd == "Sub") {
                update(1, 1, N, arr[idx] - val, idx);
            }
            else {
                _DEBUG_CMD({
                    printf("query from %d to %d\n", idx, val);
                    debug_print(1, 1, N, 0);
                });
                printf("%d\n", query(idx, val, 1, 1, N));
            }
        }
    }
    return 0;
};

#endif
#endif
