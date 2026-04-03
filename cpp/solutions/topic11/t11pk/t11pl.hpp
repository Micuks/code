#if 0
#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int maxn = 1e4 + 5;

struct Link {
    int V, Weight, Next;
    Link(int _V = 0, int _Weight = 0, int _Next = 0) : V(_V), Weight(_Weight), Next(_Next) {}
};

// we must make large ... otherwise TLE
Link edges[maxn << 2];
int Head[maxn << 1];
int Tot;
int Depth[maxn << 1];
int Current[maxn << 1];
int T;
int N, M, D;
int Ans;
int Cnt;
char Height[maxn][maxn];
char Maze[maxn][maxn];

void Init()
{
    Tot = 0;
    memset(Head, -1, sizeof(Head));
}

void AddEdge(int U, int V, int Weight, int ReverseWeight = 0)
{
    edges[Tot].V = V;
    edges[Tot].Weight = Weight;
    edges[Tot].Next = Head[U];
    Head[U] = Tot++;
    edges[Tot].V = U;
    edges[Tot].Weight = ReverseWeight;
    edges[Tot].Next = Head[V];
    Head[V] = Tot++;
}

bool Bfs(int Start, int End)
{
    memset(Depth, -1, sizeof(Depth));
    std::queue<int> Que;
    Depth[Start] = 0;
    Que.push(Start);
    while (!Que.empty()) {
        int Vertex = Que.front();
        Que.pop();
        for (int i = Head[Vertex]; i != -1; i = edges[i].Next) {
            if (Depth[edges[i].V] == -1 && edges[i].Weight > 0) {
                Depth[edges[i].V] = Depth[Vertex] + 1;
                Que.push(edges[i].V);
            }
        }
    }
    return Depth[End] != -1;
}

int Dfs(int Vertex, int End, int NowFlow)
{
    if (Vertex == End || NowFlow == 0) {
        return NowFlow;
    }
    int UsableFlow = 0, FindFlow;
    for (int &i = Current[Vertex]; i != -1; i = edges[i].Next) {
        if (edges[i].Weight > 0 && Depth[edges[i].V] == Depth[Vertex] + 1) {
            FindFlow = Dfs(edges[i].V, End, std::min(NowFlow - UsableFlow, edges[i].Weight));
            if (FindFlow > 0) {
                edges[i].Weight -= FindFlow;
                edges[i ^ 1].Weight += FindFlow;
                UsableFlow += FindFlow;
                if (UsableFlow == NowFlow) {
                    return NowFlow;
                }
            }
        }
    }
    if (!UsableFlow) {
        Depth[Vertex] = -2;
    }
    return UsableFlow;
}

int Dinic(int Start, int End)
{
    int MaxFlow = 0;
    while (Bfs(Start, End)) {
        for (int i = 0; i <= N * M * 2 + 1; ++i) {
            Current[i] = Head[i];
        }
        MaxFlow += Dfs(Start, End, INF);
    }
    return MaxFlow;
}

int main(int argc, char *argv[])
{
    scanf("%d", &T);
    for (int Case = 1; Case <= T; ++Case) {
        Init();
        scanf("%d%d", &N, &D);
        for (int i = 1; i <= N; ++i) {
            scanf("%s", Height[i]);
            getchar();
        }
        M = strlen(Height[1]);
        for (int i = 1; i <= N; ++i) {
            scanf("%s", Maze[i]);
            getchar();
        }
        Cnt = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                int Num = M * (i - 1) + j;
                AddEdge(Num, N * M + Num, (Height[i][j - 1] - '0'));
                if (Maze[i][j - 1] == 'L') {
                    AddEdge(0, Num, 1);
                    Cnt++;
                }
                bool flag = 0;
                for (int k = i - D; k <= i + D; ++k) {
                    for (int l = j - D; l <= j + D; ++l) {
                        if (k == i && l == j) {
                            continue;
                        }
                        if (k > 0 && k <= N && l > 0 && l <= M) {
                            if (abs(k - i) + abs(l - j) <= D) {
                                AddEdge(N * M + Num, M * (k - 1) + l, INF);
                            }
                        }
                        else if (abs(k - i) + abs(l - j) <= D) {
                            if (!flag) {
                                AddEdge(N * M + Num, N * M * 2 + 1, INF);
                                flag = 1;
                            }
                        }
                    }
                }
            }
        }
        Ans = Cnt - Dinic(0, N * M * 2 + 1);
        if (Ans == 0) {
            printf("Case #%d: no lizard was left behind.\n", Case);
        }
        else if (Ans == 1) {
            printf("Case #%d: %d lizard was left behind.\n", Case, Ans);
        }
        else {
            printf("Case #%d: %d lizards were left behind.\n", Case, Ans);
        }
    }
    return 0;
}
#else
#ifndef _t11pl_20210705_
#define _t11pl_20210705_
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
const int INF = 0x3F3F3F3F;
int t, n, m, d;

char lizard[MAXN][MAXN], pillar_cnt[MAXN][MAXN];
int lcnt;

struct Edge {
    int to, cap, next;
} edge[MAXN * MAXN * 20];
int head[MAXN * MAXN], dfn[MAXN * MAXN], ec;
int sidx, tidx;

