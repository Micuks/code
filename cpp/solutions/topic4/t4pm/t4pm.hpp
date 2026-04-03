#if 0
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
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 110;
const int INF = 200000000;

int w[maxn][maxn]; // w[i][j]表示物品i换j的花费
int dist[maxn];    // dist[i]表示起点到i的花费
bool vis[maxn];

int level[maxn], value[maxn]; //等级与价值
bool can_change[maxn];        //满足等级限制的标记数组
int limit_level, n;           // limit_level 表示限制的等级

int Dijkstra()
{
    int mini_cost = INF;
    memset(vis, false, sizeof(vis)); //清除所有点的标号
    for (int i = 1; i <= n; i++)
        dist[i] = INF; //设d[1] = 0,其它为 INF
    dist[1] = 0;       //（此处还未加上进入改点的花费）自己换自己为0

    for (int i = 1; i <= n; i++) //循环n 次
    {
        int x, m = INF;
        for (int y = 1; y <= n; y++) { //在所有未标号且满足等级限制的点中选出 d值最小的点 x
            if (!vis[y] && dist[y] <= m && can_change[y])
                m = dist[x = y];
        }
        vis[x] = true; //标记点x
        DEBUG_CMD(cout << x << " is minimum, ");

        for (int y = 1; y <= n; y++) // 对于从x出发的所有边 (x, y)更新dist
        {
            if (can_change[y]) { //若满足等级限制
                DEBUG_CMD(cout << "v: " << y << " d: " << dist[y] << "," << m + w[x][y]
                               << " min_val: " << m << " c: " << w[x][y] << ";";);
                dist[y] = min(dist[y], dist[x] + w[x][y]);
            }
        }
        DEBUG_CMD(cout << " is relaxed\n\n");
    }

    for (int y = 1; y <= n; y++) { //对于每个dist[y]还要满足进入改点的花费
        dist[y] += value[y];
        mini_cost = min(mini_cost, dist[y]);
    }
    DEBUG_CMD(cout << mini_cost << ' ');
    /*
                DEBUG_CMD(cout << min_idx << " is minimum, ");
                for (int h = head[min_idx]; h != -1; h = edges[h].next) {
                    int c = edges[h].cost;
                    if (!visited[h] && dist[h] > min_val + c) {
                        DEBUG_CMD(cout << "v: " << h << " d: " << dist[h] << "," << min_val + c
                                       << " min_val: " << min_val << " c: " << c << ";";);
                        dist[h] = min_val + c;
                    }
                }
                DEBUG_CMD(cout << " is relaxed\n");
            }
            DEBUG_CMD(cout << dist[1] << ' ' << "\n\n");
            min_cost = min(min_cost, dist[1]);
        }
        DEBUG_CMD(cout << endl);
    */

    return mini_cost; //返回最小值
}
int main()
{
    scanf("%d%d", &limit_level, &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                w[i][j] = 0; //从自己到自己花费为0
            else
                w[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        int change;
        scanf("%d%d%d", &value[i], &level[i], &change);
        for (int j = 1; j <= change; j++) {
            int y, Value;
            scanf("%d%d", &y, &Value);
            w[i][y] = Value;
        }
    }

    int King_level = level[1]; //酋长的等级
    int m, minicost = INF;

    for (int i = 0; i <= limit_level; i++) //枚举
    {
        memset(can_change, false, sizeof(can_change));
        for (int j = 1; j <= n; j++) { //枚举等级允许的范围
            if (level[j] >= King_level - limit_level + i && level[j] <= King_level + i)
                can_change[j] = true;
        }

        minicost = min(minicost, Dijkstra());
    }
    DEBUG_CMD(cout << endl);
    printf("%d\n", minicost);
    return 0;
}

#else
#ifndef _t4pm_20191225_
#define _t4pm_20191225_
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

const int MAXN = 128 * 128;
int M, N;
int level[MAXN];
int head[MAXN];
int dist[MAXN];
int visited[MAXN];
int edge_cnt = 0;

struct Edge {
    int u;
    int v;
    int cost;
    int next;
} edges[MAXN];

void add_edge(int u, int v, int cost)
{
    for (int i = head[u]; i != -1; i = edges[i].next) {
        if (edges[i].v == v) {
            edges[i].cost = cost;
            return;
        }
    }
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].cost = cost;
    edges[edge_cnt].u = u;
    edges[edge_cnt].v = v;
    head[u] = edge_cnt++;
}

int dijkstra()
{
    int min_level = level[1] - M;
    int max_level = level[1] + M;
    DEBUG_CMD(cout << "min_level: " << min_level << " max_level: " << max_level << endl);
    int min_cost = 0x3F3F3F3F;
    int back_dist[MAXN];
    memcpy(back_dist, dist, sizeof(back_dist));
    DEBUG_CMD(for (int i = 1; i <= N; ++i) { cout << back_dist[i] << ' '; } cout << endl;);
    for (int k = min_level; k + M <= max_level; ++k) {
        memset(visited, 0, sizeof(visited));
        memcpy(dist, back_dist, sizeof(dist));
        int level_cnt = N;
        // if (M != 0) {
        DEBUG_CMD(cout << "prefilter i: ");
        for (int i = 1; i <= N; ++i) {
            if (!(level[i] >= k && level[i] <= k + M)) {
                DEBUG_CMD(cout << i << ' ');
                visited[i] = 1;
                level_cnt--;
            }
        }
        DEBUG_CMD(cout << " are visited now" << endl;);
        //}
        for (int i = 0; i < level_cnt; ++i) {
            int min_idx;
            int min_val = 1e10;
            for (int j = 1; j <= N; ++j) {
                if (!visited[j] && min_val > dist[j]) {
                    min_val = dist[j];
                    min_idx = j;
                }
            }
            visited[min_idx] = 1;
            DEBUG_CMD(cout << min_idx << " is minimum, ");
            for (int h = head[min_idx]; h != -1; h = edges[h].next) {
                int c = edges[h].cost;
                int v = edges[h].v;
                if (!visited[v] && dist[v] > min_val + c) {
                    DEBUG_CMD(cout << "v: " << v << " d: " << dist[v] << "," << min_val + c
                                   << " min_val: " << min_val << " c: " << c << ";";);
                    dist[v] = min_val + c;
                }
            }
            DEBUG_CMD(cout << " is relaxed\n");
        }
        DEBUG_CMD(for (int x = 0; x <= N; ++x) { cout << dist[x] << ' '; } cout << endl;);
        DEBUG_CMD(cout << dist[1] << ' ' << "\n\n");
        min_cost = min(min_cost, dist[1]);
    }
    DEBUG_CMD(cout << endl);
    return min_cost;
    // return *min_element(dist + 1, dist + N);
}

int main(int argc, char **argv)
{
    int p, l, x;
    int t, v;
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
    memset(dist, 0, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    cin >> M >> N;
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d%d", &p, &l, &x);
        level[i] = l;
        dist[i] = p;
        for (int j = 0; j < x; ++j) {
            scanf("%d%d", &t, &v);
            add_edge(t, i, v);
        }
    }
    DEBUG_CMD(cout << "print the graph:\n"; for (int i = 1; i <= N; ++i) {
        cout << i << " th node, to: ";
        for (int j = head[i]; j != -1; j = edges[j].next) {
            cout << edges[j].v << ' ';
        }
        cout << endl;
    } cout << "\n\n\n";);
    int res = dijkstra();
    cout << res << endl;
    return 0;
};

#endif
#endif
