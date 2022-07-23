#ifndef _t3_20220723_
#define _t3_20220723_
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
const int MAXN = 100000;
int visited[MAXN + 10];

class Point {
  public:
    int pos;
    int distance;
    Point(const int &_p, const int &_d) : pos(_p), distance(_d){};
    inline int isValid() {
        return ((pos >= 0 && pos <= MAXN) && visited[pos] == 0);
    }
    inline string toString() {
        string str;
        // str += "(" + to_string(pos) + ", " + to_string(distance) + ")";
        return str;
    }
    Point frontP() { return Point(pos + 1, distance + 1); }
    Point rearP() { return Point(pos - 1, distance + 1); }
    Point doubleP() { return Point(pos * 2, distance + 1); }
    void setVisited() { visited[pos] = 1; }
};

int search(const int &begin, const int &end) {
    queue<Point> q;
    memset(visited, 0, sizeof(visited));
    Point b(begin, 0);
    b.setVisited();
    q.push(b);
    while (!q.empty()) {
        Point tp = q.front();
        q.pop();
        if(tp.pos == end) {
            return tp.distance;
        }
        Point tmpP = tp.frontP();
        if (tmpP.isValid()) {
            if (tmpP.pos == end) {
                // printf("---%s---", tmpP.toString().c_str());
                return tmpP.distance;
            }
            tmpP.setVisited();
            q.push(tmpP);
            // printf("%s", tmpP.toString().c_str());
        }

        tmpP = tp.rearP();
        if (tmpP.isValid()) {
            if (tmpP.pos == end) {
                // printf("---%s---", tmpP.toString().c_str());
                return tmpP.distance;
            }
            tmpP.setVisited();
            q.push(tmpP);
            // printf("%s", tmpP.toString().c_str());
        }

        tmpP = tp.doubleP();
        if (tmpP.isValid()) {
            if (tmpP.pos == end) {
                // printf("---%s---", tmpP.toString().c_str());
                return tmpP.distance;
            }
            tmpP.setVisited();
            q.push(tmpP);
            // printf("%s", tmpP.toString().c_str());
        }
        // putchar('\n');
    }
    return INT_MAX;
}

int main(int argc, char **argv) {
    int n, k;
    scanf("%d%d", &n, &k);
    int result = search(n, k);
    printf("%d\n", result);
    return 0;
};

#endif
