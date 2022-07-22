#ifndef _t2_20220722_
#define _t2_20220722_
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

const int MAXN = 40;
char maze[MAXN][MAXN][MAXN];
class Point {
  public:
    int x;
    int y;
    int z;
    int distance;
    Point() : x(-1), y(-1), z(-1), distance(-1) {}
    Point(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

Point data[MAXN][MAXN][MAXN];

void dijkstra(Point begin, Point end) {}

int main(int argc, char **argv) {
    int l, r, c;
    while (scanf("%d%d%d", &l, &r, &c) == 3 && (l != 0 && r != 0 && c != 0)) {
        memset(maze, '#', MAXN * MAXN * MAXN * sizeof(int));
        memset(distance, -1, MAXN * MAXN * MAXN * sizeof(int));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                char tmp = getchar();
                while (tmp == '\n') {
                    tmp = getchar();
                }
                maze[i][j] = tmp;
            }
        }
        dijkstra();
    }
    return 0;
};

#endif
