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
const int MAXN = 1000;
char maze[MAXN][MAXN];
int visited[MAXN][MAXN];
const int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

class State {
  public:
    int x;
    int y;
    int cost;
    State(int _x, int _y, int _c) : x(_x), y(_y), cost(_c) {}
    State(const State &ss) : x(ss.x), y(ss.y), cost(ss.cost) {}
};
bool isArrived(const State &s, const pair<int, int> kfc) {
    return ((s.x == kfc.first) && (s.y == kfc.second));
}
bool isValid(const int &x, const int &y, const int &n, const int &m) {
    return ((x >= 0 && x < n && y >= 0 && y < m) && (maze[x][y] != '#') &&
            (visited[x][y] == 0));
}
int bfs(int x, int y, pair<int, int> kfc, int n, int m) {
    memset(visited, 0, sizeof(visited));
    queue<State> q;
    q.push(State(x, y, 0));
    visited[x][y] = 1;
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        if (isArrived(s, kfc)) {
            return s.cost;
        }
        for (int i = 0; i < 4; i++) {
            int nx = s.x + dirs[i][0];
            int ny = s.y + dirs[i][1];
            if (isValid(nx, ny, n, m)) {
                visited[nx][ny] = 1;
                q.push(State(nx, ny, s.cost + 1));
            }
        }
    }
    return -1;
}
int main(int argc, char **argv) {
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
        while (!kfcs.empty()) {
            pair<int, int> kfc = kfcs.back();
            kfcs.pop_back();
            int yCost = bfs(yi, yj, kfc, n, m);
            int mCost = bfs(mi, mj, kfc, n, m);
            if (yCost == -1 || mCost == -1) // one of them cannot reach kfc
                continue;
            int total = yCost + mCost;
            bestCost = (bestCost < total) ? bestCost : total;
        }
        cout << bestCost * 11 << endl;
    }
    return 0;
};

#endif
