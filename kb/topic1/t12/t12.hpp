// #define db
#ifndef _t12_20220731_
#define _t12_20220731_
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
#include <stack>
using namespace std;
const int MAXN = 1000;
char maze[MAXN][MAXN];
int deposits[MAXN][MAXN];
stack<pair<int, int>> q;
int cnt = 0;
typedef pair<int, int> tp;
const int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1},{1,1},{1,-1},{-1,1},{-1,-1}};
template <typename t> void printMaze(int m, int n, t maze[][MAXN]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout<<maze[i][j];
        }
        cout << endl;
    }
}
bool isValid(int x, int y, int m, int n) {
    return (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == '@');
}
void dfs(int m, int n) {
    while (!q.empty()) {
        // tp p = q.front();
        tp p = q.top();
        q.pop();
        if (deposits[p.first][p.second] == -1) {
            for (int i = 0; i < 8; i++) {
                int nx = p.first + dirs[i][0];
                int ny = p.second + dirs[i][1];
                if (isValid(nx, ny, m, n) && deposits[nx][ny] != -1) {
                    deposits[p.first][p.second] = deposits[nx][ny];
                }
            }
        }
        if (deposits[p.first][p.second] == -1) {
            deposits[p.first][p.second] = cnt++;
        }
        for (int i = 0; i < 8; i++) {
            int nx = p.first + dirs[i][0];
            int ny = p.second + dirs[i][1];
            if (isValid(nx, ny, m, n) && deposits[nx][ny] == -1) {
                deposits[nx][ny] = deposits[p.first][p.second];
                q.push(make_pair(nx, ny));
            }
        }
#ifdef db
        cout << "---print\n";
        printMaze(m, n, deposits);
        cout << "deposits---\n";
#endif
    }
}
int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    int m, n;
    while (cin >> m >> n && m != 0 && n != 0) {
        cnt = 0;
        memset(deposits, -1, sizeof(deposits));
        // cout << "m[" << m << "], n[" << n << "]" << endl;
        for (int i = 0; i < m; i++) {
            // cin.getline(maze[i], MAXN, '\n');
            // cout<<maze[i]<<endl;
            for (int j = 0; j < n; j++) {
                cin >> maze[i][j];
                if (maze[i][j] == '@') {
                    q.push(make_pair(i, j));
                }
            }
        }
#ifdef db
        cout << "---print" << endl;
        printMaze(m, n, maze);
        cout << "maze---" << endl;
#endif
        dfs(m, n);
        cout << cnt << endl;
    }
    return 0;
}

#endif
