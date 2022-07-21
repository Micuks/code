#ifndef _t4pd_20191219_
#define _t4pd_20191219_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int MAXF = 1024;
const int MAX = 0x3F3F3F3F;

int farm[MAXF][MAXF];
int ivisited[MAXF];
int ovisited[MAXF];
int imin[MAXF];
int omin[MAXF];

void init()
{
    memset(farm, 0x3F, MAXF * MAXF * sizeof(int));
    memset(ivisited, 0, MAXF * sizeof(int));
    memset(ovisited, 0, MAXF * sizeof(int));
    memset(imin, 0x3F, MAXF * sizeof(int));
    memset(omin, 0x3F, MAXF * sizeof(int));
    return;
}

int N, M, X;

int dijkstra()
{
    ivisited[X] = 1;
    ovisited[X] = 1;
    for (int i = 1; i <= N; ++i) {
        imin[i] = farm[i][X];
        omin[i] = farm[X][i];
    }
    imin[X] = 0;
    omin[X] = 0;
    for (int i = 1; i < N; ++i) {
        int imin_idx, omin_idx;
        int imin_val, omin_val;
        imin_val = omin_val = MAX;
        for (int j = 1; j <= N; ++j) {
            if (!ivisited[j] && imin_val > imin[j]) {
                imin_idx = j;
                imin_val = imin[j];
            }
            if (!ovisited[j] && omin_val > omin[j]) {
                omin_idx = j;
                omin_val = omin[j];
            }
        }
        ovisited[omin_idx] = 1;
        ivisited[imin_idx] = 1;
        for (int j = 1; j <= N; ++j) {
            if (!ivisited[j] && imin[j] > imin_val + farm[j][imin_idx]) {
                imin[j] = imin_val + farm[j][imin_idx];
            }
            if (!ovisited[j] && omin[j] > omin_val + farm[omin_idx][j]) {
                omin[j] = omin_val + farm[omin_idx][j];
            }
        }
    }
    int mt[MAXF];
    transform(imin + 1, imin + N + 1, omin + 1, mt, plus<int>());
    return *max_element(mt, mt + N);
}

int main(int argc, char **argv)
{
    int u, v, val;
    init();
    scanf("%d%d%d", &N, &M, &X);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &u, &v, &val);
        farm[u][v] = min(val, farm[u][v]);
    }
    int res = dijkstra();
    cout << res << endl;
    return 0;
};

#endif
