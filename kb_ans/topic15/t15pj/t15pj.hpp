#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int Mod = 1e9 + 7;
int bit[20];
ll byte[20];
struct node {
    ll cnt, sum, ssum;
    node()
    {
        cnt = -1;
        sum = 0;
        ssum = 0;
    } //这里用于新node一个struct的初始化
    node(ll cc, ll ss, ll ssss) : cnt(cc), sum(ss), ssum(ssss) {}

} dp[22][10][10];
node dfs(int len, int sremd, int nremd, int limit)
{
    if (len < 1) {
        node n = sremd && nremd
                     ? node(1, 0, 0)
                     : node(0, 0,
                            0); //这里如果位数小于个位了，如果两个条件达到的话，说明它符合了，数量+1
        printf("dfs(%d,%d,%d,%lld,%d): %lld\n", len, nremd, sremd, n.ssum, limit == 0 ? 0 : 1,
               n.ssum);
        return n;
    }
    if (!limit && dp[len][sremd][nremd].cnt != -1) {
        printf("dfs(%d,%d,%d,%lld,%d): %lld\n", len, nremd, sremd, dp[len][sremd][nremd].ssum,
               limit == 0 ? 0 : 1, dp[len][sremd][nremd].ssum);
        return dp[len][sremd][nremd]; //通过结构体初始化判断是否访问过，秒啊
    }
    int last = limit ? bit[len] : 9;
    node ans;
    ans.cnt = 0;
    for (ll i = 0; i <= last; i++) {
        if (i == 7)
            continue;
        node temp = dfs(
            len - 1, (sremd + i) % 7, (nremd * 10 + i) % 7,
            i == last &&
                limit); //这里也没见过，直接找后面位数的状态，真正的递归思想，因为这一位的状态取决于后面的状态的
        ans.cnt = (ans.cnt + temp.cnt) % Mod;
        ll r = ((i * byte[len]) % Mod * temp.cnt % Mod) % Mod; //不断Mod。。
        ll r1 = (i * byte[len]) % Mod;
        ans.sum = (ans.sum + (r + temp.sum) % Mod) % Mod;
        ans.ssum = (ans.ssum + (temp.ssum + (((r1 * r1) % Mod) * temp.cnt) % Mod +
                                ((2 * r1) % Mod * temp.sum) % Mod) %
                                   Mod) %
                   Mod;
    }
    if (!limit)
        dp[len][sremd][nremd] = ans;
    // printf("dfs(%d,%d,%d,%d,%d): %lld\n", pos, mod, dsum, dssum, upper_limit ? 1 : 0, ret));
    printf("dfs(%d,%d,%d,%lld,%d): %lld\n", len, nremd, sremd, ans.ssum, limit == 0 ? 0 : 1,
           ans.ssum);
    return ans;
}
ll cal(ll n)
{
    int k = 0;
    while (n) {
        bit[++k] = n % 10;
        n /= 10;
    }
    return dfs(k, 0, 0, 1).ssum;
}
void init()
{
    byte[1] = 1;
    for (int i = 2; i < 20; i++)
        byte[i] = (byte[i - 1] * 10) % Mod;
}
int main()
{
    int t;
    init();
    scanf("%d", &t);
    while (t--) {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        //   cout << cal(r) << endl << cal(l-1) << endl;
        printf(
            "%lld\n",
            ((cal(r) - cal(l - 1)) % Mod + Mod) %
                Mod); //长知识，因为这里cal都是区域之后的值，可能导致这里是是负数，所以要先+Mod然后再对整体Mod
    }
    return 0;
}

// https://blog.csdn.net/qq_34374664/article/details/53128417
#else
#ifndef _t15pj_20210717_
#define _t15pj_20210717_
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
const int MOD = 1e9 + 7;
int t;
ll l, r;

const int MAXD = 1 << 5;
int digits[MAXD], dcnt;
ll powof10[1 << 6];
struct Node {
    ll cnt;
    ll sum;
    ll ssum;
};
Node dp[1 << 7][1 << 3][1 << 8];

