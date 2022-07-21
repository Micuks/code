#if 0
//============================================================================
// Name        : ZOJ.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Trie {
    int next[2010][2], fail[2010];
    bool end[2010];
    int root, L;
    int newnode()
    {
        for (int i = 0; i < 2; i++)
            next[L][i] = -1;
        end[L++] = false;
        return L - 1;
    }
    void init()
    {
        L = 0;
        root = newnode();
    }
    void insert(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (next[now][buf[i] - '0'] == -1)
                next[now][buf[i] - '0'] = newnode();
            now = next[now][buf[i] - '0'];
        }
        end[now] = true;
    }
    void build()
    {
        queue<int> Q;
        fail[root] = root;
        for (int i = 0; i < 2; i++)
            if (next[root][i] == -1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            if (end[fail[now]])
                end[now] = true;
            for (int i = 0; i < 2; i++)
                if (next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
};
Trie ac;

int bcd[2010][10];
int change(int pre, int num)
{
    if (ac.end[pre])
        return -1;
    int cur = pre;
    for (int i = 3; i >= 0; i--) {
        if (ac.end[ac.next[cur][(num >> i) & 1]])
            return -1;
        cur = ac.next[cur][(num >> i) & 1];
    }
    return cur;
}
void pre_init()
{
    for (int i = 0; i < ac.L; i++)
        for (int j = 0; j < 10; j++)
            bcd[i][j] = change(i, j);
}
const int MOD = 1000000009;
long long dp[210][2010];
int bit[210];

long long dfs(int pos, int s, bool flag, bool z)
{
    if (pos == -1)
        return 1;
    if (!flag && dp[pos][s] != -1)
        return dp[pos][s];
    long long ans = 0;
    if (z) {
        ans += dfs(pos - 1, s, flag && bit[pos] == 0, true);
        ans %= MOD;
    }
    else {
        if (bcd[s][0] != -1)
            ans += dfs(pos - 1, bcd[s][0], flag && bit[pos] == 0, false);
        ans %= MOD;
    }
    int end = flag ? bit[pos] : 9;
    for (int i = 1; i <= end; i++) {
        if (bcd[s][i] != -1) {
            ans += dfs(pos - 1, bcd[s][i], flag && i == end, false);
            ans %= MOD;
        }
    }
    if (!flag && !z)
        dp[pos][s] = ans;
    return ans;
}

long long calc(char s[])
{
    int len = strlen(s);
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < len; i++)
        bit[i] = s[len - 1 - i] - '0';
    return dfs(len - 1, 0, 1, 1);
}
char str[210];
int main()
{
    //    freopen("in.txt","r",stdin);
    //    freopen("out.txt","w",stdout);
    int T;
    scanf("%d", &T);
    int n;
    while (T--) {
        ac.init();
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            ac.insert(str);
        }
        ac.build();
        pre_init();
        int ans = 0;
        scanf("%s", str);
        int len = strlen(str);
        for (int i = len - 1; i >= 0; i--) {
            if (str[i] > '0') {
                str[i]--;
                break;
            }
            else
                str[i] = '9';
        }
        ans -= calc(str);
        // printf("calc1: %d\n", ans);
        ans %= MOD;
        scanf("%s", str);
        ans += calc(str);
        // printf("calc1: %d\n", ans);
        ans %= MOD;
        if (ans < 0)
            ans += MOD;
        printf("%d\n", ans);
    }
    return 0;
}

#else
#ifndef _t17pn_20200810_
#define _t17pn_20200810_
#include <algorithm>
#include <assert.h>
#include <chrono>
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
#include <unordered_set>
#include <vector>
namespace std {
template <> struct hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> p) const
    {
        return (hash<int>()(p.first) ^ hash<int>()(p.second));
    }
};
}; // namespace std
using namespace std;
#define set unordered_set
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

const int MAXAB = 1 << 8;
const int mod = 1e9 + 9;
int T, N;
char codes[1 << 6];
char A[MAXAB], B[MAXAB];
namespace AC {
const int MAXT = 1 << 12;
const int TRIE_WIDTH = 1 << 1;
const char ori = '0';
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT];
const int MAXBCD = 10;
const char bcd[MAXBCD][5] = {"0000", "0001", "0010", "0011", "0100",
                             "0101", "0110", "0111", "1000", "1001"};
