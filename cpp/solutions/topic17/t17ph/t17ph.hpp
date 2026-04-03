#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define REPF(i, a, b) for (int i = a; i <= b; ++i)
#define REPV(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPC(i) for (int i = 0; buf[i]; ++i)

const int MAXW = 26;
const int MAXN = 105;
const int MAXL = 1024;
const int MAXQ = 100000;
const int MOD = 20090717;

struct Trie {
    int next[MAXN][MAXW];
    int end[MAXN];
    int fail[MAXN];
    int Q[MAXQ];
    int head, tail;
    int P, root;
    int dp[26][MAXN][MAXL];

    int newnode()
    {
        REP(i, MAXW)
        next[P][i] = -1;
        end[P] = 0;
        return P++;
    }

    void init()
    {
        P = 0;
        root = newnode();
    }

    int get(char x) { return x - 'a'; }

    void insert(char buf[], int idx)
    {
        int now = root;
        REPC(i)
        {
            int x = get(buf[i]);
            if (next[now][x] == -1)
                next[now][x] = newnode();
            now = next[now][x];
        }
        end[now] = (1 << idx);
    }

    void build()
    {
        head = tail = 0;
        fail[root] = root;
        REP(i, MAXW)
        {
            if (next[root][i] == -1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q[tail++] = next[root][i];
            }
        }
        while (head != tail) {
            int now = Q[head++];
            REP(i, MAXW)
            {
                if (next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    if (end[fail[next[now][i]]])
                        end[next[now][i]] |= end[fail[next[now][i]]];
                    Q[tail++] = next[now][i];
                }
            }
        }
    }

    int solve(int n, int m, int least)
    {
        int L = 1 << m;
        REP(i, n + 1)
        REP(j, P)
#define clear(a, x, SIZE) memset(a, x, sizeof(a[0]) * (SIZE + 1))
        clear(dp[i][j], 0, L);
#undef clear
        dp[0][0][0] = 1;
        REP(i, n)
        REP(j, P)
        REP(l, L)
        if (dp[i][j][l])
            REP(k, MAXW)
            {
                int Next = next[j][k], o = (l | end[Next]);
                dp[i + 1][Next][o] += dp[i][j][l];
                if (dp[i + 1][Next][o] >= MOD)
                    dp[i + 1][Next][o] -= MOD;
            }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < P; ++j) {
                for (int k = 0; k < L; ++k) {
                    if (dp[i][j][k])
                        printf("dp[%d][%d][%d]: %d ", i, j, k, dp[i][j][k]);
                }
                printf("\n");
            }
        }
        int ans = 0;
        REP(l, L)
        {
            int cnt = 0, ll = l;
            while (ll) {
                if (ll & 1)
                    cnt++;
                ll >>= 1;
            }
            if (cnt >= least)
                REP(j, P)
                {
                    // printf("node:%d bits:%x acc:%d\n", j, l, dp[n][j][l]);
                    ans += dp[n][j][l];
                    if (ans >= MOD)
                        ans -= MOD;
                }
        }
        return ans;
    }
};

Trie ac;
char buf[MAXN];

void work()
{
    int n, m, least;
    while (~scanf("%d%d%d", &n, &m, &least) && (n || m || least)) {
        ac.init();
        REP(i, m)
        {
            scanf("%s", buf);
            ac.insert(buf, i);
        }
        ac.build();
        printf("%d\n", ac.solve(n, m, least));
    }
}

int main()
{
    work();
    return 0;
}

#else
#ifndef _t17ph_20200801_
#define _t17ph_20200801_
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

// const int MAXN <<
const int mod = 20090717;

int n, m, k;

