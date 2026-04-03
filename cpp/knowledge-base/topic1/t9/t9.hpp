// #define db
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
#include <sstream>
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
        const int x2, const int y2, int steps) {
#ifdef db
    cout << "------before\n";
    printMaze(maze, n, m);
#endif
    int result1 = 1 << 15;
    int result2 = 1 << 15;
    if (maze[x1][y1] == '#') {
        maze[x1][y1] = '.';
        for (int i = 0; i < 4; i++) {
            int nx = x1 + dirs[i][0];
            int ny = y1 + dirs[i][1];
            if (isValid(maze, n, m, nx, ny)) {
                int tmp = dfs(maze, n, m, nx, ny, -1, -1, steps + 1);
                result1 = (result1 == 1 << 15) ? tmp : result1;
                result1 = (result1 < tmp) ? tmp : result1;
            }
        }
    }
    if (x2 != -1 && y2 != -1) {
#ifdef db
        cout << "x2[" << x2 << "], y2[" << y2 << "]" << endl;
#endif
        if (maze[x2][y2] == '#') {
            maze[x2][y2] = '.';
            for (int i = 0; i < 4; i++) {
                int nx = x2 + dirs[i][0];
                int ny = y2 + dirs[i][1];
                if (isValid(maze, n, m, nx, ny)) {
                    int tmp = dfs(maze, n, m, nx, ny, -1, -1, steps + 1);
                    result2 = (result2 == 1 << 15) ? tmp : result2;
                    result2 = (result2 < tmp) ? tmp : result2;
                }
            }
        }
    }
#ifdef db
    cout << "after------\n";
    printMaze(maze, n, m);
    cout << "steps[" << steps << "], result1[" << result1 << "], result2["
         << result2 << "]" << endl;
#endif
    if (result1 != 1 << 15 && result2 != 1 << 15) {
        if (result1 > result2 && result1 > steps) {
#ifdef db
            cout << "return result1[" << result1 << "]" << endl;
#endif
            return result1;
        }
        if (result2 > result1 && result2 > steps) {
#ifdef db
            cout << "return result2[" << result2 << "]" << endl;
#endif
            return result2;
        }
#ifdef db
        cout << "return steps[" << steps << "]" << endl;
#endif
        return steps;
    } else if (result1 == 1 << 15 && result2 != 1 << 15) {
#ifdef db
        cout << "return result2[" << result2 << "]" << endl;
#endif
        return (result2 > steps) ? result2 : steps;
    } else if (result2 == 1 << 15 && result1 != 1 << 15) {
#ifdef db
        cout << "return result1[" << result1 << "]" << endl;
#endif
        return (result1 > steps) ? result1 : steps;
    }
#ifdef db
    cout << "return steps[" << steps << "]" << endl;
#endif
    return steps;
}
int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    int n, m, t;
    cin >> t;
    for (int kase = 1; kase <= t; kase++) {
        int best_steps = 1 << 15;
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
#ifdef db
                    cout << "i[" << i << "], j[" << j << "], k[" << k << "]"
                         << ", l[" << l << "]" << endl;
#endif
                    int steps = dfs(maze, n, m, i, j, k, l, 0);
                    if (steps != -1 && steps < best_steps &&
                        isAllBurnt(maze, n, m)) {
                        best_steps = steps;
                    }
#ifdef db
                    cout << "steps[" << steps << "], best_steps[" << best_steps
                         << "]" << endl;
#endif
                    memcpy(maze, origin_maze, MAXN * MAXN * sizeof(char));
                }
                for (int k = i + 1; k < n; k++) {
                    for (int l = 0; l < m; l++) {
#ifdef db
                        cout << "i[" << i << "], j[" << j << "], k[" << k << "]"
                             << ", l[" << l << "]" << endl;
                        // printMaze(maze, n, m);
#endif
                        int steps = dfs(maze, n, m, i, j, k, l, 0);
                        if (steps != -1 && steps < best_steps &&
                            isAllBurnt(maze, n, m)) {
                            best_steps = steps;
                        }
#ifdef db
                        cout << "steps[" << steps << "], best_steps["
                             << best_steps << "]" << endl;
#endif
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
