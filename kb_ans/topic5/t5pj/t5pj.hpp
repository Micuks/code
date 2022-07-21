#ifndef _t5pj_20200104_
#define _t5pj_20200104_
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

const int MAXN = 2048;
int f[MAXN], v[MAXN];
int N, bn, in;

int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    int tmp = find(f[x]);
    // v[x] = v[x] ^ v[f[x]];
    // v[x] = v[f[x]] == 0 ? 1 : 0;
    v[x] = v[f[x]] ^ v[x];
    return f[x] = tmp;
}
bool union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        if (v[x] == v[y]) {
            return false;
        }
        return true;
    }
    v[yroot] = v[x] ^ v[y] ^ 1;
    f[yroot] = xroot;
    return true;
}

void output(bool res, int case_cnt)
{
    if (res) {
        printf("Scenario #%d:\nSuspicious bugs found!\n\n", case_cnt);
    }
    else {
        printf("Scenario #%d:\nNo suspicious bugs found!\n\n", case_cnt);
    }
}

int main(int argc, char **argv)
{
    int ba, bb;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &bn, &in);
        for (int j = 0; j <= bn; ++j) {
            f[j] = j;
            v[j] = 0;
        }
        bool case_closed = false;
        for (int j = 0; j < in; ++j) {
            scanf("%d%d", &ba, &bb);
            if (!union_set(ba, bb)) {
                case_closed = true;
                // break;
            }
        }
        DEBUG_CMD({
            cout << "f[k]: ";
            for (int k = 1; k <= bn; ++k) {
                cout << f[k] << ' ';
            }
            cout << endl;
            cout << "v[k]: ";
            for (int k = 1; k <= bn; ++k) {
                cout << v[k] << ' ';
            }
            cout << endl;
        });
        output(case_closed, i);
    }
    return 0;
};

#endif
