#ifndef _t4pg_20191220_
#define _t4pg_20191220_
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

const int MAXV = 128;
const int MAXE = 128;
const int MAXINF = 0x3F3F3F3F;
int network[MAXV][MAXV];
int d[MAXV];
int visited[MAXV];
int n;

void init()
{
    memset(d, 0x3F, sizeof(int) * MAXV);
    memset(visited, 0, sizeof(int) * MAXV);
}

int dijkstra()
{
    for (int i = 0; i < n; ++i) {
        d[i] = network[0][i];
    }
    visited[0] = 1;

    for (int i = 1; i < n; ++i) {
        int idx;
        int val = MAXINF;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && d[j] < val) {
                val = d[j];
                idx = j;
            }
        }
        visited[idx] = 1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && d[j] > d[idx] + network[idx][j]) {
                d[j] = d[idx] + network[idx][j];
            }
        }
    }
    return *max_element(d, d + n);
}

int main(int argc, char **argv)
{
    char s[MAXV];
    init();
    cin >> n;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            cin >> s;
            if (s[0] == 'x') {
                network[i][j] = network[j][i] = MAXINF;
            }
            else {
                network[i][j] = network[j][i] = atoi(s);
            }
        }
    }
    int res = dijkstra();
    cout << res << endl;
    return 0;
};

#endif
