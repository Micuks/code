#ifndef _t17pj_20200802_
#define _t17pj_20200802_
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
int T, N;
char diseases[MAXN][1 << 5];
char dna[1 << 10];

namespace AC {
const int TRIE_WIDTH = 1 << 2;
const int MAXT = 1 << 10;
int cmap[1 << 8];
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT];
void init()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;

    memset(cmap, 0, sizeof(cmap));
    cmap['A'] = 0;
    cmap['T'] = 1;
    cmap['G'] = 2;
    cmap['C'] = 3;
}
void insert(const char *s)
{
    int u = 0;
    for (int i = 0; s[i] != 0; ++i) {
        int offset = cmap[s[i]];
        if (trie[u][offset] == 0) {
            trie[u][offset] = ++trie_cnt;
        }
        u = trie[u][offset];
    }
    val[u] = 1;
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

        if (val[fail[u]]) {
            val[u] = 1;
        }

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
int query(const char *s)
{
    const int DEFAUL_MIN = 0x3F3F3F3F;
    int slen = strlen(s);
    int dp[slen + 1][trie_cnt + 2];
    memset(dp, 0x3F, sizeof(dp));
    dp[0][0] = 0;
    // int nextn = 0;
    for (int i = 0; i < slen; ++i) {
        // nextn = trie[nextn][cmap[s[i]]];
        int cur_move = cmap[s[i]];
        for (int j = 0; j <= trie_cnt; ++j) {
            if (val[j] == 0 && dp[i][j] != DEFAUL_MIN) {
                for (int k = 0; k < TRIE_WIDTH; ++k) {
                    int u = trie[j][k];
                    if (val[u] == 0) {
                        _DEBUG_CMD({
                            printf("dp[%d][%d]:%d, dp[%d][%d]:%d, k:%d cur_move:%d\n", i + 1, u,
                                   dp[i + 1][u], i, j, dp[i][j], k, cur_move);
                        });
                        dp[i + 1][u] = min(dp[i + 1][u], dp[i][j] + (cur_move == k ? 0 : 1));
                    }
                }
            }
        }
    }

    _DEBUG_CMD({
        for (int i = 0; i <= slen; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
    });
    int min_ele = DEFAUL_MIN;
    for (int i = 0; i <= trie_cnt; ++i) {
        if (val[i] == 0) {
            min_ele = min(min_ele, dp[slen][i]);
        }
    }
    // int min_ele = *min_element(dp[slen], dp[slen] + trie_cnt + 1);
    if (min_ele == DEFAUL_MIN) {
        min_ele = -1;
    }
    return min_ele;
}
}; // namespace AC

int main(int argc, char **argv)
{
    int case_cnt = 0;
    // scanf("%d", &T);
    while (~scanf("%d", &N) && N) {
        AC::init();
        for (int i = 0; i < N; ++i) {
            scanf("%s", dna);
            AC::insert(dna);
        }
        scanf("%s", dna);
        AC::build();
        printf("Case %d: %d\n", ++case_cnt, AC::query(dna));
    }
    return 0;
};

#endif
