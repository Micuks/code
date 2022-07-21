#if 0
#warning compling the old code
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
#define MAXNODE 2
#define MAXSIZE 300000
#define INF (1 << 29)
//#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, issub[20], len;
string str[20], virus;

struct ACnode {

    int flag, in;
    ACnode *next[MAXNODE], *fail, *father;
};
struct Auto_AC {

    int Index[20], ans;
    int dist[100][100], spfaqu[MAXSIZE];
    int temp[MAXSIZE], in[MAXSIZE];
    int total, head, tail, dp[20][2000];
    ACnode *p, *q, *root;
    ACnode *qu[MAXSIZE], tree[MAXSIZE];

    ACnode *CreateNode()
    {

        tree[total].flag = 0;
        tree[total].in = total;
        tree[total].next[0] = NULL;
        tree[total].next[1] = NULL;
        return &tree[total++];
    }
    void Initial()
    {

        total = 0, ans = INF;
        root = CreateNode();
        root->fail = root;
        for (int i = 0; i < n; ++i) {

            for (int j = 0; j < (1 << n); ++j)
                dp[i][j] = INF;
            dp[i][1 << i] = str[i].size();
        }
    }
    int GetHash(char c) { return c - '0'; }
    void Insert(string str, int in, int kind)
    {

        p = root;
        for (int i = 0; str[i]; ++i) {

            int k = GetHash(str[i]);
            if (p->next[k] == NULL)
                p->next[k] = CreateNode();
            p = p->next[k];
        }

        if (kind == 1)
            p->flag = 1;
        else
            Index[in] = p->in;
    }
    void Build_AC()
    {

        qu[head++] = root;
        while (tail < head) {

            p = qu[tail++];
            for (int k = 0; k < MAXNODE; ++k)
                if (p->next[k]) {

                    if (p == root)
                        p->next[k]->fail = root;
                    else
                        p->next[k]->fail = p->fail->next[k];
                    qu[head++] = p->next[k];
                    p->next[k]->flag |= p->next[k]->fail->flag;
                }
                else {

                    if (p == root)
                        p->next[k] = root;
                    else
                        p->next[k] = p->fail->next[k];
                }
        }
    }
    void Spfa_ForDist(int s)
    {

        int i, j, k, u, v, ndis;
        int head = 0, tail = 0;

        temp[s] = 0;
        spfaqu[head++] = s, in[s] = 1;

        while (tail < head) {

            u = spfaqu[tail++];
            in[u] = 0;
            for (k = 0; k < MAXNODE; ++k)
                if (!tree[u].next[k]->flag) {

                    ndis = temp[u] + 1;
                    v = tree[u].next[k]->in;
                    if (ndis < temp[v]) {

                        temp[v] = ndis;
                        if (in[v] == 0)
                            spfaqu[head++] = v, in[v] = 1;
                    }
                }
        }
    }
    void CountDist()
    {

        int i, j;
        for (i = 0; i < n; ++i) {

            for (j = 0; j <= total; ++j)
                in[j] = 0, temp[j] = INF;
            Spfa_ForDist(Index[i]);
            for (j = 0; j < n; ++j)
                dist[i][j] = temp[Index[j]];
        }
    }
    int Solve_DP()
    {

        int i, j, k, nst, ndis;

        for (i = 1; i < (1 << n); ++i)
            for (j = 0; j < n; ++j)
                if (i & (1 << j))
                    for (k = 0; k < n; ++k)
                        if (!(i & (1 << k)) && dist[j][k] != INF) {

                            nst = i | (1 << k);
                            ndis = dp[j][i] + dist[j][k];
                            dp[k][nst] = min(dp[k][nst], ndis);
                        }
        printf("n:%d, (1<<%d):%d\n", n, n, 1 << n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < (1 << n); ++j) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
        for (i = 0; i < n; ++i)
            ans = min(ans, dp[i][(1 << n) - 1]);
        return ans;
    }
} AC;
int cmp(string s1, string s2) { return s1.size() > s2.size(); }
void Solve_Sub()
{

    int i, j, k = n;

    sort(str, str + n, cmp);
    memset(issub, 0, sizeof(issub));
    for (i = 0; i < n; ++i)
        for (j = i + 1; j <= n; ++j)
            if (str[i].find(str[j]) != -1)
                issub[j] = 1;
    for (n = 0, i = 0; i < k; ++i)
        if (issub[i] == 0)
            str[n++] = str[i];
}

