#if 0
#include <algorithm>
#include <bitset>
#include <iostream>
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
using namespace std;
typedef long long ll;
typedef long double ldb;
#define inf 99999999
#define pi acos(-1.0)
#define maxn 300050
#define maxnode 2050
#define MOD 1000000009
int bcd[maxnode][11]; // bcd[i][j]表示ac自动机状态i走j步后的状态

struct trie {
    int sz, root, val[maxnode], next[maxnode][2], fail[maxnode];
    int q[11111];
    void init()
    {
        int i;
        sz = root = 0;
        val[0] = 0;
        for (i = 0; i < 2; i++) {
            next[root][i] = -1;
        }
    }
    void charu(char *s)
    {
        int i, j, u = 0;
        int len = strlen(s);
        for (i = 0; i < len; i++) {
            int c = s[i] - '0';
            if (next[u][c] == -1) {
                sz++;
                val[sz] = 0;
                next[u][c] = sz;
                u = next[u][c];
                for (j = 0; j < 2; j++) {
                    next[u][j] = -1;
                }
            }
            else {
                u = next[u][c];
            }
        }
        val[u] = 1;
    }

    void build()
    {
        int i, j;
        int front, rear;
        front = 1;
        rear = 0;
        for (i = 0; i < 2; i++) {
            if (next[root][i] == -1) {
                next[root][i] = root;
            }
            else {
                fail[next[root][i]] = root;
                rear++;
                q[rear] = next[root][i];
            }
        }
        while (front <= rear) {
            int x = q[front];
            if (val[fail[x]]) //!!!!!
                val[x] = 1;
            front++;
            for (i = 0; i < 2; i++) {
                if (next[x][i] == -1) {
                    next[x][i] = next[fail[x]][i];
                }
                else {
                    fail[next[x][i]] = next[fail[x]][i];
                    rear++;
                    q[rear] = next[x][i];
                }
            }
        }
    }
} ac;

int change(int jiedian, int num)
{
    int i, j, len = 0;
    int shu[10];
    while (num) {
        shu[++len] = num % 2;
        num /= 2;
    }
    while (len < 4)
        shu[++len] = 0;
    for (i = 4; i >= 1; i--) {
        if (ac.val[ac.next[jiedian][shu[i]]] == 1)
            return -1;
        else
            jiedian = ac.next[jiedian][shu[i]];
    }
    return jiedian;
}

void pre_init()
{
    int i, j;
    for (i = 0; i <= ac.sz; i++) {
        for (j = 0; j <= 9; j++) {
            bcd[i][j] = change(i, j);
        }
    }
}

int wei[300];
ll dp[300][maxnode];

ll dfs(int pos, int jiedian, int lim, int zero)
{
    int i, j;
    if (pos == -1) {
        // printf("dfs(%d,%d,%d,%d): 1\n", pos, jiedian, lim, zero);
        return 1;
    }
    if (lim == 0 && zero == 0 && dp[pos][jiedian] != -1) { //这里和下面同理，也不要省略zero==0
        // printf("dfs(%d,%d,%d,%d): %d\n", pos, jiedian, lim, zero, dp[pos][jiedian]);
        return dp[pos][jiedian];
    }
    int ed = lim ? wei[pos] : 9;
    ll ans = 0;
    for (i = 0; i <= ed; i++) {
        if (i == 0) {
            if (zero) {
                ans += dfs(pos - 1, jiedian, 0, 1);
                ans %= MOD;
            }
            else {
                if (bcd[jiedian][0] != -1) {
                    ans += dfs(pos - 1, bcd[jiedian][0], lim && i == ed, 0);
                    ans %= MOD;
                }
            }
            continue;
        }
        if (bcd[jiedian][i] != -1) {
            ans += dfs(pos - 1, bcd[jiedian][i], lim && i == ed, 0);
            ans %= MOD;
        }
    }
    if (lim == 0 &&
        zero ==
            0) { //这里要注意，不能写成if(lim==0)dp[pos][jiedian]=ans;因为zero不为0的话，即最高位还没有确定，那么可能后面几位都可以跳过去，
        dp[pos][jiedian] =
            ans; //即可以把0跳过，但是对于最高位确定的情况下，后面不管加什么数都不能跳过去，即使是0也要在ac自动机上走0这个数.
    }
    // printf("dfs(%d,%d,%d,%d): %d\n", pos, jiedian, lim, zero, ans);
    return ans;
}

