#ifndef _t4pq_20191226_
#define _t4pq_20191226_
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

const int MAXV = 1009;
const int MAXE = 100003;
int T;
int n, m;
int A, B;
int visited[MAXV];
int dist[MAXV];
int city_map[MAXV][MAXV];

struct Edge {
    int u, v, next, cost;
} edges[MAXE];
int head[MAXV];
int edge_cnt = 0;
void add_edge(int u, int v, int cost)
{
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].u = u;
    edges[edge_cnt].v = v;
    edges[edge_cnt].cost = cost;
    head[u] = edge_cnt++;
}

void dijkstra()
{
    // visited[A] = 1;
    dist[A] = 0;
    for (int i = 1; i < n; ++i) {
        int min_idx;
        int min_val = 0x3F3F3F3F;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && min_val > dist[j]) {
                min_val = dist[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int h = head[min_idx]; h != -1; h = edges[h].next) {
            const Edge &e = edges[h];
            if (!visited[e.v] && dist[e.v] > dist[e.u] + e.cost) {
                dist[e.v] = dist[e.u] + e.cost;
            }
        }
        /*
        for (int j = 1; j <= n; ++j) {
        }
        */
    }
}

int bfs(int cm[MAXV][MAXV], int prev[MAXV])
{
    queue<int> mqueue;
    mqueue.push(A);
    prev[A] = 0;

    while (!mqueue.empty()) {
        int u = mqueue.front();
        mqueue.pop();
        for (int i = 1; i <= n; ++i) {
            if (cm[u][i] != 0) {
            }
        }
    }
}
int dfs(int city_map[MAXV][MAXV], int u, int t, int f)
{
    if (u == t) {
        return f;
    }
    visited[u] = 1;
    for (int i = 1; i <= n; ++i) {
        int &c = city_map[u][i];
        if (!visited[i] && c > 0) {
            int d = dfs(city_map, i, t, min(f, c));
            if (d > 0) {
                c -= d;
                city_map[i][u] += d;
                return d;
            }
        }
    }
    return 0;
}

int maxflow()
{
    /*
    int city_map_res[MAXV][MAXV];
    int prev[MAXV];
    memset(city_map_res, 0, sizeof(city_map_res));
    int augment_flow = bfs(city_map, prev);
    */
    int flow = 0;
    while (true) {
        memset(visited, 0, sizeof(visited));
        int f = dfs(city_map, A, B, 0x3F3F3F3F);
        if (f == 0) {
            return flow;
        }
        flow += f;
    }
    return 0;
}

int main(int argc, char **argv)
{
    cin >> T;
    while (T--) {
        int a, b, c;
        edge_cnt = 0;
        memset(city_map, 0, sizeof(city_map));
        memset(dist, 0x3F, sizeof(dist));
        memset(visited, 0, sizeof(visited));
        memset(head, -1, sizeof(head));
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            // city_map[a][b] = c;
            add_edge(a, b, c);
        }
        cin >> A >> B;
        dijkstra();
        DEBUG_CMD({
            cout << "dist[]: ";
            for (int i = 1; i <= n; ++i) {
                cout << dist[i] << ' ';
            }
            cout << endl;
        });
        for (int i = 0; i < edge_cnt; ++i) {
            const Edge &e = edges[i];
            if (dist[e.v] == dist[e.u] + e.cost) {
                city_map[e.u][e.v]++;
            }
        }
        DEBUG_CMD({
            cout << "city map:\n";
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    cout << city_map[i][j] << ' ';
                }
                cout << endl;
            }
        });
        int res = maxflow();
        cout << res << endl;
    }
    return 0;
};

#endif
