#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int MAX_N = 10 * 10 + 5; //最大结点数：模式串个数 X 模式串最大长度
const int CLD_NUM = 4;         //从每个结点出发的最多边数：本题是4个ATCG

typedef long long MATRIX[MAX_N][MAX_N];

MATRIX mat, mat1, mat2;
long long (*m1)[MAX_N], (*m2)[MAX_N];

class ACAutomaton {
  public:
    int n;                    //当前结点总数
    int id['Z' + 1];          //字母x对应的结点编号为id[x]
    int fail[MAX_N];          // fail指针
    bool tag[MAX_N];          //本题所需
    int trie[MAX_N][CLD_NUM]; // trie tree

    void init()
    {
        id['A'] = 0;
        id['T'] = 1;
        id['C'] = 2;
        id['G'] = 3;
    }

    void reset()
    {
        memset(trie[0], -1, sizeof(trie[0]));
        tag[0] = false;
        n = 1;
    }

    //插入模式串s，构造单词树(keyword tree)
    void add(char *s)
    {
        int p = 0;
        while (*s) {
            int i = id[*s];
            if (-1 == trie[p][i]) {
                memset(trie[n], -1, sizeof(trie[n]));
                tag[n] = false;
                trie[p][i] = n++;
            }
            p = trie[p][i];
            s++;
        }
        tag[p] = true;
    }

    //用BFS来计算每个结点的fail指针，构造trie树
    void construct()
    {
        queue<int> Q;
        fail[0] = 0;
        for (int i = 0; i < CLD_NUM; i++) {
            if (-1 != trie[0][i]) {
                fail[trie[0][i]] = 0;
                Q.push(trie[0][i]);
            }
            else {
                trie[0][i] = 0; //这个不能丢
            }
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            if (tag[fail[u]])
                tag[u] = true; //这个很重要，当u的后缀是病毒，u也不能出现
            for (int i = 0; i < CLD_NUM; i++) {
                int &v = trie[u][i];
                if (-1 != v) {
                    Q.push(v);
                    fail[v] = trie[fail[u]][i];
                }
                else {
                    v = trie[fail[u]][i];
                }
            }
        }
    }

    /* 根据trie树来构建状态转换的邻接矩阵mat[][]
           mat[i][j]表示状态i到状态j有几条边   */
    void buildMatrix()
    {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < CLD_NUM; j++)
                if (!tag[i] &&
                    !tag[trie[i][j]]) // tag值为true的结点不能要，因为该结点的状态表示一个病毒
                    mat[i][trie[i][j]]++;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%lld ", mat[i][j]);
            }
            printf("\n");
        }
    }
} AC;

void matrixMult(MATRIX t1, MATRIX t2, MATRIX res)
{
    for (int i = 0; i < AC.n; i++)
        for (int j = 0; j < AC.n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < AC.n; k++) {
                res[i][j] += t1[i][k] * t2[k][j];
            }
            res[i][j] %= 100000;
        }
}

/*
    递归二分计算矩阵的p次幂，结果存在m2[][]中
    */
void matrixPower(int p)
{
    if (p == 1) {
        for (int i = 0; i < AC.n; i++)
            for (int j = 0; j < AC.n; j++)
                m2[i][j] = mat[i][j];
        return;
    }

    matrixPower(p / 2);     //计算矩阵的p/2次幂，结果存在m2[][]
    matrixMult(m2, m2, m1); //计算矩阵m2的平方，结果存在m1[][]

    if (p % 2) //如果p为奇数，则再计算矩阵m1乘以原矩阵mat[][]，结果存在m2[][]
        matrixMult(m1, mat, m2);
    else
        swap(m1, m2);
}

int main()
{
    int n, m;
    char s[12];

    AC.init();
    cin >> m >> n;
    AC.reset();
    while (m--) {
        scanf("%s", s);
        AC.add(s);
    }
    AC.construct();
    AC.buildMatrix();

    m1 = mat1;
    m2 = mat2;

    matrixPower(n);

    int ans = 0;
    for (int i = 0; i < AC.n; i++)
        ans += m2[0][i];
    printf("%d\n", ans % 100000);

    return 0;
}
#else
#ifndef _t17pe_20200725_
#define _t17pe_20200725_
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

const long long MAXN = 2000000000 + 11;
const int mod = 100000;