ll cal(char *s)
{
    int i, j, len;
    len = strlen(s);
    for (i = 0; i < len; i++) {
        wei[i] = s[len - 1 - i] - '0';
    }
    return dfs(len - 1, 0, 1, 1);
}

char s1[300], s2[300], s[30];
int main()
{
    int n, m, i, j, T, len1, len2;
    scanf("%d", &T);
    while (T--) {
        ac.init();
        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%s", s);
            ac.charu(s);
        }
        ac.build();
        pre_init();
        scanf("%s", s1);
        len1 = strlen(s1);
        reverse(s1, s1 + len1);
        for (i = 0; i < len1; i++) { //这里算的是(l,r],所以先要把s1的数减去1
            if (s1[i] - '0' > 0) {
                s1[i]--;
                break;
            }
            else {
                s1[i] = '9';
            }
        }
        memset(dp, -1, sizeof(dp));
        ll ans = 0;
        if (s1[len1 - 1] == '0')
            len1 -= 1;
        s1[len1] = '\0';
        reverse(s1, s1 + len1);
        ans -= cal(s1);
        ans %= MOD;
        scanf("%s", s2);
        ans += cal(s2);
        ans %= MOD;
        if (ans < 0) {
            ans = (ans + MOD) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

#else
#ifndef _t15pi_20210716_
#define _t15pi_20210716_
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
const int MOD = 1000000009;
int t, n;
char A[1 << 8], B[1 << 8];
char fbd_code[1 << 7][1 << 5];

const int TRIE_WIDTH = 1 << 1;
const int MAXT = 1 << 15;
const char ori = '0';

const int MAXBCD = 10;
const char bcd[MAXBCD][1 << 3] = {"0000", "0001", "0010", "0011", "0100",
                                  "0101", "0110", "0111", "1000", "1001"};
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT];
int state_transform_table[MAXT][MAXBCD];

#if 0
void init()
{
    trie_cnt = 0;
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(val, 0, sizeof(val));
    memset(state_transform_table, -1, sizeof(state_transform_table));
}

void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = s[i] - ori;
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
        }
        u = trie[u][offset];
    }
    val[u] = 1;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < TRIE_WIDTH; ++i) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        val[u] += val[fail[u]];
        for (int i = 0; i < TRIE_WIDTH; ++i) {
            int &n = trie[u][i];
            if (n) {
                fail[n] = trie[fail[u]][i];
                q.push(n);
            }
            else {
                n = trie[fail[u]][i];
            }
        }
    }
    for (int i = 0; i <= trie_cnt; ++i) {
        for (int j = 0; j < MAXBCD; ++j) {
            int u = i;
            bool valid = true;
            for (int k = 0; bcd[j][k] != 0; ++k) {
                int n = trie[u][(j >> (3 - k)) & 0x01];
                if (val[n] != 0) {
                    valid = false;
                    break;
                }
                else {
                    u = n;
                }
            }
            if (valid && val[u] == 0) {
                state_transform_table[i][j] = u;
            }
        }
    }
}
#endif
void init()
{
    memset(state_transform_table, -1, sizeof(state_transform_table));
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;
}
void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = s[i] - ori;
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
        }
        u = trie[u][offset];
    }
    val[u] = 1;
}
void build()
{
    queue<int> q;
    for (int i = 0; i < TRIE_WIDTH; ++i) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        val[u] += val[fail[u]];

        for (int i = 0; i < TRIE_WIDTH; ++i) {
            int &n = trie[u][i];
            if (n) {
                fail[n] = trie[fail[u]][i];
                q.push(n);
            }
            else {
                n = trie[fail[u]][i];
            }
        }
    }
    for (int i = 0; i <= trie_cnt; ++i) {
        for (int j = 0; j < MAXBCD; ++j) {
            int u = i;
            bool valid = true;
            for (int k = 0; bcd[j][k] != 0; ++k) {
                int n = trie[u][(j >> (3 - k)) & 0x1];
                if (val[n] != 0) {
                    valid = false;
                    break;
                }
                else {
                    u = n;
                }
            }
            if (valid && val[u] == 0) {
                state_transform_table[i][j] = u;
            }
        }
    }
}

