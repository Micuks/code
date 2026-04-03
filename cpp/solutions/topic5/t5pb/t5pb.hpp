#ifndef _t5pb_20191230_
#define _t5pb_20191230_
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
//#define DEBUG
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

const int MAXN = 32768;
int n, m;
int s[MAXN];

int find(int x)
{
    if (s[x] == x) {
        return x;
    }
    return s[x] = find(s[x]);
}

int union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    return s[yroot] = xroot;
}

bool same_group(int x, int y) { return find(x) == find(y); }

int main(int argc, char **argv)
{
    int k;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        for (int i = 0; i < n; ++i) {
            s[i] = i;
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d", &k);
            vector<int> svec(k);
            for (int j = 0; j < k; ++j) {
                scanf("%d", &svec[j]);
            }
            DEBUG_CMD({
                cerr << "svec: ";
                for (int x = 0; x < k; ++x) {
                    cerr << svec[x] << ' ';
                }
                cerr << endl;
            });
            for (int j = 1; j < k; ++j) {
                DEBUG_CMD({ cerr << "join " << j - 1 << " and " << j << endl; });
                union_set(svec[j - 1], svec[j]);
            }
        }
        int suspected = 0;
        for (int i = 0; i < n; ++i) {
            if (same_group(0, i)) {
                suspected += 1;
            }
        }
        DEBUG_CMD({
            for (int i = 0; i < n; ++i) {
                cerr << s[i] << " ";
            }
            cerr << endl;
        });
        cout << suspected << endl;
    }
    return 0;
};

#endif
