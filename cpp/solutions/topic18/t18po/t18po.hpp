#if 0
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#define maxn 805000
#define inf 999999
#define cha 127
using namespace std;

int n, allsize;
int all[maxn][2], height[maxn], Rank[maxn], wa[maxn], wb[maxn], wv[maxn], Ws[maxn], sa[maxn];
bool covered[4005];
int start;

void buildHeight()
{
    int i, j, k;
    for (int i = 0; i < allsize; i++)
        Rank[sa[i]] = i;
    for (i = k = 0; i < allsize; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; all[i + k][0] == all[j + k][0]; k++)
            ;
}

void buildSa()
{
    int i, j, p, *pm = wa, *k2sa = wb, *t, m = cha + n;
    for (i = 0; i < m; i++)
        Ws[i] = 0;
    for (i = 0; i < allsize; i++)
        Ws[pm[i] = all[i][0]]++;
    for (i = 1; i < m; i++)
        Ws[i] += Ws[i - 1];
    for (i = allsize - 1; i >= 0; i--)
        sa[--Ws[pm[i]]] = i;
    for (j = p = 1; p < allsize; j <<= 1, m = p) {
        for (p = 0, i = allsize - j; i < allsize; i++)
            k2sa[p++] = i;
        for (i = 0; i < allsize; i++)
            if (sa[i] >= j)
                k2sa[p++] = sa[i] - j;
        for (i = 0; i < m; i++)
            Ws[i] = 0;
        for (i = 0; i < allsize; i++)
            Ws[wv[i] = pm[k2sa[i]]]++;
        for (i = 1; i < m; i++)
            Ws[i] += Ws[i - 1];
        for (i = allsize - 1; i >= 0; i--)
            sa[--Ws[wv[i]]] = k2sa[i];
        for (t = pm, pm = k2sa, k2sa = t, pm[sa[0]] = 0, p = i = 1; i < allsize; i++) {
            int a = sa[i - 1], b = sa[i];
            if (k2sa[a] == k2sa[b] && k2sa[a + j] == k2sa[b + j])
                pm[sa[i]] = p - 1;
            else
                pm[sa[i]] = p++;
        }
    }
    return;
}

bool coveredisfull()
{
    for (int i = 1; i <= n; i++)
        if (covered[i] == false)
            return false;
    return true;
}

bool find(int l)
{
    bool flag = false;
    for (int i = 1; i <= allsize - 1; i++) {
        if (height[i] >= l && flag == false) {
            flag = true;
            covered[all[sa[i]][1]] = true;
            covered[all[sa[i - 1]][1]] = true;
        }
        else if (height[i] >= l && flag == true) {
            covered[all[sa[i]][1]] = true;
            covered[all[sa[i - 1]][1]] = true;
        }
        else if (height[i] < l && flag == true) {
            if (coveredisfull()) {
                start = sa[i - 1];
                return true;
            }
            else
                memset(covered, 0, sizeof(covered));
            flag = false;
        }
    }
    return false;
}

void bisolve()
{
    int s = 0, e = 200;
    while (s < e) {
        int mid = (s + e) / 2;
        if (find(mid))
            s = mid;
        else
            e = mid - 1;
        memset(covered, 0, sizeof(covered));
        if (s == e - 1) {
            if (find(e))
                s = e;
            break;
        }
        memset(covered, 0, sizeof(covered));
    }
    if (s == 0) {
        printf("IDENTITY LOST\n");
        return;
    }
    for (int i = start; i < start + s; i++)
        printf("%c", (char) all[i][0]);
    printf("\n");
}

void init()
{
    memset(covered, 0, sizeof(covered));
    allsize = 0;
    char line[205];
    for (int i = 1; i <= n; i++) {
        scanf("%s", line);
        for (int j = 0; line[j]; j++) {
            all[allsize][1] = i;
            all[allsize++][0] = line[j];
        }
        all[allsize++][0] = cha + i;
    }
    all[allsize - 1][0] = 0;
    buildSa();
    buildHeight();
    bisolve();
}

int main()
{
    while (scanf("%d", &n) && n)
        init();
    return 0;
}

// https://www.programminghunter.com/article/6445208061/
#else
#ifndef _t18po_20210816_
#define _t18po_20210816_
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

const int MAXN = 1 << 22;
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) *3 + 1 : ((x) -tb) * 3 + 2)

int sa[MAXN], rank_arr[MAXN], lcp[MAXN], tmp[MAXN], belong[MAXN];
int wa[MAXN], wb[MAXN], Ws[MAXN], wv[MAXN];

