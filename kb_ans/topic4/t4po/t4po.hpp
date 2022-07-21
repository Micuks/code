#ifndef _t4po_20191225_
#define _t4po_20191225_
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

#define triple_power(x) (x) * (x) * (x)

const int MAXN = 256;
long long int traffic[MAXN][MAXN];
long long int busyness[MAXN];
int visited[MAXN];
long long int dist[MAXN];
int T, n, m, q;

struct Edge {
    int u, v, next;
    long long int cost;
} edges[MAXN * MAXN];
int head[MAXN];
int edge_cnt = 0;

void add_edge(int u, int v, long long int cost)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].u = u;
    edges[edge_cnt].v = v;
    edges[edge_cnt].cost = cost;
    head[u] = edge_cnt++;
}

void dijkstra()
{
    dist[1] = 0;
    for (int i = 1; i < n; ++i) {
        int min_idx;
        long long int min_val = 0x3F3F3F3F3F3F3F3F;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && min_val > dist[j]) {
                min_val = dist[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && dist[j] > min_val + traffic[min_idx][j]) {
                dist[j] = min_val + traffic[min_idx][j];
            }
        }
    }
}

int find(int x)
{
    if (visited[x] == x) {
        return x;
    }
    else {
        return visited[x] = find(visited[x]);
    }
}
void union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot != yroot) {
        visited[yroot] = xroot;
    }
}
bool same_group(int x, int y) { return find(x) == find(y); }

void bellman_ford()
{
    dist[1] = 0;
    visited[1] = 1;
    for (int i = 1; i < n; ++i) {
        visited[i] = i;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < edge_cnt; ++j) {
            const Edge &e = edges[j];
            if (dist[e.v] > dist[e.u] + e.cost) {
                dist[e.v] = dist[e.u] + e.cost;
                union_set(e.u, e.v);
            }
        }
    }
    DEBUG_CMD(for (int i = 1; i <= n; ++i) {
        cout << visited[i] << ' ';
        cout << endl;
    });
}

int main(int argc, char **argv)
{
    cin >> T;
    for (int x = 1; x <= T; ++x) {
        int source, dest;
        memset(visited, 0, sizeof(visited));
        memset(dist, 0x3F, sizeof(dist));
        memset(busyness, 0x3F, sizeof(busyness));
        memset(traffic, 0x3F, sizeof(traffic));
        memset(head, -1, sizeof(head));
        edge_cnt = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &busyness[i]);
        }
        cin >> m;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &source, &dest);
            // traffic[source][dest] = triple_power(busyness[source] - busyness[dest]);
            add_edge(source, dest, triple_power(busyness[dest] - busyness[source]));
        }

        // dijkstra();
        bellman_ford();
        cin >> q;
        cout << "Case " << x << ":\n";
        for (int i = 1; i <= q; ++i) {
            scanf("%d", &dest);
            if (dist[dest] < 3 || dist[dest] == 0x3F3F3F3F3F3F3F3F || !same_group(dest, 1)) {
                printf("?\n");
            }
            else {
                printf("%lld\n", dist[dest]);
            }
        }
    }
    return 0;
};

#endif
