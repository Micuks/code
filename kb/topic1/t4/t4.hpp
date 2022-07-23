#ifndef _t4_20220723_
#define _t4_20220723_
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

const int MAXN = 20;
int visited[MAXN][MAXN];
int maze[MAXN][MAXN];
void printMaze(const int &m, const int &n, const int maze[][MAXN]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", maze[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}
int **dfs(const int &m, const int &n, const int **&maze) {

}
int main(int argc, char **argv) {
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i]);
        }
    }
    printMaze(m, n, maze);
    int **result = dfs(m, n, maze);
    return 0;
};

#endif
