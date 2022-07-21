#ifndef _t1pn_20191206_
#define _t1pn_20191206_
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

typedef pair<int, int> point_t;
int yvisited[256][256];
int mvisited[256][256];
char nb_map[256][256];

int dirs[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct State {
    int x;
    int y;
    int tc;
    State(int tc, int x, int y) : tc(tc), x(x), y(y) {}
};

void bfs(int vflg[][256], int sx, int sy, int n, int m)
{
    vflg[sx][sy] = 0;
    State s(0, sx, sy);
    queue<State> mqueue;
    mqueue.push(s);

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        for (int i = 0; i < 4; ++i) {
            int newx = s.x + dirs[i][0];
            int newy = s.y + dirs[i][1];
            if (newx >= 0 && newx < n && newy >= 0 && newy < m && nb_map[newx][newy] != '#' &&
                vflg[newx][newy] == -1) {
                vflg[newx][newy] = s.tc + 1;
                mqueue.push(State(s.tc + 1, newx, newy));
            }
        }
    }
}

int bfs(const vector<point_t> &mcs, int n, int m, int yx, int yy, int mx, int my)
{
    int ret_min = 0x3F3F3F3F;

    bfs(yvisited, yx, yy, n, m);
    bfs(mvisited, mx, my, n, m);
#ifdef DEBUG
    cout << "yvisited:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << int(yvisited[i][j]) << ' ';
        }
        cout << endl;
    }
    cout << "wvisited:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << int(mvisited[i][j]) << ' ';
        }
        cout << endl;
    }
#endif
    for (int i = 0; i < mcs.size(); ++i) {
        const point_t &p = mcs[i];
        if (yvisited[p.first][p.second] != -1 && mvisited[p.first][p.second] != -1) {
            ret_min = min(ret_min, yvisited[p.first][p.second] + mvisited[p.first][p.second]);
        }
    }
    return ret_min;
}

int main(int argc, char **argv)
{
    int n, m;
    while (cin >> n >> m) {
        vector<point_t> mcs;
        int yx, yy, mx, my;
        memset(yvisited, -1, sizeof(int) * 256 * 256);
        memset(mvisited, -1, sizeof(int) * 256 * 256);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> nb_map[i][j];
                switch (nb_map[i][j]) {
                    case 'Y':
                        yx = i, yy = j;
                        break;
                    case 'M':
                        mx = i, my = j;
                        break;
                    case '@':
                        mcs.push_back(point_t(i, j));
                        break;
                }
            }
        }
        cout << bfs(mcs, n, m, yx, yy, mx, my) * 11 << endl;
    }
    return 0;
};

#endif
