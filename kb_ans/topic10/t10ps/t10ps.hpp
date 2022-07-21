#if 0

#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define ll long long
using namespace std;
//一般图匹配带花树
const int MAXN = 55;
int N; //点的个数，点的编号从1到N
bool Graph[MAXN][MAXN];
int Match[MAXN];
bool InQueue[MAXN], InPath[MAXN], InBlossom[MAXN];
int Head, Tail;
int Queue[MAXN];
int Start, Finish;
int NewBase;
int Father[MAXN], Base[MAXN];
int Count; //匹配数，匹配对数是Count/2
void Push(int u)
{
    Queue[Tail] = u;
    Tail++;
    InQueue[u] = true;
}
int Pop()
{
    int res = Queue[Head];
    Head++;
    return res;
}
int FindCommonAncestor(int u, int v)
{
    memset(InPath, false, sizeof(InPath));
    while (true) {
        u = Base[u];
        InPath[u] = true;
        if (u == Start)
            break;
        u = Father[Match[u]];
    }
    while (true) {
        v = Base[v];
        if (InPath[v])
            break;
        v = Father[Match[v]];
    }
    return v;
}
void ResetTrace(int u)
{
    int v;
    while (Base[u] != NewBase) {
        v = Match[u];
        InBlossom[Base[u]] = InBlossom[Base[v]] = true;
        u = Father[v];
        if (Base[u] != NewBase)
            Father[u] = v;
    }
}
void BloosomContract(int u, int v)
{
    NewBase = FindCommonAncestor(u, v);
    memset(InBlossom, false, sizeof(InBlossom));
    ResetTrace(u);
    ResetTrace(v);
    if (Base[u] != NewBase)
        Father[u] = v;
    if (Base[v] != NewBase)
        Father[v] = u;
    for (int tu = 1; tu <= N; tu++)
        if (InBlossom[Base[tu]]) {
            Base[tu] = NewBase;
            if (!InQueue[tu])
                Push(tu);
        }
}
void FindAugmentingPath()
{
    memset(InQueue, false, sizeof(InQueue));
    memset(Father, 0, sizeof(Father));
    for (int i = 1; i <= N; i++)
        Base[i] = i;
    Head = Tail = 1;
    Push(Start);
    Finish = 0;
    while (Head < Tail) {
        int u = Pop();
        for (int v = 1; v <= N; v++)
            if (Graph[u][v] && (Base[u] != Base[v]) && (Match[u] != v)) {
                if ((v == Start) || ((Match[v] > 0) && Father[Match[v]] > 0))
                    BloosomContract(u, v);
                else if (Father[v] == 0) {
                    Father[v] = u;
                    if (Match[v] > 0)
                        Push(Match[v]);
                    else {
                        Finish = v;
                        return;
                    }
                }
            }
    }
}
void AugmentPath()
{
    int u, v, w;
    u = Finish;
    while (u > 0) {
        v = Father[u];
        w = Match[v];
        Match[v] = u;
        Match[u] = v;
        u = w;
    }
}
void Edmonds()
{
    memset(Match, 0, sizeof(Match));
    for (int u = 1; u <= N; u++)
        if (Match[u] == 0) {
            Start = u;
            FindAugmentingPath();
            if (Finish > 0)
                AugmentPath();
        }
}
int m, u[155], v[155];
bool g[MAXN][MAXN];

void print_debug_edge()
{
    int ecnt = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (Graph[i][j]) {
                printf("edge %d, from: %d to: %d\n", ecnt++, i, j);
            }
        }
    }
}
int main()
{
    while (~scanf("%d%d", &N, &m)) {
        memset(Graph, false, sizeof(Graph));
        memset(g, false, sizeof(g));
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &u[i], &v[i]);
            Graph[u[i]][v[i]] = Graph[v[i]][u[i]] = true;
            g[u[i]][v[i]] = g[v[i]][u[i]] = true; //原图
        }
        Edmonds(); //进行匹配
        print_debug_edge();
        printf("edge matches: ");
        for (int i = 1; i <= N; ++i) {
            printf("%d ", Match[i]);
        }
        printf("\n");
        Count = 0;
        for (int u = 1; u <= N; u++)
            if (Match[u] > 0)
                Count++;
        Count /= 2;
        printf("c:%d\n", Count);
        vector<int> ans;
        for (int i = 1; i <= m; i++) {
            memcpy(Graph, g, sizeof(g));
            for (int j = 1; j <= N; j++) {
                Graph[u[i]][j] = Graph[j][u[i]] = false;
                Graph[v[i]][j] = Graph[j][v[i]] = false;
            }
            Edmonds(); //进行匹配
            print_debug_edge();
            printf("%d th edge matches: ", i - 1);
            for (int j = 1; j <= N; ++j) {
                printf("%d ", Match[j]);
            }
            printf("\n");
            int temp = 0;
            for (int u = 1; u <= N; u++)
                if (Match[u] > 0)
                    temp++;
            temp /= 2;
            printf("newc:%d\n", temp);
            if (temp < Count - 1)
                ans.push_back(i);
        }
        int siz = ans.size();
        printf("%d\n", siz);
        for (int i = 0; i < siz; i++) {
            printf("%d", ans[i]);
            if (i != siz - 1)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}

