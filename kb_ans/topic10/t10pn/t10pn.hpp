#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define LL long long
using namespace std;
const int maxn = 10000 + 10;
const int INF = 100000000;
struct Edge {
    int from, to, cap, flow;
    Edge(int u, int v, int c, int w) : from(u), to(v), cap(c), flow(w) {}
};
int n, m, s, t;
vector<Edge> edges;
vector<int> G[maxn];
bool vis[maxn];
int d[maxn];
int cur[maxn];
void init()
{
    for (int i = 0; i <= n + 1; i++)
        G[i].clear();
    edges.clear();
}
void AddEdge(int from, int to, int cap)
{
    edges.push_back(Edge(from, to, cap, 0));
    edges.push_back(Edge(to, from, 0, 0));
    int M = edges.size();
    G[from].push_back(M - 2);
    G[to].push_back(M - 1);
}
bool BFS()
{
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < G[x].size(); i++) {
            Edge &e = edges[G[x][i]];
            if (!vis[e.to] && e.cap > e.flow) {
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                Q.push(e.to);
            }
        }
    }
    return vis[t];
}
int DFS(int x, int a)
{
    if (x == t || a == 0)
        return a;
    int flow = 0, f;
    for (int &i = cur[x]; i < G[x].size(); i++) {
        Edge &e = edges[G[x][i]];
        if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
            e.flow += f;
            edges[G[x][i] ^ 1].flow -= f;
            flow += f;
            a -= f;
            if (a == 0)
                break;
        }
    }
    return flow;
}
int Maxflow()
{
    int flow = 0;
    while (BFS()) {
        memset(cur, 0, sizeof(cur));
        flow += DFS(s, INF);
    }
    return flow;
}
int K, C, M;
int dis[500][500];
void creat_graph(int limit)
{
    init();
    for (int i = K + 1; i <= n; i++)
        AddEdge(0, i, 1);
    for (int i = 1; i <= K; i++)
        AddEdge(i, n + 1, M);
    for (int i = K + 1; i <= n; i++) {
        for (int j = 1; j <= K; j++) {
            if (dis[i][j] <= limit)
                AddEdge(i, j, 1);
        }
    }
    s = 0, t = n + 1;
}
int main()
{
    while (scanf("%d%d%d", &K, &C, &M) != EOF) {
        n = K + C;
        memset(dis, 0, sizeof(dis));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &dis[i][j]);
                if (dis[i][j] == 0)
                    dis[i][j] = INF;
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
        int L = 0, R = 10000;
        int ans;
        while (L < R) {
            int m = (L + R) / 2;
            ans = 0;
            creat_graph(m);
            ans = Maxflow();
            if (ans >= C)
                R = m;
            else
                L = m + 1;
        }
        printf("%d\n", R);
    }
    return 0;
}

