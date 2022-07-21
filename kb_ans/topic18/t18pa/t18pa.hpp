#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int getint()
{
    int i = 0, f = 1;
    char c;
    for (c = getchar(); (c < '0' || c > '9') && c != '-'; c = getchar())
        ;
    if (c == '-')
        f = -1, c = getchar();
    for (; c >= '0' && c <= '9'; c = getchar())
        i = (i << 3) + (i << 1) + c - '0';
    return i * f;
}

const int N = 20005;
int n, m, a[N], rank_arr[N], sa[N], tp[N], c[N], height[N];

void Rsort()
{
    for (int i = 1; i <= m; i++)
        c[i] = 0;
    for (int i = 1; i <= n; i++)
        c[rank_arr[tp[i]]]++;
    for (int i = 1; i <= m; i++)
        c[i] += c[i - 1];
    for (int i = n; i; i--)
        sa[c[rank_arr[tp[i]]]--] = tp[i];
}

void SA_init()
{
    m = 200;
    for (int i = 1; i <= n; i++)
        rank_arr[i] = a[i], tp[i] = i;
    Rsort();
    for (int w = 1; w < n; w <<= 1) {
        int j = 0;
        for (int i = n - w + 1; i <= n; i++)
            tp[++j] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w)
                tp[++j] = sa[i] - w;
        Rsort();
        for (int i = 1; i <= n; i++)
            swap(rank_arr[i], tp[i]);
        rank_arr[sa[1]] = j = 1;
        for (int i = 2; i <= n; i++)
            rank_arr[sa[i]] =
                (tp[sa[i]] == tp[sa[i - 1]] && tp[sa[i] + w] == tp[sa[i - 1] + w] ? j : ++j);
        m = j;
    }
    int w = 0, j;
    for (int i = 1; i <= n; height[rank_arr[i++]] = w)
        for (w = w ? w - 1 : w, j = sa[rank_arr[i] - 1]; a[i + w] == a[j + w]; w++)
            ;
}

bool check(int k)
{
    int mi = n + 1, mx = 0;
    for (int i = 2; i <= n; i++) {
        if (height[i] >= k) {
            mi = min(mi, min(sa[i], sa[i - 1]));
            mx = max(mx, max(sa[i], sa[i - 1]));
            if (mx - mi > k)
                return true;
        }
        else
            mi = n + 1, mx = 0;
    }
    return false;
}

int main()
{
    // freopen("lx.in","r",stdin);
    while (n = getint()) {
        for (int i = 1; i <= n; i++)
            a[i] = getint();
        n--;
        for (int i = 1; i <= n; i++)
            a[i] = a[i + 1] - a[i] + 100;
        SA_init();
        printf("height:\n");
        for (int i = 0; i <= n; ++i) {
            printf("%d ", height[i]);
        }
        printf("\nsa: \n");
        for (int i = 0; i <= n; ++i) {
            printf("%d ", sa[i]);
        }
        printf("\nrank: \n");
        for (int i = 0; i <= n; ++i) {
            printf("%d ", rank_arr[i]);
        }
        printf("\na[]:\n");
        for (int i = 0; i <= n; ++i) {
            printf("%d ", a[i]);
        }
        printf("\n");

        int l = 0, r = n;
        while (l <= r) {
            int mid = l + r >> 1;
            if (check(mid))
                l = mid + 1;
            else
                r = mid - 1;
        }
        if (r >= 4)
            printf("%d\n", r + 1);
        else
            puts("0");
    }
    return 0;
}
// https://blog.csdn.net/cdsszjj/article/details/79185053
#else
#ifndef _t18pa_20210722_
#define _t18pa_20210722_
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
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN], n, k;
int piece[MAXN];
/*
string debug_piece(int i)
{
    if (i == n) {
        return "";
    }
    string ret = to_string(piece[i + 1]);
    for (int j = 1; j + i < n; ++j) {
        ret += "," + to_string(piece[j + i + 1]);
    }
    return ret;
}
void debug_out_sa()
{
    for (int i = 0; i <= n; ++i) {
        printf("i:%d sa[%d]:%d str:%s\n", i, i, sa[i], debug_piece(sa[i]).c_str());
    }
}
*/
bool compare_sa(int i, int j)
{
    // i, j is sa[iidx], sa[jidx]
    if (rank_arr[i] != rank_arr[j]) {
        return rank_arr[i] < rank_arr[j];
    }
    else {
        int ri = i + k <= n ? rank_arr[i + k] : -1;
        int rj = j + k <= n ? rank_arr[j + k] : -1;
        _DEBUG_CMD({
            if (ri != -1 && rj != -1) {
                printf("k:%d, i:%d, j:%d ri:%d rj:%d ri<rj?:%d s[ri]:%d s[rj]:%d, ", k, i, j, ri,
                       rj, ri < rj ? 1 : 0, piece[ri + 1], piece[rj + 1]);
                printf("sa[i]:%d str(sa[i]):%s, sa[j]:%d str(sa[j]):%s\n", i,
                       debug_piece(i).c_str(), j, debug_piece(j).c_str());
            }
        });
        return ri < rj;
    }
}

