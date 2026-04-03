#if 0

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int inf = 0x3f3f3f3f;

struct Trie {
    int nxt[510][4], fail[510], end[510];
    int root, cnt;

    int newNode()
    {
        for (int i = 0; i < 4; i++)
            nxt[cnt][i] = -1;
        end[cnt++] = 0;
        return cnt - 1;
    }
    void init()
    {
        cnt = 0;
        root = newNode();
    }
    int getch(char ch)
    {
        if (ch == 'A')
            return 0;
        else if (ch == 'C')
            return 1;
        else if (ch == 'G')
            return 2;
        return 3;
    }
    void insert(char str[])
    {
        int len = strlen(str);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (nxt[now][getch(str[i])] == -1)
                nxt[now][getch(str[i])] = newNode();
            now = nxt[now][getch(str[i])];
        }
        end[now]++;
    }
    void build()
    {
        queue<int> q;
        fail[root] = root;
        for (int i = 0; i < 4; i++) {
            if (nxt[root][i] == -1)
                nxt[root][i] = root;
            else {
                fail[nxt[root][i]] = root;
                q.push(nxt[root][i]);
            }
        }

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            end[now] += end[fail[now]]; //好像每次都是这里
            for (int i = 0; i < 4; i++) {
                if (nxt[now][i] == -1)
                    nxt[now][i] = nxt[fail[now]][i];
                else {
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                    q.push(nxt[now][i]);
                }
            }
        }
    }
    int dp[510][11 * 11 * 11 * 11 + 5];
    int bit[4], num[4];
    int solve(char str[])
    {
        int len = strlen(str);
        memset(num, 0, sizeof(num));
        for (int i = 0; i < len; i++)
            num[getch(str[i])]++;
        bit[0] = (num[1] + 1) * (num[2] + 1) * (num[3] + 1);
        bit[1] = (num[2] + 1) * (num[3] + 1);
        bit[2] = (num[3] + 1);
        bit[3] = 1;
        memset(dp, -1, sizeof(dp));
        dp[root][0] = 0;
        for (int A = 0; A <= num[0]; A++)
            for (int B = 0; B <= num[1]; B++)
                for (int C = 0; C <= num[2]; C++)
                    for (int D = 0; D <= num[3]; D++) {
                        int s = A * bit[0] + B * bit[1] + C * bit[2] + D * bit[3];
                        for (int i = 0; i < cnt; i++)
                            if (dp[i][s] >= 0) {
                                for (int k = 0; k < 4; k++) {
                                    if (k == 0 && A == num[0])
                                        continue;
                                    if (k == 1 && B == num[1])
                                        continue;
                                    if (k == 2 && C == num[2])
                                        continue;
                                    if (k == 3 && D == num[3])
                                        continue;
                                    dp[nxt[i][k]][s + bit[k]] =
                                        max(dp[nxt[i][k]][s + bit[k]], dp[i][s] + end[nxt[i][k]]);
                                }
                            }
                    }

        int ans = 0;
        int status = num[0] * bit[0] + num[1] * bit[1] + num[2] * bit[2] + num[3] * bit[3];
        for (int i = 0; i < cnt; i++)
            ans = max(ans, dp[i][status]);
        return ans;
    }
} ac;
char str[50];

int main()
{
    int n, cas = 1;
    while (scanf("%d", &n) != EOF && n) {
        ac.init();
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            ac.insert(str);
        }

        ac.build();
        scanf("%s", str);
        printf("Case %d: %d\n", cas++, ac.solve(str));
    }
    return 0;
}
#else
#ifndef _t17pl_20200803_
#define _t17pl_20200803_
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
char str[MAXN];
int N;

