#ifndef _t4pa_20191209_
#define _t4pa_20191209_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int MAX = 0x3F3F3F3F;
int N, T;
int m[1024][1024];
int visited[1024];
int dist[1024];

int dijkstra(int start, int end)
{
    // int res = -1;
    visited[start] = 1;
    for (int i = 0; i < N; ++i) {
        dist[i] = m[start][i];
    }

    for (int i = 1; i < N; ++i) {
        int min_val = MAX;
        int idx;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && dist[j] < min_val) {
                min_val = dist[j];
                idx = j;
            }
        }
        visited[idx] = 1;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && dist[j] > dist[idx] + m[idx][j]) {
                dist[j] = dist[idx] + m[idx][j];
            }
        }
    }
    return dist[end - 1];
}

int main(int argc, char **argv)
{
    memset(m, 0x3F, sizeof(int) * 1024 * 1024);
    memset(dist, 0x3F, sizeof(int) * 1024);
    memset(visited, 0, sizeof(int) * 1024);
    cin >> T >> N;
    int x, y, tc;
    while (cin >> x >> y >> tc) {
        m[x - 1][y - 1] = min(tc, m[x - 1][y - 1]);
        m[y - 1][x - 1] = min(tc, m[y - 1][x - 1]);
    }
    dijkstra(0, N);
    cout << dist[N - 1] << endl;

    return 0;
};

#endif
