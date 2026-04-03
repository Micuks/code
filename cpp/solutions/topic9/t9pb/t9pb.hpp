#ifndef _t9pb_20201227_
#define _t9pb_20201227_
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
#include <stack>
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

const int MAXN = 1 << 8;
int N;
char g[MAXN][MAXN];
// char vis[MAXN];
char instack[MAXN];
int dfn[MAXN], lowlink[MAXN];

int ss[MAXN], ss_cnt;
int belong[MAXN], scc_cnt;

int cut_vertices_cnt;

void init()
{
    memset(g, 0, sizeof(g));
    // memset(vis, 0, sizeof(vis));
    memset(instack, 0, sizeof(instack));
    memset(belong, 0, sizeof(belong));
    memset(ss, 0, sizeof(ss));
    memset(dfn, 0, sizeof(dfn));
    memset(lowlink, 0, sizeof(lowlink));
    ss_cnt = scc_cnt = cut_vertices_cnt = 0;
}

void dfs(int u, int idx)
{
    dfn[u] = lowlink[u] = idx;
    bool cut_flag = false;

    ss[ss_cnt++] = u;
    instack[u] = 1;

    int cnt = 0;
    for (int i = 1; i <= N; ++i) {
        if (g[u][i] != 0) {
            // if (vis[i] == 0) {
            if (dfn[i] == 0) {
                ++cnt;
                dfs(i, idx + 1);
                // if ((idx == 1 && cnt >= 2) || (idx != 1 && lowlink[u] <= lowlink[i])) {
                if ((idx == 1 && cnt >= 2) || (idx != 1 && dfn[u] <= lowlink[i])) {
                    // current node is a root node over at least two child nodes.
                    // or current node has a child node that can't reach a small lowlink without
                    // this very node.
                    cut_flag = true;
                }
                lowlink[u] = min(lowlink[u], lowlink[i]);
                /*
                if (lowlink[u] > lowlink[i]) {
                    lowlink[u] = lowlink[i];
                }
                */
            }
            else if (instack[i]) {
                lowlink[u] = min(lowlink[u], dfn[i]);
            }
        }
    }

    if (cut_flag) {
        ++cut_vertices_cnt;
    }

    if (lowlink[u] == dfn[u]) {
        int node;
        ++scc_cnt;
        do {
            node = ss[--ss_cnt];
            belong[node] = scc_cnt;
            instack[node] = 0;
        } while (node != u);
    }
}
void tarjan()
{
    int index = 1;
    ss_cnt = 0;

    for (int i = 1; i <= N; ++i) {
        if (dfn[i] == 0) {
            dfs(i, 1);
        }
    }
    /*
    if (root_dec = 1) {
        --cut_vertices_cnt;
    }
    */
}

int main(int argc, char **argv)
{
    while (~scanf("%d\n", &N) && N != 0) {
        int s, t;

        init();

        string line;
        getline(cin, line);
        istringstream is(line);
        is >> s;

        do {
            _DEBUG_CMD({ printf("node:%d connects to: ", s); });
            while (is >> t) {
                g[s][t] = g[t][s] = 1;
                _DEBUG_CMD({ printf("%d ", t); });
            }
            _DEBUG_CMD({ printf("\n"); });

            line.clear();
            getline(cin, line);
            is = istringstream(line);
            is >> s;
        } while (s != 0);

        tarjan();

        printf("%d\n", cut_vertices_cnt);
    }
    return 0;
};

#endif