void split_number(ll x)
{
    dcnt = 0;
    while (x) {
        digits[dcnt++] = x % 10;
        x /= 10;
    }
}
// pos, mod, digital sum, digital sqaure sum
Node dfs(int pos, int mod, int dsum, bool upper_limit)
{
    if (pos == -1) {
        if (mod != 0 && (dsum % 7) != 0) {
            _DEBUG_CMD(printf("dfs(%d,%d,%d,%d,%d): %d\n", pos, mod, dsum, dssum,
                              upper_limit ? 1 : 0, dssum));
            return Node{1, 0, 0};
        }
        else {
            _DEBUG_CMD(
                printf("dfs(%d,%d,%d,%d,%d): %d\n", pos, mod, dsum, dssum, upper_limit ? 1 : 0, 0));
            return Node{0, 0, 0};
        }
    }
    if (upper_limit == false && dp[pos][mod][dsum].cnt != -1) {
        _DEBUG_CMD(printf("dfs(%d,%d,%d,%d,%d): %lld\n", pos, mod, dsum, dssum, upper_limit ? 1 : 0,
                          dp[pos][mod][dsum]));
        return dp[pos][mod][dsum];
    }
    Node ret = {0, 0, 0};
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {

        int newmod = (mod * 10 + i) % 7;
        int newdsum = dsum + i;

        // ll k = dssum % MOD;
        // ll kpow2 = (k * k) % MOD;
        // int newdssum = ((100 * kpow2) % MOD + (20ll * i * k) % MOD + i * i) % MOD;

        if (i != 7) {
            Node res = dfs(pos - 1, newmod, newdsum, upper_limit && i == upper_bound);
            ret.cnt = (ret.cnt + res.cnt) % MOD;
            ret.sum = (ret.sum + res.sum + (res.cnt * powof10[pos]) % MOD * i) % MOD;
            ret.ssum = (ret.ssum + res.ssum) % MOD;
            ret.ssum = (ret.ssum + ((powof10[pos] * res.sum) % MOD * 2 * i % MOD)) % MOD;
            ret.ssum = (ret.ssum + (i * i * powof10[pos * 2] % MOD) * res.cnt % MOD) % MOD;
        }
    }
    if (upper_limit == false) {
        dp[pos][mod][dsum] = ret;
    }
    _DEBUG_CMD(
        printf("dfs(%d,%d,%d,%d,%d): %lld\n", pos, mod, dsum, dssum, upper_limit ? 1 : 0, ret));
    return ret;
}

ll solve(ll x)
{
    split_number(x);
    return dfs(dcnt - 1, 0, 0, true).ssum;
}

/*
void debug_print(int pos)
{
    if (pos > 0) {
        debug_print(pos - 1);
    }
    bool non_neg1 = false;
    for (int i = 0; i < (1 << 3); ++i) {
        for (int j = 0; j < (1 << 8); ++j) {
            if (dp[pos][i][j] != -1) {
                non_neg1 = true;
            }
        }
    }
    if (non_neg1 == true) {
        printf("dp[%d]: ", pos);
        for (int i = 0; i < (1 << 3); ++i) {
            for (int j = 0; j < (1 << 8); ++j) {
                if (dp[pos][i][j] != -1 && dp[pos][i][j] != 0) {
                    printf("([%d,%d]:%lld) ", i, j, dp[pos][i][j]);
                }
            }
        }
        printf("\n");
    }
}
*/
int main(int argc, char **argv)
{
    scanf("%d", &t);
    memset(dp, -1, sizeof(dp));
    powof10[0] = 1;
    for (int i = 1; i < (1 << 6); ++i) {
        powof10[i] = (powof10[i - 1] * 10) % MOD;
    }
    while (t--) {
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", (solve(r) - solve(l - 1) + MOD) % MOD);
        _DEBUG_CMD(debug_print(dcnt - 1));
    }
    return 0;
};

#endif
#endif