#elif 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 250;
const int INF = 99999999;
int n, m, sum, s1, t1; // s,t为始点和终点
int flow[maxn][maxn], cap[maxn][maxn], a[maxn], p[maxn], d[maxn][maxn], k, c, milks;
//分别为：flow[u][v]为<u,v>流量、cap[u][v]为<u,v>容量、a[i]表示源点s到节点i的路径上的最小残留量、p[i]记录i的前驱
void Edmonds_Karp(int s, int t)
{
    int i, u, v;
    queue<int> q; //队列，用bfs找增广路
    while (1) {
        memset(a, 0, sizeof(a)); //每找一次，初始化一次
        a[s] = INF;
        q.push(s); //源点入队
        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (v = 1; v <= m; v++) {
                if (!a[v] && flow[u][v] < cap[u][v]) {
                    p[v] = u;
                    q.push(v);
                    a[v] = min(a[u], cap[u][v] - flow[u][v]); // s-v路径上的最小残量
                }
            }
        }
        if (a[t] == 0) //找不到增广路,则当前流已经是最大流
            break;
        sum += a[t];                  //流加上
        for (i = t; i != s; i = p[i]) // //从汇点顺着这条增广路往回走
        {
            //      cout<<i<<" ";
            flow[p[i]][i] += a[t]; //更新正向流量
            flow[i][p[i]] -= a[t]; //更新反向流量
        }
        // cout<<endl;
    }
}
int main()
{
    int v, u, w;
    while (scanf("%d%d%d", &k, &c, &milks) != EOF) // n是边数，m是点数
    {
        int up = -1;
        int down = INF;
        for (int i = 1; i <= c + k; i++)
            for (int j = 1; j <= c + k; j++)
                scanf("%d", &d[i][j]);
        for (int k1 = 1; k1 <= c + k; k1++)
            for (int i = 1; i <= c + k; i++)
                for (int j = 1; j <= c + k; j++)
                    if (d[i][k1] && d[k1][j] && (d[i][j] == 0 || d[i][j] > d[i][k1] + d[k1][j])) {
                        d[i][j] = d[i][k1] + d[k1][j];
                        up = max(up, d[i][j]);
                        down = min(down, d[i][j]);
                    }

        m = c + k + 2;
        t1 = c + k + 2;
        s1 = c + k + 1;
        int ans = up;

        while (down <= up) {
            int mid = (down + up) / 2;
            sum = 0;                       //记录最大流量
            memset(flow, 0, sizeof(flow)); //初始化
            memset(cap, 0, sizeof(cap));
            for (int i = 1; i <= k; i++) //源点到挤奶机
                cap[s1][i] = milks;
            for (int i = k + 1; i <= k + c; i++) //奶牛到汇点
                cap[i][t1] = 1;
            for (int i = 1; i <= k; i++)
                for (int j = k + 1; j <= k + c; j++)
                    cap[i][j] = (d[i][j] != 0 && d[i][j] <= mid);
            Edmonds_Karp(s1, t1);

            if (sum == c) {
                if (mid < ans)
                    ans = mid;
                up = mid - 1;
            }
            else
                down = mid + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}

#else
#ifndef _t10pn_20210224_
#define _t10pn_20210224_
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

const int MAXN = 4000 + 10;
const int INF = 0x3F3F3F3F;
int K, C, M;
int g[MAXN][MAXN];

void floyd()
{
    const int limit = K + C;
    for (int k = 0; k < limit; ++k) {
        for (int i = 0; i < limit; ++i) {
            for (int j = 0; j < limit; ++j) {
                if (g[i][j] != INF || i != j)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}

int visited[MAXN];
int match[MAXN][1 << 4], cap[MAXN];

int dfs(int u, int max_distance, int max_cap)
{
    // for (int v = K; v < K + C; ++v) {
    for (int v = 0; v < K; ++v) {
        if (visited[v] == 0 && g[u][v] <= max_distance) {
            visited[v] = 1;
            if (cap[v] < max_cap) {
                match[v][cap[v]++] = u;
                return 1;
            }
            for (int i = 0; i < cap[v]; ++i) {
                if (dfs(match[v][i], max_distance, max_cap)) {
                    match[v][i] = u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int hungarian(int max_distance, int max_cap)
{
    memset(cap, 0, sizeof(cap));
    memset(match, -1, sizeof(match));
    // for (int i = 0; i < K; ++i) {
    for (int i = K; i < K + C; ++i) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i, max_distance, max_cap) != 1) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    scanf("%d%d%d", &K, &C, &M);
    int limit = K + C;
    int lo = INF, hi = 0;
    for (int i = 0; i < limit; ++i) {
        for (int j = 0; j < limit; ++j) {
            scanf("%d", &g[i][j]);
            hi = max(g[i][j], hi);
            if (g[i][j] == 0) {
                g[i][j] = INF;
            }
            lo = min(g[i][j], lo);
        }
    }
    floyd();
    _DEBUG_CMD({
        for (int i = 0; i < K + C; ++i) {
            for (int j = 0; j < K + C; ++j) {
                printf("%d ", g[i][j]);
            }
            printf("\n");
        }
    });
    int res = 0;
    hi = 1000000; // hi may change subject to floyd.
    lo = 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (hungarian(mid, M)) {
            res = mid;
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }
    // assert(lo == res);
    // assert(hi == res);
    printf("%d\n", res);
    return 0;
};

#endif
#endif
