#if 0
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
const int INF = 0x3f3f3f3f;
typedef long long LL;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;
using namespace std;

struct SegTree_node {
    int l;
    int r;
    int num; //区间内空瓶的数量
    int tag; //如果为-1则为初始状态,不用向下更新，如果为0意思将子区间内的花清空，为1为插满花
} SegTree[50005 << 2];

int n, m;

void PushUp(int rt) //向上传递区间信息
{
    SegTree[rt].num = SegTree[rt << 1].num + SegTree[rt << 1 | 1].num;
}

void PushDown(int rt) //向下传递状态
{
    if (SegTree[rt].tag != -1) {
        SegTree[rt << 1].tag = SegTree[rt << 1 | 1].tag = SegTree[rt].tag;
        int mid = (SegTree[rt].l + SegTree[rt].r) >> 1;
        SegTree[rt << 1].num = (mid - SegTree[rt].l + 1) * SegTree[rt].tag;
        SegTree[rt << 1 | 1].num = (SegTree[rt].r - mid) * SegTree[rt].tag;
        SegTree[rt].tag = -1;
    }
}

void Build(int l, int r, int rt)
{
    SegTree[rt].l = l;
    SegTree[rt].r = r;
    SegTree[rt].num = r - l + 1;
    SegTree[rt].tag = -1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    Build(l, mid, rt << 1);
    Build(mid + 1, r, rt << 1 | 1);
}

void Update(int L, int R, int f, int rt)
{
    int l = SegTree[rt].l;
    int r = SegTree[rt].r;
    if (L <= l && R >= r) {
        SegTree[rt].num = (r - l + 1) * f; //先计算
        SegTree[rt].tag = f;               //标记当前区间
        return;
    }
    if (l == r) //不要忘记
        return;
    PushDown(rt); //向下传递状态
    int mid = (l + r) >> 1;
    if (L <= mid)
        Update(L, R, f, rt << 1);
    if (R > mid)
        Update(L, R, f, rt << 1 | 1);
    PushUp(rt);
}

int Query(int L, int R, int rt) //得到区间[L,R]中的空花瓶数
{
    int l = SegTree[rt].l;
    int r = SegTree[rt].r;
    if (R < l || L > r)
        return 0;
    if (L <= l && R >= r)
        return SegTree[rt].num;
    PushDown(rt);
    int mid = (l + r) >> 1;
    int sum = 0;
    if (L <= mid)
        sum += Query(L, R, rt << 1);
    if (R > mid)
        sum += Query(L, R, rt << 1 | 1);
    return sum;
}

int dive(int x, int num) //二分查找，第一个为开始的位置，第二个参数为要插花的个数
{
    int l = x;
    int r = n;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (Query(x, mid, 1) >= num) {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        Build(1, n, 1);
        for (int i = 1; i <= m; i++) {
            int op;
            scanf("%d", &op);
            if (op == 1) {
                int A, F;
                scanf("%d %d", &A, &F);
                A++; //存储时序号从一开始，故序号要全加一，下同
                int cnt = Query(A, n, 1); //得到区间[A, n]中的空花瓶数
                if (cnt == 0)
                    printf("Can not put any one.\n");
                else {
                    int L = dive(A, 1);           //二分左端点(第1个能插花的位置)
                    int R = dive(A, min(cnt, F)); //二分右端点(最后一个能插花的位置)
                    Update(L, R, 0, 1);           //将区间[L,R]的花瓶全部插满
                    printf("%d %d\n", L - 1, R - 1);
                }
            }
            else if (op == 2) {
                int A, B;
                scanf("%d %d", &A, &B);
                A++;
                B++;
                printf("%d\n", B - A + 1 - Query(A, B, 1));
                Update(A, B, 1, 1); //将区间[A,B]的花瓶全部清空
            }
        }
        printf("\n");
    }
    return 0;
}
#else
#ifndef _t7pl_20201030_
#define _t7pl_20201030_
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

const int MAXN = 5e4 + 3;
int arrblank[MAXN << 2];
int lazy_eval[MAXN << 2];
int T, N, M, K;

#define mid ((l + r) / 2)
#define lson (now << 1)
#define rson ((now << 1) | 1)

