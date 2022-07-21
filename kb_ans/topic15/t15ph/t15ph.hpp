#ifndef _t15ph_20210715_
#define _t15ph_20210715_
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

typedef long long ll;
const int MAXD = 1 << 4;
int t;
ll a, b;

const int MAXN = 1 << 14;
ll dp[MAXD][MAXN];
int digits[MAXD], dcnt;

void split_number(ll n)
{
    dcnt = 0;
    while (n) {
        digits[dcnt++] = n % 10;
        n /= 10;
    }
}
int get_weight(ll n)
{
    int ret = 0;
    int pow = 1;
    while (n) {
        ret += (n % 10) * pow;
        pow = pow << 1;
        n /= 10;
    }
    return ret;
}

#if 0
ll ret = 0;
int dfs(int pos, int cur_pos, int accw, int cnt, bool upper_limit)
{
    if (cur_pos > pos) {
        return;
    }
    if (upper_limit == false && dp[cur_pos][])

        int upper_bound = upper_limit ? digits[cur_pos] : 9;
    for (int i = 0; i <= 9; ++i) {
        int newaccw = accw + i * (1 << cur_pos);
        if (upper_limit == true) {
            if (dp[cur_pos][newaccw] != -1ll) {
                dp[cur_pos][newaccw] += cnt;
            }
            else {
                dp[cur_pos][newaccw] = cnt;
            }
        }
        dfs(pos, cur_pos + 1, newaccw, cnt, upper_limit && i == upper_bound);
    }
    return;
}
// void fwd_calc(int pos) {
//}
void dfsfail(int pos, int accw, int cnt, bool upper_limit)
{
    if (pos == -1) {
        return;
    }
    if (upper_limit == false && dp[pos][accw] != -1ll) {
        return;
    }
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        int new_accw = accw + i * (1 << pos);
        if (pos != 0) {
            dfs(pos - 1, new_accw, cnt, upper_limit && i == upper_bound);
        }
        else {
            if (dp[0][new_accw] != -1) {
                dp[0][new_accw] += cnt;
            }
            else {
                dp[0][new_accw] = cnt;
            }
        }
    }
}
void dfs2(int pos, int acc_w, int cnt, bool upper_limit)
{
    if (pos == -1) {
        return;
        // return 1;
        /*
        if (dp[pos][acc_w] != -1ll) {
            dp[pos][acc_w] += 1;
        }
        else {
            dp[pos][acc_w] = 1;
        }
        */
        // return;
    }
    if (upper_limit == false && dp[pos][acc_w] != -1ll) {
        // return dp[pos][acc_w];
        return;
    }
    // ll ret = 0;
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        if (pos != 0) {
            dfs(pos - 1, acc_w + i * (1 << pos), upper_limit && i == upper_bound);
        }
        else {
        }
    }
    if (upper_limit == false) {
        for (int i = 0; i <= upper_bound; ++i) {
            if (dp[pos][acc_w + i * (1 << pos)] != -1) {
                dp[pos][acc_w + i * (1 << pos)] += dp[pos][acc_w];
            }
            else {
                dp[pos][acc_w + i * (1 << pos)] = dp[pos][acc_w];
            }
        }
    }
    // return ret;
    return;
}
#endif
ll newdfs1(int pos, int acc_w, bool upper_limit)
{
    if (pos == -1) {
        return acc_w >= 0 ? 1 : 0;
    }
    if (upper_limit == false && dp[pos][acc_w] != -1ll) {
        return dp[pos][acc_w];
    }
    ll ret = 0;
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        int newacc = acc_w - i * (1 << pos);
        if (newacc >= 0) {
            ret += newdfs1(pos - 1, newacc, upper_limit && i == upper_bound);
        }
    }
    if (upper_limit == false) {
        dp[pos][acc_w] = ret;
    }
    return ret;
}
/*
ll dfs1(int pos, int acc_w, bool upper_limit)
{
    if (pos == -1) {
        return 1;
    }
    if (upper_limit == false && dp[pos][acc_w] != -1ll) {
        return dp[pos][acc_w];
    }
    ll ret = 0;
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        ret += dfs(pos - 1, acc_w + i * (1 << pos), upper_limit && i == upper_bound);
    }
    if (upper_limit == false) {
        dp[pos][acc_w] = ret;
    }
    return ret;
}
*/

ll solve(ll a, ll b)
{
    split_number(b);
    /*
    dfs(dcnt - 1, 0, true);
    ll ret = 0;
    int weight = get_weight(a);
    for (int i = dcnt - 1; i < dcnt; ++i) {
        for (int j = 0; j <= weight; ++j) {
            if (dp[i][j] != -1ll) {
                ret += dp[i][j];
            }
        }
    }
    return ret;
    */
    return newdfs1(dcnt - 1, get_weight(a), true);
}

int main(int argc, char **argv)
{
    memset(dp, -1, sizeof(dp));
    scanf("%d", &t);
    for (int case_cnt = 0; case_cnt < t; ++case_cnt) {
        scanf("%lld%lld", &a, &b);
        ll ret = solve(a, b);
        printf("Case #%d: %lld\n", case_cnt + 1, ret);
    }
    return 0;
};

#endif
