#ifndef _t11_20220730_
#define _t11_20220730_
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
const int MAXN = 16;
char maze[MAXN][MAXN];
int visited[MAXN][MAXN];
pair<int, int> previous[MAXN][MAXN];
const int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
ostream &operator<<(ostream &os, pair<int, int> p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
bool isValid(int x, int y) {
    return (x >= 0 && x < 5 && y >= 0 && y < 5 && visited[x][y] == 0 &&
            maze[x][y] != '1');
}
template <typename T> void printMaze(T maze[][MAXN]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> maze[i][j];
        }
    }
#ifdef db
    printMaze(maze);
#endif
    memset(visited, 0, MAXN * MAXN * sizeof(int));
    queue<pair<int, int>> q;
    visited[0][0] = 1;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        if (p.first == 4 && p.second == 4) {
            break;
        }
        for (int i = 0; i < 4; i++) {
            int nx = p.first + dirs[i][0];
            int ny = p.second + dirs[i][1];
            if (isValid(nx, ny)) {
                visited[nx][ny] = 1;
                previous[nx][ny] = p;
                q.push(make_pair(nx, ny));
            }
        }
    }
#ifdef db
    printMaze(previous);
#endif
    vector<pair<int, int>> v;
    if (visited[4][4] == 1) {
        pair<int, int> p = make_pair(4, 4);
        while (!(p.first == 0 && p.second == 0)) {
            v.push_back(p);
            p = previous[p.first][p.second];
        }
        v.push_back(p);
    }
    while (!v.empty()) {
        pair<int, int> p = v.back();
        v.pop_back();
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
    return 0;
}

#endif