void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,ab:%d,le:%d,%d-%d\n", now, arrblank[now], lazy_eval[now], l, r);
    }
    else {
        printf("n:%d,ab:%d,le:%d,%d-%d\n", now, arrblank[now], lazy_eval[now], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}
void popup(int now)
{
    int ls = (now | 0x01);
    int rs = (ls ^ 0x01);
    int father = (now >> 1);
    if (father != 0) {
        arrblank[father] = arrblank[ls] + arrblank[rs];
    }
}
void pushdown(int now, int l, int r)
{
    if (l == r) {
        if (lazy_eval[now] != -1) {
            arrblank[now] = lazy_eval[now];
            lazy_eval[now] = -1;
        }
        return;
    }
    if (lazy_eval[now] != -1) {
        // update sons lazy evaluation flag and arr too.
        lazy_eval[lson] = lazy_eval[now];
        lazy_eval[rson] = lazy_eval[now];
        arrblank[lson] = lazy_eval[lson] == 0 ? 0 : mid - l + 1;
        arrblank[rson] = lazy_eval[rson] == 0 ? 0 : r - mid;
        lazy_eval[now] = -1;
    }
}
void build(int now, int l, int r)
{
    if (l == r) {
        arrblank[now] = 1;
        lazy_eval[now] = -1;
        popup(now);
        return;
    }
    build(lson, l, mid);
    build(rson, mid + 1, r);
    popup(now);
}
int query(int now, int l, int r, int s, int e)
{
    pushdown(now, l, r);
    if (l >= s && r <= e) {
        return arrblank[now];
    }
    int ret = 0;
    if (mid >= s) {
        ret += query(lson, l, mid, s, e);
    }
    if (mid < e) {
        ret += query(rson, mid + 1, r, s, e);
    }
    return ret;
}
void put(int now, int l, int r, int s, int e)
{
    pushdown(now, l, r);
    if (l >= s && r <= e) {
        lazy_eval[now] = 0;
        arrblank[now] = 0;
        popup(now);
        return;
    }
    if (mid >= s) {
        put(lson, l, mid, s, e);
    }
    if (mid < e) {
        put(rson, mid + 1, r, s, e);
    }
    popup(now);
}
int find_left_margin(int start, int blank_cnt)
{
    int beg = start;
    int count = N - start + 2;
    while (count > 0) {
        int step = count / 2;
        if (query(1, 1, N, start, beg + step) < blank_cnt) {
            beg = beg + step + 1;
            count = count - step - 1;
        }
        else {
            count = step;
        }
    }
    return beg;
}
pair<int, int> find_insert_position(int start, int blank_cnt)
{
    int beg = find_left_margin(start, 1);
    int rem = query(1, 1, N, start, N);
    _DEBUG_CMD({
        printf("query(1, 1, N, start, N):\n");
        debug_print(1, 1, N, 0);
    });
    int end = find_left_margin(start, min(rem, blank_cnt));
    _DEBUG_CMD({
        printf("in find_insert_position, start:%d, min(rem:%d, blank_cnt:%d):%d beg:%d, end:%d\n",
               start, rem, blank_cnt, end, beg, end);
    });
    return pair<int, int>(beg, end);
}
void dump(int now, int l, int r, int s, int e)
{
    pushdown(now, l, r);
    if (l >= s && r <= e) {
        lazy_eval[now] = 1;
        arrblank[now] = r - l + 1;
        popup(now);
        return;
    }
    if (mid >= s) {
        dump(lson, l, mid, s, e);
    }
    if (mid < e) {
        dump(rson, mid + 1, r, s, e);
    }
    popup(now);
}
pair<int, int> insert(int start, int cnt)
{
    pair<int, int> pos = find_insert_position(start, cnt);
    if (pos.first != N + 1) {
        put(1, 1, N, pos.first, pos.second);
        _DEBUG_CMD({
            printf("after insert %d %d:\n", pos.first, pos.second);
            debug_print(1, 1, N, 0);
        });
    }
    return pos;
}

int main(int argc, char **argv)
{
    int K, s, e;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        memset(arrblank, 0, sizeof(arrblank));
        memset(lazy_eval, -1, sizeof(lazy_eval));
        build(1, 1, N);
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &K, &s, &e);
            if (K == 1) {
                pair<int, int> res = insert(s + 1, e);
                if (res.first > res.second) {
                    printf("Can not put any one.\n");
                }
                else {
                    printf("%d %d\n", res.first - 1, res.second - 1);
                }
                // DEBUG_CMD({ debug_print(1, 1, N, 0); });
            }
            else if (K == 2) {
                int res = query(1, 1, N, s + 1, e + 1);
                printf("%d\n", e - s + 1 - res);
                _DEBUG_CMD({
                    printf("before dumping %d %d:\n", s + 1, e + 1);
                    debug_print(1, 1, N, 0);
                });
                dump(1, 1, N, s + 1, e + 1);
                _DEBUG_CMD({
                    printf("after dumping %d %d:\n", s + 1, e + 1);
                    debug_print(1, 1, N, 0);
                });
            }
            else {
                printf("err k: %d\n", K);
                abort();
            }
        }
        puts("");
    }
    return 0;
};

#endif
#endif
