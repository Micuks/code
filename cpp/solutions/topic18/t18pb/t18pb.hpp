#ifndef _t18pb_20210726_
#define _t18pb_20210726_
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
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN];
int pattern[MAXN];
int n, k;

/*
string get_str(int *S, int n, int i)
{
    if (i >= n) {
        return "";
    }
    string ret = to_string(S[i]);
    for (int k = i + 1; k < n; ++k) {
        ret += "," + to_string(S[k]);
    }
    return ret;
}
void print_sa(int *S, int n, int i)
{
    printf("sa[%d]:%d %s\n", i, sa[i], get_str(S, n, sa[i]).c_str());
}
string get_str_limit(int *S, int n, int i, int len)
{
    if (i >= n) {
        return "";
    }
    string ret = to_string(S[i]);
    for (int j = i; j < n && len > 0; ++j, --len) {
        ret += "," + to_string(S[j]);
    }
    return ret;
}
void print_rank(int *S, int n, int rnk1, int rnk2, int len, int res)
{
    printf("len:%d rank1:%d str:%s rank2:%d str:%s r1<r2:%d\n", len, rnk1,
           get_str_limit(S, n, rnk1, len).c_str(), rnk2, get_str_limit(S, n, rnk2, len).c_str(),
           res);
}
*/

struct Comparator {
    int k, n;
    Comparator(int m, int n) : k(m), n(n) {}
    bool operator()(const int &i, const int &j) const
    {
        if (rank_arr[i] != rank_arr[j]) {
            return rank_arr[i] < rank_arr[j];
        }
        else {
            int ri = i + k <= n ? rank_arr[i + k] : -1;
            int rj = j + k <= n ? rank_arr[j + k] : -1;
            _DEBUG_CMD(if (ri != -1 && rj != -1) {
                /*
                printf("k:%d n:%d i:%d j:%d ri:%d rj:%d ri < rj:%d\n", k, n, i, j, ri, rj,
                       ri < rj ? 1 : 0);
                */
                print_rank(pattern, n, ri, rj, k, ri < rj ? 1 : 0);
            });
            return ri < rj;
        }
    }
};
void build_sa(int *S, int n)
{
    for (int i = 0; i <= n; ++i) {
        sa[i] = i;
        rank_arr[i] = i < n ? S[i] : -1;
    }
    for (int k = 1; k <= n; k *= 2) {
        // Comparator cmp{k, n};
        Comparator cmp(k, n);
        sort(sa, sa + n + 1, cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            _DEBUG_CMD({
                printf("k:%d,n:%d sa[%d]%d: sa[%d]%d \"%s\" < \"%s\": %d\n", k, n, i - 1, sa[i - 1],
                       i, sa[i], get_str(S, n, sa[i - 1]).c_str(), get_str(S, n, sa[i]).c_str(),
                       cmp(sa[i - 1], sa[i]) ? 1 : 0);
            });
        }
        for (int i = 0; i <= n; ++i) {
            rank_arr[i] = tmp[i];
        }
        _DEBUG_CMD(for (int i = 0; i <= n; ++i) print_sa(S, n, i););
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
            if (S[j + h] != S[i + h])
                break;
        }
        lcp[rank_arr[i] - 1] = h;
    }
}

int query(int k, int n)
{
    int max_len = 0;
    for (int i = 1; i <= n; ++i) {
        int sub_max_len = 2e6;
        for (int j = 0; j < k - 1; ++j) {
            sub_max_len = min(sub_max_len, lcp[i + j]);
        }
        max_len = max(max_len, sub_max_len);
    }
    return max_len;
}

int main(int argc, char **argv)
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &pattern[i]);
    }
    build_sa(pattern, n);
    build_lcp(pattern, n, lcp);
    _DEBUG_CMD({
        printf("pattern:\n");
        for (int i = 0; i < n; ++i) {
            printf("%d ", pattern[i]);
        }
        printf("\nlcp:\n");
        for (int i = 0; i <= n; ++i) {
            printf("%d ", lcp[i]);
        }
        printf("\n");
        for (int i = 0; i <= n; ++i) {
            print_sa(pattern, n, i);
        }
    });
    printf("%d\n", query(k, n));
    return 0;
};

#endif