void debug_print_rank(const string &s = "")
{
    if (s != "") {
        printf("%s ", s.c_str());
    }
    printf("rank:\n");
    for (int i = 0; i <= n; ++i) {
        printf("%d ", rank_arr[i]);
    }
    printf("\n");
}
void debug_print_sa(const string &s = "")
{
    if (s != "") {
        printf("%s ", s.c_str());
    }
    printf("sa:\n");
    for (int i = 0; i <= n; ++i) {
        printf("%d ", sa[i]);
    }
    printf("\n");
}

void construct_sa(int *S, int n, int *sa)
{
    // int n = S.length();
    for (int i = 0; i <= n; ++i) {
        sa[i] = i;
        rank_arr[i] = i < n ? S[i] : -1;
    }
    _DEBUG_CMD(debug_print_rank());
    for (k = 1; k <= n; k *= 2) {
        sort(sa, sa + n + 1, compare_sa);
        // DEBUG_CMD(debug_print_sa());
        _DEBUG_CMD(debug_out_sa());

        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        // memcpy(rank_arr, tmp, sizeof(rank_arr));
        for (int i = 0; i <= n; ++i) {
            rank_arr[i] = tmp[i];
        }
        _DEBUG_CMD(debug_print_rank());
    }
    _DEBUG_CMD({
        printf("final sa:\n");
        debug_out_sa();
    });
}

/*
string stoidxs(const string &s)
{
    string ret = to_string(int(s[0]));
    for (int i = 1; i < s.size(); ++i) {
        ret += string(",") + to_string(int(s[i]));
    }
    return ret;
}
string stoidxs(int *s, int n)
{
    string ret = to_string(int(s[0]));
    for (int i = 0; i < n; ++i) {
        ret += string(",") + to_string(int(s[i]));
    }
    return ret;
}
*/
void construct_lcp(int *S, int n, int *sa, int *lcp)
{
    // int n = S.length();
    for (int i = 0; i <= n; ++i) {
        rank_arr[sa[i]] = i;
    }
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; ++i) {
        int j = sa[rank_arr[i] - 1];
        int oldh = h;
        if (h > 0)
            --h;
        for (; j + h < n && i + h < n; ++h) {
            if (S[j + h] != S[i + h])
                break;
        }
        lcp[rank_arr[i] - 1] = h;
        _DEBUG_CMD({
            if (h == 3) {
                printf("j:%d sa[rank_arr[%d] - 1](%d)\n", j, i, rank_arr[i] - 1);
                printf("lcp[rank_arr[%d] - 1(%d)] = nh(3),oh(%d) s[%d]:%s, s[%d]:%s\n", i,
                       rank_arr[i] - 1, oldh, i, stoidxs(&S[i], n - i).c_str(), j,
                       stoidxs(&S[j], n - j).c_str());
                printf("s[%d+%d]:%d s[%d+%d]:%d\n", j, h, S[j + h], i, h, S[i + h]);
            }
        });
    }
}

