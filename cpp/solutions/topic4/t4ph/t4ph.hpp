#ifndef _t4ph_20191221_
#define _t4ph_20191221_
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

const int MAXC = 1024;
int cow_contest[MAXC][MAXC];
int N, M;

int floyd()
{
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = 1; k <= N; ++k) {
                if (cow_contest[j][i] && cow_contest[i][k]) {
                    cow_contest[j][k] = 1;
                }
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= N; ++i) {
        bool brk_flag = false;
        for (int j = 1; j <= N; ++j) {
            if (i == j)
                continue;
            if (cow_contest[i][j] == 0 && cow_contest[j][i] == 0) {
                brk_flag = true;
                break;
            }
        }
        if (brk_flag == false) {
            res += 1;
        }
    }

    return res;
}

int main(int argc, char **argv)
{
    int a, b;
    while (scanf("%d%d", &N, &M) == 2) {
        memset(cow_contest, 0, sizeof(cow_contest));
        // cin >> N >> M;
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &a, &b);
            cow_contest[a][b] = 1;
        }
        int res = floyd();
        cout << res << endl;
    }
    return 0;
};

#endif
