#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef unsigned long long LL;
const double EPS = 1e-6;
const int INF = 2e9;
const LL LNF = 9e18;
const int MOD = 1e9 + 7;
const int MAXN = 30 + 10;

int Size;
struct MA {
    LL mat[30][30];
    void init()
    {
        for (int i = 0; i < Size; i++)
            for (int j = 0; j < Size; j++)
                mat[i][j] = (i == j);
    }
};

MA operator+(const MA &x, const MA &y)
{
    MA ret;
    memset(ret.mat, 0, sizeof(ret.mat));
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            ret.mat[i][j] = x.mat[i][j] + y.mat[i][j];
    return ret;
}

MA operator*(const MA &x, const MA &y)
{
    MA ret;
    memset(ret.mat, 0, sizeof(ret.mat));
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            for (int k = 0; k < Size; k++)
                ret.mat[i][j] += 1LL * x.mat[i][k] * y.mat[k][j];
    return ret;
}

MA qpow(MA x, int y)
{
    MA s;
    s.init();
    while (y) {
        if (y & 1)
            s = s * x;
        x = x * x;
        y >>= 1;
    }
    return s;
}

MA solve(MA x, int n)
{
    if (n == 1)
        return x;
    MA s;
    s.init();
    s = (s + qpow(x, n / 2)) * solve(x, n / 2);
    if (n % 2)
        s = s + qpow(x, n);
    return s;
}

struct Trie {
    const static int sz = 26, base = 'a';
    int next[MAXN][sz], fail[MAXN], end[MAXN];
    int root, L;
    int newnode()
    {
        for (int i = 0; i < sz; i++)
            next[L][i] = -1;
        end[L++] = 0;
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
            if (next[now][buf[i] - base] == -1)
                next[now][buf[i] - base] = newnode();
            now = next[now][buf[i] - base];
        }
        end[now] = 1;
    }
    void build()
    {
        queue<int> Q;
        fail[root] = root;
        for (int i = 0; i < sz; i++) {
            if (next[root][i] == -1)
                next[root][i] = root;
            else
                fail[next[root][i]] = root, Q.push(next[root][i]);
        }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            end[now] |= end[fail[now]]; //当前串的后缀是否也包含单词
            for (int i = 0; i < sz; i++) {
                if (next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else
                    fail[next[now][i]] = next[fail[now]][i], Q.push(next[now][i]);
            }
        }
    }

    LL query(int n)
    {
        MA s;
        memset(s.mat, 0, sizeof(s.mat));
        for (int i = 0; i < L; i++) {
            if (end[i])
                continue; //存在单词的状态没有后继
            for (int j = 0; j < sz; j++)
                if (end[next[i][j]] == 0) //存在单词的状态没有前驱
                    s.mat
                        [i]
                        [next[i]
                             [j]]++; // i到next[i][j]的路径数+1。注意，当next[i][j]==root时，路径数很可能大于1。
        }

        Size = L;
        s = solve(s, n);
        LL ret = 0;
        for (int i = 0; i < L; i++) //答案为：初始状态到各个状态（包括初始状态）的路径数之和。
            ret += s.mat[0][i];
        Size = 1;
        memset(s.mat, 0, sizeof(s.mat)); // 26+26^2……+26^n。
        s.mat[0][0] = 26;
        s = solve(s, n);
        return s.mat[0][0] - ret;
    }
};

Trie ac;
char buf[20];
int main()
{
    int n, L;
    while (scanf("%d%d", &n, &L) != EOF) {
        ac.init();
        for (int i = 1; i <= n; i++) {
            scanf("%s", buf);
            ac.insert(buf);
        }
        ac.build();
        LL ans = ac.query(L);
        printf("%llu\n", ans);
    }
    return 0;
}
#else
#ifndef _t17pf_20200726_
#define _t17pf_20200726_
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

