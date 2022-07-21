#if 0
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define mann 1010
#define INF 0x3f3f3f3f
typedef long long LL;
int t, n, cnt;
char s[mann][mann];
int a[mann][mann];
int head[mann], mylink[mann], vis[mann];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
struct node {
    int to, next;
} eg[mann * 20];
void add(int u, int v)
{
    eg[cnt].to = v;
    eg[cnt].next = head[u];
    head[u] = cnt++;
}
int dfs(int u)
{
    for (int i = head[u]; i != -1; i = eg[i].next) {
        int v = eg[i].to;
        if (!vis[v]) {
            vis[v] = 1;
            if (mylink[v] == -1 || dfs(mylink[v])) {
                mylink[v] = u;
                return true;
            }
        }
    }
    return false;
}
int match(int nn)
{
    int ans = 0;
    memset(mylink, -1, sizeof(mylink));
    for (int i = 0; i < nn; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i))
            ans++;
    }
    return ans;
}
int main()
{
    int T = 0;
    scanf("%d", &t);
    while (t--) {
        memset(head, -1, sizeof(head));
        memset(a, 0, sizeof(a));
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);
        int num = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (s[i][j] == '#') {
                    a[i][j] = num++;
                    //  printf("%d ",a[i][j]);
                }
            }
            //  printf("\n");
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (s[i][j] == '#') {
                    for (int k = 0; k < 4; k++) //相邻的四个方向
                    {
                        int xx = i + dx[k];
                        int yy = j + dy[k];
                        if (xx >= 0 && xx < n && yy >= 0 && yy < n && s[xx][yy] == '#') {
                            add(a[i][j], a[xx][yy]);
                            add(a[xx][yy], a[i][j]);
                            // printf("%d*%d  ",a[i][j],a[xx][yy]);
                        }
                    }
                }
            }
        }
        int ans = match(num) >> 1; //这里要注意
        printf("Case %d: %d\n", ++T, ans);
    }
}
#else
#ifndef _t10pg_20210211_
#define _t10pg_20210211_
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
int K, N;
char m[MAXN][MAXN];
int g[MAXN][MAXN];
int vnum;

char visited[MAXN];
int match[MAXN];

// const int MAXN = 1 << 12;
int head[MAXN], ecnt;
const int MAXE = MAXN * 20;
struct Edge {
    int v;
    int next;
} edges[MAXE];

void add_edge(int u, int v)
{
    edges[ecnt].next = head[u];
    edges[ecnt].v = v;
    head[u] = ecnt++;
}

int dfs(int u)
{
    // for (int h = head[u]; h = edges[h].next; h != -1) {
    for (int h = head[u]; h != -1; h = edges[h].next) {
        int v = edges[h].v;
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
    for (int i = 1; i < vnum; ++i) {
        memset(visited, 0, sizeof(visited));
        ret += dfs(i);
    }
    return ret;
}

int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main(int argc, char **argv)
{
    scanf("%d", &K);
    for (int c = 1; c <= K; ++c) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%s", m[i]);
        }
        memset(g, 0, sizeof(g));
        memset(head, -1, sizeof(head));
        ecnt = 0;

        vnum = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (m[i][j] == '#') {
                    g[i][j] = vnum++;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (m[i][j] != '#') {
                    continue;
                }
                for (int k = 0; k < 4; ++k) {
                    int newi = i + dir[k][0];
                    int newj = j + dir[k][1];
                    if (newi >= 0 && newi < N && newj >= 0 && newj < N && m[newi][newj] == '#') {
                        add_edge(g[i][j], g[newi][newj]);
                        add_edge(g[newi][newj], g[i][j]);
                    }
                }
            }
        }
        int res = hungarian();
        _DEBUG_CMD({
            printf("matches: ");
            for (int i = 1; i < vnum; ++i) {
                printf("%d ", match[i]);
            }
            puts("");
        });
        printf("Case %d: %d\n", c, res / 2);
    }
    return 0;
};

#endif
#endif
