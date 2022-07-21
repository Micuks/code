#ifndef _t1pj_20191206_
#define _t1pj_20191206_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> point_t;

ostream &operator<<(ostream &out, const point_t &pt)
{
    out << '(' << pt.first << ", " << pt.second << ')';
    return out;
}

int dirs[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
char maze[1024][1024];
int visited[1024][1024];
int fired[1024][1024];

struct State {
    State(int x, int y, int tc) : x(x), y(y), tc(tc) {}
    int x;
    int y;
    int tc;
};

int bfs(int r, int c, int jx, int jy, vector<int> &fx, vector<int> &fy)
{
    queue<State> mqueue;
    for (int i = 0; i < fx.size(); ++i) {
        mqueue.push(State(fx[i], fy[i], 0));
        fired[fx[i]][fy[i]] = 0;
    }
    while (!mqueue.empty()) {
        State s = mqueue.front();
        mqueue.pop();
        // assigned here would be much more slower than in below, but why?
        // fired[s.x][s.y] = s.tc;
        for (int i = 0; i < 4; ++i) {
            int newx = s.x + dirs[i][0];
            int newy = s.y + dirs[i][1];
            if (newx >= 0 && newx < r && newy >= 0 && newy < c && maze[newx][newy] != '#' &&
                fired[newx][newy] > s.tc + 1) {
                mqueue.push(State(newx, newy, s.tc + 1));
                fired[newx][newy] = s.tc + 1;
            }
        }
    }

    State s(jx, jy, 0);
    visited[jx][jy] = 1;
    mqueue.push(s);

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        for (int i = 0; i < 4; ++i) {
            int newx = s.x + dirs[i][0];
            int newy = s.y + dirs[i][1];
            if (newx < 0 || newx >= r || newy < 0 || newy >= c) {
                return s.tc + 1;
            }
            if (maze[newx][newy] == '.' && visited[newx][newy] != 1 &&
                s.tc + 1 < fired[newx][newy]) {
                visited[newx][newy] = 1;
                mqueue.push(State(newx, newy, s.tc + 1));
            }
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    int case_cnt;
    int r, c;
    cin >> case_cnt;
    for (int i = 0; i < case_cnt; ++i) {
        memset(visited, -1, sizeof(int) * 1024 * 1024);
        memset(fired, 0x3F, sizeof(int) * 1024 * 1024);
        int jx, jy;
        vector<int> fx, fy;
        cin >> r >> c;
        for (int j = 0; j < r; ++j) {
            // gets(maze[j]);
            scanf("%s\n", &maze[j]);
            for (int k = 0; k < c; ++k) {
                // cin >> maze[j][k];
                switch (maze[j][k]) {
                    case 'F':
                        fx.push_back(j), fy.push_back(k);
                        break;
                    case 'J':
                        jx = j, jy = k;
                        break;
                    default:
                        break;
                }
            }
        }
        int res = bfs(r, c, jx, jy, fx, fy);
        if (res == -1) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << res << endl;
        }
    }
    return 0;
};

#endif