string mapstr[MAXT];
int state_transform_table[MAXT][MAXBCD];
void init()
{
    memset(state_transform_table, -1, sizeof(state_transform_table));
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;
    _DEBUG_CMD(mapstr[0] = "";);
}
void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = s[i] - ori;
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
            _DEBUG_CMD(mapstr[trie[u][offset]] = mapstr[u] + s[i];);
        }
        u = trie[u][offset];
    }
    val[u] = 1;
    _DEBUG_CMD(mapstr[u] = s;);
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
void dump_tree()
{
    DEBUG_CMD({
        printf("dumping the trie tree:\n");
        for (int i = 0; i <= trie_cnt; ++i) {
            printf("node:%d val:%d prefix:%s\n", i, val[i], mapstr[i].c_str());
        }
        printf("dumping the transformation matrix:\n");
        for (int i = 0; i <= trie_cnt; ++i) {
            printf("node %d: ", i);
            for (int j = 0; j < MAXBCD; ++j) {
                printf("%d ", state_transform_table[i][j]);
            }
            printf("\n");
        }
    });
}
inline void add(int &a, const int &b) { a = (a == -1 ? b : a + b) % mod; }
int find(const char *str, int sidx, int eidx)
{
    int ret = 0;
    int search_len = eidx - sidx;
    if (search_len == 0) {
        _DEBUG_CMD(printf("get a find of zero-search_len: %s return 0\n", str + sidx));
        return ret;
    }
    int iter_dp[search_len + 1][trie_cnt + 1];
    // int dp[search_len + 1][trie_cnt + 1];
    int dpup[search_len + 1][trie_cnt + 1];

    memset(iter_dp, 0, sizeof(iter_dp));
    // memset(dp, -1, sizeof(dp));
    memset(dpup, 0, sizeof(dpup));
    typedef pair<int, int> layer_state_type;
    typedef layer_state_type lst;
    typedef pair<lst, int> lstt;
    // dp[0][0] = 1;
    stack<lst> q;
    set<lst> sts;
    sts.insert(lst(0, 0));
    iter_dp[0][0] = 1;

    for (int i = 1; i < search_len; ++i) {
        set<lst> newsts;
        for (set<lst>::iterator k = sts.begin(); k != sts.end(); ++k) {
            q.push(*k);
            const int &layer = k->first;
            const int &state = k->second;
            const int start_idx = (layer == 0 ? 1 : 0);
            for (int j = start_idx; j < MAXBCD; ++j) {
                int dst_state = state_transform_table[state][j];
                if (dst_state != -1) {
                    newsts.insert(lst(i, dst_state));
                    add(iter_dp[i][dst_state], iter_dp[layer][state]);
                    add(ret, iter_dp[layer][state]);
                }
            }
        }
        sts = newsts;
    }

    /*
    // init base case
    // const int last_upper_limit = str[eidx - 1] - ori;
    for (int i = 0; i < MAXBCD; ++i) {
        for (set<lst>::iterator iter = sts.begin(); iter != sts.end(); ++iter) {
            const int &layer = iter->first;
            const int &state = iter->second;
            // add(dp[layer][state], 1); // !!!IMPORTANT!!!
            dp[layer][state] = 1;
        }
    }
    while (!q.empty()) {
        lst layer_state = q.top();
        q.pop();
        const int &layer = layer_state.first;
        const int &state = layer_state.second;
        // const int &in_edge = layer_state.second;
        _DEBUG_CMD(printf("stack layer:%d state:%d\n", layer, state));
        for (int i = 0; i < MAXBCD; ++i) {
            int dst_state = state_transform_table[state][i];
            // int upper_limit = str[layer - 1 + sidx] - ori;
            if (dst_state != -1) {
                add(dp[layer][state], dp[layer + 1][dst_state]);
                _DEBUG_CMD(printf("add dp[%d][%d]:%d from dp[%d][%d]:%d\n", layer, state,
                                  dp[layer][state], layer + 1, dst_state,
                                  dp[layer + 1][dst_state]));
            }
        }
    }
    */

    _DEBUG_CMD(printf("ret after being assigned to iter_dp arr: %d\n", ret));
    sts.clear();
    vector<int> eqstat;
    eqstat.resize(1 << 8);
    // eqstat.push_back(0);
    eqstat[0] = 0;
    dpup[0][0] = 1;
    sts.insert(lst(0, 0));

    for (int i = 0; i < search_len; ++i) {
        set<lst> newsts;
        const int upper_limit = str[sidx + i] - ori;
        const int st_idx = (i == 0 ? 1 : 0);
        const int ed_idx = (i == 0 ? upper_limit + 1 : MAXBCD);
        for (set<lst>::iterator iter = sts.begin(); iter != sts.end(); ++iter) {
            const int &layer = iter->first;
            const int &state = iter->second;
            // for (int j = st_idx; j < ed_idx; ++j) {
            for (int j = st_idx; j < MAXBCD; ++j) {
                int dst_state = state_transform_table[state][j];
                if (dst_state != -1) {
                    _DEBUG_CMD({
                        if (i == 2)
                            printf("state_trans_table[%d][%d]:%d:\n", state, j, dst_state);
                    });
                    if (j <= upper_limit) {
                        dpup[layer + 1][dst_state] =
                            (dpup[layer + 1][dst_state] + dpup[layer][state]) % mod;
                        DEBUG_CMD({
                            printf("dpup[%d][%d]:%d += dpup[%d][%d]:%d with (%d)<=(%d)\n",
                                   layer + 1, dst_state, dpup[layer + 1][dst_state], layer, state,
                                   dpup[layer][state], j, upper_limit);
                        });
                        if (j == upper_limit && state == eqstat[layer]) {
                            // eqstat.push_back(dst_state);
                            eqstat[layer + 1] = dst_state;
                        }
                    }
                    else {
                        if (state != eqstat[layer]) {
                            DEBUG_CMD({
                                printf(
                                    "dpup[%d][%d]:%d += dpup[%d][%d]:%d with no addon from j:%d \n",
                                    layer + 1, dst_state, dpup[layer + 1][dst_state], layer, state,
                                    dpup[layer][state], j);
                            });
                            dpup[layer + 1][dst_state] =
                                (dpup[layer + 1][dst_state] + dpup[layer][state]) % mod;
                        }
                        else {
                            // there is one and only one path which prefix has exact the same
                            // numbers as upper limit in str, thus - 1
                            int addon = dpup[layer][state] - 1;
                            DEBUG_CMD({
                                printf("dpup[%d][%d]:%d += dpup[%d][%d]:%d - 1, %d from j:%d "
                                       "state:%d hit eqstat[%d]:%d\n",
                                       layer + 1, dst_state, dpup[layer + 1][dst_state], layer,
                                       state, dpup[layer][state], addon, j, state, layer,
                                       eqstat[layer]);
                            });
                            if (addon > 0) {
                                dpup[layer + 1][dst_state] =
                                    (dpup[layer + 1][dst_state] + addon) % mod;
                            }
                        }
                    }
                    newsts.insert(lst(layer + 1, dst_state));
                }
            }
        }
        sts = newsts;
    }
    _DEBUG_CMD({
        /*
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j < MAXBCD; ++j) {
                printf("%d ", state_transform_table[i][j]);
            }
            printf("\n");
        }
        */
        printf("sts.size():%ld ", sts.size());
        printf("eqstate: ");
        for (int i = 0; i < eqstat.size(); ++i) {
            printf("%d ", eqstat[i]);
        }
        printf("\n");
    });
    for (set<lst>::iterator iter = sts.begin(); iter != sts.end(); ++iter) {
        const int &layer = iter->first;
        const int &state = iter->second;
        _DEBUG_CMD(printf("final acc dpup[%d][%d]:%d\n", layer, state, dpup[layer][state]));
        ret = (ret + dpup[layer][state]) % mod;
    }
    _DEBUG_CMD({
        // int dp[search_len + 1][trie_cnt + 1];
        printf("ret after tightened accumulating in dp arr:%d\n", ret);
        printf("dp arr, search_len:%d, trie_cnt:%d:\n", search_len, trie_cnt);
        for (int i = 0; i < search_len; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
    });
    _DEBUG_CMD({
        // int dpup[search_len + 1][MAXBCD];
        printf("dpup arr, search_len:%d, MAXBCD:%d:\n", search_len, MAXBCD);
        for (int i = 0; i <= search_len; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%d ", dpup[i][j]);
            }
            printf("\n");
        }
    });
    DEBUG_CMD(printf("find on \"%s\" val: %d, q.size():%lu\n", str + sidx, ret, q.size()));
    return ret;
}

int query(const char *s)
{
    // acm = build_matrix();
    int slen = strlen(s);
    int sidx = 0;
    for (int i = 0; i < slen; ++i) {
        if (s[i] != '0') {
            sidx = i;
            break;
        }
    }

    return find(s, sidx, slen);
}
}; // namespace AC

void dec(char *s)
{
    int slen = strlen(s);
    for (int i = slen - 1; i >= 0; --i) {
        if (s[i] == '0') {
            s[i] = '9';
        }
        else {
            --s[i];
            break;
        }
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while (T--) {
        AC::init();
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%s", codes);
            AC::insert(codes);
        }
        scanf("%s%s", A, B);
        _DEBUG_CMD(printf("A:%s, B:%s\n", A, B));
        AC::build();
        AC::dump_tree();
        dec(A);
        int a = AC::query(A);
        int b = AC::query(B);
        printf("%d\n", (b - a + mod) % mod);
    }
    return 0;
};

#endif
#endif