struct State {
    State() : a(0), t(0), g(0), c(0){};
    State(const State &s) = default;
    State &operator=(const State &s) = default;
    ~State() = default;
    State operator+(const State &s) const { return State(a + s.a, t + s.t, g + s.g, c + s.c); }
    State operator-(const State &s) const { return State(a - s.a, t - s.t, g - s.g, c - s.c); }
    bool operator<(const State &s) const
    {
        if (a != s.a) {
            return a < s.a;
        }
        if (t != s.t) {
            return t < s.t;
        }
        if (g != s.g) {
            return g < s.g;
        }
        if (c != s.c) {
            return c < s.c;
        }
        return false;
    }
    bool valid() const { return a >= 0 && t >= 0 && g >= 0 && c >= 0; }
    State(char a, char t, char g, char c) : a(a), t(t), g(g), c(c){};
    char a, t, g, c;
};
ostream &operator<<(ostream &oss, const State &s)
{
    // oss << "a: " << s.a << " t: " << s.t << " g: " << s.g << " c: " << s.c;
    oss << s.a << ',' << s.t << ',' << s.g << ',' << s.c;
    return oss;
}
const State A(1, 0, 0, 0), T(0, 1, 0, 0), G(0, 0, 1, 0), C(0, 0, 0, 1);
const State sa[] = {A, T, G, C};
const char ca[] = {'A', 'T', 'G', 'C'};

namespace AC {
const int TRIE_WIDTH = 1 << 2;
const int MAXT = 1 << 9;
int cmap[1 << 8];
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT];
// int end[MAXT], last_match[MAXT];
// int hits[MAXT][2];

