#if 0
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <string.h>
using namespace std;
const int maxn = 5e4 + 5;
unsigned char aa[maxn];
#define dbg(x) cout << #x << " " << x << endl;
struct ACTrie {
    int tree[maxn][256], fail[maxn], end_[maxn];
    int root, cnt, num;
    set<int> s;
    int newnode()
    {
        for (int i = 0; i < 256; i++)
            tree[cnt][i] = -1;
        end_[cnt] = 0;
        return cnt++;
    }
    void init()
    {
        cnt = 0;
        num = 0;
        root = newnode();
    }
    void insert_(unsigned char str[], int len)
    {
        int pos = root;
        for (int i = 0; i < len; i++) {
            int id = str[i];
            if (tree[pos][id] == -1)
                tree[pos][id] = newnode();
            pos = tree[pos][id];
        }
        end_[pos] = ++num;
    }
    void build()
    {
        queue<int> que;
        fail[root] = root;
        for (int i = 0; i < 256; i++) {
            if (tree[root][i] == -1)
                tree[root][i] = root;
            else {
                fail[tree[root][i]] = root;
                que.push(tree[root][i]);
            }
        }
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            for (int i = 0; i < 256; i++) {
                if (tree[now][i] == -1)
                    tree[now][i] = tree[fail[now]][i];
                else {
                    fail[tree[now][i]] = tree[fail[now]][i];
                    que.push(tree[now][i]);
                }
            }
        }
    }
    int query(unsigned char *str, int len)
    {
        s.clear();
        int now = root;
        int res = 0;
        for (int i = 0; i < len; i++) {
            int id = (int) str[i];
            now = tree[now][id];
            int temp = now;
            while (temp != root) {
                if (end_[temp] != 0)
                    s.insert(end_[temp]);
                temp = fail[temp];
            }
        }
        return (int) s.size();
    }
};
unsigned char cal(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }
    if (c >= '0' && c <= '9') {
        return c - '0' + 52;
    }
    if (c == '+')
        return 62;
    else
        return 63;
}
int change(unsigned char str[], int len)
{
    int t = 0;
    for (int i = 0; i < len; i += 4) //每四个字符计算一次，转换为三个字符
    {
        aa[t++] = ((str[i] << 2) | (str[i + 1] >> 4)); //截取第一个字符的全部+第二个字符前两位
        if (i + 2 < len)
            aa[t++] =
                ((str[i + 1] << 4) | (str[i + 2] >> 2)); //截取第二个字符后四位+第三个字符前四位
        if (i + 3 < len)
            aa[t++] = ((str[i + 2] << 6) | str[i + 3]); //截取第三个字符后两位+第四个字符全部
    }
    return t;
}
ACTrie ac;
char str[maxn];
unsigned char ss[maxn];
int main()
{
    int n, m;
    while (scanf("%d", &n) != EOF) {
        ac.init();
        while (n--) {
            scanf("%s", str);
            int len = strlen(str);
            while (str[len - 1] == '=')
                len--;
            for (int i = 0; i < len; i++)
                ss[i] = cal(str[i]);
            int len2 = change(ss, len);
            ac.insert_(aa, len2); //转换之后插入AC自动机
        }
        ac.build();
        scanf("%d", &m);
        while (m--) {
            // gets(str);
            scanf("%s", str);
            int len = strlen(str);
            while (str[len - 1] == '=')
                len--;
            for (int i = 0; i < len; i++)
                ss[i] = cal(str[i]);
            int len2 = change(ss, len);
            printf("%d\n", ac.query(aa, len2));
        }
        printf("\n");
    }
    return 0;
}
#else
#ifndef _t17pd_20200724_
#define _t17pd_20200724_
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

static const char *B64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int B64index[256] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  62, 63, 62, 62, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,
    0,  0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 0,  0,  0,  0,  63, 0,  26, 27, 28, 29, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

