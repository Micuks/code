#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int N = 305;
int n, tot, mn;
;
int vis[N], head[N], c[N][N], d[N];
struct Edge {
    int v, w, next;
} e[N * N << 1];
void adde(int u, int v, int w)
{
    e[tot].v = v;
    e[tot].w = w;
    e[tot].next = head[u];
    head[u] = tot++;
}
void spfa(int s)
{
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    memset(d, INF, sizeof(d));
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (d[v] > d[u] + e[i].w) {
                d[v] = d[u] + e[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
            if (v == s) {
                mn = min(mn, d[u] + e[i].w);
            }
        }
    }
    return;
}
int main()
{
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                scanf("%d", &c[i][j]);
        memset(head, -1, sizeof(head));
        tot = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j)
                    continue;
                adde(i, j, c[i][j]);
            }
        }
        mn = INF;
        spfa(1);
        int tmp = mn, ans = INF;
        mn = INF;
        ans = d[n];
        spfa(n);
        ans = min(ans, mn + tmp);
        cout << ans << endl;
    }
    return 0;
}

#else
#ifndef _t4pr_20191227_
#define _t4pr_20191227_
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

const int MAXN = 512;
int n;
int c[MAXN][MAXN];
int dist[MAXN];
int visited[MAXN];

int dijkstra()
{
    dist[1] = 0;
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
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && dist[j] > dist[min_idx] + c[min_idx][j]) {
                dist[j] = dist[min_idx] + c[min_idx][j];
            }
        }
    }
    return dist[n];
}

int spfa(int ori)
{
    int min_cir = 0x3F3F3F3F;
    dist[ori] = 0x3F3F3F3F;
    // visited[ori] = 1;
    queue<int> mqueue;
    for (int i = 1; i <= n; ++i) {
        if (i == ori) {
            continue;
        }
        dist[i] = c[ori][i];
        mqueue.push(i);
        visited[i] == 1;
        // DEBUG_CMD({ printf("dist[%d]=%d ", i, dist[i]); });
    }
    // DEBUG_CMD({ cout << endl; });
    DEBUG_CMD({
        cout << "dist before spfa: ";
        for (int i = 1; i <= n; ++i) {
            cout << dist[i] << " ";
        }
        cout << endl;
    });
    // mqueue.push(ori);
    while (!mqueue.empty()) {
        int u = mqueue.front();
        mqueue.pop();
        visited[u] = 0;
        for (int i = 1; i <= n; ++i) {
            DEBUG_CMD({
                if (i == ori) {
                    printf("visited[%d]=%d, dist[%d](%d) : dist[%d](%d) + c[%d][%d](%d)\n", i,
                           visited[i], i, dist[i], u, dist[u], u, i, c[u][i]);
                }
            });
            if (dist[i] > dist[u] + c[u][i]) {
                dist[i] = dist[u] + c[u][i];
                if (!visited[i]) {
                    visited[i] = 1;
                    mqueue.push(i);
                }
                if (i == ori) {
                    min_cir = min(min_cir, dist[i]);
                }
            }
        }
    }
    DEBUG_CMD({
        cout << "dists for spfa: ";
        for (int i = 1; i <= n; ++i) {
            cout << dist[i] << ' ';
        }
        cout << endl;
    });
    return min_cir;
}

int dijkstra2(int ori)
{
    for (int i = 1; i <= n; ++i) {
        if (i == ori) {
            continue;
        }
        dist[i] = c[ori][i];
        // mqueue.push(i);
        // visited[i] == 1;
        // DEBUG_CMD({ printf("dist[%d]=%d ", i, dist[i]); });
    }
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
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && dist[j] > dist[min_idx] + c[min_idx][j]) {
                dist[j] = dist[min_idx] + c[min_idx][j];
            }
        }
    }
    return dist[ori];
}

int main(int argc, char **argv)
{
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &c[i][j]);
                if (i == j) {
                    c[i][j] = 0x3F3F3F3F;
                }
            }
        }
        memset(dist, 0x3F, sizeof(dist));
        memset(visited, 0, sizeof(visited));
        int min_route = dijkstra();
        memset(dist, 0x3F, sizeof(dist));
        memset(visited, 0, sizeof(visited));
        // int min_cir1 = spfa(1);
        int min_cir1 = dijkstra2(1);
        memset(dist, 0x3F, sizeof(dist));
        memset(visited, 0, sizeof(visited));
        // int min_cir2 = spfa(n);
        int min_cir2 = dijkstra2(n);
        DEBUG_CMD({
            cout << "min_route: " << min_route << endl;
            cout << "min_cir1: " << min_cir1 << endl;
            cout << "min_cirn: " << min_cir2 << endl;
        });
        cout << min(min_route, min_cir1 + min_cir2) << endl;
    }
    return 0;
};

#endif
#endif
