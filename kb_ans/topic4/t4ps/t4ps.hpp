#if 0
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
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define INF 0xfffffff
using namespace std;

const int V = 1010;
const int E = 20010;
int n, ml, md;
int pnt[E], cost[E], nxt[E];
int e, head[V], dis[V];
int vis[V];
int cnt[V];

int relax(int u, int v, int c)
{
    if (dis[v] > dis[u] + c) {
        dis[v] = dis[u] + c;
        return 1;
    }
    return 0;
}

inline void addedge(int u, int v, int c)
{
    pnt[e] = v;
    cost[e] = c;
    nxt[e] = head[u];
    head[u] = e++;
}

int SPFA(int src, int n)
{
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i)
        dis[i] = INF;
    dis[src] = 0;
    queue<int> q;
    q.push(src);
    vis[src] = 1;
    ++cnt[src];
    while (!q.empty()) {
        int u, v;
        u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = nxt[i]) {
            v = pnt[i];
            if (relax(u, v, cost[i]) && !vis[v]) {
                q.push(v);
                vis[v] = 1;
                if (++cnt[v] > n)
                    return -1;
            }
        }
    }
    if (dis[n] == INF)
        return -2;
    return dis[n];
}

int main()
{
    while (~scanf("%d%d%d", &n, &ml, &md)) {
        int a, b, c;
        e = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < ml; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            if (a > b)
                swap(a, b);
            addedge(a, b, c);
        }
        for (int i = 0; i < md; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            if (a < b)
                swap(a, b);
            addedge(a, b, -c);
        }
        printf("%d\n", SPFA(1, n));
        DEBUG_CMD({
            cout << "dis: ";
            for (int i = 1; i <= n; ++i) {
                cout << dis[i] << ' ';
            }
            cout << endl;
        });
    }
    return 0;
}

#else
#ifndef _t4ps_20191228_
#define _t4ps_20191228_
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

const int MAXN = 1e6 + 3;
int N, ML, MD;
long long MLS[MAXN];
long long MDS[MAXN];
const int MAXC = 1024;
// long long farm[MAXC][MAXC];
long long dist[MAXC];
struct Edge {
    int u;
    int v;
    int next;
    int cost;
} edges[MAXN * 2];
int edge_cnt = 0;
int head[MAXN * 2];
void add_edge(int u, int v, int c)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].u = u;
    edges[edge_cnt].v = v;
    edges[edge_cnt].cost = c;
    head[u] = edge_cnt++;
}

long long bellman_ford()
{
    dist[1] = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < edge_cnt; ++j) {
            const Edge &e = edges[j];
            if (dist[e.u] != 0x3F3F3F3F3F3F3F3F && dist[e.v] > dist[e.u] + e.cost) {
                dist[e.v] = dist[e.u] + e.cost;
                if (i == N - 1) {
                    DEBUG_CMD({
                        cerr << "dist: ";
                        for (int i = 1; i <= N; ++i) {
                            cerr << dist[i] << ' ';
                        }
                        cerr << endl;
                    });
                    return -1;
                }
            }
        }
    }
    DEBUG_CMD({
        cerr << "dist: ";
        for (int i = 1; i <= N; ++i) {
            cerr << dist[i] << ' ';
        }
        cerr << endl;
    });
    if (dist[N] == 0x3F3F3F3F3F3F3F3F) {
        return -2;
    }
    return dist[N];
}

int main(int argc, char **argv)
{
    edge_cnt = 0;
    memset(dist, 0x3F, sizeof(dist));
    memset(head, -1, sizeof(head));
    // memset(farm, 0x3F, sizeof(farm));
    cin >> N >> ML >> MD;
    DEBUG_CMD({ cerr << "N: " << N << " ML: " << ML << " MD: " << MD << endl; });
    int A, B, D;
    for (int i = 0; i < ML; ++i) {
        scanf("%d%d%d", &A, &B, &D);
        int ori = min(A, B);
        int dst = max(A, B);
        // farm[ori][dst] = D;
        add_edge(ori, dst, D);
    }
    for (int i = 0; i < MD; ++i) {
        scanf("%d%d%d", &A, &B, &D);
        int ori = max(A, B);
        int dst = min(A, B);
        // farm[ori][dst] = -D;
        add_edge(ori, dst, -D);
    }
    for (int i = 1; i + 1 < N; ++i) {
        // add_edge(i + 1, i, 0);
    }
    long long res = bellman_ford();
    cout << res << endl;
    return 0;
};

#endif
#endif
