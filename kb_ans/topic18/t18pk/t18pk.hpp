#ifndef _t18pk_20210812_
#define _t18pk_20210812_
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

const int MAXN = 1 << 18;
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN];
int t, n, num;
char msg[MAXN];
int msgint[MAXN];
int msgseg[MAXN];

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

void build_sa(int *S, int n)
{
    for (int i = 0; i <= n; ++i) {
        sa[i] = i;
        rank_arr[i] = i < n ? S[i] : -1;
    }
    for (int k = 1; k <= n; k *= 2) {
        Comparator cmp{n, k};
        sort(sa, sa + n + 1, cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        memcpy(rank_arr, tmp, sizeof(rank_arr));
    }
}
void build_lcp(int *S, int n, int *lcp)
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

// int posidx[1 << 4][2];
// bool check_num(int val, int nidx) {}
int mx[1 << 4], mi[1 << 4];
void reset_mxmi()
{
    memset(mx, 0xD1, sizeof(mx));
    memset(mi, 0x3F, sizeof(mi));
}
bool check(int val)
{
    reset_mxmi();
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] >= val) {
            mx[msgseg[sa[i]]] = max(mx[msgseg[sa[i]]], sa[i]);
            mi[msgseg[sa[i]]] = min(mi[msgseg[sa[i]]], sa[i]);
            mx[msgseg[sa[i - 1]]] = max(mx[msgseg[sa[i - 1]]], sa[i - 1]);
            mi[msgseg[sa[i - 1]]] = min(mi[msgseg[sa[i - 1]]], sa[i - 1]);
        }
        else {
            reset_mxmi();
            mx[msgseg[sa[i]]] = sa[i];
            mi[msgseg[sa[i]]] = sa[i];
        }
        int j = 0;
        for (j = 0; j < num; ++j) {
            if (mx[j] - mi[j] < val)
                break;
        }
        if (j == num) {
            _DEBUG_CMD(printf("check(%d) return true, str[mx]:%s\n", val, msg + mx[0]));
            return true;
        }
    }
    return false;
}

int solve(int n)
{
    int lb = 0, ub = 10001;
    int mid = (lb + ub) / 2 + 1;
    while (lb < ub) {
        if (check(mid)) {
            _DEBUG_CMD(printf("check(%d): true\n", mid););
            lb = mid;
        }
        else {
            _DEBUG_CMD(printf("check(%d): false\n", mid););
            ub = mid - 1;
        }
        mid = (lb + ub) / 2 + 1;
    }
    return lb;
}

char buf[1 << 16];
int main(int argc, char **argv)
{
    scanf("%d", &t);
    while (t--) {
        n = 0;
        scanf("%d", &num);
        for (int i = 0; i < num; ++i) {
            scanf("%s", buf);
            int slen = strlen(buf);
            memcpy(msg + n, buf, slen);
            for (int j = 0; j < slen; ++j) {
                msgint[j + n] = buf[j];
            }
            fill_n(msgseg + n, slen + 1, i);
            msg[n + slen] = 0;
            msgint[n + slen] = i + 128;
            n += slen + 1;
        }
        build_sa(msgint, n);
        build_lcp(msgint, n, lcp);
        _DEBUG_CMD({
            printf("msgseg: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", msgseg[i]);
            }
            printf("\n");
            printf("msgint: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", msgint[i]);
            }
            printf("\n");
            for (int i = 0; i <= n; ++i) {
                printf("sa[%d]:%d lcp[%d]:%d seg[%d]:%d str[]:%s\n", i, sa[i], i, lcp[i], sa[i],
                       msgseg[sa[i]], msg + sa[i]);
            }
        });
        printf("%d\n", solve(n));
    }
    return 0;
};

#endif
