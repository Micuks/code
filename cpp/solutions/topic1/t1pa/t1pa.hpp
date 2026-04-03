#ifndef _t1pa_20191202_
#define _t1pa_20191202_
#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

char maze[10][10] = {{0}};

int find_ans(int ns, int n, int k, int iter_depth, char mz[][10])
{
    char new_maze[10][10];
    memcpy(new_maze, mz, 10 * 10 * sizeof(char));
    int total_count = 0;
    if (iter_depth == k) {
        return 1;
    }
    if (iter_depth + n - ns < k) {
        return 0;
    }
    for (int i = ns; i < ns + 1; ++i) {
        for (int j = 0; j < n; ++j) {
            if (new_maze[i][j] == '#') {

                // take position of maze[i][j]
                memset(new_maze[i], '.', 10 * sizeof(char));
                for (int m = 0; m < 10; ++m) {
                    new_maze[m][j] = '.';
                }
                total_count += find_ans(i + 1, n, k, iter_depth + 1, new_maze);
                memcpy(new_maze[i], mz[i], 10 * sizeof(char));
                for (int m = 0; m < 10; ++m) {
                    new_maze[m][j] = mz[m][j];
                }
            }
        }
        // don't take position of maze[i]
        total_count += find_ans(i + 1, n, k, iter_depth, new_maze);
    }
    return total_count;
};

int main(int argc, char **argv)
{
    int n, k;
    while (cin >> n >> k && n != -1 && k != -1) {
        memset(maze, 0, 10 * 10 * sizeof(char));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> maze[i][j];
            }
        }
        cout << find_ans(0, n, k, 0, maze) << endl;
    }
    return 0;
};

#endif