bool check_valid3(int k)
{
    int mx_pos = 0, mi_pos = n + 1;
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] >= k) {
            mx_pos = max(mx_pos, max(sa[i], sa[i + 1]));
            mi_pos = min(mi_pos, min(sa[i], sa[i + 1]));
            if (mx_pos - mi_pos > k) {
                return true;
            }
        }
        else {
            mx_pos = 0, mi_pos = n + 1;
        }
    }
    return false;
}
bool check_valid(int k)
{
    for (int i = 1; i <= n;) {
        int min_lcp = lcp[i];
        int j = i;
        bool fast_skip = false;
        for (; j <= n; ++j) {
            min_lcp = min(min_lcp, lcp[j]);
            if (min_lcp >= k) {
                fast_skip = true;
            }
            if (min_lcp >= k && abs(sa[i] - sa[j + 1]) > k) {
                return true;
            }
        }
        _DEBUG_CMD(printf("i:%d j:%d failed, min_lcp:%d sa[%d]:%d sa[%d]:%d\n", i, j, min_lcp, i,
                          sa[i], j + 1, sa[j + 1]));
        // i = j;
        if (fast_skip) {
            i = j;
        }
        else {
            ++i;
        }
    }
    return false;
}
bool check_valid2(int k)
{
    int mi = n + 1, mx = 0;
    for (int i = 1; i <= n; ++i) {
        if (lcp[i] >= k) {
            mi = min(mi, min(sa[i], sa[i + 1]));
            mx = max(mx, max(sa[i], sa[i + 1]));
            if (mx - mi > k) {
                return true;
            }
        }
        else {
            mi = n + 1, mx = 0;
        }
    }
    return false;
}
int binary_search(int lb, int ub)
{
    int mid = (lb + ub) / 2 + 1;
    while (lb < ub) {
        if (check_valid3(mid)) {
            _DEBUG_CMD(printf("valid(%d) succ, lb:%d => %d\n", mid, lb, mid));
            lb = mid;
        }
        else {
            _DEBUG_CMD(printf("valid(%d) fail, ub:%d => %d\n", mid, ub, mid - 1));
            ub = mid - 1;
        }
        mid = (lb + ub) / 2 + 1;
    }
    return lb;
}

int main(int argc, char **argv)
{
    while (~scanf("%d", &n) && n != 0) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &piece[i]);
        }
        //*
        for (int i = 1; i < n; ++i) {
            piece[i] = piece[i + 1] - piece[i] + 100;
        }
        //*/
        _DEBUG_CMD({
            printf("piece[]: ");
            for (int i = 1; i <= n; ++i) {
                printf("%d ", piece[i]);
            }
            printf("\n");
        });
        // string str(piece + 1, piece + n);
        /*
        string str;
        str.resize(n);
        for (int i = 0; i < n; ++i) {
            str[i] = char(piece[i]);
        }
        */
        // construct_sa(str, sa);
        // construct_lcp(str, sa, lcp);
        construct_sa(piece + 1, n, sa);
        construct_lcp(piece + 1, n, sa, lcp);

        _DEBUG_CMD({
            printf("sa: \n");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", sa[i]);
            }
            printf("\nsa, lcp[]: \n");
            for (int i = 0; i <= n; ++i) {
                printf("(%d,%d) ", sa[i], lcp[i]);
            }
            printf("\nrank[]: \n");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", rank_arr[i]);
            }
            printf("\nrank[sa[i]]: \n");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", rank_arr[sa[i]]);
            }
            printf("\nsa[rank[i]]: \n");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", sa[rank_arr[i]]);
            }
            printf("\nlcp:[]:\n");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", lcp[i]);
            }
            printf("\n");
        });
        int ret = binary_search(0, n - 1);
        ret = ret + 1 >= 5 ? ret + 1 : 0;
        printf("%d\n", ret);
    }
    return 0;
};

#endif
#endif
