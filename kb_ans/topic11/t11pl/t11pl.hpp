#ifndef _t11pl_20210706_
#define _t11pl_20210706_
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

const int INF = 0x3F3F3F3F;
const int MAXN = 1 << 8;
int n, m;

char maze[MAXN][MAXN][1 << 3];
char output[MAXN][MAXN];
int c[MAXN][MAXN][2];
struct Edge {
    int to, cap, next;
} edge[MAXN * MAXN * MAXN * 4];
int head[MAXN * MAXN], dfn[MAXN * MAXN], ec;
int sidx = 0, tidx = 1, row_idx, col_idx;

void init_graph()
{
    memset(c, 0, sizeof(c));
    memset(head, -1, sizeof(head));
    ec = 0;
}
void add_edge(int u, int v, int cap)
{
    edge[ec] = Edge{v, cap, head[u]};
    head[u] = ec++;
}

int str2int(const char *s)
{
    if (s[0] == '.') {
        return -1;
    }
    if (s[0] == 'X') {
        return -2;
    }
    int ret = 0;
    assert(strlen(s) < 4);
    for (int i = 0; i < strlen(s); ++i) {
        ret = ret * 10 + s[i] - '0';
    }
    return ret;
}

void build_graph()
{
    char pos1[4], pos2[4], pad;
    row_idx = tidx;
    int row;
    std::vector<int> bv;
    for (int i = 0; i < n; ++i) {
        for (int j = m - 1; j >= 0; --j) {
            sscanf(maze[i][j], "%3s%c%3s", pos1, &pad, pos2);
            int v2 = str2int(pos2);
            if (v2 > 0) {
                _DEBUG_CMD({ printf("%d,%d pos:%s > 0\n", i, j, pos2); });
                row_idx += 1;
                row = i * m + j + 2;
                add_edge(sidx, row, v2 - bv.size());
                add_edge(row, sidx, 0);
                for (int k = 0; k < bv.size(); ++k) {
                    int blank = i * m + bv[k] + 2;
                    add_edge(row, blank, 8);
                    add_edge(blank, row, 0);
                }
                bv.clear();
                c[i][j][1] = v2;
            }
            else if (v2 == -1) {
                bv.push_back(j);
            }
            else if (v2 == -2) {
                assert(bv.size() == 0);
            }
        }
    }
    assert(bv.size() == 0);
    col_idx = row_idx;
    int col;
    for (int j = 0; j < m; ++j) {
        for (int i = n - 1; i >= 0; --i) {
            sscanf(maze[i][j], "%3s", pos1);
            int v1 = str2int(pos1);
            if (v1 > 0) {
                _DEBUG_CMD({ printf("%d,%d pos:%s > 0\n", i, j, pos1); });
                col_idx += 1;
                col = i * m + j + 2 + n * m;
                add_edge(col, tidx, v1 - bv.size());
                add_edge(tidx, col, 0);
                for (int k = 0; k < bv.size(); ++k) {
                    // int blank = i * m + bv[k] + 2;
                    int blank = bv[k] * m + j + 2;
                    add_edge(blank, col, 8);
                    add_edge(col, blank, 0);
                    _DEBUG_CMD(printf("(%d,%d)->(%d,%d)\n", bv[k], j, i, j));
                }
                bv.clear();
                c[i][j][0] = v1;
            }
            else if (v1 == -1) {
                bv.push_back(i);
            }
            else if (v1 == -2) {
                assert(bv.size() == 0);
            }
        }
    }
}

void debug_node(int u)
{
    printf("u:%d ", u);
    for (int h = head[u]; h != -1; h = edge[h].next) {
        printf("(%d,%d) ", edge[h].to, edge[h].cap);
    }
    printf("\n");
}
void debug_graph()
{
    for (int i = 0; i <= col_idx; ++i) {
        if (head[i] != -1) {
            debug_node(head[i]);
        }
    }
}

bool bfs(int s, int t)
{
    memset(dfn, -1, sizeof(dfn));
    std::queue<int> q;
    dfn[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int h = head[u]; h != -1; h = edge[h].next) {
            Edge &e = edge[h];
            int v = edge[h].to;
            if (dfn[v] == -1 && e.cap > 0) {
                dfn[v] = dfn[u] + 1;
                q.push(v);
            }
        }
    }
    return dfn[t] != -1;
}
int dfs(int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    int ret = 0;
    for (int h = head[u]; h != -1; h = edge[h].next) {
        Edge &e = edge[h];
        Edge &revE = edge[h ^ 0x01];
        int v = e.to;
        if (dfn[v] == dfn[u] + 1 && e.cap > 0) {
            int d = dfs(v, t, min(e.cap, f - ret));
            if (d > 0) {
                e.cap -= d;
                revE.cap += d;
                ret += d;
                if (ret == f) {
                    break;
                }
            }
        }
    }
    if (ret == 0) {
        dfn[u] = -1;
    }
    return ret;
}
int dinic()
{
    int maxflow = 0;
    while (bfs(sidx, tidx)) {
        maxflow += dfs(sidx, tidx, INF);
    }
    return maxflow;
}

void print_output()
{
    memset(output, '_', sizeof(output));
    _DEBUG_CMD({
        printf("cmap:\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%03d\\%03d ", c[i][j][0], c[i][j][1]);
            }
            printf("\n");
        }
    });
    for (int s1 = head[sidx]; s1 != -1; s1 = edge[s1].next) {
        int to = edge[s1].to;
        _DEBUG_CMD({
            int i = (to - 2) / m;
            int j = (to - 2) % m;
            printf("s1:%d coord:(%d, %d) m:%d\n", s1, i, j, m);
        });
        for (int h = head[to]; h != -1; h = edge[h].next) {
            if ((h & 0x01) == 0) {
                Edge &e = edge[h];
                int v = e.to;
                int i = (v - 2) / m;
                int j = (v - 2) % m;
                output[i][j] = 8 - e.cap + 1 + '0';
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j == 0) {
                printf("%c", output[i][j]);
            }
            else {
                printf(" %c", output[i][j]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    while (~scanf("%d%d", &n, &m)) {
        init_graph();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%s", maze[i][j]);
            }
        }
        build_graph();
        int ret = dinic();
        // printf("%d\n", ret);
        print_output();
    }
    return 0;
};

#endif
