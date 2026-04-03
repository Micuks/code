#ifndef _t1pi_20191205_
#define _t1pi_20191205_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

char board[16][16];
char visited[16][16];
vector<pair<int, int>> grass_vec;
int dirs[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct State {
    int tc;
    int x;
    int y;
    State(int tc, int x, int y) : tc(tc), x(x), y(y) {}
};

ostream &operator<<(ostream &out, const pair<int, int> &pt) {
    out << "(" << pt.first << ", " << pt.second << ")";
    return out;
}

int bfs(int n, int m) {
    int total_cost = 1e9 + 7;
    size_t gs_size = grass_vec.size();
    for (int i = 0; i < gs_size; ++i) {
        for (int j = i; j < gs_size; ++j) {
            // cout << "gs_size loop, i: " << i << grass_vec[i] << " j: " << j
            // << grass_vec[j] << endl;
            int tb = 2 - static_cast<int>(i == j);
            memset(visited, 0, 16 * 16);
            deque<State> mqueue;
            State s(0, grass_vec[i].first, grass_vec[i].second);
            visited[s.x][s.y] = 1;
            mqueue.push_back(s);

            if (i != j) {
                s = State(0, grass_vec[j].first, grass_vec[j].second);
                visited[s.x][s.y] = 1;
                mqueue.push_back(s);
            }
#ifdef DEUBG
            if (i == 1 && j == 4) {
                for (int p = 0; p < n; ++p) {
                    for (int q = 0; q < m; ++q) {
                        cout << board[p][q] << ' ';
                    }
                    cout << endl;
                }
            }
#endif

            while (!mqueue.empty()) {
#ifdef DEBUG
                if (i == 1 && j == 4) {
                    cout << "get in! " << grass_vec[i] << ", " << grass_vec[j]
                         << " tb_size: " << tb
                         << " mqueue.size(): " << mqueue.size() << " n: " << n
                         << " m: " << m << endl;
                    for (int p = 0; p < n; ++p) {
                        for (int q = 0; q < m; ++q) {
                            cout << static_cast<int>(visited[p][q]) << ' ';
                        }
                        cout << endl;
                    }
                }
#endif
                if (tb == gs_size) {
                    int max_tc = -1;
                    for (deque<State>::iterator iter = mqueue.begin();
                         iter != mqueue.end(); ++iter) {
                        max_tc = max(max_tc, iter->tc);
                    }
                    if (max_tc != -1) {
                        total_cost = min(total_cost, max_tc);
                    }
                    break;
                }
                s = mqueue.front();
                mqueue.pop_front();
                for (int k = 0; k < 4; ++k) {
                    int newx = s.x + dirs[k][0];
                    int newy = s.y + dirs[k][1];
                    if (newx >= 0 && newx < n && newy >= 0 && newy < m &&
                        visited[newx][newy] == 0 && board[newx][newy] == '#') {
                        visited[newx][newy] = 1;
                        ++tb;
                        mqueue.push_back(State(s.tc + 1, newx, newy));
                    }
                }
            }
        }
    }
    if (total_cost != 1e9 + 7) {
        return total_cost;
    }
    return -1;
}

int main(int argc, char **argv) {
    int cases, n, m;
    cin >> cases;
    for (int i = 0; i < cases; ++i) {
        cin >> n >> m;
        grass_vec.clear();
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                cin >> board[j][k];
                if (board[j][k] == '#') {
                    grass_vec.push_back(pair<int, int>(j, k));
                }
            }
        }
        printf("Case %d: %d\n", i + 1, bfs(n, m));
    }
    return 0;
};

#endif
