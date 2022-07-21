#if 0
#include "cstdio"
#include "cstring"
#include "fstream"
#include "iostream"
#include "string"
using namespace std;
int G[401][401], mylink[401];
int map[410][410];
bool vis[801];
int Case, n, m, pos;
void AddEdge(int x, int y)
{
    G[x][y] = 1; //本点连影子点
}
bool dfs(int u)
{
    for (int v = 1; v <= pos; v++) {
        if (G[u][v] && !vis[v]) {
            vis[v] = true;
            if (!mylink[v] || dfs(mylink[v])) {
                mylink[v] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
#define fin cin
    // ifstream fin("in.txt");
    string line;
    cin >> Case;
    while (Case--) {
        pos = 0;
        int res = 0;
        cin >> n >> m;
        getline(cin, line);
        for (int i = 1; i <= n; i++) //吸收残留
        {
            getline(cin, line);
            for (int j = 0; j < line.size(); j++)
                if (line[j] == '*')
                    map[i][j + 1] = ++pos;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (map[i][j] && map[i - 1][j])
                    AddEdge(map[i][j], map[i - 1][j]);
                if (map[i][j] && map[i + 1][j])
                    AddEdge(map[i][j], map[i + 1][j]);
                if (map[i][j] && map[i][j - 1])
                    AddEdge(map[i][j], map[i][j - 1]);
                if (map[i][j] && map[i][j + 1])
                    AddEdge(map[i][j], map[i][j + 1]);
            }
        }
        for (int i = 1; i <= pos; i++) {
            memset(vis, 0, sizeof(vis));
            if (dfs(i))
                res++;
        }
        printf("matches: ");
        for (int i = 1; i <= pos; ++i) {
            printf("%d ", mylink[i]);
        }
        puts("");
        res = pos - res / 2;
        cout << res << endl;
        memset(map, 0, sizeof(map));
        memset(G, 0, sizeof(G));
        memset(mylink, 0, sizeof(mylink));
    }
}

#else
#ifndef _t10ph_20210212_
#define _t10ph_20210212_
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

int n, w, h;

const int GS = 1 << 6;
char g[GS][GS];
int gi[GS][GS];
int vcnt;

const int MAXN = 1 << 9;
int head[MAXN], ecnt;
struct Edge {
    int v;
    int next;
} edges[MAXN * 20];

void add_edge(int u, int v)
{
    assert(u >= 1 && u < vcnt);
    assert(v >= 1 && v < vcnt);
    edges[ecnt].next = head[u];
    edges[ecnt].v = v;
    head[u] = ecnt++;
}

int visited[MAXN], match[MAXN];

int dfs(int u)
{
    for (int vidx = head[u]; vidx != -1; vidx = edges[vidx].next) {
        int v = edges[vidx].v;
        if (visited[v] == 0) {
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
    int ret = 0;
    memset(match, -1, sizeof(match));
    int prev_nz = 0;
    for (int i = 1; i < vcnt; ++i) {
        memset(visited, 0, sizeof(visited));
        int ans = dfs(i);
        _DEBUG_CMD({
            if (ans != 0) {
                printf("hungarian loop is not zero, ans:%d\n", ans);
                int nz = 0;
                for (int j = 1; j < vcnt; ++j) {
                    printf("%d ", match[j]);
                    if (match[j] != -1) {
                        nz++;
                    }
                }
                printf("nz:%d, prev_nz:%d diff:%d\n", nz, prev_nz, prev_nz - nz);
                prev_nz = nz;
            }
        });
        ret += ans;
    }
    return ret;
}

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int main(int argc, char **argv)
{
    scanf("%d", &n);
    for (int cc = 0; cc < n; ++cc) {
        vcnt = 1;
        scanf("%d%d", &h, &w);
        for (int i = 0; i < h; ++i) {
            scanf("%s", g[i]);
            _DEBUG_CMD(puts(g[i]));
        }
        // memset(gi, 0, sizeof(gi));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (g[i][j] == '*') {
                    gi[i][j] = vcnt++;
                    _DEBUG_CMD({ printf("i:%d j:%d g:%d\n", i, j, gi[i][j]); });
                }
            }
        }
        memset(head, -1, sizeof(head));
        ecnt = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (g[i][j] != '*') {
                    continue;
                }
                for (int k = 0; k < 4; ++k) {
                    int newi = i + dir[k][0];
                    int newj = j + dir[k][1];
                    if (newi >= 0 && newi < h && newj >= 0 && newj < w && g[newi][newj] == '*') {
                        add_edge(gi[i][j], gi[newi][newj]);
                        // add_edge(gi[newi][newj], gi[i][j]);
                    }
                }
            }
        }
        int ret = hungarian();
        _DEBUG_CMD({
            printf("vcnt: %d hret:%d matches: ", vcnt, ret);
            for (int i = 1; i < vcnt; ++i) {
                printf("%d ", match[i]);
            }
            puts("");
        });
        assert(ret % 2 == 0);
        // exit(0);
        printf("%d\n", vcnt - 1 - ret / 2);
    }
    return 0;
};

#endif
#endif
