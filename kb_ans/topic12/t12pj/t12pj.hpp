#ifndef _t12pj_20200310_
#define _t12pj_20200310_
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

const int MAXN = 1 << 10;
const int MAXC = 1e4 + 7;
struct M {
    int w;
    int s;
    int idx;
    bool operator<(const M &m) const
    {
        if (w != m.w) {
            return w < m.w;
        }
        return s > m.s;
    }
};
M m[MAXN];
// int W[MAXN];
// int S[MAXN];
int prev_x[MAXN];
int dp[MAXC];

void recursive_print(int idx)
{
    if (prev_x[idx] < 0) {
        printf("%d\n", m[idx].idx);
        return;
    }
    int next = prev_x[idx];
    recursive_print(next);
    printf("%d\n", m[idx].idx);
    return;
}

ostream &operator<<(ostream &os, const M &m)
{
    os << "w: " << m.w << " s: " << m.s << " idx: " << m.idx;
    return os;
}

int main(int argc, char **argv)
{
    int w, s;
    int mcnt = 0;
    int maxs = 0;
    fill_n(prev_x, MAXN, 0);
    fill_n(dp, MAXC, 0);
    while (~scanf("%d%d", &w, &s)) {
        m[mcnt].w = w;
        m[mcnt].s = s;
        m[mcnt].idx = mcnt + 1;
        ++mcnt;
    }
    sort(m, m + mcnt);
    for (int i = 0; i < mcnt; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (m[i].w > m[j].w && m[i].s < m[j].s) {
                if (dp[i] < dp[j] + 1) {
                    _DEBUG_CMD({
                        if (i == 4 && j == 2) {
                            cout << "i: " << i << " " << m[i] << endl;
                            cout << "j: " << j << " " << m[j] << endl;
                        }
                    });
                    dp[i] = dp[j] + 1;
                    prev_x[i] = j;
                    maxs = max(maxs, dp[i]);
                }
            }
        }
        if (dp[i] == 0) {
            dp[i] = 1;
            prev_x[i] = -1;
            maxs = max(maxs, dp[i]);
        }
    }
    _DEBUG_CMD({
        cout << "m:\n";
        for (int i = 0; i < mcnt; ++i) {
            cout << m[i] << endl;
        }
        cout << "prev_x: ";
        for (int i = 0; i < mcnt; ++i) {
            cout << prev_x[i] << " ";
        }
        cout << endl;
        cout << "dp: ";
        for (int i = 0; i < mcnt; ++i) {
            cout << dp[i] << " ";
        }
        cout << endl;
    });
    int max_offset = max_element(dp, dp + mcnt) - dp;
    printf("%d\n", maxs);
    recursive_print(max_offset);
    return 0;
};

#endif
