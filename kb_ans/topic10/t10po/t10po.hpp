#ifndef _t10po_20210304_
#define _t10po_20210304_
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

const int MAXN = 1 << 10;
const int MAXB = 24;
int N, B;

// int l[MAXN][MAXB];
int g[MAXN][MAXB];

int match[MAXB][MAXB], cap[MAXB], used[MAXB], visited[MAXN];
// int max_r, min_r;

int dfs(int u, int lo, int hi)
{
    for (int v = 1; v <= B; ++v) {
        if (visited[v] == 0 && g[u][v] >= lo && g[u][v] <= hi) {
            visited[v] = 1;
            if (used[v] < cap[v]) {
                match[v][used[v]++] = u;
                return 1;
            }
            for (int i = 0; i < cap[v]; ++i) {
                if (dfs(match[v][i], lo, hi)) {
                    match[v][i] = u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int hungarian1(int lo, int hi)
{
    memset(match, -1, sizeof(match));
    memset(used, 0, sizeof(used));
    int min_hit = hi;
    int mid = (hi + lo) / 2;
    int lidx = lo;
    int ridx = hi;

    while (lidx < ridx) {
        mid = (lidx + ridx) / 2;

        int ret = 0;
        for (int i = 1; i <= N; ++i) {
            memset(visited, 0, sizeof(visited));
            ret += dfs(i, lo, mid);
        }

        if (ret == N) {
            min_hit = mid;
            ridx = mid;
            memset(match, -1, sizeof(match));
            memset(used, 0, sizeof(used));
        }
        else {
            lidx = mid + 1;
        }
    }
    _DEBUG_CMD({
        printf("hungarian %d~%d: %d ret:%d min(N, B):%d\n", lo, hi, int(ret == min(N, B)), ret,
               min(N, B));
    });
    // return ret == N;
    return min_hit - lo + 1;
}

bool hungarian(int lo, int hi)
{
    memset(match, -1, sizeof(match));
    memset(used, 0, sizeof(used));
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i, lo, hi) == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    int d;
    scanf("%d%d", &N, &B);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= B; ++j) {
            scanf("%d", &d);
            g[i][d] = j;
            // g[i][j] = d;
        }
    }
    for (int i = 1; i <= B; ++i) {
        scanf("%d", &cap[i]);
    }

    int max_diff = max(N, B);
    // int lo = 0, hi = max(N, B);
    for (int i = 1; i <= B; ++i) {
        // max_diff = min(max_diff, hungarian(i, B + 1));
        //*
        int lidx = i;
        int ridx = B + 1;
        _DEBUG_CMD({
            printf("i: %d, lidx:%d ridx:%d mid:%d max_diff: %d before search\n", i, lidx, ridx,
                   (lidx + ridx) / 2, max_diff);
        });
        while (lidx < ridx) {
            int mid = (lidx + ridx) / 2;
            _DEBUG_CMD(printf("i:%d lidx:%d mid:%d ridx:%d\n", i, lidx, mid, ridx));
            if (hungarian(i, mid)) {
                max_diff = min(max_diff, mid - i + 1);
                ridx = mid;
            }
            else {
                lidx = mid + 1;
            }
        }
        _DEBUG_CMD({
            printf("i: %d, lidx:%d ridx:%d mid:%d max_diff: %d after search\n", i, lidx, ridx,
                   (lidx + ridx) / 2, max_diff);
        });
        //*/
    }
    // DEBUG_CMD(printf("hungarian(6, 6): %d\n", int(hungarian(6, 6))));
    printf("%d\n", max_diff);

    return 0;
};

#endif
