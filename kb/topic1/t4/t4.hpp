// #define DEBUG
#ifndef _t4_20220723_
#define _t4_20220723_
#include <algorithm>
#include <assert.h>
#include <climits>
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

const int MAXN = 20;
int maze[MAXN][MAXN];
int tramp[MAXN][MAXN];
int best_steps = INT_MAX;
int best_tramp[MAXN][MAXN];

void printMaze(const int &m, const int &n, const int maze[][MAXN]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", maze[i][j]);
        }
        putchar('\n');
    }
}
int isAllZero(const int &m, const int &n, const int maze[][MAXN]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == 1)
                return 0;
        }
    }
    return 1;
}
bool isValid(int i, int j, int m, int n) {
    return (i >= 0 && i < m && j >= 0 && j < n);
}
void flip(const int &i, const int &j, const int &m, const int &n,
          int maze[][MAXN]) {
    int dirs[][2] = {{0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (int k = 0; k < 5; k++) {
        int ni = i + dirs[k][0];
        int nj = j + dirs[k][1];
        if (isValid(ni, nj, m, n)) {
            maze[ni][nj] = (maze[ni][nj] == 1) ? 0 : 1;
        }
    }
    // printf("---flip[%d][%d]\n", i, j);
    // printMaze(m, n, maze);
    // printf("flip[%d][%d]---\n", i, j);
}
void dfs(int first_step, const int &m, const int &n, int maze[][MAXN]) {
    int new_tramp[MAXN][MAXN];
    memset(new_tramp, 0, MAXN * MAXN * sizeof(int));
    int steps = 0;
    for (int i = 0; i < n; i++) {
        new_tramp[0][n - 1 - i] = ((first_step >> i) & 0x1);
        if (new_tramp[0][n - 1 - i] == 1) {
            steps++;
            flip(0, n - 1 - i, m, n, maze);
        }
    }
#ifdef DEBUG
    printf("---first\n");
    printMaze(m, n, maze);
    printf("step---\n");
#endif

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i - 1][j] == 1) {
                new_tramp[i][j] = 1;
                steps++;
            }
        }
        for (int j = 0; j < n; j++) {
            if (new_tramp[i][j] == 1)
                flip(i, j, m, n, maze);
        }
    }
    for (int i = 0; i < n; i++) {
        if (maze[m - 1][i] == 1) {
            steps = INT_MAX;
        }
    }
#ifdef DEBUG
    printf("---after\n");
    printMaze(m, n, maze);
    printf("---flip\n");
    printf("---tramp\n");
    printMaze(m, n, new_tramp);
    printf("tramp---\n");
#endif
    if (isAllZero(m, n, maze)) {
        if (steps < best_steps) {
            best_steps = steps;
            memcpy(best_tramp, new_tramp, MAXN * MAXN * sizeof(int));
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (new_tramp[i][j] == 1) {
                flip(i, j, m, n, maze);
            }
        }
    }
#ifdef DEBUG
    printf("---rev\n");
    printMaze(m, n, maze);
    printf("vert---\n");
#endif
}
int main(int argc, char **argv) {
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    // printMaze(m, n, maze);
    for (int i = 0; i < (1 << n); i++) {
#ifdef DEBUG
        printf("case[%d]:\n", i);
#endif
        dfs(i, m, n, maze);
    }
    if (best_steps == INT_MAX) {
        printf("IMPOSSIBLE\n");
    } else {
#ifdef DEBUG
        printf("best_steps[%d]\n", best_steps);
#endif
        printMaze(m, n, best_tramp);
    }
    return 0;
};

#endif