int main()
{
    int i, j, k;

    while (cin >> n >> m, n + m) {
        printf("__LINE__:%d n:%d\n", __LINE__, n);
        for (i = 0; i < n; ++i)
            cin >> str[i];
        Solve_Sub(), AC.Initial();
        printf("__LINE__:%d n:%d\n", __LINE__, n);
        for (i = 0; i < n; ++i)
            AC.Insert(str[i], i, 0);
        for (i = 0; i < m; ++i)
            cin >> virus, AC.Insert(virus, i, 1);

        AC.Build_AC();
        printf("__LINE__:%d n:%d\n", __LINE__, n);
        AC.CountDist();
        printf("__LINE__:%d n:%d\n", __LINE__, n);
        printf("%d\n", AC.Solve_DP());
    }
}

#endif
#if 0
#warning compiling the newest example code
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define Maxn 60010
#define Maxl 1200
#define Mn 20
#define INF 0xfffffff
#define Mod 20090717

int n, m;
char s[Maxl];

struct node {
    // int cnt;
    int fail, mark;
    int son[3];
} t[Maxn];
int tot;
// int num;
int p[Mn], sl[Mn];

void upd(int x)
{
    // t[x].cnt=0;
    t[x].mark = 0;
    memset(t[x].son, 0, sizeof(t[x].son));
}

int mymin(int x, int y) { return x < y ? x : y; }
int mymax(int x, int y) { return x > y ? x : y; }

void read_trie(int tk)
{
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    if (tk != -1)
        sl[tk] = len;
    int now = 0;
    for (int i = 1; i <= len; i++) {
        int ind = s[i] - '0' + 1;
        if (!t[now].son[ind]) {
            t[now].son[ind] = ++tot;
            upd(tot);
        }
        now = t[now].son[ind];
        if (i == len) {
            if (tk == -1)
                t[now].mark = -1;
            else
                t[now].mark = tk, p[tk] = now;
        }
    }
}

queue<int> q;
void build_AC()
{
    while (!q.empty())
        q.pop();
    q.push(0);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 1; i <= 2; i++) {
            if (t[x].son[i]) {
                t[t[x].son[i]].fail = x ? t[t[x].fail].son[i] : 0;
                q.push(t[x].son[i]);
            }
            else
                t[x].son[i] = t[t[x].fail].son[i];
        }
        // t[x].mark+=t[t[x].fail].mark;
    }
}

int dis[Mn][Maxn];
bool inq[Mn];
void spfa(int x)
{
    while (!q.empty())
        q.pop();
    memset(dis[x], 63, sizeof(dis[x]));
    memset(inq, 0, sizeof(inq));
    dis[x][p[x]] = 0;
    q.push(p[x]);
    inq[p[x]] = 1;
    while (!q.empty()) {
        int now = q.front();
        for (int i = 1; i <= 2; i++)
            if (t[t[now].son[i]].mark != -1) {
                if (dis[x][t[now].son[i]] > dis[x][now] + 1) {
                    dis[x][t[now].son[i]] = dis[x][now] + 1;
                    if (!inq[t[now].son[i]]) {
                        inq[t[now].son[i]] = 1;
                        q.push(t[now].son[i]);
                    }
                }
            }
        q.pop();
        inq[now] = 0;
    }
}
void init()
{
    tot = 0;
    upd(0);
    for (int i = 1; i <= n; i++) {
        read_trie(i);
    }
    for (int i = 1; i <= m; i++)
        read_trie(-1);
    build_AC();
    for (int i = 1; i <= n; i++) {
        spfa(i);
    }
}

