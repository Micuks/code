#ifndef _t17pg_20200727_
#define _t17pg_20200727_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
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

const int MAXN = 1 << 9;
int n, m, p;
int alphabet_map[MAXN];
unsigned char alphabet[MAXN];
unsigned char forbidden[MAXN];

namespace AC {
const int TRIE_WIDTH = 1 << 6;
int trie[MAXN][TRIE_WIDTH], trie_cnt;
int cnt[MAXN], fail[MAXN];
typedef struct MAT_TYPE {
    static const int MAXM = 1 << 7;
    MAT_TYPE()
    {
        _DEBUG_CMD(printf("default constructor\n"));
        memset(mat, 0, sizeof(mat));
    }
    MAT_TYPE(const MAT_TYPE &m)
    {
        _DEBUG_CMD(printf("copy constructor\n"));
        memcpy(mat, m.mat, sizeof(mat));
    }
    MAT_TYPE &operator=(const MAT_TYPE &m)
    {
        _DEBUG_CMD(printf("assignment operator\n"));
        if (&m != this) {
            memcpy(mat, m.mat, sizeof(mat));
        }
        return *this;
    }
    MAT_TYPE operator+(const MAT_TYPE &m) const
    {
        MAT_TYPE tm;
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                tm.mat[i][j] = mat[i][j] + m.mat[i][j];
            }
        }
        return tm;
    }
    MAT_TYPE operator*(const MAT_TYPE &m) const
    {
        MAT_TYPE tm;
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                for (int k = 0; k <= trie_cnt; ++k) {
                    tm.mat[i][j] += mat[i][k] * m.mat[k][j];
                }
            }
        }
        return tm;
    }
    MAT_TYPE fastpow(int p) const
    {
        // DEBUG_CMD({ printf("p: %d\n", p); });
        MAT_TYPE *tm = new MAT_TYPE(*this);
        MAT_TYPE ret;
        for (int i = 0; i <= trie_cnt; ++i) {
            ret.mat[i][i] = 1;
        }
        while (p != 0) {
            if (p & 0x1) {
                ret = ret * (*tm);
            }
            (*tm) = (*tm) * (*tm);
            p = (p >> 1);
        }
        delete tm;
        return ret;
    }
    void clear() { memset(mat, 0, sizeof(mat)); }
    long long mat[MAXM][MAXM];
} MAT;
void init()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(cnt, 0, sizeof(cnt));
    trie_cnt = 0;
}
void insert(const unsigned char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        if (!trie[u][alphabet_map[s[i]]]) {
            trie[u][alphabet_map[s[i]]] = ++trie_cnt;
        }
        u = trie[u][alphabet_map[s[i]]];
    }
    cnt[u] = 1;
}
void build()
{
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (cnt[fail[u]] == 1) {
            cnt[u] = 1;
        }
        for (int i = 0; i < n; ++i) {
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
void build_matrix(MAT &mat)
{
    // mat = MAT();
    for (int i = 0; i <= trie_cnt; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cnt[i] == 0 && cnt[trie[i][j]] == 0) {
                mat.mat[i][trie[i][j]] += 1;
            }
        }
    }
}
typedef struct BI {
    static const int MAXD = 1 << 6;
    static const int mod = 10000;
    BI()
    {
        memset(digits, 0, sizeof(digits));
        digits[0] = 1;
    };
    BI(const BI &bi) { memcpy(digits, bi.digits, sizeof(digits)); }
    void set(int x)
    {
        assert(x < mod && x >= 0);
        digits[0] = 1;
        digits[1] = x;
    }
    BI &operator=(const BI &bi)
    {
        if (this != &bi) {
            memcpy(digits, bi.digits, sizeof(digits));
        }
        return *this;
    }
    BI operator+(const BI &bi) const
    {
        BI c;
        c.digits[0] = max(digits[0], bi.digits[0]);
        for (int i = 1; i <= c.digits[0]; ++i) {
            int cur_dig = digits[i] + bi.digits[i] + c.digits[i];
            c.digits[i] = cur_dig % mod;
            c.digits[i + 1] += cur_dig / mod;
        }
        if (c.digits[c.digits[0] + 1] > 0) {
            ++c.digits[0];
        }
        return c;
    }
    void print()
    {
        printf("%d", digits[digits[0]]);
        for (int i = digits[0] - 1; i > 0; --i) {
            int k = 10;
            int di = 1;
            while (k * digits[i] < mod && di < 4) {
                k = k * 10;
                ++di;
                printf("0");
            }
            printf("%d", digits[i]);
        }
    }
    int digits[MAXD];
} BigInteger;
long long query(int x)
{
    BigInteger dp[m + 1][trie_cnt + 1];
    _DEBUG_CMD(printf("dp size:%lu\n", sizeof(dp)));
    dp[0][0].set(1);
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            for (int k = 0; k < n; ++k) {
                int u = trie[j][k];
                if (cnt[u] == 0) {
                    assert(i >= 0 && i <= m);
                    assert(u >= 0 && u <= trie_cnt);
                    assert(j >= 0 && j <= trie_cnt);
                    dp[i][u] = dp[i][u] + dp[i - 1][j];
                }
            }
        }
    }

    BigInteger ans;
    for (int i = 0; i <= trie_cnt; ++i) {
        ans = ans + dp[m][i];
    }
    ans.print();
    printf("\n");
    /*

    MAT mpx = mat.fastpow(x);
    DEBUG_CMD({
        printf("trie_cnt:%d\n", trie_cnt);
        printf("mat:\n");
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%lld ", mat.mat[i][j]);
            }
            printf("\n");
        }
        printf("mpx:\n");
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%lld ", mpx.mat[i][j]);
            }
            printf("\n");
        }
    });
    long long fcnt = accumulate(mpx.mat[0], mpx.mat[0] + trie_cnt + 1, 0LL);

    return fcnt;
    */
    return 0LL;
}
}; // namespace AC

int main(int argc, char **argv)
{
    // printf("sizeof(MAT): %lu\n", sizeof(AC::MAT));
    _DEBUG_CMD({
        printf("print a big int with zero in between;");
        AC::BigInteger bi;
        bi.digits[0] = 3;
        bi.digits[1] = 1;
        bi.digits[2] = 0;
        bi.digits[3] = 3;
        printf("bi: \n300000001\n");
        bi.print();
        printf("\n");
    });
    while (~scanf("%d%d%d\n", &n, &m, &p)) {

        // while (cin >> n >> m >> p) {
        // scanf("%s", alphabet);
        _DEBUG_CMD(printf("n:%d, m:%d p:%d ab:%s\n", n, m, p, alphabet));
        cin.getline((char *) alphabet, sizeof(alphabet));
        // int slen = strlen((char *) alphabet);
        // alphabet[n] = 0;
        // assert(slen == n);
        // unsigned char uc;
        for (int i = 0; i < n; ++i) {
            // scanf("%c", &alphabet[i]);
            alphabet_map[alphabet[i]] = i;
        }

        AC::init();
        for (int i = 0; i < p; ++i) {
            // scanf("%s", forbidden);
            cin.getline((char *) forbidden, sizeof(forbidden));
            _DEBUG_CMD(printf("fbd:%s\n", forbidden));
            // cin.getline(forbidden, MAXN);
            AC::insert(forbidden);
        }
        AC::build();
        // printf("%lld\n", AC::query(m));
        AC::query(m);
    }
    return 0;
};

#endif
