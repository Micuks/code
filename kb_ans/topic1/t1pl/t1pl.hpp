#ifndef _t1pl_20191206_
#define _t1pl_20191206_
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
char visited[128][128];
char graph_map[128][128];
int dirs[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int bfs(int m, int n, vector<point_t> &oil_pockets)
{
    int total_cnt = 0;
    queue<point_t> mqueue;

    for (int i = 0; i < oil_pockets.size(); ++i) {
        const point_t &to_discover = oil_pockets[i];
        if (visited[to_discover.first][to_discover.second] == 0) {
            visited[to_discover.first][to_discover.second] = 1;
            ++total_cnt;
            mqueue.push(to_discover);

            while (!mqueue.empty()) {
                point_t pt = mqueue.front();
                mqueue.pop();

                for (int j = 0; j < 8; ++j) {
                    int newx = pt.first + dirs[j][0];
                    int newy = pt.second + dirs[j][1];
                    if (newx >= 0 && newx < m && newy >= 0 && newy < n &&
                        visited[newx][newy] == 0 && graph_map[newx][newy] == '@') {
                        visited[newx][newy] = 1;
                        mqueue.push(point_t(newx, newy));
                    }
                }
            }
        }
    }
    return total_cnt;
}

int main(int argc, char **argv)
{
    int m, n;
    while (cin >> m >> n && m != 0) {
        memset(visited, 0, sizeof(char) * 128 * 128);
        vector<point_t> oil_pockets;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> graph_map[i][j];
                if (graph_map[i][j] == '@') {
                    oil_pockets.push_back(pair<int, int>(i, j));
                }
            }
        }
        cout << bfs(m, n, oil_pockets) << endl;
    }
    return 0;
};

#endif
