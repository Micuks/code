#ifndef _t18ph_20210802_
#define _t18ph_20210802_
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
// const int MAXN = 50001;
char str[MAXN];
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN];
int minnum[MAXN][18];
int n1, n2;
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
        lcp[rank_arr[i]] = h;
    }
}

void build_rmq(int n)
{
    memset(minnum, 0, sizeof(minnum));
    int m = (int) (log(n * 1.0) / log(2.0));
    for (int i = 1; i <= n; ++i) {
        minnum[i][0] = lcp[i];
    }
    for (int j = 1; j <= m; ++j) {
        int stride = (1 << j);
        int half_s = (1 << (j - 1));
        for (int i = 1; i + stride - 1 <= n; ++i) {
            minnum[i][j] = min(minnum[i][j - 1], minnum[i + half_s][j - 1]);
        }
    }
}
int min_between(int a, int b)
{
    int k = int(log(b - a + 1.0) / log(2.0));
    return min(minnum[a][k], minnum[b - (1 << k) + 1][k]);
}
int calc_prefix(int a, int b)
{
    int ra = rank_arr[a], rb = rank_arr[b];
    if (ra > rb) {
        swap(ra, rb);
    }
    int min_lcp = min_between(ra + 1, rb);
    _DEBUG_CMD(printf("a:%d b:%d ra:%d, rb:%d, min_lcp:%d, sa:%s sb:%s\n", a, b, ra, rb, min_lcp,
                      str + ra, str + rb););
    return min_lcp;
}

int main(int argc, char **argv)
{
    scanf("%s", str);
    n1 = strlen(str);
    str[n1] = '#';
    scanf("%s", str + n1 + 1);
    n2 = strlen(str);
    _DEBUG_CMD(printf("%s\n", str));
    build_sa(str, n2);
    build_lcp(str, n2, lcp);
    int max_cnt = 0;
    for (int i = 1; i <= n2; ++i) {
        int aidx = sa[i];
        int bidx = sa[i - 1];
        if (lcp[i] > max_cnt && ((aidx < n1) ^ (bidx < n1))) {
            max_cnt = lcp[i];
        }
    }
    _DEBUG_CMD({
        printf("lcp: ");
        for (int i = 0; i <= n2; ++i) {
            printf("%d ", lcp[i]);
        }
        printf("\n");
    });
    printf("%d\n", max_cnt);
    return 0;
};

#endif
