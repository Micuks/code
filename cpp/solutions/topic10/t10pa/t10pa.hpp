#ifndef _t10pa_20200406_
#define _t10pa_20200406_
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

const int MAXN = 32;
int N;
char maze[MAXN][MAXN];
int mazev[MAXN][MAXN];
int mazeh[MAXN][MAXN];

int g[MAXN][MAXN];

int match[MAXN];
int visited[MAXN];

int dfs_search(int x)
{
    for (int i = 0; i < N * N * 2; ++i) {
        if (!visited[i] && g[i][x]) {
            visited[i] = 1;
            if (match[i] == -1 || dfs_search(match[i])) {
                match[i] = x;
                match[x] = i;
                return 1;
            }
        }
    }
    return 0;
}

int hungarian_algo()
{
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (maze[i][j] != 'X') {
                // int idx = i * N + j;
                int idx = mazeh[i][j];
                _DEBUG_CMD({
                    printf("idx:%d\n", idx);
                    for (int k = 0; k < N * N * 2; ++k) {
                        printf("g[3][%d]: %d\n", k, g[3][k]);
                    }
                });

                // DEBUG_CMD({ printf("idx:%d\n", idx); });
                if (match[idx] == -1) {
                    memset(visited, 0, sizeof(visited));
                    sum += dfs_search(idx);
                }
            }
        }
    }
    _DEBUG_CMD({
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("match[%d]: %d\n", i * N + j, match[i * N + j]);
            }
        }
    });
    return sum;
}

int main(int argc, char **argv)
{
    while (cin >> N && N != 0) {
        int x_cnt = 0;
        memset(match, -1, sizeof(match));
        memset(g, 0, sizeof(g));
        memset(mazeh, -1, sizeof(mazeh));
        memset(mazev, -1, sizeof(mazev));

        for (int i = 0; i < N; ++i) {
            scanf("%s", maze[i]);
        }
        _DEBUG_CMD({
            for (int i = 0; i < N; ++i) {
                // cout << maze[i] << endl;
                printf("%s\n", maze[i]);
            }
        });

        int mcnt = 0;
        for (int i = 0; i < N; ++i) {
            _DEBUG_CMD({ printf("maze[%d]: ", i); });
            for (int j = 0; j < N; ++j) {
                _DEBUG_CMD({ printf("%c", maze[i][j]); });
                // DEBUG_CMD({ cout << maze[i][j]; });
                // printf("setting mazeh, i:%d j:%d\n", i, j);
                if (maze[i][j] == 'X') {
                    mcnt++;
                    continue;
                }
                mazeh[i][j] = mcnt;
            }
            _DEBUG_CMD({ printf("\n"); });
            mcnt++;
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (maze[j][i] == 'X') {
                    mcnt++;
                    continue;
                }
                mazev[j][i] = mcnt;
            }
            mcnt++;
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (maze[i][j] != 'X') {
                    int x = mazev[i][j];
                    int y = mazeh[i][j];
                    // g[mazev[i][j]][mazeh[i][j]] = g[mazeh[i][j]][mazev[i][j]] = 1;
                    g[x][y] = g[y][x] = 1;
                    // printf("x:%d, y:%d\n", x, y);
                }
            }
        }

        _DEBUG_CMD({
            cout << "mazeh:" << endl;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << mazeh[i][j] << ' ';
                }
                cout << endl;
            }
            cout << "mazev:" << endl;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << mazev[i][j] << ' ';
                }
                cout << endl;
            }
        });
        _DEBUG_CMD({
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    int idx1 = i * N + j;
                    for (int m = 0; m < N; ++m) {
                        for (int n = 0; n < N; ++n) {
                            int idx2 = m * N + n;
                            printf("%d ", g[idx1][idx2]);
                        }
                    }
                    printf("\n");
                }
            }
        });
        int hm = hungarian_algo();
        // int hm = 0;
        // cout << "hm: " << hm << endl;
        // cout << N * N - hm - x_cnt << endl;
        cout << hm << endl;
    }
    return 0;
};

#endif
