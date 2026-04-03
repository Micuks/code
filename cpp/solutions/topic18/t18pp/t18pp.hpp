#ifndef _t18pp_20210816_
#define _t18pp_20210816_
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

int case_cnt, m, n;
const int MAXN = 1 << 10;
int sa[MAXN], lcp[MAXN], tmp[MAXN], rank_arr[MAXN], belong[MAXN];
char dna[MAXN];

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
        for (; i + h < n && j + h < n; ++h) {
            if (S[i + h] != S[j + h])
                break;
        }
        lcp[rank_arr[i]] = h;
    }
}

string ans;
bool check_valid(int k)
{
    char valid[1 << 4];
    int cnt = 0;
    memset(valid, 0, sizeof(valid));
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] >= k) {
            int b1 = belong[sa[i]];
            int b2 = belong[sa[i - 1]];
            if (valid[b1] == 0) {
                valid[b1] = 1;
                ++cnt;
            }
            if (valid[b2] == 0) {
                valid[b2] = 1;
                ++cnt;
            }
            if (cnt == m) {
                ans = string(dna + sa[i], 0, k);
                return true;
            }
        }
        else {
            cnt = 0;
            memset(valid, 0, sizeof(valid));
        }
    }
    return false;
}

void solve()
{
    int lb = 0, ub = 61;
    int mid = (lb + ub) / 2 + 1;
    while (lb < ub) {
        if (check_valid(mid)) {
            lb = mid;
        }
        else {
            ub = mid - 1;
        }
        mid = (lb + ub) / 2 + 1;
    }
    if (lb < 3) {
        printf("no significant commonalities\n");
    }
    else {
        printf("%s\n", ans.c_str());
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &case_cnt);
    while (case_cnt--) {
        scanf("%d", &m);
        memset(dna, 0, sizeof(dna));
        for (int i = 0; i < m; ++i) {
            scanf("%s", dna + i * 61);
            dna[i * 61 + 60] = '$' + i;
            fill_n(belong + i * 61, 60, i);
        }
        n = m * 61;
        build_sa(dna, n);
        build_lcp(dna, n, lcp);
        solve();
        _DEBUG_CMD({
            printf("sa\tlcp\ts:\n");
            for (int i = 0; i <= n; ++i) {
                printf("%d\t%d\t%s\n", sa[i], lcp[i], dna + sa[i]);
            }
        });
        _DEBUG_CMD({
            printf("lcp: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", lcp[i]);
            }
            printf("\n");
        });
    }
    return 0;
};

#endif
