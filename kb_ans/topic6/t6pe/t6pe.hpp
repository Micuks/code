#ifndef _t6pe_20200111_
#define _t6pe_20200111_
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

const int MAXN = 1024;
int t, n;
int conn_fee[MAXN];
int wire_fee[MAXN][MAXN];

int prim()
{
    // int res = 0;
    int d[MAXN];
    int visited[MAXN];
    memset(d, 0x3F, sizeof(d));
    memset(visited, 0, sizeof(visited));
    d[0] = 0;
    visited[0] = 1;
    for (int i = 1; i < n; ++i) {
        int min_val = 1e9;
        int min_idx;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && min_val > d[j]) {
                min_val = d[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && d[j] > wire_fee[min_idx][j]) {
                d[j] = wire_fee[min_idx][j];
            }
        }
    }
    return accumulate(d, d + n, 0);
}

int main(int argc, char **argv)
{
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &conn_fee[i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &wire_fee[i][j]);
                if (i != j)
                    wire_fee[i][j] = wire_fee[i][j] + conn_fee[i] + conn_fee[j];
            }
        }
        int res = prim();
        cout << res << endl;
    }
    return 0;
};

#endif
