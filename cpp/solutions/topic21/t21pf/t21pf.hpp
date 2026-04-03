#ifndef _t21pf_20210829_
#define _t21pf_20210829_
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
#include <stack>
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
const int MAXN = 1 << 7;
int T, n;
int ladder[MAXN][2];
int to[MAXN];

const double eps = 1e-9;
double a[MAXN][MAXN];

int gauss_elmination(int r, int c)
{
    int col, row, mxr;
    for (row = col = 1; row <= r && col <= c; row++, col++) {
        mxr = row;
        for (int i = row + 1; i <= r; i++)
            if (fabs(a[i][col]) > fabs(a[row][col]))
                mxr = i;
        if (mxr != row)
            swap(a[row], a[mxr]);
        if (fabs(a[row][col]) < eps) {
            row--;
            continue;
        }
        for (int i = 1; i <= r; i++) //消成上三角矩阵
            if (i != row && fabs(a[i][col]) > eps)
                for (int j = c; j >= col; j--)
                    a[i][j] -= a[row][j] / a[row][col] * a[i][col];
    }
    row--;
    for (int i = row; i >= 1; i--) //回代成对角矩阵
    {
        for (int j = i + 1; j <= row; j++)
            a[i][c] -= a[j][c] * a[i][j];
        a[i][c] /= a[i][i];
    }
    return row;
}

int main(int argc, char **argv)
{
    int pa, pb;
    scanf("%d", &T);
    for (int cc = 1; cc <= T; ++cc) {
        fill_n(to, MAXN, 0);
        memset(a, 0, sizeof(a));
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &pa, &pb);
            to[pa] = pb;
        }
        for (int i = 1; i <= 99; ++i) {
            if (to[i] != 0) {
                a[i][to[i]] = -1;
                a[i][i] = 1;
                a[i][101] = 0;
            }
            else {
                int d = min(6, 100 - i);
                a[i][i] = 1 - (6.0 - d) / 6.0;
                for (int j = i + 1; j <= min(100, i + 6); ++j) {
                    a[i][j] = -1.0 / 6;
                }
                a[i][101] = 1;
            }
        }
        a[100][100] = 1;
        a[100][101] = 0;
        gauss_elmination(100, 101);
        printf("Case %d: %.6lf\n", cc, a[1][101]);
    }
    return 0;
};

#endif