void dec(char *s)
{
    int t = strlen(s) - 1;
    while (true) {
        // assert(t >= 0);
        if (s[t] == '0') {
            s[t] = '9';
            t -= 1;
        }
        else {
            s[t] -= 1;
            if (t == 0) {
            }
            break;
        }
    }
}

const int MAXD = 1 << 8;
int dp[MAXD][MAXT];

int dfs(const char *s, int pos, int state, bool upper_limit, bool zero)
{
    assert(state <= trie_cnt);
    assert(pos < 256);
    if (state <= -1) {
        return 0;
    }
    if (pos <= -1) {
        // return state != -1 ? 1 : 0;
        _DEBUG_CMD(printf("dfs(%d,%d,%d,%d): 1\n", pos, state, upper_limit ? 1 : 0, zero ? 1 : 0));
        return 1;
    }
    if (upper_limit == false && zero == false && dp[pos][state] != -1) {
        _DEBUG_CMD(printf("dfs(%d,%d,%d,%d): %d\n", pos, state, upper_limit ? 1 : 0, zero ? 1 : 0,
                          dp[pos][state]));
        return dp[pos][state];
    }
    int ret = 0;
    int upper_bound = upper_limit ? s[pos] - ori : 9;
    assert(upper_bound <= 9);
    for (int i = 0; i <= upper_bound; ++i) {
        int newstate = state_transform_table[state][i];
        if (i == 0) {
            if (zero) {
                ret = (ret + dfs(s, pos - 1, state, false, true)) % MOD;
            }
            else {
                if (newstate != -1) {
                    ret =
                        (ret + dfs(s, pos - 1, newstate, upper_limit && i == upper_bound, false)) %
                        MOD;
                }
            }
            continue;
        }
        if (newstate != -1) {
            ret = (ret + dfs(s, pos - 1, newstate, upper_limit && i == upper_bound, false)) % MOD;
        }
    }
    if (upper_limit == false && zero == false) {
        dp[pos][state] = ret;
    }
    _DEBUG_CMD(
        printf("dfs(%d,%d,%d,%d): %d\n", pos, state, upper_limit ? 1 : 0, zero ? 1 : 0, ret));
    return ret;
}

void debug_dp(int pos, int max_state)
{
    printf("print debug state\n");
    for (int i = 0; i < pos; ++i) {
        printf("dp[%d]: ", i);
        for (int j = 0; j <= max_state; ++j) {
            if (dp[i][j] != -1) {
                printf("(%d,%d) ", j, dp[i][j]);
            }
        }
        printf("\n");
    }
}
int solve(const char *s)
{
    /*
    while (*s == '0') {
        ++s;
    }
    */

    string str(s);
    string str_rev(str.rbegin(), str.rend());
    _DEBUG_CMD(printf("in solve %s\n", s););
    int ret = dfs(str_rev.c_str(), strlen(s) - 1, 0, true, true);
    _DEBUG_CMD(debug_dp(strlen(s) - 1, trie_cnt));
    return ret;
}

int main(int argc, char **argv)
{
    scanf("%d", &t);
    while (t--) {
        init();
        memset(dp, -1, sizeof(dp));
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", fbd_code[i]);
            insert(fbd_code[i]);
        }
        build();
        scanf("%s", A);
        scanf("%s", B);
        dec(A);
        int ans = (solve(B) - solve(A) + MOD) % MOD;
        printf("%d\n", ans);
    }
    return 0;
};

#endif
#endif
