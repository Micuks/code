// #define db
#ifndef _t10_20220729_
#define _t10_20220729_
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

const int MAXN = 1024;
char maze[MAXN][MAXN];
int fired[MAXN][MAXN];
int visited[MAXN][MAXN];
int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
void printMaze(int r, int c) {
    cout << "---print\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "Maze---\n";
}
class State {
  public:
    int x;
    int y;
    int cost;
    State(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
};
bool isValid(int r, int c, int nx, int ny, int cost) {
    return (nx >= 0 && nx < r && ny >= 0 && ny < c && maze[nx][ny] != '#' &&
            cost < fired[nx][ny]);
}
bool isEscaped(int r, int c, int nx, int ny) {
    return (nx < 0 || nx >= r || ny < 0 || ny >= c);
}
bool isWalkable(int r, int c, int x, int y, int cost) {
    return (x >= 0 && x < r && y >= 0 && y < c && maze[x][y] == '.' &&
            fired[x][y] > cost);
}
int bfs(int r, int c, int jx, int jy, vector<int> &fx, vector<int> &fy) {
    queue<State> q;
    for (int i = 0; i < fx.size(); i++) {
        fired[fx[i]][fy[i]] = 0;
        q.push(State(fx[i], fy[i], 0));
    }
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = s.x + dirs[i][0];
            int ny = s.y + dirs[i][1];
            if (isValid(r, c, nx, ny, s.cost + 1)) {
                fired[nx][ny] = s.cost + 1;
                q.push(State(nx, ny, s.cost + 1));
            }
        }
    }
#ifdef db
    cout << "---fired\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << fired[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "fired---\n";
#endif
    visited[jx][jy] = 1;
    q.push(State(jx, jy, 0));
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = s.x + dirs[i][0];
            int ny = s.y + dirs[i][1];
            if (isEscaped(r, c, nx, ny)) {
                return s.cost + 1;
            }
            if (isWalkable(r, c, nx, ny, s.cost + 1)) {
                q.push(State(nx, ny, s.cost + 1));
                visited[nx][ny] = 1;
            }
        }
    }
    return -1;
}
int main(int argc, char **argv) {
    // ios_base::sync_with_stdio(false);
    int kases, c, r;
    cin >> kases;
    while (kases--) {
        cin >> r >> c;
        memset(fired, 0x3f, MAXN * MAXN * sizeof(int));
        memset(visited, 0, MAXN * MAXN * sizeof(int));
#ifdef db
        cout << "---fired\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << fired[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "fired---\n";
#endif
        vector<int> fx, fy;
        int jx, jy;
        for (int i = 0; i < r; i++) {
            scanf("%s\n", &maze[i]);
            for (int j = 0; j < c; j++) {
                switch (maze[i][j]) {
                case 'F':
                    fx.push_back(i);
                    fy.push_back(j);
                    break;
                case 'J':
                    jx = i;
                    jy = j;
                    break;
                default:
                    break;
                }
            }
        }
#ifdef db
        printMaze(r, c);
#endif
        int result = bfs(r, c, jx, jy, fx, fy);
        if (result == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << result << endl;
        }
    }
    return 0;
};

#endif
