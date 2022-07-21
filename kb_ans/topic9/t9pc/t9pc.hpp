#ifndef _t9pc_20201229_
#define _t9pc_20201229_
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

// const int MAXN = 1 << 8;
const int MAXN = 2e4 - 3;

int no;

struct Edge {
    int from, to, next;
} edges[MAXN * 10];
int edge_cnt;
int head[MAXN];

set<pair<int, int>> ans;

void add_edge(int u, int v)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].from = u;
    edges[edge_cnt].to = v;
    head[u] = edge_cnt++;
}

void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
    ans.clear();
}

char instack[MAXN];
int stack_arr[MAXN], stack_cnt;
int dfn[MAXN], lowlink[MAXN];
void dfs(int u, int idx, int indeg)
{
    dfn[u] = lowlink[u] = idx;
    stack_arr[stack_cnt++] = u;
    instack[u] = 1;

    int h = head[u];
    // int ccnt = 0;
    while (h != -1) {
        const Edge &e = edges[h];
        if (indeg == e.to) {
            h = e.next;
            continue;
        }
        if (dfn[e.to] == 0) {
            //++ccnt;
            dfs(e.to, idx + 1, e.from);
            lowlink[u] = min(lowlink[u], lowlink[e.to]);
            _DEBUG_CMD({ printf("dfn[%d]:%d lowlink[%d]:%d\n", u, dfn[u], e.to, lowlink[e.to]); });
            if (dfn[u] < lowlink[e.to]) {
                pair<int, int> p(min(u, e.to), max(u, e.to));
                ans.insert(p);
            }
        }
        // else if (lowlink[u] > lowlink[e.to] && instack[e.to]) {
        else if (instack[e.to]) {
            lowlink[u] = min(lowlink[u], dfn[e.to]);
        }
        /*
        if (lowlink[u] <= lowlink[e.to]) {
            pair<int, int> p(min(u, e.to), max(u, e.to));
            ans.insert(p);
        }
        */
        h = e.next;
    }

    if (lowlink[u] == dfn[u]) {
        int node;
        //++scc_cnt;
        do {
            node = stack_arr[--stack_cnt];
            instack[node] = 0;
        } while (node != u);
    }
}
void tarjan()
{
    stack_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));
    memset(lowlink, 0, sizeof(lowlink));

    for (int i = 0; i < no; ++i) {
        if (dfn[i] == 0) {
            dfs(i, 1, -1);
        }
    }
}

void print()
{
    printf("%lu critical links\n", ans.size());
    for (auto p : ans) {
        printf("%d - %d\n", p.first, p.second);
    }
}

int main(int argc, char **argv)
{
    int from, to, ec;
    while (~scanf("%d", &no)) {
        init();
        for (int j = 0; j < no; ++j) {
            scanf("%d (%d)", &from, &ec);
            _DEBUG_CMD({ printf("from: %d ec:%d, to:", from, ec); });
            for (int i = 0; i < ec; ++i) {
                scanf("%d", &to);
                _DEBUG_CMD({ printf("%d, ", to); });
                add_edge(from, to);
                add_edge(to, from);
            }
            _DEBUG_CMD({ printf("\n"); });
        }
        tarjan();
        print();
        printf("\n");
    }
    return 0;
};

#endif
