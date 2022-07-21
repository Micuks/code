#ifndef _t17pa_20200723_
#define _t17pa_20200723_
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

const int MAXN = 5e5 + 9;
const int MAXM = 1e6 + 3;
char keyword[1 << 8];
int n;
char dest[MAXM];

namespace AC {
const int CNT = 'z' - 'a' + 1;
const char ori = 'a';
int trie[MAXN][CNT], tot;
int e[MAXN], fail[MAXN];

void clear()
{
    memset(e, 0, sizeof(e));
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    tot = 0;
}

void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        const char cur_char = s[i] - ori;
        if (!trie[u][cur_char])
            trie[u][cur_char] = ++tot;
        u = trie[u][cur_char];
    }
    e[u]++;
}
queue<int> q;
void build()
{
    for (int i = 0; i < CNT; ++i) {
        if (trie[0][i])
            q.push(trie[0][i]);
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < CNT; ++i) {
            int &next_node = trie[u][i];
            int cur_fail = fail[u];
            if (next_node) {
                fail[next_node] = trie[cur_fail][i];
                q.push(next_node);
            }
            else {
                next_node = trie[cur_fail][i];
            }
        }
    }
}
int query(const char *s)
{
    int u = 0, res = 0;

    for (int i = 0; s[i] != 0; ++i) {
        u = trie[u][s[i] - ori];
        for (int j = u; j && e[j] != -1; j = fail[j]) {
            res += e[j];
            e[j] = -1;
        }
    }

    return res;
}
}; // namespace AC

int main(int argc, char **argv)
{
    scanf("%d", &n);
    while (n--) {
        int ks;
        AC::clear();
        scanf("%d", &ks);
        for (int i = 0; i < ks; ++i) {
            scanf("%s", keyword);
            AC::insert(keyword);
        }
        AC::build();
        scanf("%s", dest);
        printf("%d\n", AC::query(dest));
    }
    return 0;
};

#endif
