#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define lch rt * 2, l, m
#define rch rt * 2 + 1, m + 1, r
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
ll tree[maxn * 4];
int mark[maxn * 4];
void pushup(int rt)
{
    tree[rt] = tree[rt * 2] + tree[rt * 2 + 1]; //向上更新， 是 =， 根节点就等于左右子树想加。。。
    mark[rt] = mark[rt * 2] && mark[rt * 2 + 1];
}
void built(int rt, int l, int r)
{
    mark[rt] = 0;
    if (l == r) {
        scanf("%lld", &tree[rt]);
        return;
    }
    int m = (l + r) / 2;
    built(lch);
    built(rch);
    pushup(rt);
}
void update(int rt, int l, int r, int i, int j)
{
    if (l == r) {
        tree[rt] = sqrt(tree[rt]);
        if (tree[rt] <= 1)
            mark[rt] = 1; //小于<=1就没必要更新了
        return;
    }
    int m = (l + r) / 2;
    if (i <= m && !mark[rt])
        update(lch, i, j); //如果没被标记更新，标记了就不必更新了， mark标记用在这里的。。。
    if (j > m && !mark[rt])
        update(rch, i, j);
    pushup(rt);
}
ll query(int rt, int l, int r, int i, int j)
{
    if (l >= i && r <= j) {
        return tree[rt];
    }
    int m = (l + r) / 2;
    ll ans = 0;
    if (i <= m)
        ans += query(lch, i, j); //查询的时候 肯定每个都要查询。。
    if (j > m)
        ans += query(rch, i, j);
    return ans;
}
int main()
{
    int n, k = 1;
    while (~scanf("%d", &n)) {
        built(1, 1, n);
        int m;
        scanf("%d", &m);
        int flag = 1;
        while (m--) {
            int t, x, y;
            scanf("%d%d%d", &t, &x, &y);
            if (x > y)
                swap(x, y); //没说哪个大哪个小
            if (t == 0) {
                update(1, 1, n, x, y);
            }
            else {
                if (flag == 1) {
                    printf("Case #%d:\n", k);
                    flag = 0;
                }
                printf("%lld\n", query(1, 1, n, x, y));
            }
        }
        k++;
        puts("");
    }
    return 0;
}

#else
#ifndef _t7ph_20200924_
#define _t7ph_20200924_
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

const int MAXN = 1e5 + 3;
int N, M;
long long arr[MAXN];
long long arrsum[MAXN << 2];
const int MAXSQRT = 8;
long long sqrtsum[MAXN << 2][MAXSQRT];
int shit[MAXN << 2];
int lazy_eval[MAXN << 2];
int eval_hit[MAXN << 2];

#define OFFSET(x) ((x) < MAXSQRT ? (x) : MAXSQRT - 1)
void pushdown(int now, int l, int r)
{
    if (l == r) {
        shit[now] += lazy_eval[now];
        lazy_eval[now] = 0;
        arrsum[now] = sqrtsum[now][OFFSET(shit[now])];
        if (arrsum[now] <= 1) {
            eval_hit[now] = 1;
        }
        return;
    }
    lazy_eval[lson] += lazy_eval[now];
    lazy_eval[rson] += lazy_eval[now];
    lazy_eval[now] = 0;
    /*
    if (rson < (N << 2) && lson < (N << 2)) {
        // int offset = shit[now] < MAXSQRT ? shit[now] : MAXSQRT - 1;
        lazy_eval[lson] += lazy_eval[now];
        lazy_eval[rson] += lazy_eval[now];
        lazy_eval[now] = 0;
        // shit[lson] = max(shit[lson], shit[now]);
        // shit[rson] = max(shit[rson], shit[now]);

        arrsum[lson] = sqrtsum[lson][OFFSET(shit[lson] + lazy_eval[lson])];
        arrsum[rson] = sqrtsum[rson][OFFSET(shit[rson] + lazy_eval[rson])];

        arrsum[now] = arrsum[lson] + arrsum[rson];
        return;
    }
    if (lson < (N << 2)) {
        lazy_eval[lson] += lazy_eval[now];
        lazy_eval[now] = 0;
        // shit[lson] = max(shit[lson], shit[now]);
        arrsum[lson] = sqrtsum[lson][OFFSET(shit[lson] + lazy_eval[lson])];
        arrsum[now] = arrsum[lson];
        return;
    }
    */
}
void popup(int now)
{
    if (now == 0) {
        return;
    }
    int father = (now >> 1);
    int other_son = (now ^ 0x01);
    /*
    if (arrsum[father] != arrsum[now] + arrsum[other_son]) {
        arrsum[father] = arrsum[now] + arrsum[other_son];
        for (int i = 0; i < MAXSQRT; ++i) {
            sqrtsum[father][i] = sqrtsum[now][i] + sqrtsum[other_son][i];
        }
        popup(father);
    }
    */
    eval_hit[father] = eval_hit[now] & eval_hit[other_son];
    arrsum[father] = arrsum[now] + arrsum[other_son];
}

