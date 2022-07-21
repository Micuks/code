#if 0
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#define eps 1e-9
#define LL long long
#define PI acos(-1.0)
#define bitnum(a) __builtin_popcount(a)
using namespace std;
const int N = 5005;
const int M = 100005;
const int inf = 1000000007;
const int mod = 1000000007;
const int MAXN = 50005;
// rnk从0开始
// sa从1开始,因为最后一个字符(最小的)排在第0位
// height从1开始,因为表示的是sa[i - 1]和sa[i]
//倍增算法 O(nlogn)
int wa[MAXN], wb[MAXN], wv[MAXN], ws_[MAXN];
// Suffix函数的参数m代表字符串中字符的取值范围,是基数排序的一个参数,如果原序列都是字母可以直接取128,如果原序列本身都是整数的话,则m可以取比最大的整数大1的值
//待排序的字符串放在r数组中,从r[0]到r[n-1]，长度为n
//为了方便比较大小,可以在字符串后面添加一个字符,这个字符没有在前面的字符中出现过,而且比前面的字符都要小
//同上,为了函数操作的方便,约定除r[n-1]外所有的r[i]都大于0,r[n-1]=0
//函数结束后,结果放在sa数组中,从sa[0]到sa[n-1]
void Suffix(int *r, int *sa, int n, int m)
{
    int i, j, k, *x = wa, *y = wb, *t;
    //对长度为1的字符串排序
    //一般来说,在字符串的题目中,r的最大值不会很大,所以这里使用了基数排序
    //如果r的最大值很大,那么把这段代码改成快速排序
    for (i = 0; i < m; ++i)
        ws_[i] = 0;
    for (i = 0; i < n; ++i)
        ws_[x[i] = r[i]]++; //统计字符的个数
    for (i = 1; i < m; ++i)
        ws_[i] += ws_[i - 1]; //统计不大于字符i的字符个数
    for (i = n - 1; i >= 0; --i)
        sa[--ws_[x[i]]] = i; //计算字符排名
                             //基数排序
                             // x数组保存的值相当于是rank值
    for (j = 1, k = 1; k < n; j *= 2, m = k) {
        // j是当前字符串的长度,数组y保存的是对第二关键字排序的结果
        //第二关键字排序
        for (k = 0, i = n - j; i < n; ++i)
            y[k++] = i; //第二关键字为0的排在前面
        for (i = 0; i < n; ++i)
            if (sa[i] >= j)
                y[k++] = sa[i] -
                         j; //长度为j的子串sa[i]应该是长度为2 * j的子串sa[i] -
                            // j的后缀（第二关键字）,对所有的长度为2 * j的子串根据第二关键字来排序
        for (i = 0; i < n; ++i)
            wv[i] = x[y[i]]; //提取第一关键字
                             //按第一关键字排序 (原理同对长度为1的字符串排序)
        for (i = 0; i < m; ++i)
            ws_[i] = 0;
        for (i = 0; i < n; ++i)
            ws_[wv[i]]++;
        for (i = 1; i < m; ++i)
            ws_[i] += ws_[i - 1];
        for (i = n - 1; i >= 0; --i)
            sa[--ws_[wv[i]]] = y[i]; //按第一关键字,计算出了长度为2 * j的子串排名情况
        //此时数组x是长度为j的子串的排名情况,数组y仍是根据第二关键字排序后的结果
        //计算长度为2 * j的子串的排名情况,保存到数组x
        t = x;
        x = y;
        y = t;
        for (x[sa[0]] = 0, i = k = 1; i < n; ++i)
            x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + j] == y[sa[i] + j]) ? k - 1 : k++;
        //若长度为2 * j的子串sa[i]与sa[i - 1]完全相同,则他们有相同的排名
    }
}
int Rank[MAXN], height[MAXN], sa[MAXN], r[MAXN];
void calheight(int *r, int *sa, int n)
{
    int i, j, k = 0;
    for (i = 1; i <= n; i++)
        Rank[sa[i]] = i;
    for (i = 0; i < n; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; r[i + k] == r[j + k]; k++)
            ;
}
int n, minnum[MAXN][16];
void RMQ() //预处理  O(nlogn)
{
    int i, j;
    int m = (int) (log(n * 1.0) / log(2.0));
    for (i = 1; i <= n; i++)
        minnum[i][0] = height[i];
    for (j = 1; j <= m; j++)
        for (i = 1; i + (1 << j) - 1 <= n; i++)
            minnum[i][j] = min(minnum[i][j - 1], minnum[i + (1 << (j - 1))][j - 1]);
}
int Ask_MIN(int a, int b) // O(1)
{
    int k = int(log(b - a + 1.0) / log(2.0));
    return min(minnum[a][k], minnum[b - (1 << k) + 1][k]);
}
int calprefix(int a, int b)
{
    a = Rank[a], b = Rank[b];
    if (a > b)
        swap(a, b);
    return Ask_MIN(a + 1, b);
}
char s[5];
int main()
{
    int t, i, j, k, ans, Max;
    scanf("%d", &t);
    while (t--) {
        Max = 1;
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%s", s);
            r[i] = s[0] - 'a' + 1;
        }
        r[i] = 0;
        Suffix(r, sa, n + 1, 3);
        calheight(r, sa, n);
        RMQ();
        printf("lcp: ");
        for (int i = 0; i <= n; ++i) {
            printf("%d ", height[i]);
        }
        printf("\nsa: ");
        for (int i = 0; i <= n; ++i) {
            printf("%d ", sa[i]);
        }
        printf("\n");
        for (i = 1; i <= n; i++) {
            for (j = 0; j + i < n; j += i) {
                ans = calprefix(j, j + i);
                k = j - (i - ans % i);
                ans = ans / i + 1;
                if (k >= 0 && calprefix(k, k + i) >= i)
                    ans++;
                // printf("L=%d,R=%d\n",i,ans);
                Max = max(Max, ans);
            }
        }
        printf("%d\n", Max);
    }
    return 0;
}