bool check(int x, int y, int z)
{
    // if(x==0&&y==0&&z==0) return 1;
    // if(y==0||z==0) return 0;
    if (((1 << y - 1) & z) == 0)
        return 0;
    int h = 0;
    for (int i = 1; i <= n; i++) {
        if ((1 << i - 1) & z)
            h++;
    }
    if (h == x)
        return 1;
    return 0;
}

int f[Maxl][Mn];
void dp()
{
    memset(f, 63, sizeof(f));
    // f[0][0]=0;
    for (int i = 1; i <= n; i++)
        f[1 << i - 1][i] = sl[i];
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= (1 << n) - 1; k++)
                if (check(i, j, k)) {
                    if (f[k][j] > INF)
                        continue;
                    for (int l = 1; l <= n; l++)
                        if ((k & (1 << l - 1)) == 0)
                            f[k + (1 << l - 1)][l] =
                                mymin(f[k + (1 << l - 1)][l], f[k][j] + dis[j][p[l]]);
                }
    int ans = INF;
    for (int i = 1; i <= n; i++)
        ans = mymin(ans, f[(1 << n) - 1][i]);
    printf("%d\n", ans);
}

int main()
{
    int kase = 0;
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0)
            break;
        init();
        dp();
    }
    return 0;
}

#else
#warning compiling my own code
#ifndef _t17pm_20200807_
#define _t17pm_20200807_
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

const int MAXN = 1 << 4;
const int MAXRL = 1 << 10;
const int MAXVT = 6e4 + 13;
const int MAXRT = 1 << 14;
char resources[MAXN][MAXRL];
int n, m;