void build(int now, int l, int r)
{
    if (l == r) {
        sqrtsum[now][0] = arrsum[now] = arr[l];
        for (int i = 1; i < MAXSQRT; ++i) {
            sqrtsum[now][i] = static_cast<long long>(sqrt(sqrtsum[now][i - 1]));
        }
        popup(now);
        return;
    }

    build(lson, l, mid);
    build(rson, mid + 1, r);
    popup(now);
    return;
}
void update(int now, int l, int r, int beg, int end, int le_hit = 1)
{
    pushdown(now, l, r);
    if (l == r) {
        if (le_hit) {
            ++lazy_eval[now];
            le_hit = 0;
        }
        shit[now] += lazy_eval[now];
        lazy_eval[now] = 0;
        arrsum[now] = sqrtsum[now][OFFSET(shit[now])];
        if (arrsum[now] <= 1) {
            eval_hit[now] = 1;
        }
        popup(now);
        return;
    }
    if (l >= beg && r <= end) {
        if (le_hit) {
            ++lazy_eval[now];
            pushdown(now, l, r);
            le_hit = 0;
            // int offset = shit[now] < MAXSQRT ? shit[now] : MAXSQRT - 1;
            // arrsum[now] = sqrtsum[lson][OFFSET(shit[lson])] + sqrtsum[rson][OFFSET(shit[rson])];
            // arrsum[now] = sqrtsum[now][OFFSET(shit[now] + lazy_eval[now])];
            popup(now);
        }
        if (eval_hit[now]) {
            return;
        }
    }
    // assert(l != r);
    if (beg <= mid && eval_hit[lson] == 0) {
        update(lson, l, mid, beg, end, le_hit);
    }
    if (end > mid && eval_hit[rson] == 0) {
        update(rson, mid + 1, r, beg, end, le_hit);
    }
    popup(now);
}
long long query(int now, int l, int r, int beg, int end)
{
    pushdown(now, l, r);
    if (l >= beg && r <= end) {
        return arrsum[now];
    }
    long long ret = 0;
    if (beg <= mid) {
        ret += query(lson, l, mid, beg, end);
    }
    if (end > mid) {
        ret += query(rson, mid + 1, r, beg, end);
    }
    return ret;
}
void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("\t");
    }
    if (l == r) {
        printf("n:%d,as:%lld,hs:%d,le:%d,ss:%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,bt%d-%d\n", now,
               arrsum[now], shit[now], lazy_eval[now], sqrtsum[now][0], sqrtsum[now][1],
               sqrtsum[now][2], sqrtsum[now][3], sqrtsum[now][4], sqrtsum[now][5], sqrtsum[now][6],
               sqrtsum[now][7], l, r);
    }
    else {
        printf("n:%d,as:%lld,hs:%d,le:%d,ss:%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,bt%d-%d\n", now,
               arrsum[now], shit[now], lazy_eval[now], sqrtsum[now][0], sqrtsum[now][1],
               sqrtsum[now][2], sqrtsum[now][3], sqrtsum[now][4], sqrtsum[now][5], sqrtsum[now][6],
               sqrtsum[now][7], l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    int act_type, x, y;
    while (~scanf("%d", &N)) {
        for (int i = 1; i <= N; ++i) {
            scanf("%lld", &arr[i]);
        }
        memset(shit, 0, sizeof(shit));
        memset(lazy_eval, 0, sizeof(lazy_eval));
        memset(eval_hit, 0, sizeof(eval_hit));
        build(1, 1, N);
        scanf("%d", &M);
        printf("Case #%d:\n", ++case_cnt);
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &act_type, &x, &y);
            if (x > y) {
                swap(x, y);
            }
            if (act_type == 0) {
                update(1, 1, N, x, y);
                _DEBUG_CMD({
                    printf("after update on between %d %d\n", x, y);
                    debug_print(1, 1, N, 0);
                });
            }
            else {
                printf("%lld\n", query(1, 1, N, x, y));
                _DEBUG_CMD({
                    printf("after query on between %d %d\n", x, y);
                    debug_print(1, 1, N, 0);
                });
            }
        }
        puts("");
    }
    return 0;
};

#endif
#endif