// https://blog.csdn.net/queuelovestack/article/details/53031731
#else
#ifndef _t18pf_20210731_
#define _t18pf_20210731_
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
// const int MAXN = 50001;
char str[MAXN];
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], lcp[MAXN];
int minnum[MAXN][16];
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
    // a = rank_arr[a], b = rank_arr[b];
    int ra = rank_arr[a], rb = rank_arr[b];
    if (ra > rb) {
        swap(ra, rb);
    }
    int min_lcp = min_between(ra + 1, rb);
    _DEBUG_CMD(printf("a:%d b:%d ra:%d, rb:%d, min_lcp:%d, sa:%s sb:%s\n", a, b, ra, rb, min_lcp,
                      str + ra, str + rb););
    return min_lcp;
}
char s[256];
int main(int argc, char **argv)
{
    int t, n, max_num;
    scanf("%d", &t);
    while (t--) {
        max_num = 1;
        scanf("%d", &n);
        memset(str, 0, sizeof(str));
        for (int i = 0; i < n; ++i) {
            scanf("%s", s);
            str[i] = s[0];
        }
        build_sa(str, n);
        build_lcp(str, n, lcp);
        build_rmq(n);
        _DEBUG_CMD({
            printf("lcp: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", lcp[i]);
            }
            printf("\nsa: ");
            for (int i = 0; i <= n; ++i) {
                printf("%d ", sa[i]);
            }
            printf("\n");
        });
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j + i < n; j += i) {
                int ans = calc_prefix(j, j + i);
                int k = j - (i - ans % i);
                _DEBUG_CMD(printf("ans:%d, i:%d, j:%d\n", ans, i, j));
                ans = ans / i + 1;
                if (k >= 0 && calc_prefix(k, k + i) >= i) {
                    ++ans;
                }
                max_num = max(max_num, ans);
            }
        }
        printf("%d\n", max_num);
    }
    return 0;
};

#endif
#endif
