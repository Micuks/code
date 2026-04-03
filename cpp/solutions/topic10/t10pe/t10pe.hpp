#ifndef _t10pe_20210130_
#define _t10pe_20210130_
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
int N;
char g[MAXN][MAXN], visited[MAXN], match[MAXN];

int dfs(int u)
{
    for (int v = 1; v <= N; ++v) {
        if (g[u][v] != 0 && visited[v] == 0) {
            visited[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int hungarian()
{
    int ans = 0;
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        ans += dfs(i);
    }
    return ans;
}

int main(int argc, char **argv)
{
    int a;
    while (~scanf("%d", &N)) {
        memset(g, 0, sizeof(g));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                scanf("%d", &a);
                g[i][j] = a;
            }
        }
        int ans = hungarian();
        if (ans != N) {
            printf("-1\n");
        }
        else {
            _DEBUG_CMD({
                printf("match: ");
                for (int i = 1; i <= N; ++i) {
                    printf("%d ", (int) match[i]);
                }
                printf("\n");
            });
            // int s = 0;
            vector<string> res;
            char buf[1 << 8];
            for (int i = 1; i <= N; ++i) {
                if (i == match[i]) {
                    continue;
                }
                for (int j = i + 1; j <= N; ++j) {
                    if (match[j] == i) {
                        match[j] = match[i];
                        match[i] = i;
                        // printf("R %d %d\n", );
                        sprintf(buf, "C %d %d\n", i, j);
                        res.push_back(buf);
                    }
                }
            }
            printf("%lu\n", res.size());
            for (int i = 0; i < res.size(); ++i) {
                printf("%s", res[i].c_str());
            }
        }
    }
    return 0;
};

#endif
