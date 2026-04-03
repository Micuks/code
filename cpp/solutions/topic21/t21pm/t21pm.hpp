#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 100 + 10;
struct node {
    int u;
    double p;
    node(int a, double b)
    {
        u = a;
        p = b;
    }
    bool operator<(const node &a) const { return p < a.p; }
};
struct Edge {
    int to, nxt;
    double w;
} edge[N * N];
int tot;
int first[N];
void addedge(int u, int v, double w)
{
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].nxt = first[u];
    first[u] = tot++;
}
double d[N];
void dj(int s, int n)
{
    priority_queue<node> q;
    for (int i = 0; i < n; i++)
        d[i] = 0.0;
    q.push(node(s, 1.0));
    d[s] = 1.0;
    while (!q.empty()) {
        node a = q.top();
        q.pop();
        int u = a.u;
        double p = a.p;
        for (int i = first[u]; i != -1; i = edge[i].nxt) {
            int nu = edge[i].to;
            double np = p * edge[i].w;
            if (d[nu] < np) {
                d[nu] = np;
                q.push(node(nu, np));
            }
        }
    }
}
int main()
{
    int T, kase = 0;
    int n, m, s, k;
    scanf("%d", &T);
    while (T--) {
        int a, b, c;
        tot = 0;
        memset(first, -1, sizeof(first));
        scanf("%d%d%d%d", &n, &m, &s, &k);
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            addedge(a, b, 1.0 * c / 100);
            addedge(b, a, 1.0 * c / 100);
        }
        dj(0, n);
        printf("prob: %lf\n", d[n - 1]);
        printf("Case %d: %.6f\n", ++kase, 2.0 * k * s / d[n - 1]);
    }
    return 0;
}

#else
#ifndef _t21pm_20210903_
#define _t21pm_20210903_
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

const int MAXN = 1 << 7;
int T, N, M, S, K;
// int g[MAXN][MAXN];
double g[MAXN][MAXN];
double dp[MAXN];
int vis[MAXN];

double solve1()
{
    queue<int> q;
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    dp[0] = 1;
    q.push(0);
    while (q.empty() == false) {
        int u = q.front();
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        for (int v = 1; v < N; ++v) {
            if (vis[v] == 0 && g[u][v] != 0) {
                double newp = dp[u] * (g[u][v] / 100.0);
                if (newp > dp[v]) {
                    dp[v] = newp;
                }
                q.push(v);
            }
        }
    }
    return dp[N - 1];
}

double solve2()
{
    priority_queue<int, vector<int>, std::function<bool(int, int)>> q(
        [](int i, int j) { return dp[i] < dp[j]; });
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    dp[0] = 1;
    q.push(0);
    while (q.empty() == false) {
        int u = q.top();
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        for (int v = 1; v < N; ++v) {
            if (g[u][v] != 0) {
                double newp = dp[u] * g[u][v];
                if (newp > dp[v]) {
                    dp[v] = newp;
                    q.push(v);
                    std::make_heap(const_cast<int *>(&q.top()),
                                   const_cast<int *>(&q.top()) + q.size(),
                                   [](int i, int j) { return dp[i] < dp[j]; });
                }
            }
        }
    }

    return dp[N - 1];
}
struct Node {
    int v;
    double p;
    bool operator<(const Node &n) const { return p < n.p; }
};
double solve_dijkstra()
{
    priority_queue<Node> q;
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    dp[0] = 1;
    q.push(Node{0, 1});
    while (q.empty() == false) {
        Node n = q.top();
        int u = n.v;
        double p = n.p;
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        for (int v = 1; v < N; ++v) {
            if (g[u][v] != 0) {
                double newp = p * g[u][v];
                if (newp > dp[v]) {
                    dp[v] = newp;
                    q.push(Node{v, newp});
                }
            }
        }
    }

    return dp[N - 1];
}
double solve()
{
    // floyd
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (g[j][k] < g[j][i] * g[i][k]) {
                    g[j][k] = g[j][i] * g[i][k];
                }
            }
        }
    }
    return g[0][N - 1];
}

int main(int argc, char **argv)
{
    int u, v, w;
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        scanf("%d%d%d%d", &N, &M, &S, &K);
        memset(g, 0, sizeof(g));
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = g[v][u] = w / 100.0;
        }
        // double ans = solve_dijkstra();
        double ans = solve2();
        _DEBUG_CMD(printf("ans:%lf\n", ans));
        ans = 2.0 * K * S / ans;
        printf("Case %d: %lf\n", cc, ans);
    }
    return 0;
};

#endif
#endif
