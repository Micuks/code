#ifndef _t17po_20200822_
#define _t17po_20200822_
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

const int mod = 1e9 + 7;
int T, M, N;
char trace[1 << 1][1 << 7];
namespace AC {
const int MAXT = 1 << 8;
const int TRIE_WIDTH = 1 << 1;
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT], node_cnt;
int path(char c)
{
    // path('R') yields 0, path('D') yields 1
    return (c - 'R') / ('D' - 'R');
}
void init()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;
    node_cnt = 0;
}
void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = path(s[i]);
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
        }
        u = trie[u][offset];
    }
    val[u] = ++node_cnt;
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

        val[u] = (val[u] | val[fail[u]]);

        for (int i = 0; i < TRIE_WIDTH; ++i) {
            int &n = trie[u][i];
            if (n != 0) {
                fail[n] = trie[fail[u]][i];
                q.push(n);
            }
            else {
                n = trie[fail[u]][i];
            }
        }
    }
}
int query(int m, int n)
{
    int ret = 0;
    int dp[m + 1][n + 1][trie_cnt + 1][1 << 2];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= trie_cnt; ++k) {
                for (int l = 0; l < (1 << 2); ++l) {
                    if (dp[i][j][k][l] != 0) {
                        // path('R') yields 0, path('D') yields 1
                        if (i != m) {
                            // can go down
                            int st = 1;
                            int nu = trie[k][st];
                            // int ns = (val[nu] == 0) ? l : (l | (1 << val[nu]));
                            int ns = (val[nu] | l);
                            dp[i + 1][j][nu][ns] = (dp[i + 1][j][nu][ns] + dp[i][j][k][l]) % mod;
                        }
                        if (j != n) {
                            // can go right
                            int st = 0;
                            int nu = trie[k][st];
                            // int ns = (val[nu] == 0) ? l : (l | (1 << val[nu]));
                            int ns = (val[nu] | l);
                            dp[i][j + 1][nu][ns] = (dp[i][j + 1][nu][ns] + dp[i][j][k][l]) % mod;
                        }
                    }
                }
            }
        }
    }
    _DEBUG_CMD({ for (int i = 0; i <) });
    for (int i = 0; i <= trie_cnt; ++i) {
        ret = (ret + dp[m][n][i][3]) % mod;
    }

    return ret;
}
}; // namespace AC

int main(int argc, char **argv)
{
    cin >> T;
    while (T--) {
        AC::init();
        scanf("%d%d", &N, &M);
        for (int i = 0; i < 2; ++i) {
            scanf("%s", trace[i]);
            AC::insert(trace[i]);
        }
        AC::build();
        printf("%d\n", AC::query(M, N));
    }
    return 0;
};

#endif
