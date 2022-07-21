#ifndef _t18pl_20210813_
#define _t18pl_20210813_
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

const int MAXN = 1 << 16;
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN], belong[MAXN];
int msg[MAXN];
int t, n, num;
struct Comparator {
    int n, k;
    bool operator()(int i, int j) const
    {
        if (rank_arr[i] != rank_arr[j]) {
            return rank_arr[i] < rank_arr[j];
        }
        int ri = i + k <= n ? rank_arr[i + k] : -1;
        int rj = j + k <= n ? rank_arr[j + k] : -1;
        return ri < rj;
    }
};

void build_sa(const int *S, int n)
{
    for (int i = 0; i <= n; ++i) {
        sa[i] = i;
        rank_arr[i] = i < n ? S[i] : -1;
    }
    for (int k = 1; k <= n; k *= 2) {
        Comparator cmp{n, k};
        sort(sa, sa + n + 1, cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        memcpy(rank_arr, tmp, sizeof(rank_arr));
    }
}
void build_lcp(const int *S, int n, int *lcp)
{
    for (int i = 0; i <= n; ++i) {
        rank_arr[sa[i]] = i;
    }
    int h = 0;
    lcp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int j = sa[rank_arr[i] - 1];
        if (h > 0)
            --h;
        for (; j + h < n && i + h < n; ++h) {
            if (S[i + h] != S[j + h])
                break;
        }
        lcp[rank_arr[i]] = h;
    }
}

bool check(int k)
{
    int valid[1 << 8], cnt = 0;
    memset(valid, -1, sizeof(valid));
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] < k) {
            memset(valid, -1, sizeof(valid));
            cnt = 0;
        }
        else {
            if (valid[belong[sa[i]]] == -1) {
                ++cnt;
                valid[belong[sa[i]]] = 1;
            }
            if (valid[belong[sa[i - 1]]] == -1) {
                ++cnt;
                valid[belong[sa[i - 1]]] = 1;
            }
            if (cnt == num) {
                return true;
            }
        }
    }
    return false;
}

int solve()
{
    int lb = 0, ub = 1 << 8;
    int mid = (ub + lb) / 2 + 1;
    while (lb < ub) {
        if (check(mid)) {
            lb = mid;
        }
        else {
            ub = mid - 1;
        }
        mid = (ub + lb) / 2 + 1;
    }
    return lb;
}

int main(int argc, char **argv)
{
    char buf[1 << 8];
    scanf("%d", &t);
    while (t--) {
        n = 0;
        scanf("%d", &num);
        for (int i = 0; i < num; ++i) {
            scanf("%s", buf);
            int slen = strlen(buf);
            for (int j = 0; j < slen; ++j) {
                msg[j + n] = buf[j];
            }
            msg[slen + n] = '$' + 256 + i;
            for (int j = 0; j < slen; ++j) {
                msg[j + slen + n + 1] = buf[slen - j - 1];
            }
            msg[2 * slen + n + 1] = 128 + i;
            fill_n(belong + n, 2 * (slen + 1), i);
            n += 2 * (slen + 1);
        }
        build_sa(msg, n);
        build_lcp(msg, n, lcp);
        int ret = solve();
        printf("%d\n", ret);
    }
    return 0;
};

#endif