void init()
{
    // memset(last_match, -1, sizeof(last_match));
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    // memset(hits, 0, sizeof(hits));
    memset(cmap, 0, sizeof(cmap));
    cmap['A'] = 0;
    cmap['T'] = 1;
    cmap['G'] = 2;
    cmap['C'] = 3;
    // memset(end, 0, sizeof(end));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;
}
void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        // int offset = s[i] - ori;
        int offset = cmap[s[i]];
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
            // val[trie[u][offset]] = val[u] + 1;
        }
        u = trie[u][offset];
    }
    // end[idx] = u;
    ++val[u];
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
}
/*
int query_tle(const char *s)
{ // 0 means overlapping is allowed, 1 means not.
    int slen = strlen(s);
    assert(slen <= 40);
    long int state_cnt = 1L << slen;
    typedef map<long int, int> dt;
    dt dp[slen + 1][trie_cnt + 2];
    dp[0][0][0] = 0;
    for (int i = 0; i < slen; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            for (int j = 0; j <= trie_cnt; ++j) {
                for (dt::iterator ki = dp[i][j].begin(); ki != dp[i][j].end(); ++ki) {
                    long int k = ki->first;
                    int old_cnt = ki->second;
                    for (int l = 0; l < slen; ++l) {
                        bool used_flag = ((1L << l) & k);
                        int nxt_state_represent = ((1L << l) | k);
                        int nxt_state_id = trie[j][cmap[s[l]]];
                        dt &nxt_dp = dp[i + 1][nxt_state_id];
                        if (!used_flag) {
                            if (nxt_dp.find(nxt_state_represent) != nxt_dp.end()) {
                                nxt_dp[nxt_state_represent] = max(nxt_dp[nxt_state_represent],
                                                                  dp[i][j][k] + val[nxt_state_id]);
                            }
                            else {
                                nxt_dp[nxt_state_represent] = dp[i][j][k] + val[nxt_state_id];
                            }
                        }
                    }
                }
            }
        }
    }

    int ret = 0;
    for (int i = 0; i <= trie_cnt; ++i) {
        // ret = max(ret, dp[slen][i][state_cnt - 1]);
        // ret = max(ret, dp[i]);
        ret = max(ret, dp[slen][i][state_cnt - 1]);
    }
    return ret;
}
int query_mle(const char *s)
{ // 0 means overlapping is allowed, 1 means not.
    int slen = strlen(s);
    State si;
    for (int i = 0; s[i]; ++i) {
        switch (s[i]) {
            case 'A':
                si.a++;
                break;
            case 'T':
                si.t++;
                break;
            case 'G':
                si.g++;
                break;
            case 'C':
                si.c++;
                break;
        }
    }
    _DEBUG_CMD({
        cout << "S: " << s << endl;
        cout << "si: " << si << endl;
    });
    typedef map<State, int> dt;
    dt dp[slen + 1][trie_cnt + 2];
    dp[0][0][si] = 0;
    for (int i = 0; i < slen; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            for (dt::iterator ki = dp[i][j].begin(); ki != dp[i][j].end(); ++ki) {
                State ks = ki->first;
                int old_cnt = ki->second;

                for (int k = 0; k < TRIE_WIDTH; ++k) {
                    State ns = ks - sa[k];
                    if (ns.valid()) {
                        int nxt_state = trie[j][cmap[ca[k]]];
                        dt &nxt_dp = dp[i + 1][nxt_state];
                        if (nxt_dp.find(ns) == nxt_dp.end()) {
                            nxt_dp[ns] = old_cnt + val[nxt_state];
                        }
                        else {
                            nxt_dp[ns] = max(nxt_dp[ns], old_cnt + val[nxt_state]);
                        }
                    }
                }
            }
        }
    }

    int ret = 0;
    State sf(0, 0, 0, 0);
    _DEBUG_CMD({ cout << "sf: " << sf << endl; });
    for (int i = 0; i <= trie_cnt; ++i) {
        if (dp[slen][i].find(sf) != dp[slen][i].end()) {
            ret = max(ret, dp[slen][i][sf]);
        }
    }
    _DEBUG_CMD({
        for (int i = 0; i <= trie_cnt; ++i) {
            cout << "state in trie_node: " << i << endl;
            for (dt::iterator ki = dp[slen][i].begin(); ki != dp[slen][i].end(); ++ki) {
                cout << "state: " << ki->first << " cost: " << ki->second << ' ';
            }
            cout << endl;
        }
    });
    return ret;
}
*/
int query_tle_mle(const char *s)
{ // 0 means overlapping is allowed, 1 means not.
    int slen = strlen(s);
    State si;
    for (int i = 0; s[i]; ++i) {
        switch (s[i]) {
            case 'A':
                si.a++;
                break;
            case 'T':
                si.t++;
                break;
            case 'G':
                si.g++;
                break;
            case 'C':
                si.c++;
                break;
        }
    }
    _DEBUG_CMD({
        cout << "S: " << s << endl;
        cout << "si: " << si << endl;
    });
    typedef map<State, int> dt;
    vector<dt> dp_new(trie_cnt + 2);
    vector<dt> dp_old(trie_cnt + 2);
    dp_old[0][si] = 0;
    for (int i = 0; i < slen; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            for (dt::iterator ki = dp_old[j].begin(); ki != dp_old[j].end(); ++ki) {
                State ks = ki->first;
                int old_cnt = ki->second;

                for (int k = 0; k < TRIE_WIDTH; ++k) {
                    State ns = ks - sa[k];
                    if (ns.valid()) {
                        int nxt_state = trie[j][cmap[ca[k]]];
                        dt &nxt_dp = dp_old[nxt_state];
                        if (nxt_dp.find(ns) == nxt_dp.end()) {
                            nxt_dp[ns] = old_cnt + val[nxt_state];
                        }
                        else {
                            nxt_dp[ns] = max(nxt_dp[ns], old_cnt + val[nxt_state]);
                        }
                    }
                }
            }
        }
        dp_new = dp_old;
    }

    int ret = 0;
    State sf(0, 0, 0, 0);
    _DEBUG_CMD({ cout << "sf: " << sf << endl; });
    for (int i = 0; i <= trie_cnt; ++i) {
        if (dp_new[i].find(sf) != dp_new[i].end()) {
            ret = max(ret, dp_new[i][sf]);
        }
    }
    _DEBUG_CMD({
        for (int i = 0; i <= trie_cnt; ++i) {
            cout << "state in trie_node: " << i << endl;
            for (dt::iterator ki = dp[slen][i].begin(); ki != dp[slen][i].end(); ++ki) {
                cout << "state: " << ki->first << " cost: " << ki->second << ' ';
            }
            cout << endl;
        }
    });
    return ret;
    // return 0;
}
int query(const char *s)
{ // 0 means overlapping is allowed, 1 means not.
    int slen = strlen(s);
    State si;
    for (int i = 0; s[i]; ++i) {
        switch (s[i]) {
            case 'A':
                si.a++;
                break;
            case 'T':
                si.t++;
                break;
            case 'G':
                si.g++;
                break;
            case 'C':
                si.c++;
                break;
        }
    }
    _DEBUG_CMD({
        cout << "S: " << s << endl;
        cout << "si: " << si << endl;
    });
    int b1 = (si.c + 1) * (si.g + 1) * (si.t + 1);
    int b2 = (si.c + 1) * (si.g + 1);
    int b3 = (si.c + 1);
    int b4 = 1;
    const int aa_max[] = {si.a, si.t, si.g, si.c};
    const int ba[] = {b1, b2, b3, b4};
    const char ca[] = {'A', 'T', 'G', 'C'};
    int maxs = b1 * (si.a + 1);
    vector<int> v(maxs, -1);
    vector<vector<int>> vv(trie_cnt + 2, v);
    // vector<vector<vector<int>>> dp(slen + 1, vv);
    // dp[0][0][0] = 0;
    vv[0][0] = 0;
    // for (int i = 0; i < slen; ++i) {
    for (int k = 0; k < maxs; ++k) {
        for (int j = 0; j <= trie_cnt; ++j) {
            if (vv[j][k] != -1) {
                int a1 = k / b1;                            // A
                int a2 = (k - a1 * b1) / b2;                // T
                int a3 = (k - a1 * b1 - a2 * b2) / b3;      // G
                int a4 = (k - a1 * b1 - a2 * b2 - a3 * b3); // C
                const int aa[] = {a1, a2, a3, a4};
                for (int l = 0; l < TRIE_WIDTH; ++l) {
                    if (aa[l] + 1 <= aa_max[l]) {
                        int offset = cmap[ca[l]];
                        int nt = trie[j][offset];
                        int ns = k + ba[l];
                        _DEBUG_CMD(
                            printf("aa[%d]:%d aa_max[%d]:%d j:%d nt:%d k:%d ns:%d ca[%d]:%d, "
                                   "cmap[%d]:%d, vv[%d][%d]:%d, vv[%d][%d]:%d val[%d]:%d\n",
                                   l, aa[l], l, aa_max[l], j, nt, k, ns, l, ca[l], ca[l],
                                   cmap[ca[l]], nt, ns, vv[nt][ns], j, k, vv[j][k], nt, val[nt]));
                        vv[nt][ns] = max(vv[nt][ns], vv[j][k] + val[nt]);
                    }
                }
            }
        }
    }
    //}

    _DEBUG_CMD({
        printf("val:\n");
        for (int i = 0; i <= trie_cnt; ++i) {
            printf("%d ", val[i]);
        }
        printf("\ndp, maxs:%d, slen:%d:", maxs, slen);
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= maxs; ++j) {
                printf("dp[%d][%d]:%d ", i, j, vv[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    });
    // int whole = si.a * b1 + si.t * b2 + si.g * b3 + si.c;
    int ret = 0;
    for (int i = 0; i <= trie_cnt; ++i) {
        ret = max(ret, vv[i][maxs - 1]);
    }
    return ret;
    // return 0;
}
}; // namespace AC

int main(int argc, char **argv)
{
    int case_cnt = 0;
    char s1[1 << 4];
    while (~scanf("%d", &N) && N) {
        AC::init();
        for (int i = 0; i < N; ++i) {
            scanf("%s", s1);
            AC::insert(s1);
        }
        AC::build();
        scanf("%s", str);
        printf("Case %d: %d\n", ++case_cnt, AC::query(str));
    }
    return 0;
};

#endif
#endif
