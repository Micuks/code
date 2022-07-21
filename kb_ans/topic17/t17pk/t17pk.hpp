#ifndef _t17pk_20200803_
#define _t17pk_20200803_
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

const int MAXN = 6e5 + 11;
char str[MAXN];
int opt[MAXN], n;

namespace AC {
const char ori = 'a';
const int TRIE_WIDTH = 'z' - 'a' + 1;
const int MAXT = 6e5 + 11;
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT];
int end[MAXT], last_match[MAXT];
int hits[MAXT][2];

void init()
{
    memset(last_match, -1, sizeof(last_match));
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(hits, 0, sizeof(hits));
    memset(end, 0, sizeof(end));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;
}
void insert(const char *s, int idx)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = s[i] - ori;
        if (!trie[u][offset]) {
            trie[u][offset] = ++trie_cnt;
            val[trie[u][offset]] = val[u] + 1;
        }
        u = trie[u][offset];
    }
    end[idx] = u;
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
void query(const char *s)
{ // 0 means overlapping is allowed, 1 means not.
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = s[i] - ori;
        u = trie[u][offset];
        int tmp = u;
        while (tmp != 0) {
            ++hits[tmp][0];
            if (i - last_match[tmp] >= val[tmp]) {
                last_match[tmp] = i;
                ++hits[tmp][1];
            }
            tmp = fail[tmp];
        }
    }
    _DEBUG_CMD({
        // printf("");
        printf("hits: ");
        for (int i = 0; i <= trie_cnt; ++i) {
            printf("hits[%d][0]:%d hits[%d][1]:%d ", i, hits[i][0], i, hits[i][1]);
        }
        printf("\n");
    });
}
}; // namespace AC

int main(int argc, char **argv)
{
    int case_cnt = 0;
    char s1[1 << 4];
    while (~scanf("%s", str)) {
        AC::init();
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &opt[i]);
            scanf("%s", s1);
            AC::insert(s1, i);
        }
        AC::build();
        AC::query(str);
        printf("Case %d\n", ++case_cnt);
        for (int i = 0; i < n; ++i) {
            printf("%d\n", AC::hits[AC::end[i]][opt[i]]);
        }
        printf("\n");
    }
    return 0;
};

#endif
