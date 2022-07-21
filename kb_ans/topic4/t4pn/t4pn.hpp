#ifndef _t4pn_20191225_
#define _t4pn_20191225_
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

const int MAXN = 128;
int N, A, B;
int visited[MAXN];
int route[MAXN][MAXN];
int dist[MAXN];

int dijkstra()
{
    // visited[A] = 1;
    dist[A] = 0;

    for (int i = 1; i < N; ++i) {
        int min_idx;
        int min_val = 0x3F3F3F3F;
        for (int j = 1; j <= N; ++j) {
            if (!visited[j] && min_val > dist[j]) {
                min_val = dist[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int j = 1; j <= N; ++j) {
            if (!visited[j] && route[min_idx][j] != -1 && dist[j] > route[min_idx][j] + min_val) {
                dist[j] = route[min_idx][j] + min_val;
            }
        }
    }

    return dist[B] == 0x3F3F3F3F ? -1 : dist[B];
}

int main(int argc, char **argv)
{
    int k, to;
    memset(visited, 0, sizeof(visited));
    memset(route, -1, sizeof(route));
    memset(dist, 0x3F, sizeof(dist));
    cin >> N >> A >> B;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &k);
        for (int j = 1; j <= k; ++j) {
            scanf("%d", &to);
            if (j == 1) {
                route[i][to] = 0;
            }
            else {
                route[i][to] = 1;
            }
        }
    }
    int res = dijkstra();
    cout << res << endl;
    return 0;
};

#endif
