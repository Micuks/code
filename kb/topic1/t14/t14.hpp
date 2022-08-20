// #define db
#ifndef _t14_20220801_
#define _t14_20220801_
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
const int MAXN = 210;
char maze[MAXN][MAXN];
int yvisited[MAXN][MAXN];
int mvisited[MAXN][MAXN];
const int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

template <typename T> void printMaze(int n, int m, T maze[MAXN][MAXN]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
}
class State {
  public:
    int x;
    int y;
    int cost;
    State(int _x, int _y, int _c) : x(_x), y(_y), cost(_c) {}
    State(const State &ss) : x(ss.x), y(ss.y), cost(ss.cost) {}
};
bool isValid(int visited[][MAXN], const int &x, const int &y, const int &n,
             const int &m) {
    return ((x >= 0 && x < n && y >= 0 && y < m) && (maze[x][y] != '#') &&
            (visited[x][y] == -1));
}
int bfs(int visited[][MAXN], int x, int y, int n, int m) {
    memset(visited, -1, MAXN * MAXN * sizeof(int));
    queue<State> q;
    q.push(State(x, y, 0));
    visited[x][y] = 0;
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = s.x + dirs[i][0];
            int ny = s.y + dirs[i][1];
            if (isValid(visited, nx, ny, n, m)) {
                visited[nx][ny] = s.cost + 1;
                q.push(State(nx, ny, s.cost + 1));
            }
        }
    }
    return -1;
}
int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    int n, m;
    vector<pair<int, int>> kfcs;
    int yi, yj, mi, mj;
    int bestCost;
    while (cin >> n >> m) {
        bestCost = 1 << 30;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> maze[i][j];
                switch (maze[i][j]) {
                case 'Y':
                    yi = i;
                    yj = j;
                    break;
                case 'M':
                    mi = i;
                    mj = j;
                    break;
                case '@':
                    kfcs.push_back(make_pair(i, j));
                }
            }
        }
        // printMaze(n,m,maze);
        bfs(yvisited, yi, yj, n, m);
        bfs(mvisited, mi, mj, n, m);
        while (!kfcs.empty()) {
            pair<int, int> kfc = kfcs.back();
            kfcs.pop_back();
            int yCost = yvisited[kfc.first][kfc.second];
            if (yCost == -1)
                continue;
            int mCost = mvisited[kfc.first][kfc.second];
            if (mCost == -1)
                continue;
            int total = yCost + mCost;
            bestCost = (bestCost < total) ? bestCost : total;
        }
        cout << bestCost * 11 << endl;
    }
    return 0;
};

#endif
