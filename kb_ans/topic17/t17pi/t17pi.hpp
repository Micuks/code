#if 0
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;
const double eps(1e-8);
typedef long long lint;

int t, n, m;
int w[101]; //每个编号的权值

int dp[52][1010];
string dps[52][1010];
/*
 * dp[i][j]表示长度为i的串，结尾停在Trie树上结点编号为j的位置时能得到的最大权值
 * dps[i][j]表示dp[i][j]对应的最优解的字符串
 */

struct Trie {
    int next[1010][26], fail[1010], end[1010];
    int root, L;
    int newnode()
    {
        for (int i = 0; i < 26; i++)
            next[L][i] = -1;
        end[L++] = 0;
        return L - 1;
    }
    void init()
    {
        L = 0;
        root = newnode();
        return;
    }
    void insert(char *s, int id)
    {
        int now = root;
        for (; *s; s++) {
            if (next[now][*s - 'a'] == -1)
                next[now][*s - 'a'] = newnode();
            now = next[now][*s - 'a'];
        }
        end[now] += w[id];
        return;
    }
    void build()
    {
        queue<int> Q;
        fail[root] = root;
        Q.push(root);
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            if (end[fail[now]])
                end[now] += end[fail[now]]; // end[i]表示节点i处能带来的权值
            for (int i = 0; i < 26; i++)
                if (next[now][i] == -1)
                    next[now][i] = now == root ? root : next[fail[now]][i];
                else {
                    fail[next[now][i]] = now == root ? root : next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
        return;
    }
    void solve()
    {
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i <= n; i++)
            for (int j = 0; j < L; j++)
                dps[i][j] = "";
        dp[0][0] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < L; j++) {
                if (dp[i][j] == -1)
                    continue;
                for (int t = 0; t < 26; t++) {
                    if (dp[i + 1][next[j][t]] == dp[i][j] + end[next[j][t]] &&
                        dps[i + 1][next[j][t]] > dps[i][j] + char(t + 'a')) //相等时比较字符串字典序
                    {
                        dps[i + 1][next[j][t]] = dps[i][j] + char(t + 'a');
                    }
                    if (dp[i + 1][next[j][t]] < dp[i][j] + end[next[j][t]]) //不等时取更优的解
                    {
                        dp[i + 1][next[j][t]] = dp[i][j] + end[next[j][t]];
                        dps[i + 1][next[j][t]] = dps[i][j] + (char) (t + 'a');
                    }
                }
            }
        int ans = 0;
        int ansi = 0, ansj = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < L; j++) {
                if (ans == dp[i][j] && dps[ansi][ansj] > dps[i][j]) {
                    ansi = i;
                    ansj = j;
                }
                if (ans < dp[i][j]) {
                    ans = dp[i][j];
                    ansi = i;
                    ansj = j;
                }
            }
        cout << dps[ansi][ansj] << endl;
        return;
    }
};

Trie AC;

int main()
{
    char ts[101][11];
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        AC.init();
        for (int i = 1; i <= m; i++) {
            scanf("%s", ts[i]);
        }
        for (int i = 1; i <= m; i++) {
            scanf("%d", w + i);
            AC.insert(ts[i], i);
        }
        AC.build();
        AC.solve();
    }
    return 0;
}

#else
#ifndef _t17pi_20200802_
#define _t17pi_20200802_
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

const int MAXN = 1 << 6;
const int MAXM = 1 << 7;
const int MAXSTRLEN = 1 << 4;
int T, N, M;
char words[MAXM][MAXSTRLEN];
int wvalue[MAXM];

namespace AC {
const char ori = 'a';
const int TRIE_WIDTH = 'z' - 'a' + 1;
const int MAXT = 1 << 10;
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT];
void init()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;
}
void insert(const char *s, int word_value)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = s[i] - ori;
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
        }
        u = trie[u][offset];
    }
    val[u] = word_value;
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
string query(int n)
{
    // typedef pair<int, char> from_type;    // state, symbol
    // typedef pair<int, from_type> dp_type; // current value, from where.
    string ret;
    // dp_type dp[n + 1][trie_cnt + 2];
    int dp[n + 1][trie_cnt + 2];
    char dps[n + 1][trie_cnt + 2][MAXN];
    memset(dp, -1, sizeof(dp));
    memset(dps, 0, sizeof(dps));

    int max_val = 0;
    dp[0][0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            if (dp[i][j] != -1) {
                for (int k = 0; k < TRIE_WIDTH; ++k) {
                    int u = trie[j][k];
                    if (dp[i + 1][u] < dp[i][j] + val[u] ||
                        (dp[i + 1][u] == dp[i][j] + val[u] &&
                         string(dps[i + 1][u]) > string(dps[i][j]).append(1, char(ori + k)))) {
                        _DEBUG_CMD({
                            printf("dp[%d][%d]:%d dp[%d][%d]:%d + val[%d]:%d, make change, "
                                   "dps[%d][%d]: %s, dps[%d][%d]:%s, max_val:%d, ret:%s\n",
                                   i + 1, u, dp[i + 1][u], i, j, dp[i][j], u, val[u], i + 1, u,
                                   dps[i + 1][u], i, j, dps[i][j], max_val, ret.c_str());
                        });
                        dp[i + 1][u] = dp[i][j] + val[u];
                        memcpy(dps[i + 1][u], dps[i][j], MAXN);
                        dps[i + 1][u][i] = char(ori + k);

                        /*
                        if (dp[i + 1][u] > max_val ||
                            (dp[i + 1][u] == max_val && (strlen(dps[i + 1][u]) < ret.size() ||
                                                         (strlen(dps[i + 1][u]) == ret.size() &&
                                                          string(dps[i + 1][u]) < ret)))) {
                            max_val = dp[i + 1][u];
                            ret = string(dps[i + 1][u]);
                        }
                        if (dp[i + 1][u] > max_val ||
                            (dp[i + 1][u] == max_val && string(dps[i + 1][u]) < ret)) {
                            max_val = dp[i + 1][u];
                            ret = dps[i + 1][u];
                        }
                        */
                    }
                }
            }
        }
    }
    // ** description does not match the problem solving steps
    max_val = 0;
    ret = "";
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            if ((max_val == dp[i][j] && string(dps[i][j]) < ret) || max_val < dp[i][j]) {
                max_val = dp[i][j];
                ret = dps[i][j];
            }
        }
    }
    return ret;
}
}; // namespace AC

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while (T--) {
        AC::init();
        scanf("%d%d", &N, &M);
        for (int i = 0; i < M; ++i) {
            scanf("%s", words[i]);
        }
        for (int i = 0; i < M; ++i) {
            scanf("%d", &wvalue[i]);
            AC::insert(words[i], wvalue[i]);
        }
        AC::build();

        string ret = AC::query(N);
        printf("%s\n", ret.c_str());
    }
    return 0;
};

#endif
#endif
