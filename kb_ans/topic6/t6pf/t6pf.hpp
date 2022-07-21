#ifndef _t6pf_20200111_
#define _t6pf_20200111_
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

const int MAXN = 2048;
int N;
vector<string> types;
int dist[MAXN][MAXN];

int prim()
{
    int d[MAXN];
    int visited[MAXN];
    memset(d, 0x3F, sizeof(d));
    memset(visited, 0, sizeof(visited));
    d[0] = 0;
    // visited[0] = 1;
    for (int i = 1; i < N; ++i) {
        int min_idx, min_val = 1e9;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && d[j] < min_val) {
                min_val = d[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && d[j] > dist[min_idx][j]) {
                d[j] = dist[min_idx][j];
            }
        }
    }
    return accumulate(d, d + N, 0);
}

int main(int argc, char **argv)
{
    while (cin >> N && N != 0) {
        types.resize(N);
        for (int i = 0; i < N; ++i) {
            cin >> types[i];
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                int d = 0;
                for (int k = 0; k < 7; ++k) {
                    if (types[i][k] != types[j][k]) {
                        ++d;
                    }
                }
                dist[i][j] = dist[j][i] = d;
            }
        }
        int res = prim();
        // cout << 1.0f / res << endl;
        printf("The highest possible quality is 1/%d.\n", res);
    }
    return 0;
};

#endif