int n, N;
int tr[MAXN];
char trs[MAXN];

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
int c0(int *r, int a, int b)
{
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}
int c12(int k, int *r, int a, int b)
{
    if (k == 2)
        return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
    return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
}
void Rsort(int *r, int *a, int *b, int n, int m)
{
    for (int i = 0; i < n; i++)
        wv[i] = r[a[i]];
    for (int i = 0; i < m; i++)
        Ws[i] = 0;
    for (int i = 0; i < n; i++)
        Ws[wv[i]]++;
    for (int i = 1; i < m; i++)
        Ws[i] += Ws[i - 1];
    for (int i = n - 1; i >= 0; i--)
        b[--Ws[wv[i]]] = a[i];
}
void build_sa_dc3(int *r, int *sa, int n, int m)
{
    int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    r[n] = r[n + 1] = 0;
    for (i = 0; i < n; i++)
        if (i % 3 != 0)
            wa[tbc++] = i;
    Rsort(r + 2, wa, wb, tbc, m);
    Rsort(r + 1, wb, wa, tbc, m);
    Rsort(r, wa, wb, tbc, m);
    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
    if (p < tbc)
        build_sa_dc3(rn, san, tbc, p);
    else
        for (i = 0; i < tbc; i++)
            san[rn[i]] = i;
    for (i = 0; i < tbc; i++)
        if (san[i] < tb)
            wb[ta++] = san[i] * 3;
    if (n % 3 == 1)
        wb[ta++] = n - 1;
    Rsort(r, wb, wa, ta, m);
    for (i = 0; i < tbc; i++)
        wv[wb[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++)
        sa[p] = wa[i++];
    for (; j < tbc; p++)
        sa[p] = wb[j++];
}

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

void get_height(int n)
{
    int i, j, k = 0;
    for (i = 1; i <= n; i++)
        rank_arr[sa[i]] = i;
    for (i = 0; i < n; lcp[rank_arr[i++]] = k)
        for (k ? k-- : 0, j = sa[rank_arr[i] - 1]; tr[i + k] == tr[j + k]; k++)
            ;
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
string ans;
bool check_valid(int k)
{
    char valid[1 << 12];
    int cnt = 0;
    memset(valid, 0, sizeof(char) * N);
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] >= k) {
            int bsi = belong[sa[i]];
            int bsim1 = belong[sa[i - 1]];
            if (valid[bsi] == 0) {
                valid[bsi] = 1;
                ++cnt;
                _DEBUG_CMD({
                    if (k == 5) {
                        printf("k:%d sa[%d]:%d belong:%d cnt:%d\n", k, i, sa[i], bsi, cnt);
                        printf("suff(%d): ", sa[i]);
                        for (int j = 0; j < k; ++j) {
                            printf("%c", tr[sa[i] + j]);
                        }
                        printf("\n");
                    }
                });
            }
            if (valid[bsim1] == 0) {
                valid[bsim1] = 1;
                ++cnt;
                _DEBUG_CMD({
                    if (k == 5) {
                        printf("k:%d sa[%d]:%d belong:%d cnt:%d\n", k, i + 1, sa[i + 1], bsim1,
                               cnt);
                        printf("suff(%d): ", sa[i + 1]);
                        for (int j = 0; j < k; ++j) {
                            printf("%c", tr[sa[i + 1] + j]);
                        }
                        printf("\n");
                    }
                });
            }
            if (cnt == N) {
                string s(string(trs + sa[i]), 0, k);
                ans = s;
                return true;
            }
        }
        else {
            cnt = 0;
            memset(valid, 0, sizeof(char) * N);
        }
    }
    return false;
}
/*
void print_valid(int k)
{
    char valid[1 << 12];
    int cnt = 0;
    memset(valid, 0, sizeof(valid));
    for (int i = 2; i <= n; ++i) {
        if (lcp[i] >= k) {
            int bsi = belong[sa[i]];
            int bsim1 = belong[sa[i - 1]];
            if (valid[bsi] == 0) {
                valid[bsi] = 1;
                ++cnt;
            }
            if (valid[bsim1] == 0) {
                valid[bsim1] = 1;
                ++cnt;
            }
            if (cnt == N) {
                string s(string(trs + sa[i]), 0, k);
                printf("%s\n", s.c_str());
                return;
            }
        }
        else {
            cnt = 0;
            memset(valid, 0, sizeof(valid));
        }
    }
}
*/

void solve()
{
    int lb = 0, ub = 200;
    int mid = (ub + lb) / 2 + 1;
    while (lb < ub) {
        if (check_valid(mid)) {
            lb = mid;
        }
        else {
            ub = mid - 1;
        }
        mid = (lb + ub) / 2 + 1;
    }
    _DEBUG_CMD(printf("lb:%d\n", lb));
    if (lb == 0) {
        printf("IDENTITY LOST\n");
    }
    else {
        // print_valid(lb);
        printf("%s\n", ans.c_str());
    }
}
int main(int argc, char **argv)
{
    // char buf[1 << 12];
    char buf[1 << 8];
    while (~scanf("%d", &N) && N) {
        n = 0;
        // memset(lcp, 0, sizeof(lcp));
        memset(tr, 0, sizeof(tr));
        // memset(trs, 0, sizeof(trs));

        for (int i = 0; i < N; ++i) {
            scanf("%s", buf);
            int slen = strlen(buf);
            for (int j = 0; j < slen; ++j) {
                tr[n + j] = buf[j];
            }
            tr[n + slen] = 128 + i;
            memcpy(trs + n, buf, slen);
            trs[n + slen] = 0;

            fill_n(belong + n, slen, i);

            n += slen + 1;
        }
        // build_sa(tr, n);
        // tr[n + 1] = 0;
        build_sa_dc3(tr, sa, n + 1, 4000 + 128);
        // sa[0] = n;
        build_lcp(tr, n, lcp);
        _DEBUG_CMD({
            printf("lcp: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", lcp[i]);
            }
            printf("\n");
            printf("sa: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", sa[i]);
            }
            printf("\n");
            printf("belong: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", belong[i]);
            }
            printf("\n");
            printf("sa\tlcp\tsuff:\n");
            for (int i = 0; i <= n; ++i) {
                printf("%d\t%d\t%s\n", sa[i], lcp[i], trs + sa[i]);
            }
            printf("\n");
        });
        solve();
    }
    return 0;
};

#endif
#endif