#else
#ifndef _t10ps_20210618_
#define _t10ps_20210618_
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
//#define DEBUG
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
const int MAXM = 1 << 8;
int n, m;
// int g[MAXN][MAXN];
int markfordelete;
int match[MAXN], pre[MAXN], visit[MAXN], fa[MAXN], dfn[MAXN], tim;
// int que[MAXN], qhead, qtail;
// int pt[MAXN];

struct Edge {
    int u, v, idx, next;
    int valid;
} edges[MAXM];
int edge_cnt = 0, head[MAXN];

void init_graph()
{
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
}

void add_edge(int u, int v, int idx)
{
    edges[edge_cnt].u = u;
    edges[edge_cnt].v = v;
    edges[edge_cnt].valid = 1;
    edges[edge_cnt].idx = idx;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

int ufind(int x) { return fa[x] == x ? x : fa[x] = ufind(fa[x]); }
int LCA(int x, int y)
{
    ++tim;
    x = ufind(x);
    y = ufind(y);
    while (dfn[x] != tim) {
        dfn[x] = tim;
        x = ufind(pre[match[x]]);
        if (y)
            std::swap(x, y);
    }
    return x;
}

queue<int> Q;
void blossom(int x, int y, int lcaRoot)
{
    while (ufind(x) != lcaRoot) {
        pre[x] = y, y = match[x];
        if (visit[y] == 2)
            visit[y] = 1, Q.push(y);
        if (ufind(x) == x)
            fa[x] = lcaRoot;
        if (ufind(y) == y)
            fa[y] = lcaRoot;
        x = pre[y];
    }
}

bool augment(int s)
{
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    memset(dfn, 0, sizeof(dfn));
    tim = 0;

    memset(visit, 0, sizeof(visit));
    memset(pre, 0, sizeof(pre));

    while (!Q.empty())
        Q.pop();
    Q.push(s);
    visit[s] = 1; // black node, 2 denotes white node

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int n = head[u]; n != -1; n = edges[n].next) {
            int v = edges[n].v;
            if (edges[n].valid == 0) {
                continue;
            }
            if (ufind(u) == ufind(v) || visit[v] == 2) {
                continue;
            }
            if (!visit[v]) {
                visit[v] = 2;
                pre[v] = u;
                if (!match[v]) {
                    for (int x = v, lst; x; x = lst) {
                        lst = match[pre[x]], match[x] = pre[x], match[pre[x]] = x;
                    }
                    return true;
                }
                visit[match[v]] = 1, Q.push(match[v]);
            }
            else {
                int root = LCA(u, v);
                blossom(u, v, root);
                blossom(v, u, root);
            }
        }
    }
    return false;
}

int blossom_km()
{
    int ans = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; ++i) {
        if (!match[i]) {
            if (augment(i)) {
                ans += 1;
            }
        }
    }
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (match[i] != 0) {
            ++ans;
        }
    }
    return ans;
}

void invalid_edge(int u)
{
    for (int i = 0; i < edge_cnt; ++i) {
        if (edges[i].u == u || edges[i].v == u) {
            edges[i].valid = 0;
        }
    }
}

void valid_edge(int u)
{
    for (int i = 0; i < edge_cnt; ++i) {
        if (edges[i].u == u || edges[i].v == u) {
            edges[i].valid = 1;
        }
    }
}

void print_valid_edge()
{
    for (int i = 0; i < edge_cnt; ++i) {
        if (edges[i].valid == 1) {
            printf("e:%d from:%d to:%d\n", i, edges[i].u, edges[i].v);
        }
    }
}
int main(int argc, char **argv)
{
    int u, v;
    while (~scanf("%d%d", &n, &m)) {
        init_graph();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v, i);
            add_edge(v, u, i);
        }
        // markfordelete = -1;
        int c = blossom_km() / 2;
        DEBUG_CMD(print_valid_edge());
        DEBUG_CMD({
            printf("edge matches: ");
            for (int j = 1; j <= n; ++j) {
                printf("%d ", match[j]);
            }
            printf("\n");
        });
        DEBUG_CMD(printf("c:%d\n", c));
        vector<int> rv;
        for (int i = 0; i < edge_cnt; i += 2) {
            const Edge &e = edges[i];
            invalid_edge(e.u);
            invalid_edge(e.v);

            // markfordelete = i;
            int newc = blossom_km() / 2;
            DEBUG_CMD(print_valid_edge());
            DEBUG_CMD({
                printf("%dth edge matches: ", i / 2);
                for (int j = 1; j <= n; ++j) {
                    printf("%d ", match[j]);
                }
                printf("\n");
            });
            DEBUG_CMD(printf("newc:%d\n", newc));
            //*
            if (newc < c - 1) {
                rv.push_back(e.idx + 1);
            }
            valid_edge(e.u);
            valid_edge(e.v);
            //*/
            /*
            if (newc <= c - 1) {
                rv.push_back(e.idx + 1);
            }
            */
            // markfordelete = -1;
        }
        rv.erase(std::unique(rv.begin(), rv.end()), rv.end());
        printf("%ld\n", rv.size());
        if (rv.size() > 0) {
            for (int i = 0; i < rv.size() - 1; ++i) {
                printf("%d ", rv[i]);
            }
            printf("%d\n", rv[rv.size() - 1]);
        }
        else {
            printf("\n");
        }
    }
    return 0;
};

#endif
#endif
