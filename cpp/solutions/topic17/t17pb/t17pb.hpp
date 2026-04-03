#ifndef _t17pb_20200724_
#define _t17pb_20200724_
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

const int MAXN = 1e5 + 3;

namespace AC {
const int TRIE_SIZE = 130;
int trie_node;
struct {
    int next[TRIE_SIZE];
    int cnt;
    int fail;
    int idx;
} trie[MAXN];
void init()
{
    trie_node = 0;
    memset(trie, 0, sizeof(trie));
}
void insert(const char *s, int idx)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        if (!trie[u].next[s[i]]) {
            trie[u].next[s[i]] = ++trie_node;
        }
        u = trie[u].next[s[i]];
    }
    ++trie[u].cnt;
    trie[u].idx = idx;
}
void build()
{
    std::queue<int> q;
    for (int i = 0; i < TRIE_SIZE; ++i) {
        if (trie[0].next[i]) {
            q.push(trie[0].next[i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < TRIE_SIZE; ++i) {
            if (trie[u].next[i]) {
                trie[trie[u].next[i]].fail = trie[trie[u].fail].next[i];
                q.push(trie[u].next[i]);
            }
            else {
                trie[u].next[i] = trie[trie[u].fail].next[i];
            }
        }
    }
}
const int MAXN_VIRUS_CNT = 3;
vector<int> virus;
void query(const char *t)
{
    virus.clear();
    int u = 0;

    for (int i = 0; t[i] != 0 && virus.size() < MAXN_VIRUS_CNT; ++i) {
        u = trie[u].next[t[i]];
        for (int j = u; j != 0 && virus.size() < MAXN_VIRUS_CNT; j = trie[j].fail) {
            if (trie[j].cnt) {
                virus.push_back(trie[j].idx);
            }
        }
    }
    sort(virus.begin(), virus.end());
}
}; // namespace AC

int N, M;
char vir[MAXN], src[MAXN];
int main(int argc, char **argv)
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%s", vir);
        AC::insert(vir, i + 1);
    }
    AC::build();

    int total = 0;
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        scanf("%s", src);
        AC::query(src);
        if (AC::virus.size() != 0) {
            printf("web %d:", i + 1);
            for (int j = 0; j < AC::virus.size(); ++j) {
                printf(" %d", AC::virus[j]);
            }
            printf("\n");
            ++total;
        }
    }
    printf("total: %d\n", total);

    return 0;
};

#endif