const int MAXN = 1 << 5;
typedef unsigned long long ULL;
namespace AC {
const int TRIE_WIDTH = 'z' - 'a' + 1;
const char ori = 'a';
int trie[MAXN][TRIE_WIDTH], trie_cnt;
int fail[MAXN], cnt[MAXN];
typedef unsigned long long MAT_TYPE[MAXN][MAXN];
// MAT_TYPE mat;
typedef struct _MAT {
    _MAT() { memset(mat, 0, sizeof(mat)); };
    _MAT(const _MAT &m) { memcpy(mat, m.mat, sizeof(mat)); };
    ~_MAT() = default;
    _MAT &operator=(const _MAT &m)
    {
        if (this == &m) {
            return *this;
        }
        memcpy(this->mat, m.mat, sizeof(this->mat));
        return *this;
    };
    _MAT operator*(const _MAT &m) const
    {
        _MAT tm;
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                for (int k = 0; k <= trie_cnt; ++k) {
                    tm.mat[i][j] += this->mat[i][k] * m.mat[k][j];
                }
            }
        }
        return tm;
    }
    _MAT operator+(const _MAT &m) const
    {
        _MAT tm;
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                tm.mat[i][j] = this->mat[i][j] + m.mat[i][j];
            }
        }
        return tm;
    }
    static _MAT E()
    {
        _MAT m;
        for (int i = 0; i <= trie_cnt; ++i) {
            m.mat[i][i] = 1;
        }
        return m;
    }
    _MAT ullpow(ULL x) const
    {
        if (x == 0) {
            return E();
        }
        if (x == 1) {
            return *this;
        }
        _MAT m = this->ullpow(x / 2);
        _MAT m2 = m * m;
        if (x % 2) {
            m2 = m2 * (*this);
        }
        return m2;
    }
    _MAT add_e() const
    {
        _MAT m(*this);
        for (int i = 0; i <= trie_cnt; ++i) {
            m.mat[i][i] += 1;
        }
        return m;
    }
    _MAT pow_acc(ULL x) const
    {
        // A + A ^ 2 + A ^ 3 + A ^ 4 + ... + A ^ x
        if (x == 0) {
            return _MAT();
        }
        if (x == 1) {
            return *this;
        }
        return ((this->ullpow(x / 2)).add_e()) * this->pow_acc(x / 2) +
               (x % 2 == 0 ? _MAT() : this->ullpow(x));
    }
    MAT_TYPE mat;
} MAT;
MAT mat;
void init()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(cnt, 0, sizeof(cnt));
    // memset(mat, 0, sizeof(mat));
    mat = MAT();
    trie_cnt = 0;
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
    cnt[u] = 1;
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

        if (cnt[fail[u]]) {
            cnt[u] = 1;
        }

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
void build_matrix()
{
    for (int i = 0; i <= trie_cnt; ++i) {
        for (int j = 0; j < TRIE_WIDTH; ++j) {
            if (cnt[i] == 0 && cnt[trie[i][j]] == 0) {
                mat.mat[i][trie[i][j]] += 1;
            }
        }
    }
}
ULL query(ULL x)
{
    build_matrix();
    MAT ans_mat = mat.pow_acc(x);
    _DEBUG_CMD({
        printf("after building matrix:\n");
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%llu ", mat.mat[i][j]);
            }
            printf("\n");
        }
        printf("mat.pow_acc(%llu):\n", x);
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%llu ", ans_mat.mat[i][j]);
            }
            printf("\n");
        }
    });
    ULL res = accumulate(ans_mat.mat[0], ans_mat.mat[0] + trie_cnt + 1, 0LL);
    mat = MAT();
    mat.mat[0][0] = 26;
    _DEBUG_CMD({
        printf("26 matrix before pow_acc, x:%llu\n", x);
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%llu ", mat.mat[i][j]);
            }
            printf("\n");
        }
    });
    ans_mat = mat.pow_acc(x);
    _DEBUG_CMD({
        printf("26 pow_acc %llu\n", x);
        for (int i = 0; i <= trie_cnt; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%llu ", ans_mat.mat[i][j]);
            }
            printf("\n");
        }
        printf("pow_acc(%llu) 26^x: %llu res: %llu mat.mat[0][0]:%llu\n", x, ans_mat.mat[0][0], res,
               mat.mat[0][0]);
    });
    return ans_mat.mat[0][0] - res;
}
}; // namespace AC

int n;
ULL l;
char word_root[1 << 4];
int main(int argc, char **argv)
{
    // printf("sizeof(long long int): %ld\n", sizeof(long long int));
    while (cin >> n >> l) {
        AC::init();
        for (int i = 0; i < n; ++i) {
            scanf("%s", word_root);
            AC::insert(word_root);
        }
        AC::build();
        // DEBUG_CMD({ printf("ans: "); });
        printf("%llu\n", AC::query(l));
    }
    return 0;
};

#endif
#endif