namespace AC {
const char ori = 'a';
const int MAXT = 1 << 7;
const int TRIE_WIDTH = 'z' - 'a' + 1;
const int MAXPSWDLENGTH = 1 << 5;
const int ALLPSWDSET = 1 << 11;
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], km[MAXT], km_cnt;
void init()
{
    memset(km, 0, sizeof(km));
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    trie_cnt = 0;
    km_cnt = 0;
}
void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        const int offset = s[i] - ori;
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
        }
        u = trie[u][offset];
    }
    km[u] = ++km_cnt;
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
        for (int i = 0; i < TRIE_WIDTH; ++i) {
            if (trie[u][i]) {
                fail[trie[u][i]] = trie[fail[u]][i];
                q.push(trie[u][i]);
            }
            else {
                trie[u][i] = trie[fail[u]][i];
            }
        }
    }
}
int get1bits(int x)
{
    int res = 0;
    while (x != 0) {
        if (x & 0x1) {
            ++res;
        }
        x = x >> 1;
    }
    return res;
}
int query(int pl)
{
    int res = 0;
    int maxs = 1 << m;
    int dp[MAXPSWDLENGTH][trie_cnt + 2][maxs + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i <= pl; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            /* // wrong code
            for (int k = 0; k < TRIE_WIDTH; ++k) {
                int u = trie[j][k];
                int hitkey = km[u];
                for (int p = 0; p < (1 << m); ++p) {
                    // int flag = (1 << hitkey) & p;
                    int idx = (1 << hitkey) | p;
                    dp[i + 1][u][idx] += dp[i][j][p];
                    dp[i + 1][u][idx] %= mod;
                }
            }
            */
            for (int k = 0; k < maxs; ++k) {
                if (dp[i][j][k]) {
                    for (int l = 0; l < TRIE_WIDTH; ++l) {
                        int u = trie[j][l];
                        int nu = u;
                        int hitkey = km[nu];
                        int newidx = k;
                        if (nu != 0) {
                            while (nu != 0) {
                                if (hitkey > 0) {
                                    newidx = ((1 << (hitkey - 1)) | newidx);
                                }
                                nu = fail[nu];
                                hitkey = km[nu];
                            }
                        }
                        _DEBUG_CMD({
                            printf("hitkey:%d (1<<%d):%d, k:%d newidx:%d\n", hitkey, hitkey,
                                   (1 << hitkey), k, newidx);
                        });
                        _DEBUG_CMD({
                            if (i + 1 == 4 && u == 5) {
                                printf("i+1:4, u:5, hitkey:%d k:%d, nu:%d km[%d]:%d\n", hitkey, k,
                                       nu, nu, km[nu]);
                            }
                        });
                        dp[i + 1][u][newidx] += dp[i][j][k];
                        dp[i + 1][u][newidx] %= mod;
                    }
                }
            }
        }
    }
    // res = accumulate(dp[pl], dp[pl])
    _DEBUG_CMD({
        for (int i = 0; i <= pl; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                for (int k = 0; k < maxs; ++k) {
                    if (dp[i][j][k])
                        printf("dp[%d][%d][%d]: %d ", i, j, k, dp[i][j][k]);
                }
                printf("\n");
            }
        }
    });
    for (int i = 0; i <= trie_cnt; ++i) {
        for (int p = 0; p < (1 << m); ++p) {
            if (get1bits(p) >= k) {
                _DEBUG_CMD(printf("node:%d bits:%x acc:%d\n", i, p, dp[pl][i][p]););
                res = (res + dp[pl][i][p]) % mod;
            }
        }
    }
    // DEBUG_CMD({});
    return res;
}
}; // namespace AC

char key[AC::MAXPSWDLENGTH];
int main(int argc, char **argv)
{
    while (~scanf("%d%d%d", &n, &m, &k) && (n || m || k)) {
        _DEBUG_CMD(printf("get a new set of input, n:%d m:%d k:%d\n", n, m, k));
        AC::init();
        for (int i = 0; i < m; ++i) {
            scanf("%s", key);
            _DEBUG_CMD(printf("get candidate key: %s\n", key));
            AC::insert(key);
        }
        AC::build();
        printf("%d\n", AC::query(n));
    }
    return 0;
};

#endif
#endif