unsigned char res[4 << 10];
int res_len;
const std::string b64encode(const void *data, const size_t &len)
{
    std::string result((len + 2) / 3 * 4, '=');
    char *p = (char *) data, *str = &result[0];
    size_t j = 0, pad = len % 3;
    const size_t last = len - pad;

    for (size_t i = 0; i < last; i += 3) {
        int n = int(p[i]) << 16 | int(p[i + 1]) << 8 | p[i + 2];
        str[j++] = B64chars[n >> 18];
        str[j++] = B64chars[n >> 12 & 0x3F];
        str[j++] = B64chars[n >> 6 & 0x3F];
        str[j++] = B64chars[n & 0x3F];
    }
    if (pad) /// set padding
    {
        int n = --pad ? int(p[last]) << 8 | p[last + 1] : p[last];
        str[j++] = B64chars[pad ? n >> 10 & 0x3F : n >> 2];
        str[j++] = B64chars[pad ? n >> 4 & 0x03F : n << 4 & 0x3F];
        str[j++] = pad ? B64chars[n << 2 & 0x3F] : '=';
    }
    return result;
}

// const std::string b64decode(const void *data, const size_t &len)
void b64decode(const void *data, const size_t &len)
{
    if (len == 0) {
        // res[0] = '\0';
        memset(res, 0, sizeof(res));
        return;
    }

    unsigned char *p = (unsigned char *) data;
    size_t j = 0, pad1 = len % 4 || p[len - 1] == '=',
           pad2 = pad1 && (len % 4 > 2 || p[len - 2] != '=');
    const size_t last = (len - pad1) / 4 << 2;
    std::string result(last / 4 * 3 + pad1 + pad2, '\0');
    unsigned char *str = (unsigned char *) &result[0];
    str = res;

    for (size_t i = 0; i < last; i += 4) {
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 |
                B64index[p[i + 3]];
        str[j++] = n >> 16;
        str[j++] = n >> 8 & 0xFF;
        str[j++] = n & 0xFF;
    }
    if (pad1) {
        int n = B64index[p[last]] << 18 | B64index[p[last + 1]] << 12;
        str[j++] = n >> 16;
        if (pad2) {
            n |= B64index[p[last + 2]] << 6;
            str[j++] = n >> 8 & 0xFF;
        }
    }
    res_len = j;
    str[j++] = '\0';
    // return result;
    // res_len = j;
    return;
}

std::string b64encode(const std::string &str) { return b64encode(str.c_str(), str.size()); }

// std::string b64decode(const std::string &str64) { return b64decode(str64.c_str(), str64.size());
// }

const int MAXN = (1 << 15) + 3;

namespace AC {
const int TRIE_SIZE = (1 << 8) + 1;
int trie[MAXN][TRIE_SIZE], trie_node;
int fail[MAXN], cnt[MAXN];
void init()
{
    trie_node = 0;
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(cnt, 0, sizeof(cnt));
}
void insert(const unsigned char *s, int len)
// void insert(const int *s, int len)
{
    int u = 0;
    for (int i = 0; i < len; ++i) {
        int conv = s[i] == 0 ? (1 << 8) : s[i];
        if (!trie[u][conv]) {
            trie[u][conv] = ++trie_node;
        }
        u = trie[u][conv];
    }
    ++cnt[u];
}
void build()
{
    queue<int> q;
    for (int i = 0; i < TRIE_SIZE; ++i) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < TRIE_SIZE; ++i) {
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
int query(const unsigned char *t, int len)
{
    int res = 0;
    int u = 0;
    set<int> s;
    for (int i = 0; i < len; ++i) {
        int conv = t[i] == 0 ? (1 << 8) : t[i];
        u = trie[u][conv];
        for (int j = u; j != 0; j = fail[j]) {
            // res += cnt[j];
            if (cnt[j]) {
                s.insert(j);
            }
        }
    }
    return s.size();
}
}; // namespace AC

int N, M;
unsigned char b64in[4 << 10];
int main(int argc, char **argv)
{
    while (cin >> N) {
        AC::init();
        for (int i = 0; i < N; ++i) {
            scanf("%s", b64in);
            b64decode(b64in, strlen((const char *) b64in));
            AC::insert(res, res_len);
        }
        AC::build();
        cin >> M;
        for (int i = 0; i < M; ++i) {
            scanf("%s", b64in);
            b64decode(b64in, strlen((const char *) b64in));
            cout << AC::query(res, res_len) << endl;
        }
        cout << endl;
    }
    return 0;
};

#endif
#endif
