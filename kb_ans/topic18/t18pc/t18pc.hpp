#ifndef _t18pc_20210726_
#define _t18pc_20210726_
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

const int MAXN = 1 << 10;
char str[MAXN];
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN];
int T;

struct Comparator {
    int k, n;
    bool operator()(const int &i, const int &j) const
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
        Comparator cmp{k, n};
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
            if (S[j + h] != S[i + h])
                break;
        }
        lcp[rank_arr[i] - 1] = h;
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        memset(rank_arr, 0, sizeof(rank_arr));
        scanf("%s", str);
        int n = strlen(str);
        build_sa(str, n);
        build_lcp(str, n, lcp);
        int res = (n + 1) * n / 2;
        for (int i = 0; i < n; ++i) {
            res = res - lcp[i];
        }
        _DEBUG_CMD({
            printf("lcp: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", lcp[i]);
            }
            printf("\n");
        });
        printf("%d\n", res);
    }
    return 0;
};

#endif