void init_graph()
{
    memset(head, -1, sizeof(head));
    ec = 0;
}
void add_edge(int u, int v, int cap)
{
    edge[ec] = Edge{v, cap, head[u]};
    head[u] = ec++;
}

void bfs_building(int x, int y)
{
    add_edge(sidx, x * m + y, 1);
    add_edge(x * m + y, sidx, 0);

    if (dfn[x * m + y] != 0) {
        return;
    }

    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int, int>(x, y));
    dfn[x * m + y] = 1;

    while (!q.empty()) {
        pair<int, int> u = q.front();
        q.pop();
        int cur_in = u.first * m + u.second, cur_out = cur_in + n * m;

        for (int i = u.first - d; i <= u.first + d; ++i) {
            for (int j = u.second - (d - abs(i - u.first)); j <= u.second + (d - abs(i - u.first));
                 ++j) {
                int pin = i * m + j, pout = i * m + j + n * m;
                if (i == u.first && j == u.second) {
                    continue;
                }
                if (i < 0 || i >= n || j < 0 || j >= m) {
                    add_edge(cur_out, tidx, INF);
                    add_edge(tidx, cur_out, 0);
                }
                if (pillar_cnt[i][j] > '0') {
                    add_edge(cur_out, pin, INF);
                    add_edge(pin, cur_out, 0);
                    if (dfn[pin] == 0) {
                        dfn[pin] = 1;
                        q.push(pair<int, int>(i, j));
                    }
                }
            }
        }
    }
}
void split_pillar_node(int x, int y)
{
    int pin = x * m + y, pout = x * m + y + n * m;
    add_edge(pin, pout, pillar_cnt[x][y] - '0');
    add_edge(pout, pin, 0);
}

void build_graph()
{
    sidx = n * m + n * m;
    tidx = sidx + 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (pillar_cnt[i][j] != '0') {
                split_pillar_node(i, j);
            }
        }
    }
    memset(dfn, 0, sizeof(dfn));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool reach_exit = false;
            int cur_in = i * m + j, cur_out = cur_in + n * m;
            if (lizard[i][j] == 'L') {
                ++lcnt;
                add_edge(sidx, cur_in, 1);
                add_edge(cur_in, sidx, 0);
            }
            for (int x = i - d; x <= i + d; ++x) {
                for (int y = j - (d - abs(x - i)); y <= j + (d - abs(x - i)); ++y) {
                    if (x == i && y == j) {
                        continue;
                    }
                    int pin = x * m + y, pout = pin + n * m;
                    if (x < 0 || x >= n || y < 0 || y >= m) {
                        if (reach_exit == false) {
                            reach_exit = true;
                            add_edge(cur_out, tidx, INF);
                            add_edge(tidx, cur_out, 0);
                        }
                    }
                    else {
                        add_edge(cur_out, pin, INF);
                        add_edge(pin, cur_out, 0);
                    }
                }
            }
        }
    }
}

void debug_print(int u)
{
    printf("u:%d ", u);
    for (int h = head[u]; h != -1; h = edge[h].next) {
        printf("(%d,%d) ", edge[h].to, edge[h].cap);
    }
    printf("\n");
}
void debug_graph()
{
    for (int i = 0; i <= tidx; ++i) {
        if (head[i] != -1) {
            debug_print(i);
        }
    }
}

bool bfs(int s, int t)
{
    memset(dfn, -1, sizeof(dfn));
    dfn[s] = 0;
    std::queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int h = head[u]; h != -1; h = edge[h].next) {
            Edge &e = edge[h];
            int v = e.to;
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
    int res = 0;
    for (int h = head[u]; h != -1; h = edge[h].next) {
        Edge &e = edge[h];
        Edge &revE = edge[h ^ 0x01];
        int v = e.to;
        if (dfn[v] == dfn[u] + 1 && e.cap > 0) {
            int d = dfs(v, t, min(f - res, e.cap));
            e.cap -= d;
            revE.cap += d;
            res += d;
            if (res == f) {
                break;
            }
        }
    }
    if (res == 0) {
        dfn[u] = -1;
    }
    return res;
}
int dinic()
{
    int maxflow = 0;
    while (bfs(sidx, tidx)) {
        maxflow += dfs(sidx, tidx, INF);
    }
    return maxflow;
}

int main(int argc, char **argv)
{
    scanf("%d", &t);
    for (int case_cnt = 0; case_cnt < t; ++case_cnt) {
        init_graph();
        lcnt = 0;
        scanf("%d%d", &n, &d);
        for (int i = 0; i < n; ++i) {
            scanf("%s", pillar_cnt[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s", lizard[i]);
        }
        m = strlen(pillar_cnt[0]);
        build_graph();
        int ret = lcnt - dinic();
        if (ret == 0) {
            printf("Case #%d: no lizard was left behind.\n", case_cnt + 1);
        }
        else if (ret == 1) {
            printf("Case #%d: %d lizard was left behind.\n", case_cnt + 1, ret);
        }
        else {
            printf("Case #%d: %d lizards were left behind.\n", case_cnt + 1, ret);
        }
    }
    return 0;
};

#endif
#endif