template <int NODE_CNT> struct AC {
    // const int MAXVT = 5e4 + 21;
    static const int MAXVT = NODE_CNT;
    static const int TRIE_WIDTH = 2;
    static const char ori = '0';
    int trie[MAXVT][TRIE_WIDTH], trie_cnt, res_cnt;
    int res_idx[MAXN], dist[MAXN][MAXVT], res_len[MAXN];
    int fail[MAXVT], virus[MAXVT]; //, res_id[MAXVT];
    AC() { init(); }
    void init()
    {
        memset(res_idx, 0, sizeof(res_idx));
        // memset(res_id, 0, sizeof(res_id));
        memset(dist, 0x3F, sizeof(dist));
        memset(virus, 0, sizeof(virus));
        memset(trie, 0, sizeof(trie));
        memset(fail, 0, sizeof(fail));
        trie_cnt = 0;
        res_cnt = 0;
    }
    void insert(const char *s, int type)
    {
        int u = 0;
        for (int i = 0; s[i] != 0; ++i) {
            int offset = s[i] - ori;
            if (!trie[u][offset]) {
                trie[u][offset] = ++trie_cnt;
            }
            u = trie[u][offset];
        }
        if (type == 0) {
            virus[u] = 1;
        }
        else {
            // res_id[u] = type;
            res_len[res_cnt] = strlen(s);
            res_idx[res_cnt] = u;
            ++res_cnt;
        }
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

            virus[u] += virus[fail[u]];

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
    void spfa(int x)
    {
        queue<int> q;
        _DEBUG_CMD({ printf("spfa on resources:%d, trie_node:%d\n", x, res_idx[x]); });
        int start = res_idx[x];
        dist[x][start] = 0;
        q.push(start);
        char visited[trie_cnt + 2];
        memset(visited, 0, sizeof(visited));
        visited[start] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < TRIE_WIDTH; ++i) {
                int nd = trie[u][i];
                if (dist[x][nd] > dist[x][u] + 1 && virus[nd] == 0) {
                    dist[x][nd] = dist[x][u] + 1;
                    if (!visited[nd]) {
                        q.push(nd);
                        visited[nd] = 1;
                    }
                }
            }
        }
        while (start != 0) {
            start = fail[start];
            dist[x][start] = 0;
        }
    }

    int valid_state(int i, int j, int k)
    {
        if (((1 << j) & k) == 0) {
            return 0;
        }
        int res = 0;
        int nk = k;
        while (nk != 0) {
            if (nk & 0x1) {
                res++;
            }
            nk = nk >> 1;
        }
        return res == i ? 1 : 0;
    }

    int query(int rsize)
    {
        assert(rsize <= 10);
        for (int i = 0; i < rsize; ++i) {
            spfa(i);
        }
        _DEBUG_CMD({
            printf("res_idx:\n");
            for (int i = 0; i < rsize; ++i) {
                printf("%d ", res_idx[i]);
            }
            printf("\nvirus:\n");
            for (int i = 0; i <= trie_cnt; ++i) {
                printf("%d ", virus[i]);
            }
            printf("\nresult of spfa:\n");
            for (int i = 0; i < rsize; ++i) {
                for (int j = 0; j <= trie_cnt; ++j) {
                    printf("%d ", dist[i][j]);
                }
                printf("\n");
            }
        });
        int maxs = 1 << rsize;

        const int MAX = 0x3F3F3F3F;
        int dp[rsize + 1][maxs];
        memset(dp, 0x3F, sizeof(dp));
        // dp[0][0] = 0;

        for (int i = 0; i < rsize; ++i) {
            dp[i][1 << i] = res_len[i];
        }
        _DEBUG_CMD({
            // wrong digital dp
            for (int i = 0; i < rsize; ++i) {
                for (int j = 0; j < maxs; ++j) {
                    if (dp[i][j] != MAX) {
                        for (int k = 0; k < rsize; ++k) {
                            int nf = ((1 << k) & j);
                            int ns = ((1 << k) | j);
                            // int res_i = res_idx[i];
                            int res_k = res_idx[k];
                            DEBUG_CMD({
                                printf(
                                    "nf:%d, ns:%d, dp[%d][%d]:%d, dp[%d][%d]:%d, dist[%d][%d]:%d\n",
                                    nf, ns, i, j, dp[i][j], k, ns, dp[k][ns], i, res_k,
                                    dist[i][res_k]);
                            });
                            if (nf == 0 && dp[k][ns] > dp[i][j] + dist[i][res_k]) {
                                dp[k][ns] = dp[i][j] + dist[i][res_k];
                                DEBUG_CMD({
                                    printf("nf:%d, ns:%d, dp[%d][%d]:%d, dp[%d][%d]:%d, "
                                           "dist[%d][%d]:%d updated\n",
                                           nf, ns, i, j, dp[i][j], k, ns, dp[k][ns], i, res_k,
                                           dist[i][res_k]);
                                });
                            }
                        }
                    }
                }
            }
        });
        for (int i = 1; i <= rsize; ++i) {    // use of i items out of total rsize items
            for (int j = 0; j < rsize; ++j) { // state end up with usage of the j-th item
                for (int k = 0; k < maxs; ++k) {
                    if (valid_state(i, j, k)) { // transform from state k to new state via l-th item
                        for (int l = 0; l < rsize; ++l) {
                            int nf = ((1 << l) & k);
                            int ns = ((1 << l) | k);
                            int res_l = res_idx[l];
                            if (nf == 0 && dp[l][ns] > dp[j][k] + dist[j][res_l]) {
                                dp[l][ns] = dp[j][k] + dist[j][res_l];
                            }
                        }
                    }
                }
            }
        }
        int ret = MAX;
        for (int i = 0; i < rsize; ++i) {
            ret = min(ret, dp[i][maxs - 1]);
        }
        _DEBUG_CMD({
            printf("result of dp:\n");
            for (int i = 0; i < rsize; ++i) {
                for (int j = 0; j < maxs; ++j) {
                    printf("%d ", dp[i][j]);
                }
                printf("\n");
            }
        });
        return ret;
    }
}; // namespace AC

char vir[MAXVT];
int main(int argc, char **argv)
{
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        AC<MAXVT> ac;
        for (int i = 0; i < n; ++i) {
            scanf("%s", resources[i]);
            ac.insert(resources[i], i + 1);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%s", vir);
            ac.insert(vir, 0);
        }
        ac.build();
        printf("%d\n", ac.query(n));
    }
    return 0;
};

#endif
#endif