namespace AC {
const int MAXND = 1 << 7; // 128 >= 10 * 10
const int TRIE_WIDTH = 4;
typedef long long MAT_TYPE[MAXND][MAXND];
// long long mat1[MAXND][MAXND], mat2[MAXND][MAXND], mat[MAXND][MAXND];
MAT_TYPE mat1, mat2, mat;
int c2i[1 << 8];

int trie[MAXND][TRIE_WIDTH], trie_node;
int fail[MAXND], cnt[MAXND];
vector<string> strdict;

void init()
{
    c2i['A'] = 0;
    c2i['T'] = 1;
    c2i['G'] = 2;
    c2i['C'] = 3;
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(cnt, 0, sizeof(cnt));
    memset(mat, 0, sizeof(mat));
    trie_node = 0;
    strdict.clear();
    strdict.push_back("");
}

void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        if (!trie[u][c2i[s[i]]]) {
            trie[u][c2i[s[i]]] = ++trie_node;
            strdict.push_back(string(s, 0, i + 1));
        }
        u = trie[u][c2i[s[i]]];
    }
    if (cnt[u] == 0) {
        cnt[u] = 1;
        // strdict.push_back(s);
        assert(strdict.size() == trie_node + 1);
    }
    _DEBUG_CMD(printf("u:%d, trie_node:%d\n", u, trie_node));
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

        // TODO
        if (cnt[fail[u]] == 1) {
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
    for (int i = 0; i < trie_node; ++i) {
        for (int j = 0; j < TRIE_WIDTH; ++j) {
            if (cnt[i] == 0 && cnt[trie[i][j]] == 0) {
                ++mat[i][trie[i][j]];
            }
        }
    }
}

void mat_multi(MAT_TYPE &m_ret, MAT_TYPE &m1, MAT_TYPE &m2)
{
    MAT_TYPE m0;
    memset(m0, 0, sizeof(m0));
    _DEBUG_CMD({ printf("addr of m_ret: %p\n", &m_ret); });
    for (int i = 0; i < trie_node; ++i) {
        for (int j = 0; j < trie_node; ++j) {
            for (int k = 0; k < trie_node; ++k) {
                m0[i][j] += m1[i][k] * m2[k][j];
                m0[i][j] = m0[i][j] % mod;
            }
        }
    }
    // memcpy(m_ret, m0, sizeof(m0));
    for (int i = 0; i < trie_node; ++i) {
        for (int j = 0; j < trie_node; ++j) {
            m_ret[i][j] = m0[i][j];
        }
    }
}

void mat_power(MAT_TYPE &m_ret, MAT_TYPE &m, long long x)
{
    if (x == 1) {
        // memcpy(m_ret, m, sizeof(m_ret));
        for (int i = 0; i < trie_node; ++i) {
            for (int j = 0; j < trie_node; ++j) {
                m_ret[i][j] = m[i][j];
            }
        }
        return;
    }
    MAT_TYPE m0;
    mat_power(m0, m, x / 2);
    _DEBUG_CMD({
        printf("before multiplication, m0:\n");
        for (int i = 0; i < trie_node; ++i) {
            for (int j = 0; j < trie_node; ++j) {
                printf("%lld ", m0[i][j]);
            }
            printf("\n");
        }
        printf("addr of m0: %p, \n", &m0);
    });
    mat_multi(m0, m0, m0);
    _DEBUG_CMD({
        printf("after multiplication, m0:\n");
        for (int i = 0; i < trie_node; ++i) {
            for (int j = 0; j < trie_node; ++j) {
                printf("%lld ", m0[i][j]);
            }
            printf("\n");
        }
        printf("addr of m0: %p, \n", &m0);
    });
    if (x % 2) {
        mat_multi(m0, m0, m);
    }
    _DEBUG_CMD({
        printf("after power, m0:\n");
        for (int i = 0; i < trie_node; ++i) {
            for (int j = 0; j < trie_node; ++j) {
                printf("%lld ", m0[i][j]);
            }
            printf("\n");
        }
    });
    // memcpy(m_ret, m0, sizeof(m0));
    for (int i = 0; i < trie_node; ++i) {
        for (int j = 0; j < trie_node; ++j) {
            m_ret[i][j] = m0[i][j];
        }
    }
}

long long query(long long x)
{
    long long ret = 0;
    build_matrix();
    if (trie_node == 0) {
        trie_node = 1;
        mat[0][0] = TRIE_WIDTH;
    }
    mat_power(mat1, mat, x);
    /*
    for (int i = 0; i < trie_node; ++i) {
        ret += mat1[i][0];
    }
    */
    ret = accumulate(mat1[0], mat1[0] + trie_node, 0LL);
    _DEBUG_CMD({
        printf("mat:\n");
        for (int i = 0; i <= trie_node; ++i) {
            for (int j = 0; j <= trie_node; ++j) {
                printf("%lld ", mat[i][j]);
            }
            printf("\n");
        }
        printf("mat1:\n");
        for (int i = 0; i <= trie_node; ++i) {
            for (int j = 0; j <= trie_node; ++j) {
                printf("%lld ", mat1[i][j]);
            }
            printf(", \t%s\n", strdict[i].c_str());
        }
    });
    return ret % mod;
}
}; // namespace AC

long long m, n;
char defects[1 << 10];
int main(int argc, char **argv)
{
    cin >> m >> n;
    AC::init();
    for (int i = 0; i < m; ++i) {
        scanf("%s", defects);
        AC::insert(defects);
        _DEBUG_CMD(printf("i:%d, defects:%s\n", i, defects););
    }
    AC::build();
    printf("%lld\n", AC::query(n));
    return 0;
};

#endif
#endif
