#ifndef _t18pm_20210813_
#define _t18pm_20210813_
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
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN];
int minnum[MAXN][30];
char pld[MAXN];
int n;

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
void build_sa(const char *S, int n)
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
void build_lcp(const char *S, int n, int *lcp)
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
void solve()
{
    string s1 = "";
    int ri = rank_arr[n / 2 + 1];
    // int ri = n / 2;
    // int ri = sa[n / 2];
    int mingap = lcp[ri]; // ri && sa[ri - 1]
    for (int i = 1; i < ri; ++i) {
        int sj = sa[ri - i];
        if (sj < (n / 2) && sj == 0 && mingap == n / 2) {
            s1 = string(pld, 0, n / 2);
            break;
        }
        else if (sj < (n / 2) && sj + mingap >= n / 2) {
            // hit!
            s1 = string(pld, 0, n / 2 - mingap / 2);
            _DEBUG_CMD(printf("pld[0~n/2]:%s\n", s1.c_str()););
            int half_beg = n / 2 + 1 + (mingap + 1) / 2;
            int half_len = n / 2 + 1 - (mingap + 1) / 2;
            s1 += string(pld, half_beg, half_len);
            _DEBUG_CMD(printf("s1 mingap:%d ri:%d sj:%d news1:%s\npld:%s pos:%d lenth:%d\n", mingap,
                              ri, sj, s1.c_str(), pld, half_beg, half_len));
            break;
        }
        else {
            mingap = min(mingap, lcp[ri - i]);
        }
    }
    string s2 = "";
    mingap = lcp[ri + 1];
    for (int i = 1; i + ri <= n; ++i) {
        int sj = sa[ri + i];
        if (sj < (n / 2) && sj == 0 && mingap == n / 2) {
            s2 = string(pld, 0, n / 2);
            break;
        }
        else if (sj < (n / 2) && sj + mingap >= n / 2) {
            s2 = string(pld, 0, n / 2 - mingap / 2);
            _DEBUG_CMD(printf("pld[0~n/2]:%s\n", s2.c_str()););
            s2 += string(pld, n / 2 + 1 + mingap / 2, n / 2 + 1 - mingap / 2);
            _DEBUG_CMD(printf("s2 mingap:%d ri:%d sj:%d, s[sa[ri]]:%s s[sj]:%s\n", mingap, ri, sj,
                              pld + sa[ri], pld + sj));
            break;
        }
        else {
            mingap = min(mingap, lcp[ri + i]);
        }
    }
    if (s1 == "") {
        _DEBUG_CMD(printf("s1 is blank\n"););
        printf("%s\n", s2.c_str());
        return;
    }
    if (s2 == "") {
        _DEBUG_CMD(printf("s2 is blank\n"););
        printf("%s\n", s1.c_str());
        return;
    }
    _DEBUG_CMD(
        printf("s1:%s len:%ld s2:%s len:%ld\n", s1.c_str(), s1.length(), s2.c_str(), s2.length()));
    const string &s = s1.length() < s2.length() ? s1 : s2;
    printf("%s\n", s.c_str());
    return;
}

int main(int argc, char **argv)
{
    while (~scanf("%s", pld)) {
        int slen = strlen(pld);
        for (int i = 0; i < slen; ++i) {
            pld[i + slen + 1] = pld[slen - i - 1];
        }
        pld[slen] = '$';
        pld[2 * slen + 1] = 0;
        n = 2 * slen + 1;
        build_sa(pld, n);
        build_lcp(pld, n, lcp);
        // build_rmq(n);
        _DEBUG_CMD({
            printf("n:%d s:%s\n", n, pld);
            printf("sa: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", sa[i]);
            }
            printf("\n");
            printf("lcp: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", lcp[i]);
            }
            printf("\n");
        });
        _DEBUG_CMD({
            for (int i = 0; i <= n; ++i) {
                printf("sa[%d]:%d lcp[%d]:%d part:%d, st:%d s:%s\n", i, sa[i], i, lcp[i],
                       (sa[i] < (n / 2) ? 1 : 0), (sa[i] == (n / 2 + 1) ? 1 : 0), pld + sa[i]);
            }
        });
        solve();
    }
    return 0;
};

#endif
