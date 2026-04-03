#if 0
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1009;
int dp[N];
struct Node {
    int l, r, v;
    bool operator<(const Node &t) const { return l < t.l; }
} a[N];

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].v);
    sort(a, a + m);
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int mmax = 0;
        for (int j = 0; j < i; j++)
            if (a[j].r + r <= a[i].l && mmax < dp[j])
                mmax = dp[j];
        dp[i] = mmax + a[i].v;
        ans = max(ans, dp[i]);
        cout << dp[i] << ' ';
    }
    cout << endl;
    cout << ans << endl;
    return 0;
}

#else
#ifndef _t12pr_20200328_
#define _t12pr_20200328_
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

const int MAXM = 1024;
int N, M, R;
struct WorkingSheet {
    int s;
    int e;
    int effi;
    bool operator<(const WorkingSheet &works) const { return s < works.s; }
};

WorkingSheet works[MAXM];

int max_milk[MAXM];

int main(int argc, char **argv)
{
    cin >> N >> M >> R;
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &works[i].s, &works[i].e, &works[i].effi);
    }
    sort(works, works + M);
    memset(max_milk, 0, sizeof(max_milk));
    // max_milk[1] = works[0].effi;
    // ============================================================================================
    // 错误 input
    // ============================================================================================
    // 46 9 1
    // 38 44 6
    // 10 25 34
    // 17 39 14
    // 10 39 16
    // 7 23 31
    // 34 41 47
    // 9 36 38
    // 17 39 27
    // 2 6 32
    // ============================================================================================
    // max_milk 此处记录 到 i 为止最大值, 但是这种记法会出现问题
    // 错误答案:
    // 32 63 70 70 70 70 70 117 117 0
    // (2, 6): 32,
    // (7, 23): 31,
    // (9, 36): 38,
    // (10, 25): 34,
    // (10, 39): 16,
    // (17, 39): 14,
    // (17, 39): 27,
    // (34, 41): 47,
    // (38, 44): 6,
    // 117
    // 正确答案:
    // 32 63 70 66 48 46 59 113 76
    // 113

    // 错误原因是只记录到当前位置的最大值, 但是没有记录此最大值是从什么地方过来的,
    // 因此可能出现 (10, 25) 继承了 (9, 36) 的最大值, 后续 (34, 41) 错误选择了这个最大值
    // 没有考虑这个值的来历

    // 正确解法: max_milk[i] 为选择 works[i] 为最后一段所能取到的最大值
    // 强制这个地方不选的策略收益为 0, 那么 max_milk[i] 就一定是选择 works[i] 的基础上
    // 所能达到的最大值

    for (int i = 0; i <= M; ++i) {
        // int donttake = max_milk[i - 1];
        // =========================================================================================
        // magic line
        int donttake = 0;
        // =========================================================================================
        bool all_false = true;
        for (int j = i - 1; j >= 0; --j) {
            if (works[i].s - works[j].e >= R) {
                max_milk[i] = max(max(max_milk[j] + works[i].effi, donttake), max_milk[i]);
                all_false = false;
                // break;
            }
        }
        if (all_false) {
            max_milk[i] = works[i].effi;
        }
    }
    _DEBUG_CMD({
        for (int i = 0; i <= M; ++i) {
            cout << max_milk[i] << ' ';
        }
        cout << endl;
        for (int i = 0; i < M; ++i) {
            cout << "(" << works[i].s << ", " << works[i].e << "): " << works[i].effi << ", "
                 << endl;
        }
        // cout << endl;
    });
    cout << *max_element(max_milk, max_milk + M) << endl;
    return 0;
};

#endif
#endif
