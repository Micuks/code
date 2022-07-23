#ifndef _t2_20220722_
#define _t2_20220722_
#include <algorithm>
#include <assert.h>
#include <climits>
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

const int CANNOT_REACH = INT_MAX;
const int MAXN = 40;
const int dirs[6][3] = {{1, 0, 0},  {0, 1, 0},  {0, 0, 1},
                        {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}};
int visited[MAXN][MAXN][MAXN];
char maze[MAXN][MAXN][MAXN];
int l, r, c;

class Point {
  public:
    int x;
    int y;
    int z;
    int distance;
    Point() : x(-1), y(-1), z(-1), distance(-1) {}
    Point(const int &_x, const int &_y, const int &_z, const int &_d = -1)
        : x(_x), y(_y), z(_z), distance(_d) {}
    Point(const Point &_p) {
        x = _p.x;
        y = _p.y;
        z = _p.z;
        distance = _p.distance;
    }
    void setPoint(const int &_x, const int &_y, const int &_z,
                  const int &_d = -1) {
        x = _x;
        y = _y;
        z = _z;
        distance = _d;
    }
    void setDistance(const int &_dst) { distance = _dst; }
    inline int isValid() {
        return ((x >= 0 && x < r) && (y >= 0 && y < c) && (z >= 0 && z < l) &&
                visited[x][y][z] == 0 &&
                (maze[x][y][z] == '.' || maze[x][y][z] == 'E'));
    }
    inline string toString() {
        string str;
        str += to_string(x) + ", " + to_string(y) + ", " + to_string(z);
        return str;
    }
};

int bfs(Point b, Point e) {
    queue<Point> q;
    memset(visited, 0, MAXN * MAXN * MAXN * sizeof(int));
    b.setDistance(0);
    visited[b.x][b.y][b.z] = 1;

    q.push(Point(b.x, b.y, b.z, b.distance));
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        for (int i = 0; i < 6; i++) {
            Point tp(p.x + dirs[i][0], p.y + dirs[i][1], p.z + dirs[i][2]);
            if (tp.isValid() == 1) {
                visited[tp.x][tp.y][tp.z] = 1;
                if (maze[tp.x][tp.y][tp.z] == 'E') {
                    return p.distance + 1;
                }
                tp.setDistance(p.distance + 1);
                q.push(tp);
            }
        }
    }
    return CANNOT_REACH;
}

void printMaze() {
    for (int k = 0; k < l; k++) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                printf("%c ", maze[i][j][k]);
            }
            putchar('\n');
        }
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    Point begin, end;
    while (scanf("%d%d%d", &l, &r, &c) == 3 && (l != 0 && r != 0 && c != 0)) {
        for (int k = 0; k < l; k++) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    char tmp = getchar();
                    while (tmp == '\n') {
                        tmp = getchar();
                    }
                    maze[i][j][k] = tmp;
                    if (tmp == 'S') {
                        begin.setPoint(i, j, k);
                    } else if (tmp == 'E') {
                        end.setPoint(i, j, k);
                    }
                }
            }
        }
        // printf("begin[%s], end[%s]", begin.toString().c_str(),
        //        end.toString().c_str());
        // putchar('\n');
        // printMaze();
        int result = bfs(begin, end);
        if (result == CANNOT_REACH) {
            printf("Trapped!\n");
        } else {
            printf("Escaped in %d minute(s).\n", result);
        }
    }
    return 0;
};

#endif
