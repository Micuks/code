#ifndef _t1pb_20191203_
#define _t1pb_20191203_
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
//#include <unordered_map>
//#include <unordered_set>
#include <assert.h>
#include <map>
#include <queue>
#include <set>
using namespace std;

#define SIX_DIRS 6
int dirs[SIX_DIRS][3] = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {0, 0, -1}, {0, -1, 0}, {-1, 0, 0}};
int L, R, C;
const int CANNOT_REACH = 1000000;
int shortest_time = CANNOT_REACH;
char maze[32][32][32];
int visited[32][32][32];
int fast_search[32][32][32];

bool valid(int i, int j, int k)
{
    return i >= 0 && i < L && j >= 0 && j < R && k >= 0 && k < C && (maze[i][j][k] == 'E' || maze[i][j][k] == '.');
}

int dfs(int ci, int cj, int ck, int di, int dj, int dk, int tc)
{
    if (ci == di && cj == dj && ck == dk) {
        if (tc < shortest_time) {
            shortest_time = tc;
        }
        return tc;
    }
    bool dead_end = true;
    int shortest_this_thread = CANNOT_REACH;
    for (int i = 0; i < SIX_DIRS; ++i) {
        int ni = ci + dirs[i][0];
        int nj = cj + dirs[i][1];
        int nk = ck + dirs[i][2];
        if (valid(ni, nj, nk)) {
            dead_end = false;
            char old_sym = maze[ni][nj][nk];
            maze[ni][nj][nk] = '#';
            if (fast_search[ni][nj][nk] != -1) {
                /*
                if (fast_search[ni][nj][nk] + tc < shortest_time) {
                    shortest_time = fast_search[ni][nj][nk] + tc;
                }
                shortest_this_thread = min(shortest_this_thread, fast_search[ni][nj][nk] + tc);
                */
                if (fast_search[ni][nj][nk] != CANNOT_REACH && fast_search[ni][nj][nk] > tc + 1) {
                    fast_search[ni][nj][nk] = tc + 1;
                }
                shortest_this_thread = min(shortest_this_thread, fast_search[ni][nj][nk]);
            }
            else {
                fast_search[ni][nj][nk] = dfs(ni, nj, nk, di, dj, dk, tc + 1);
                shortest_this_thread = min(shortest_this_thread, fast_search[ni][nj][nk]);
            }
            maze[ni][nj][nk] = old_sym;
        }
    }
    if (dead_end == true) {
        fast_search[ci][cj][ck] = CANNOT_REACH;
        return CANNOT_REACH;
    }
    return shortest_this_thread;
}

struct Pos {
    int i;
    int j;
    int k;
    int tc;
};

int bfs(int ci, int cj, int ck, int di, int dj, int dk, int)
{
    queue<Pos> m_queue;
    visited[ci][cj][ck] = 0;
    m_queue.push(Pos{ci, cj, ck, 0});

    while (!m_queue.empty()) {
        Pos p = m_queue.front();
        m_queue.pop();

        for (int i = 0; i < SIX_DIRS; ++i) {
            int ni = p.i + dirs[i][0];
            int nj = p.j + dirs[i][1];
            int nk = p.k + dirs[i][2];
            if (valid(ni, nj, nk) && visited[ni][nj][nk] == -1) {
                visited[ni][nj][nk] = p.tc + 1;
                if (ni == di && nj == dj && nk == dk) {
                    return p.tc + 1;
                }
                m_queue.push(Pos{ni, nj, nk, p.tc + 1});
            }
        }
    }
    return CANNOT_REACH;
}

int main(int argc, char **argv)
{
    int si, sj, sk;
    int ei, ej, ek;
    while (cin >> L >> R >> C && L != 0 && R != 0 && C != 0) {
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < R; ++j) {
                for (int k = 0; k < C; ++k) {
                    cin >> maze[i][j][k];
                    switch (maze[i][j][k]) {
                        case 'S':
                            si = i;
                            sj = j;
                            sk = k;
                            break;
                        case 'E':
                            ei = i;
                            ej = j;
                            ek = k;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        shortest_time = CANNOT_REACH;
        memset(fast_search, -1, sizeof(int) * 32 * 32 * 32);
        memset(visited, -1, sizeof(int) * 32 * 32 * 32);
        int res = bfs(si, sj, sk, ei, ej, ek, 0);
        if (res != CANNOT_REACH) {
            printf("Escaped in %d minute(s).\n", res);
        }
        else {
            printf("Trapped!\n");
        }
    }
    return 0;
};

#endif
