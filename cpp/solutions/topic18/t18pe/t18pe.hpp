#ifndef _t18pe_20210726_
#define _t18pe_20210726_
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

const int MAXN = 1 << 20;
char str[MAXN];
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN];
struct Comparator {
    int n, k;
    bool operator()(int i, int j) const
    {
        if (rank_arr[i] != rank_arr[j]) {
            return rank_arr[i] < rank_arr[j];
        }
        else {
            int ri = i + k <= n ? rank_arr[i + k] : -1;
            int rj = j + k <= n ? rank_arr[j + k] : -1;
            return ri < rj;
        }
    }
};
void build_sa(char *S, int n)
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
void build_lcp(char *S, int n, int *lcp)
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
        lcp[rank_arr[i] - 1] = h;
    }
}

bool query_repeating_part(int k)
{
    int n = strlen(str);
    if (n % k) {
        return false;
    }
    if (rank_arr[0] != rank_arr[k] + 1) {
        return false;
    }
    return true;
}

int nxt[MAXN];

void kmp_build(char *s)
{
    int i = 0, j = -1;
    int len = strlen(s);
    nxt[0] = -1;
    while (i < len) {
        while (j != -1 && s[i] != s[j])
            j = nxt[j];
        if (str[++i] == str[++j])
            nxt[i] = nxt[j];
        else
            nxt[i] = j;
    }
}

int main(int argc, char **argv)
{
    while (~scanf("%s", str) && strcmp(str, ".") != 0) {
        int n = strlen(str);
        // build_sa(str, n);
        // build_lcp(str, n, lcp);
        kmp_build(str);
        int res = 1;
        if (n % (n - nxt[n]) == 0) {
            res = n / (n - nxt[n]);
        }
        printf("%d\n", res);
    }
    return 0;
};

#endif
