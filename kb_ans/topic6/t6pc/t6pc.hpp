#ifndef _t6pc_20200111_
#define _t6pc_20200111_
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

const int MAXN = 128;
int n;
float xi[MAXN], yi[MAXN], zi[MAXN], r[MAXN];
float dist[MAXN][MAXN];

#define EUCLIDEAN_D(x, y, z) sqrt((x) * (x) + (y) * (y) + (z) * (z))

float prim()
{
    float d[MAXN];
    int visited[MAXN];
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; ++i) {
        d[i] = dist[i][0];
    }
    visited[0] = 1;
    for (int i = 1; i < n; ++i) {
        int min_idx;
        float min_val = 1e9;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && min_val > d[j]) {
                min_idx = j;
                min_val = d[j];
            }
        }
        visited[min_idx] = 1;
        for (int j = 0; j < n; ++j) {
            // if (!visited[j] && d[j] > min_val + dist[min_idx][j]) {
            if (!visited[j] && d[j] > dist[min_idx][j]) {
                // d[j] = min_val + dist[min_idx][j];
                d[j] = dist[min_idx][j];
            }
        }
    }
    _DEBUG_CMD({
        cout << "d[i]: ";
        for (int i = 0; i < n; ++i) {
            cout << d[i] << " ";
        }
        cout << endl;
        cout << "dist[i][0]: ";
        for (int i = 0; i < n; ++i) {
            cout << dist[i][0] << ' ';
        }
        cout << endl;
    });
    // return *max_element(d, d + n);
    return accumulate(d, d + n, 0.0f);
}

int main(int argc, char **argv)
{
    while (cin >> n && n != 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%f%f%f%f", &xi[i], &yi[i], &zi[i], &r[i]);
        }
        // DEBUG_CMD({ cout << "here i am, all data input done\n"; });
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                dist[i][j] = dist[j][i] =
                    EUCLIDEAN_D(xi[i] - xi[j], yi[i] - yi[j], zi[i] - zi[j]) - r[i] - r[j];
                if (dist[i][j] < 0) {
                    dist[i][j] = dist[j][i] = 0;
                }
            }
        }
        float res = prim();
        printf("%.3f\n", res);
    }
    return 0;
};

#endif
