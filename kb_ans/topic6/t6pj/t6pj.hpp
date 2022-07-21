#ifndef _t6pj_20200112_
#define _t6pj_20200112_
#include "stdio.h"
#include "string.h"
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define DEBUG
#ifdef DEBUG
#define DEBUG_CMD(cmd)                                                                             \
    do {                                                                                           \
        cmd;                                                                                       \
    } while (false)
#else
#define DEBUG_CMD(cmd)                                                                             \
    do {                                                                                           \
        ;                                                                                          \
    } while (false)
#endif
#define _DEBUG_CMD(cmd)                                                                            \
    do {                                                                                           \
        ;                                                                                          \
    } while (false)

typedef pair<int, int> pt_type;
const int MAXP = 128;
char maze[MAXP][MAXP];
int dist[MAXP][MAXP];
int pt_cnt = 0;
map<pair<int, int>, int> pt2idx;
vector<pt_type> pt;

int N;
int x, y;

int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Node {
    int val;
    pt_type pt;
};

void bfs(pt_type st, char m[MAXP][MAXP])
{
    int visited[MAXP][MAXP];
    memset(visited, 0, sizeof(visited));
    queue<Node> myqueue;
    Node n;
    n.val = 0;
    n.pt = st;
    myqueue.push(n);
    visited[st.first][st.second] = 1;
    while (!myqueue.empty()) {
        n = myqueue.front();
        myqueue.pop();
        for (int i = 0; i < 4; ++i) {
            int newx = n.pt.first + dirs[i][0];
            int newy = n.pt.second + dirs[i][1];
            if (newx >= 0 && newx < x && newy >= 0 && newy < y && m[newx][newy] != '#' &&
                !visited[newx][newy]) {
                Node nn;
                nn.pt.first = newx;
                nn.pt.second = newy;
                nn.val = n.val + 1;
                myqueue.push(nn);
                visited[newx][newy] = 1;

                // if (pt2idx.find(nn.pt) != pt2idx.end()) {
                if (m[newx][newy] == 'S' || m[newx][newy] == 'A') {
                    int ori = pt2idx[st];
                    int dst = pt2idx[nn.pt];
                    dist[ori][dst] = dist[dst][ori] = n.val + 1;
                }
            }
        }
    }
    _DEBUG_CMD({
        cout << "###################\n";
        for (int i = 0; i < pt_cnt; ++i) {
            for (int j = 0; j < pt_cnt; ++j) {
                cout << dist[i][j] << ' ';
            }
            cout << endl;
        }
    });
}
int prim()
{
    int d[MAXP];
    int visited[MAXP];
    memset(d, 0x3F, sizeof(d));
    memset(visited, 0, sizeof(visited));
    d[0] = 0;
    for (int i = 0; i < pt_cnt; ++i) {
        int min_idx, min_val = 1e9;
        for (int j = 0; j < pt_cnt; ++j) {
            if (!visited[j] && d[j] < min_val) {
                min_val = d[j];
                min_idx = j;
            }
        }
        visited[min_idx] = 1;
        for (int j = 0; j < pt_cnt; ++j) {
            if (!visited[j] && d[j] > dist[min_idx][j]) {
                d[j] = dist[min_idx][j];
            }
        }
    }
    return accumulate(d, d + pt_cnt, 0);
}

int main(int argc, char **argv)
{
    cin >> N;
    while (N--) {
        pt.clear();
        pt2idx.clear();
        pt_cnt = 0;
        memset(dist, 0x3F, sizeof(dist));

        scanf("%d%d", &y, &x);
        char buf[128];
        cin.getline(buf, sizeof(buf));
        // string buf;
        for (int i = 0; i < x; ++i) {
            // scanf("%s", buf);
            // gets(buf, stdin);
            cin.getline(buf, sizeof(buf));
            // cin >> buf;
            for (int j = 0; j < y; ++j) {
                // scanf("%c", &maze[i][j]);
                maze[i][j] = buf[j];
                if (maze[i][j] == 'S' || maze[i][j] == 'A') {
                    pt_type p = pt_type(i, j);
                    pt.push_back(p);
                    pt2idx[p] = pt_cnt++;
                }
            }
        }
        _DEBUG_CMD({
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    cout << maze[i][j] << ' ';
                }
                cout << endl;
            }
        });
        for (int i = 0; i < pt_cnt; ++i) {
            bfs(pt[i], maze);
        }
        int res = prim();
        cout << res << endl;
    }
    return 0;
};

#endif
