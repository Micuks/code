#ifndef _t1pk_20191206_
#define _t1pk_20191206_
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
#include <stack>
#include <string>
#include <vector>
using namespace std;

int maze[16][16];
char visited[16][16];
int dirs[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
pair<int, int> previous[16][16];

struct State {
    int x;
    int y;
    int tc;
    State(int x, int y, int tc) : x(x), y(y), tc(tc) {}
};
ostream &operator<<(ostream &out, const State &s)
{
    out << '(' << s.x << ',' << ' ' << s.y << ')';
    return out;
}

int main(int argc, char **argv)
{
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> maze[i][j];
        }
    }
    memset(visited, 0, sizeof(char) * 16 * 16);
    queue<State> mqueue;
    stack<State> stk;
    State s(0, 0, 0);
    mqueue.push(s);

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        for (int i = 0; i < 4; ++i) {
            int newx = s.x + dirs[i][0];
            int newy = s.y + dirs[i][1];
            if (newx >= 0 && newx < 5 && newy >= 0 && newy <= 5 && visited[newx][newy] == 0 &&
                maze[newx][newy] == 0) {
                visited[newx][newy] = 1;
                mqueue.push(State(newx, newy, s.tc + 1));
                previous[newx][newy] = pair<int, int>(s.x, s.y);
            }
        }
    }
    pair<int, int> prev(4, 4);
    stk.push(State(4, 4, 0));
    while (prev = previous[prev.first][prev.second], prev != pair<int, int>(0, 0)) {
        stk.push(State(prev.first, prev.second, 0));
    }
    stk.push(State(0, 0, 0));
    while (!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }

    return 0;
};

#endif
