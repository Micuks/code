#if 0

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
const int INF = 2e9;
const LL LNF = 9e18;
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 100;

int id[MAXN]; //记录属于哪个字符串
int r[MAXN], sa[MAXN], Rank[MAXN], height[MAXN];
int t1[MAXN], t2[MAXN], c[MAXN];

bool cmp(int *r, int a, int b, int l) { return r[a] == r[b] && r[a + l] == r[b + l]; }

void DA(int str[], int sa[], int Rank[], int height[], int n, int m)
{
    n++;
    int i, j, p, *x = t1, *y = t2;
    for (i = 0; i < m; i++)
        c[i] = 0;
    for (i = 0; i < n; i++)
        c[x[i] = str[i]]++;
    for (i = 1; i < m; i++)
        c[i] += c[i - 1];
    for (i = n - 1; i >= 0; i--)
        sa[--c[x[i]]] = i;
    for (j = 1; j <= n; j <<= 1) {
        p = 0;
        for (i = n - j; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;

        for (i = 0; i < m; i++)
            c[i] = 0;
        for (i = 0; i < n; i++)
            c[x[y[i]]]++;
        for (i = 1; i < m; i++)
            c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--c[x[y[i]]]] = y[i];

        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for (i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;

        if (p >= n)
            break;
        m = p;
    }

    int k = 0;
    n--;
    for (i = 0; i <= n; i++)
        Rank[sa[i]] = i;
    for (i = 0; i < n; i++) {
        if (k)
            k--;
        j = sa[Rank[i] - 1];
        while (str[i + k] == str[j + k])
            k++;
        height[Rank[i]] = k;
    }
}

bool vis[110];
bool test(int n, int len, int k)
{
    int cnt = 0;
    memset(vis, false, sizeof(vis));
    for (int i = 2; i <= len; i++) {
        if (height[i] < k) {
            cnt = 0;
            memset(vis, false, sizeof(vis));
        }
        else {
            if (!vis[id[sa[i - 1]]])
                vis[id[sa[i - 1]]] = true, cnt++;
            if (!vis[id[sa[i]]])
                vis[id[sa[i]]] = true, cnt++;
            if (cnt > n / 2)
                return true;
        }
    }
    return false;
}

void Print(int n, int len, int k)
{
    int cnt = 0, flag = false;
    memset(vis, false, sizeof(vis));
    for (int i = 2; i <= len; i++) {
        if (height[i] < k) {
            flag = false;
            cnt = 0;
            memset(vis, false, sizeof(vis));
        }
        else {
            if (!vis[id[sa[i - 1]]])
                vis[id[sa[i - 1]]] = true, cnt++;
            if (!vis[id[sa[i]]])
                vis[id[sa[i]]] = true, cnt++;
            if (cnt > n / 2 && !flag) {
                flag = true; //表明当前组已经输出了
                for (int j = sa[i]; j < sa[i] + k; j++)
                    putchar(r[j] + 'a' - 1);
                putchar('\n');
            }
        }
    }
}

char str[MAXN];
int main()
{
    int n, firCase = false;
    while (scanf("%d", &n) && n) {
        int len = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            int LEN = strlen(str);
            for (int j = 0; j < LEN; j++) {
                r[len] = str[j] - 'a' + 1;
                id[len++] = i;
            }
            r[len] = 30 + i; //分隔符要各异
            id[len++] = i;
        }
        r[len] = 0;
        DA(r, sa, Rank, height, len, 200);

        int l = 0, r = 1000;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (test(n, len, mid))
                l = mid + 1;
            else
                r = mid - 1;
        }

        if (firCase)
            printf("\n");
        firCase = true;
        if (r == 0)
            puts("?");
        else
            Print(n, len, r);
    }
}
#else
#ifndef _t18pj_20210809_
#define _t18pj_20210809_
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

const int MAXN = 2e5 + 3;
int n, type_num;
int sa[MAXN], lcp[MAXN], tmp[MAXN], rank_arr[MAXN], dna_seq[MAXN];
// bool visit[MAXN];
char visit[1 << 8];
char dna[MAXN];
int dna_num[MAXN];

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
        // lcp[rank_arr[i] - 1] = h;
        lcp[rank_arr[i]] = h;
    }
}

bool check_valid(int k)
{
    int cnt = 0;
    memset(visit, 0, sizeof(visit));
    // int half = type_num / 2;
    // half += (type_num % 2);
    int half = type_num / 2 + 1;
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] >= k) {
            if (visit[dna_seq[sa[i]]] == false) {
                visit[dna_seq[sa[i]]] = true;
                ++cnt;
            }
            if (visit[dna_seq[sa[i - 1]]] == false) {
                visit[dna_seq[sa[i - 1]]] = true;
                ++cnt;
            }
            if (cnt >= half) {
                return true;
            }
        }
        else {
            _DEBUG_CMD({
                if (k == 2) {
                    printf("old_cnt:%d, lcp[i-1]:%d: %s\n", cnt, lcp[i - 1], dna + sa[i - 1]);
                }
            });
            cnt = 0;
            memset(visit, 0, sizeof(visit));
        }
    }
    return false;
}

void print_ans(int k)
{
    int cnt = 0;
    bool flag = true;
    // int half = type_num / 2;
    // half += ((type_num % 2) ? 1 : 0);
    int half = type_num / 2 + 1;
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] >= k) {
            if (visit[dna_seq[sa[i]]] == false) {
                visit[dna_seq[sa[i]]] = true;
                ++cnt;
            }
            if (visit[dna_seq[sa[i - 1]]] == false) {
                visit[dna_seq[sa[i - 1]]] = true;
                ++cnt;
            }
            if (cnt >= half && flag) {
                flag = false;
                // return true;
                for (int j = 0; j < k; ++j) {
                    putchar(dna[sa[i] + j]);
                }
                putchar('\n');
            }
        }
        else {
            flag = true;
            cnt = 0;
            memset(visit, 0, sizeof(visit));
        }
    }
    // return false;
}
void solve()
{
    int lb = 0, ub = 1000;
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
    _DEBUG_CMD(printf("lb:%d ub:%d mid:%d\n", lb, ub, mid));
    if (lb > 1) {
        print_ans(lb);
    }
    else {
        printf("?\n");
    }
}

int main(int argc, char **argv)
{
    char str[1 << 10];
    bool first_run = true;
    while (~scanf("%d", &type_num) && type_num) {
        n = 0;
        for (int i = 0; i < type_num; ++i) {
            scanf("%s", str);
            int slen = strlen(str);
            memcpy(dna + n, str, slen);
            fill_n(dna_seq + n, slen + 1, i);
            for (int j = 0; j < slen; ++j) {
                dna_num[j + n] = dna[j + n];
            }
            // dna[n + slen + 1] = (char) (i + 256);
            dna[n + slen] = 0;
            dna_num[n + slen] = i + 256;
            n += slen + 1;
        }

        build_sa(dna_num, n);
        build_lcp(dna_num, n, lcp);
        _DEBUG_CMD({
            for (int k = 0; k <= n; ++k) {
                printf("sa[%d]:%d lcp[%d]:%d %s\n", k, sa[k], k, lcp[k], dna + sa[k]);
            }
        });
        if (first_run == false) {
            printf("\n");
        }
        first_run = false;
        solve();
    }
    return 0;
};

#endif
#endif
