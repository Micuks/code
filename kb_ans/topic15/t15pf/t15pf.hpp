#if 0
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
const double eps = 1e-6;
const int INF = 2e9;
const LL LNF = 9e18;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 10;

int digit[20];
LL dp[20][20][4000];

LL dfs(int pos, int pivot, int num, bool lim)
{
    if (!pos)
        return (num == 0);
    //剪枝，因为先加左边的，后减左边的，最终结果需要为0，如果过程中都出现负数，那减下去更加负，所以不可能符合条件
    if (num < 0)
        return 0;
    if (!lim && dp[pos][pivot][num] != -1)
        return dp[pos][pivot][num];

    LL ret = 0;
    int maxx = lim ? digit[pos] : 9;
    for (int i = 0; i <= maxx;
         i++) // num+(pos-pivot)*i: 高位的加， 低位的减。这条式子很漂亮，刚好能满足力矩的计算
        ret += dfs(pos - 1, pivot, num + (pos - pivot) * i, lim && (i == maxx));

    if (!lim)
        dp[pos][pivot][num] = ret;
    return ret;
}

LL solve(LL n)
{
    int len = 0;
    while (n) {
        digit[++len] = n % 10;
        n /= 10;
    }

    LL ret = 0;
    for (int i = 1; i <= len; i++)
        ret += dfs(len, i, 0, true);

    /*
            为什么要减去len-1呢？原因是“0”这种情况，0在这里的表示是：000……00（len个0）。对于一个数
                    我们枚举每个位置作为平衡点，去判断是否存在一个位置使得这个数左右平衡。对于非0的数，如果
                            它是平衡数，那么它的平衡点只有一个，所以是+1，正好一一对应.
       但对于000……00来说，它的每个 位置都可以作为平衡点（
       因为左右两边都等于0），所以是+len，但是000……00却只是一个数，所以
                                            需要减去重复计算的部分，即len-1.
                                                */
    return ret - (len - 1);
}

int main()
{
    LL T, n, m;
    scanf("%lld", &T);
    memset(dp, -1, sizeof(dp));
    while (T--) {
        scanf("%lld%lld", &m, &n);
        LL ans = solve(n) - solve(m - 1);
        printf("%lld\n", ans);
    }
    return 0;
}
#else
#ifndef _t15pf_20210714_
#define _t15pf_20210714_
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
const int MAXD = 1 << 6;
const int TMID = 1 << 7;
// plain_sum:  2^8 = 256 > 171 = 19 * 9
// torque_sum: 2^11 = 2048 > 1539 = (18+1)*18/2 * 9
std::map<int, ll> dp[MAXD][1 << 8];
// ll dp[MAXD][1 << 8][1 << 11];
int digits[MAXD], dcnt;
int t;
ll x, y;

void split_number(ll n)
{
    dcnt = 0;
    while (n) {
        digits[dcnt++] = n % 10;
        n /= 10;
    }
}

ll dfs(int pos, int plain_sum, int torque_sum, bool upper_limit)
{
    if (pos == -1) {
        // return torque == TMID ? 1 : 0;
        // return torque_sum == 0 ? 1 : 0;
        return ((plain_sum == 0 && torque_sum == 0) || ((torque_sum % plain_sum) == 0)) ? 1 : 0;
    }
    if (upper_limit == false && dp[pos][plain_sum].find(torque_sum) != dp[pos][plain_sum].end()) {
        return dp[pos][plain_sum][torque_sum];
    }
    ll ret = 0;
    int upper_bound = upper_limit ? digits[pos] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        int new_plain_sum = plain_sum + i;
        int new_torque_sum = torque_sum + new_plain_sum;
        ret += dfs(pos - 1, new_plain_sum, new_torque_sum, upper_limit && i == upper_bound);
    }
    if (upper_limit == false) {
        dp[pos][plain_sum][torque_sum] = ret;
    }
    return ret;
}

ll solve(ll n)
{
    split_number(n);
    return dfs(dcnt - 1, 0, 0, true);
}
int main(int argc, char **argv)
{
    // memset(dp, -1, sizeof(dp));
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &x, &y);
        printf("%lld\n", solve(y) - solve(x - 1));
    }
    return 0;
};

#endif
#endif
