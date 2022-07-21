#ifndef _t17pc_20200724_
#define _t17pc_20200724_
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

const int MAXN = 2e6 + 3;
int N;
char str[MAXN];
const int MAXD = 5e4 + 21;

namespace AC {
const int TRIE_SIZE = 26;
const char ori = 'A';
int trie[MAXD][TRIE_SIZE];
int fail[MAXD], cnt[MAXD], idx[MAXD];
int trie_cnt;
map<int, string> vir_idx;
int vir_cnt;
int match[MAXD];

void init()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(cnt, 0, sizeof(cnt));
    memset(match, 0, sizeof(match));
    memset(idx, 0, sizeof(idx));
    trie_cnt = 0;
    vir_cnt = 0;
    vir_idx.clear();
}

void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = s[i] - ori;
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
        }
        u = trie[u][offset];
    }
    ++cnt[u];
    idx[u] = vir_cnt;
    vir_idx[vir_cnt++] = s;
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
            // char c = ori + i;
            if (trie[u][i]) {
                fail[trie[u][i]] = trie[fail[u]][i], q.push(trie[u][i]);
            }
            else {
                trie[u][i] = trie[fail[u]][i];
            }
        }
    }
}

int query(const char *t)
{
    int u = 0, res = 0;
    for (int i = 0; t[i] != 0; ++i) {
        int offset = t[i] - ori;
        if (offset < TRIE_SIZE && offset >= 0) {
            u = trie[u][offset];
            for (int j = u; j != 0; j = fail[j]) {
                // res += cnt[j];
                if (cnt[j]) {
                    match[idx[j]] += cnt[j];
                }
            }
        }
        else {
            u = 0;
            continue;
        }
    }
    return res;
}
}; // namespace AC

int main(int argc, char **argv)
{
    char virus[1 << 8];
    while (~scanf("%d", &N)) {
        // scanf("%d", &N);
        AC::init();
        for (int i = 0; i < N; ++i) {
            scanf("%s", virus);
            AC::insert(virus);
        }
        AC::build();
        scanf("%s", str);
        AC::query(str);

        for (int i = 0; i < N; ++i) {
            if (AC::match[i]) {
                printf("%s: %d\n", AC::vir_idx[i].c_str(), AC::match[i]);
            }
        }
    }
    return 0;
};

#endif
