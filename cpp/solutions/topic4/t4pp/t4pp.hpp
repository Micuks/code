#ifndef _t4pp_20191226_
#define _t4pp_20191226_
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

const long long INF = 0x3F3F3F3F3F3F3F3F;
const int MAXN = 2e5 + 3;
int T, N, M, C;
int visited[MAXN * 3];
int layer_max;
int layer;

struct Edge {
    int u, v;
    int next;
    long long cost;
} edges[MAXN * 3];
int edge_cnt = 0;
int head[MAXN * 3];
void add_edge(int u, int v, long long cost)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].u = u;
    edges[edge_cnt].v = v;
    edges[edge_cnt].cost = cost;
    head[u] = edge_cnt++;
}

long long dist[MAXN * 3];

struct Node {
    int u;
    long long int cost;
    bool operator<(const Node &n) const { return cost > n.cost; }
    Node(int u = 1, long long int cost = 0) : u(u), cost(cost) {}
};

long long int dijkstra()
{
    priority_queue<Node> mqueue;
    dist[1] = 0;
    mqueue.push(Node());
    while (!mqueue.empty()) {
        int u = mqueue.top().u;
        mqueue.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = 1;
        DEBUG_CMD(cout << u << " is minimum, v: ";);
        for (int h = head[u]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            if (!visited[e.v] && dist[e.v] > dist[e.u] + e.cost) {
                dist[e.v] = dist[e.u] + e.cost;
                mqueue.push(Node(e.v, dist[e.v]));
                DEBUG_CMD(cout << "v:" << e.v << ",d:" << dist[e.v] << ' ';);
            }
        }
        DEBUG_CMD(cout << endl;);
    }
    DEBUG_CMD(for (int i = 1; i <= 2 * N; ++i) { cout << dist[i] << ' '; } cout << endl;);
    return dist[N];
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        edge_cnt = 0;
        layer_max = 0;
        memset(head, -1, sizeof(head));
        memset(visited, 0, sizeof(visited));
        memset(dist, 0x3F, sizeof(dist));
        scanf("%d%d%d", &N, &M, &C);
        for (int j = 1; j <= N; ++j) {
            scanf("%d", &layer);
            layer_max = max(layer_max, layer);
            add_edge(j, N + 2 * layer, 0);
            add_edge(N + 2 * layer + 1, j, 0);
        }
        for (int j = 1; j <= layer_max + 1; ++j) {
            add_edge(N + 2 * j, N + 2 * j - 1, C);
            add_edge(N + 2 * (j - 1), N + 2 * j + 1, C);
        }
        for (int j = 1; j <= M; ++j) {
            int u, v, cost;
            scanf("%d%d%d", &u, &v, &cost);
            add_edge(u, v, cost);
            add_edge(v, u, cost);
        }
        DEBUG_CMD(for (int j = 1; j <= N + 2 * layer_max + 3; ++j) {
            cout << "after edges added u:" << j << ";v,c:";
            for (int h = head[j]; h != -1; h = edges[h].next) {
                cout << edges[h].v << "," << edges[h].cost << ' ';
            }
            cout << endl;
        });
        long long res = dijkstra();
        // DEBUG_CMD(printf("Case #%d: %lld\n", i, -1););
        DEBUG_CMD(printf("Case #%d: -1\n", i););
        if (res != INF) {
            printf("Case #%d: %lld\n", i, res);
        }
        else {
            printf("Case #%d: -1\n", i);
        }
    }
    return 0;
};

#endif
