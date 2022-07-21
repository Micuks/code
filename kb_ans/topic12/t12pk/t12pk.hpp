#ifndef _t12pk_20200310_
#define _t12pk_20200310_
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

#if 0
const int MAXN = 256;
const int MAXM = 32;
const int DIFF_OFFSET = 20 * 20 * 2 + 1;
int n, m;
int pi[MAXN], di[MAXN];
int case_idx = 0;
// int dp[MAXN][MAXN];
int path[MAXM][DIFF_OFFSET];
int dp[MAXM][DIFF_OFFSET];
int add[MAXN], sub[MAXN];

bool valid_opt(int mx, int dx, int k)
{
    if (mx == 0) {
        return true;
    }
    if (path[mx][dx] == k) {
        return false;
    }
    return valid_opt(mx - 1, dx - sub[path[mx][dx]], k);
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d", &n, &m) && n != 0 && m != 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &pi[i], &di[i]);
            add[i] = pi[i] + di[i];
            sub[i] = pi[i] - di[i];
        }
        // memset(dp[0], );
        // fill_n(dp[0], (DIFF_OFFSET << 1) + 1, -1);
        // for (int i = 0; i < DIFF_OFFSET; ++i) {
        //    fill(begin(dp[i]), end(dp[i]), 0xC0C0C0C0);
        //}
        // fill(begin(dp[0]), end(dp[0]), 0xC0C0C0C0);
        memset(dp, 0xC0, sizeof(dp));
        // memset((int *) dp, sizeof(dp), 0xC0);
        // cout << "dp[0][0]: " << dp[0][0] << endl;
        // fill(begin(path[0]), end(path[0]), 0);
        int fix = m * 20;
        // memset(path, sizeof(path), 0);
        memset(path, 0, sizeof(path));
        dp[0][fix] = 0;

        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j <= 2 * fix; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (dp[i - 1][j] >= 0 && valid_opt(i - 1, j, k) &&
                        dp[i][j + sub[k]] < dp[i - 1][j] + add[k]) {
                        dp[i][j + sub[k]] = dp[i - 1][j] + add[k];
                        // path[i][j] = k;
                        path[i][j + sub[k]] = k;
                    }
                }
            }
        }
        vector<int> output;
        output.reserve(MAXN);
        // int *sp = max_element(begin(dp[m]), end(dp[m]));
        int kk = 0;
        while (dp[m][fix - kk] < 0 && dp[m][fix + kk] < 0)
            kk++;
        int div = dp[m][fix - kk] > dp[m][fix + kk] ? fix - kk : fix + kk;
        _DEBUG_CMD({
            for (int j = 0; j <= m; ++j) {
                cout << "dp[" << j << "]" << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << dp[j][i] << ' ';
                }
                cout << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << dp[j][2 * fix - i] << ' ';
                }
                cout << endl;
            }
            for (int j = 0; j <= m; ++j) {
                cout << "path[" << j << "]" << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << path[j][i] << ' ';
                }
                cout << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << path[j][2 * fix - i] << ' ';
                }
                cout << endl;
            }
            cout << "kk = " << kk << " div = " << div << " fix = " << fix << endl;
        });
        int max_ps = (dp[m][div] + div - fix) / 2;
        int max_ds = (dp[m][div] - div + fix) / 2;
        for (int i = 0, j = m, k = div; i < m; ++i) {
            output.push_back(path[j][k]);
            k -= sub[output[i]];
            --j;
        }
        // sort(output);
        // output.sort();
        sort(output.begin(), output.end());
        printf("Jury #%d\n", ++case_idx);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", max_ps,
               max_ds);
        int idx = 0;
        for (idx = 0; idx < output.size(); ++idx) {
            printf(" %d", output[idx] + 1);
        }
        printf("\n");
    }
    return 0;
};

#elif 1
const int MAXN = 256;
const int MAXM = 32;
const int DIFF_OFFSET = 20 * 20 * 2 + 1;
int n, m;
int pi[MAXN], di[MAXN];
int case_idx = 0;
// int dp[MAXN][MAXN];
int path[MAXM][DIFF_OFFSET];
int dp[MAXM][DIFF_OFFSET];
int add[MAXN], sub[MAXN];

bool valid_opt(int mx, int dx, int k)
{
    while (mx >= 0) {
        if (path[mx][dx] == k) {
            return false;
        }
        // dx -= sub[k];
        dx -= sub[path[mx][dx]];
        mx -= 1;
    }
    return true;
}

int solve(int mx, int dx)
{
    if (dp[mx][dx] >= 0) {
        return dp[mx][dx];
        // return dx;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < dx; ++j) {
            if (dx > sub[i]) {
                int res = solve(mx - 1, dx - sub[i]);
                if (dp[mx - 1][dx - sub[i]] >= 0 && valid_opt(mx, dx, i) &&
                    res + add[i] > dp[mx][dx]) {
                    dp[mx][dx] = res + add[i];
                    path[mx][dx] = i;
                }
            }
        }
    }
    return dp[mx][dx];
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    while (~scanf("%d%d", &n, &m) && n != 0 && m != 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &pi[i], &di[i]);
            add[i] = pi[i] + di[i];
            sub[i] = pi[i] - di[i];
        }
        int fix = 20 * m;
        memset(dp, 0xC0, sizeof(dp));
        memset(path, 0, sizeof(path));
        dp[0][fix] = 0;

        for (int i = 2 * fix; i > 0; --i)
            solve(m, i);

        int kk = 0;
        vector<int> ans;
        ans.reserve(m);
        while (dp[m][m + kk] < 0 && dp[m][m - kk] < 0)
            ++kk;
        int div = dp[m][fix - kk] > dp[m][fix + kk] ? fix - kk : fix + kk;
        int max_ps = (dp[m][div] + div - fix) / 2;
        int max_ds = (dp[m][div] - div + fix) / 2;

        for (int i = 0, j = m, k = div; i < m; ++i) {
            ans.push_back(path[j][k]);
            k -= sub[path[j][k]];
            --j;
        }

        sort(ans.begin(), ans.end());
        DEBUG_CMD({
            for (int j = 0; j <= m; ++j) {
                cout << "dp[" << j << "]" << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << dp[j][i] << ' ';
                }
                cout << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << dp[j][2 * fix - i] << ' ';
                }
                cout << endl;
            }
            for (int j = 0; j <= m; ++j) {
                cout << "path[" << j << "]" << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << path[j][i] << ' ';
                }
                cout << endl;
                for (int i = 0; i <= fix; ++i) {
                    cout << path[j][2 * fix - i] << ' ';
                }
                cout << endl;
            }
            cout << "kk = " << kk << " div = " << div << " fix = " << fix << endl;
        });
        printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n",
               ++case_cnt, max_ps, max_ds);
        for (int i = 0; i < ans.size(); ++i) {
            printf(" %d", ans[i] + 1);
        }
        printf("\n");
    }
    return 0;
}
#endif
#endif
