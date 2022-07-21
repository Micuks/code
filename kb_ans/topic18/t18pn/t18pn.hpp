#ifndef _t18pn_20210815_
#define _t18pn_20210815_
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
//#define DEBUG
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

const int MAXN = 200000 * 2 + 3;
int sa[MAXN], rank_arr[MAXN], lcp[MAXN], tmp[MAXN];
int s1[MAXN], s2[MAXN], s3[MAXN], s4[MAXN];
int n, num;
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
        for (int i = 1; i <= n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        memcpy(rank_arr, tmp, sizeof(rank_arr));
    }
}
void build_lcp(const int *S, int n, int *lcp) {}

int main(int argc, char **argv)
{
    scanf("%d", &num);
    for (int i = 0; i < num; ++i) {
        scanf("%d", s1 + i);
    }
    // sort(s1, s1 + num);
    memcpy(s2, s1, sizeof(int) * num);
    sort(s2, s2 + num);
    int *s2end = unique(s2, s2 + num);
    map<int, int> discrete_map;
    for (int *s2beg = s2; s2beg != s2end; ++s2beg) {
        discrete_map[*s2beg] = s2beg - s2 + 1;
    }
    DEBUG_CMD({
        printf("s2(in number): ");
        for (int i = 0; i < s2end - s2; ++i) {
            printf("%d ", s2[i]);
        }
        printf("\n");
    });
    for (int i = 0; i < num; ++i) {
        s3[i] = discrete_map[s1[num - i - 1]];
    }
    DEBUG_CMD({
        printf("s3(in number): ");
        for (int i = 0; i < num; ++i) {
            printf("%d ", s3[i]);
        }
        printf("\n");
    });
    n = num;
    build_sa(s3, n);
    // build_lcp(s3, n, lcp);
    int k1, k2;
    for (int i = 1; i <= n; ++i) {
        if (sa[i] >= 2 && sa[i] < n) {
            k1 = sa[i];
            break;
        }
    }
    int rem_size = k1 * 2;
    for (int i = 0; i < k1; ++i) {
        s4[i] = s3[i];
    }
    for (int i = 0; i < k1; ++i) {
        s4[i + k1] = s3[i];
    }
    build_sa(s4, rem_size);
    DEBUG_CMD({
        printf("rem_size:%d\n", rem_size);
        printf("s4(in number): ");
        for (int i = 0; i < rem_size; ++i) {
            printf("%d ", s2[s4[i] - 1]);
        }
        printf("\n");
    });
    for (int i = 1; i <= rem_size; ++i) {
        if (sa[i] >= 1 && sa[i] < rem_size / 2) {
            k2 = sa[i];
            break;
        }
    }
    DEBUG_CMD(printf("k1:%d, k2:%d\n", k1, k2););
    for (int i = k1; i < n; ++i) {
        printf("%d\n", s2[s3[i] - 1]);
    }
    for (int i = k2; i < rem_size / 2 + k2; ++i) {
        printf("%d\n", s2[s4[i] - 1]);
    }
    return 0;
};

#endif
