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

#define OFFSET(x) ((x) < MAXSQRT ? (x) : MAXSQRT - 1)
void pushdown(int now, int l, int r)
{
    if (l == r) {
        arrsum[now] = sqrtsum[now][OFFSET(shit[now])];
        return;
    }
    if (rson < (N << 2) && lson < (N << 2)) {
        // int offset = shit[now] < MAXSQRT ? shit[now] : MAXSQRT - 1;
        shit[lson] = max(shit[lson], shit[now]);
        shit[rson] = max(shit[rson], shit[now]);

        arrsum[lson] = sqrtsum[lson][OFFSET(shit[lson])];
        arrsum[rson] = sqrtsum[rson][OFFSET(shit[rson])];

        arrsum[now] = arrsum[lson] + arrsum[rson];
        return;
    }
    if (lson < (N << 2)) {
        shit[lson] = max(shit[lson], shit[now]);
        arrsum[lson] = sqrtsum[lson][OFFSET(shit[lson])];
        arrsum[now] = arrsum[lson];
        return;
    }
}
void popup(int now)
{
    if (now == 0) {
        return;
    }
    int father = (now >> 1);
    int other_son = (now ^ 0x01);
    if (arrsum[father] != arrsum[now] + arrsum[other_son]) {
        arrsum[father] = arrsum[now] + arrsum[other_son];
        for (int i = 0; i < MAXSQRT; ++i) {
            sqrtsum[father][i] = sqrtsum[now][i] + sqrtsum[other_son][i];
        }
        popup(father);
    }
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
    return;
}
void update(int now, int l, int r, int beg, int end)
{
    pushdown(now, l, r);
    if (l == r) {
        ++shit[now];
        arrsum[now] = sqrtsum[now][OFFSET(shit[now])];
        popup(now);
        return;
    }
    if (l >= beg && r <= end) {
        ++shit[now];
        // int offset = shit[now] < MAXSQRT ? shit[now] : MAXSQRT - 1;
        // arrsum[now] = sqrtsum[lson][OFFSET(shit[lson])] + sqrtsum[rson][OFFSET(shit[rson])];
        arrsum[now] = sqrtsum[now][OFFSET(shit[now])];
        popup(now);
        return;
    }
    assert(l != r);
    if (beg <= mid) {
        update(lson, l, mid, beg, end);
    }
    if (end > mid) {
        update(rson, mid + 1, r, beg, end);
    }
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
        printf("n:%d,as:%lld,hs:%d,ss:%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,bt%d-%d\n", now,
               arrsum[now], shit[now], sqrtsum[now][0], sqrtsum[now][1], sqrtsum[now][2],
               sqrtsum[now][3], sqrtsum[now][4], sqrtsum[now][5], sqrtsum[now][6], sqrtsum[now][7],
               l, r);
    }
    else {
        printf("n:%d,as:%lld,hs:%d,ss:%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,bt%d-%d\n", now,
               arrsum[now], shit[now], sqrtsum[now][0], sqrtsum[now][1], sqrtsum[now][2],
               sqrtsum[now][3], sqrtsum[now][4], sqrtsum[now][5], sqrtsum[now][6], sqrtsum[now][7],
               l, r);
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
        build(1, 1, N);
        scanf("%d", &M);
        printf("Case #%d:\n", ++case_cnt);
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &act_type, &x, &y);
            if (act_type == 0) {
                update(1, 1, N, x, y);
                DEBUG_CMD({
                    printf("after update on between %d %d\n", x, y);
                    debug_print(1, 1, N, 0);
                });
            }
            else {
                printf("%lld\n", query(1, 1, N, x, y));
                DEBUG_CMD({
                    printf("after query on between %d %d\n", x, y);
                    debug_print(1, 1, N, 0);
                });
            }
        }
        puts("");
    }
    return 0;
};
