#define DEBUG 1
#ifdef DEBUG
#define DEBUG_STR(str)                                                                             \
    do {                                                                                           \
        std::cout << str;                                                                          \
    } while (false)
#else
#define DEBUG_STR(str)                                                                             \
    do {                                                                                           \
    } while (false)
#endif
#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int const MAX = 405;
int const INF = 100000000.0;

struct Node {
    double u, v;
} nd[MAX];

double dis[MAX], e[MAX][MAX];
bool vis[MAX];
int cnt;

double get_dis(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void Dijkstra(int v0)
{
    for (int i = 0; i < cnt; i++)
        dis[i] = e[v0][i];
    dis[v0] = 0;
    vis[v0] = true;
    for (int i = 0; i < cnt; ++i) {
        DEBUG_STR(dis[i] * 60 << ' ');
    }
    DEBUG_STR(endl);
    for (int i = 0; i < cnt - 1; i++) {
        double mi = INF;
        int u = v0;
        for (int j = 0; j < cnt; j++) {
            if (!vis[j] && mi > dis[j]) {
                u = j;
                mi = dis[j];
            }
        }
        DEBUG_STR(u << " is the minimum, ");
        vis[u] = true;
        for (int k = 0; k < cnt; k++)
            if (!vis[k] && dis[k] > dis[u] + e[u][k]) {
                DEBUG_STR(k << ", ");
                dis[k] = dis[u] + e[u][k];
            }
        DEBUG_STR(" is relaxed\n");
    }
    for (int i = 0; i < cnt; ++i) {
        DEBUG_STR(dis[i] * 60 << ' ');
    }
    DEBUG_STR(endl);
}

int main()
{
    memset(vis, false, sizeof(vis));
    memset(e, 0, sizeof(e));
    scanf("%lf %lf %lf %lf", &nd[0].u, &nd[0].v, &nd[1].u, &nd[1].v);
    double u, v;
    int tmp = 2;
    cnt = 2;
    while (scanf("%lf %lf", &u, &v) != EOF) {
        if (u == -1.0 && v == -1.0) {
            for (int i = tmp; i < cnt - 1; i++) {
                double get = get_dis(nd[i].u, nd[i].v, nd[i + 1].u, nd[i + 1].v) / 40000.0;
                e[i][i + 1] = e[i + 1][i] = get;
            }
            tmp = cnt;
            continue;
        }
        nd[cnt].u = u;
        nd[cnt++].v = v;
    }
    for (int i = 0; i < cnt; i++)
        for (int j = i + 1; j < cnt; j++)
            if (e[i][j] == 0)
                e[i][j] = e[j][i] = get_dis(nd[i].u, nd[i].v, nd[j].u, nd[j].v) / 10000.0;
    DEBUG_STR("cmap:\n");
    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < cnt; ++j) {
            DEBUG_STR(e[i][j] * 60 << ' ');
        }
        DEBUG_STR(endl);
    }
    DEBUG_STR(endl);
    Dijkstra(0);
    printf("%d\n", (int) (dis[1] * 60.0 + 0.5));
}

#endif
//#define _t4pl_20191224_
#ifndef _t4pl_20191224_
#define _t4pl_20191224_
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

const int MAXN = 256;
struct Stop {
    double x;
    double y;
} stops[MAXN];
double cmap[MAXN][MAXN];
double hx, hy, sx, sy;
int stop_cnt = 0;
int visited[MAXN];

double euclidean_distance(const Stop &s1, const Stop &s2)
{
    return sqrt((s1.x - s2.x) * (s1.x - s2.x) + (s1.y - s2.y) * (s1.y - s2.y));
}

double dijkstra()
{
    double d[MAXN];
    for (int i = 0; i < stop_cnt; ++i) {
        d[i] = cmap[i][0];
    }
    visited[0] = 1;
    d[0] = 0;

    for (int i = 0; i < stop_cnt; ++i) {
        DEBUG_STR(d[i] << ' ');
    }
    DEBUG_STR(endl);
    for (int i = 1; i < stop_cnt; ++i) {
        int min_idx;
        double min_val = 1e10;
        for (int j = 0; j < stop_cnt; ++j) {
            if (!visited[j] && min_val > d[j]) {
                min_idx = j;
                min_val = d[j];
            }
        }
        DEBUG_STR(min_idx << " is the minimum, ");
        visited[min_idx] = 1;
        for (int j = 0; j < stop_cnt; ++j) {
            if (!visited[j] && d[j] > cmap[j][min_idx] + min_val) {
                DEBUG_STR(j << ", ");
                d[j] = cmap[j][min_idx] + min_val;
            }
        }
        DEBUG_STR(" is relaxed\n");
    }
    for (int i = 0; i < stop_cnt; ++i) {
        DEBUG_STR(d[i] << ' ');
    }
    DEBUG_STR(endl);
    return d[1];
}

int main(int argc, char **argv)
{
    double bx, by;
    int last_bus = 2;
    int node_idx = 2;
    // memset(cmap, 0, sizeof(cmap));
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            if (i == j) {
                cmap[i][j] = 0;
            }
            else {
                cmap[i][j] = 1e10;
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    cin >> hx >> hy >> sx >> sy;
    stops[0].x = hx;
    stops[0].y = hy;
    stops[1].x = sx;
    stops[1].y = sy;
    cmap[0][1] = cmap[1][0] = euclidean_distance(stops[0], stops[1]) * 6.0 / 1000.0;
    stop_cnt = 2;
    while (scanf("%lf%lf", &bx, &by) == 2) {
        if (bx != -1 && by != -1) {
            stops[node_idx].x = bx;
            stops[node_idx].y = by;
            for (int j = 0; j < last_bus; ++j) {
                cmap[j][node_idx] = cmap[node_idx][j] =
                    euclidean_distance(stops[j], stops[node_idx]) * 6.0 / 1000.0;
            }
            if (node_idx - 1 >= last_bus)
                cmap[node_idx][node_idx - 1] = cmap[node_idx - 1][node_idx] =
                    euclidean_distance(stops[node_idx - 1], stops[node_idx]) * 6.0 / 4000.0;
            ++node_idx;
            ++stop_cnt;
        }
        else {
            /*
                for (int j = last_bus; j < node_idx; ++j) {
                    float dist = 0;
                    for (int k = 1; k + j < node_idx; ++k) {
                        cmap[j][j + k] = cmap[j + k][j] =
                            euclidean_distance(stops[j + k], stops[j + k - 1]) * 6.0 / 4000.0 +
               dist; dist = cmap[j][j + k];
                    }
                }
            */
            last_bus = node_idx;
        }
    }
    for (int i = 0; i < stop_cnt; ++i) {
        for (int j = i; j < stop_cnt; ++j) {
            if (cmap[i][j] == 1e10) {
                cmap[i][j] = cmap[j][i] = euclidean_distance(stops[i], stops[j]) * 6.0 / 1000.0;
            }
        }
    }
    DEBUG_STR("cmap:\n");
    for (int i = 0; i < stop_cnt; ++i) {
        for (int j = 0; j < stop_cnt; ++j) {
            DEBUG_STR(cmap[i][j] << ' ');
        }
        DEBUG_STR(endl);
    }
    DEBUG_STR(endl);
    double ret = dijkstra();
    cout << long(ret + 0.5f) << endl;
    return 0;
};

#endif
