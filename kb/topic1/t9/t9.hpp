#ifndef _t9_20220726_
#define _t9_20220726_
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
const int MAXN = 100;
int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char maze[MAXN][MAXN];

void printMaze(const char maze[][MAXN], const int n, const int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}
bool isAllBurnt(const char maze[][MAXN], const int n, const int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == '#')
                return false;
        }
    }
    return true;
}
bool isValid(const char maze[][MAXN], const int n, const int m, const int x,
             const int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == '#');
}
int dfs(char maze[][MAXN], const int n, const int m, const int x1, const int y1,
        const int x2, const int y2, const int steps) {
    cout << "------before\n";
    printMaze(maze, n, m);
    if (isAllBurnt(maze, n, m)) {
        cout << "---all burnt---\n";
        return steps;
    }
    int result = 1 << 15;
    if (maze[x1][y1] == '#') {
        maze[x1][y1] = '.';
        for (int i = 0; i < 4; i++) {
            int nx = x1 + dirs[i][0];
            int ny = y1 + dirs[i][1];
            if (isValid(maze, n, m, nx, ny)) {
                int tmp = dfs(maze, n, m, nx, ny, -1, -1, steps + 1);
                result = (tmp != -1 && tmp < result) ? tmp : result;
                if (result != 1 << 15) {
                    cout << "result[" << result << "]" << endl;
                    return result;
                }
            }
        }
    }
    if (x2 != -1 && y2 != -1) {
        if (maze[x2][y2] == '#') {
            maze[x2][y2] = '.';
            for (int i = 0; i < 4; i++) {
                int nx = x2 + dirs[i][0];
                int ny = y2 + dirs[i][1];
                if (isValid(maze, n, m, nx, ny)) {
                    int tmp = dfs(maze, n, m, nx, ny, -1, -1, steps + 1);
                    result = (tmp != -1 && tmp < result) ? tmp : result;
                    if (result != 1 << 15) {
                        cout << "result[" << result << "]" << endl;
                        return result;
                    }
                }
            }
        }
    }
    cout << "result[" << result << "]" << endl;
    cout << "after------\n";
    printMaze(maze, n, m);
    if (isAllBurnt(maze, n, m)) {
        cout << "---all burnt---\n";
        return steps;
    }
    if (result == 1 << 15)
        return -1;
    return result;
}
int main(int argc, char **argv) {
    int n, m, t;
    cin >> t;
    int best_steps = 1 << 15;
    for (int kase = 1; kase <= t; kase++) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            string tmp;
            cin >> tmp;
            memcpy(maze[i], tmp.c_str(), m * sizeof(char));
        }
        char origin_maze[MAXN][MAXN];
        memcpy(origin_maze, maze, MAXN * MAXN * sizeof(char));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int l = j; l < m; l++) {
                    // printMaze(maze, n, m);
                    int k = i;
                    int steps = dfs(maze, n, m, i, j, k, l, 0);
                    if (steps != -1 && steps < best_steps) {
                        best_steps = steps;
                    }
                    memcpy(maze, origin_maze, MAXN * MAXN * sizeof(char));
                }
                for (int k = i + 1; k < n; k++) {
                    for (int l = 0; l < m; k++) {
                        // printMaze(maze, n, m);
                        int steps = dfs(maze, n, m, i, j, k, l, 0);
                        if (steps != -1 && steps < best_steps) {
                            best_steps = steps;
                        }
                        memcpy(maze, origin_maze, MAXN * MAXN * sizeof(char));
                    }
                }
            }
        }
        best_steps = (best_steps == 1 << 15) ? -1 : best_steps;
        cout << "Case " << kase << ": " << best_steps << endl;
    }
    return 0;
};

#endif
