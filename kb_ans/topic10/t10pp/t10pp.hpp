#if 0

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define INF 0x3f3f3f3f
/*  KM算法
 *   复杂度O(nx*nx*ny)
 *  求最大权匹配
 *  若求最小权匹配，可将权值取相反数，结果取相反数
 *  点的编号从0开始
 */

const int N = 317;
int nx, ny;                  //两边的点数
int g[N][N];                 //二分图描述
int linker[N], lx[N], ly[N]; // y中各点匹配状态，x,y中的点标号
int slack[N];
bool visx[N], visy[N];

bool DFS(int x)
{
    visx[x] = true;
    for (int y = 0; y < ny; y++) {
        if (visy[y])
            continue;
        int tmp = lx[x] + ly[y] - g[x][y];
        if (tmp == 0) {
            visy[y] = true;
            if (linker[y] == -1 || DFS(linker[y])) {
                linker[y] = x;
                return true;
            }
        }
        else if (slack[y] > tmp)
            slack[y] = tmp;
    }
    return false;
}
int KM()
{
    memset(linker, -1, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    for (int i = 0; i < nx; i++) {
        lx[i] = -INF;
        for (int j = 0; j < ny; j++)
            if (g[i][j] > lx[i])
                lx[i] = g[i][j];
    }
    for (int x = 0; x < nx; x++) {
        for (int i = 0; i < ny; i++)
            slack[i] = INF;
        while (true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if (DFS(x))
                break;
            int d = INF;
            for (int i = 0; i < ny; i++)
                if (!visy[i] && d > slack[i])
                    d = slack[i];
            for (int i = 0; i < nx; i++)
                if (visx[i])
                    lx[i] -= d;
            for (int i = 0; i < ny; i++) {
                if (visy[i])
                    ly[i] += d;
                else
                    slack[i] -= d;
            }
        }
    }
    printf("matches: ");
    for (int i = 0; i < ny; ++i) {
        printf("%d ", linker[i]);
    }
    printf("\n");
    int res = 0;
    for (int i = 0; i < ny; i++)
        if (linker[i] != -1)
            res += g[linker[i]][i];
    return res;
}
int main()
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        }
        nx = ny = n;
        int ans = KM();
        printf("%d\n", ans);
    }
    return 0;
}

#else
#ifndef _t10pp_20210307_
#define _t10pp_20210307_
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

const int MAXN = 1 << 9;
int n;
int g[MAXN][MAXN];
int lx[MAXN], ly[MAXN], match[MAXN], visx[MAXN], visy[MAXN];
int slack[MAXN];
int fa[MAXN + MAXN];

int dfs(int u)
{
    visx[u] = 1;
    for (int v = 0; v < n; ++v) {
        if (visy[v] == 0) {
            int dt = lx[u] + ly[v] - g[u][v];
            if (dt == 0) {
                visy[v] = 1;
                if (match[v] == -1 || dfs(match[v])) {
                    match[v] = u;
                    return 1;
                }
            }
            else {
                slack[v] = min(slack[v], dt);
            }
        }
    }
    return 0;
}

int KM2()
{
    memset(match, -1, sizeof(match));
    memset(ly, 0, sizeof(ly));
    for (int u = 0; u < n; ++u) {
        lx[u] = -1;
        for (int v = 0; v < n; ++v) {
            lx[u] = max(lx[u], g[u][v]);
        }
    }
    for (int u = 0; u < n; ++u) {
        memset(slack, 0x3F, sizeof(slack));
        while (1) {

            _DEBUG_CMD({
                int cnt = 0;
                for (int di = 0; di < n; ++di) {
                    for (int dj = 0; dj < n; ++dj) {
                        if (lx[di] + ly[dj] == g[di][dj]) {
                            ++cnt;
                        }
                    }
                };
                // int vxz = 0, vyz = 0; //wrong
                int vxz = 0;
                int vyz = 0;

                for (int di = 0; di < n; ++di) {
                    vxz += visx[di];
                    vyz += visy[di];
                };
                printf("u: %d, set visx visy cnt:%d, vxz:%d vyz:%d\n", u, cnt, vxz, vyz);
            });

            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));

            if (dfs(u)) {
                _DEBUG_CMD(printf("dfs on %d hit, break from inner loop\n", u));
                break;
            }
            int d = 0x3F3F3F3F;
            for (int i = 0; i < n; ++i) {
                if (!visy[i]) {
                    d = min(d, slack[i]);
                }
            }
            _DEBUG_CMD(printf("u:%d d:%d\n", u, d));
            for (int i = 0; i < n; ++i) {
                if (visx[i]) {
                    lx[i] -= d;
                }
            }
            for (int i = 0; i < n; ++i) {
                if (visy[i]) {
                    ly[i] += d;
                }
                else {
                    slack[i] -= d;
                }
            }
            _DEBUG_CMD(printf("u: %d ordinary loop end\n", u));
        }
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
            ret += g[match[i]][i];
        }
    }
    return ret;
}

int dfs2(int u)
{
    visx[u] = 1;
    for (int v = 0; v < n; ++v) {
        if (!visy[v]) {
            int dt = lx[u] + ly[v] - g[u][v];
            if (dt == 0) {
                visy[v] = 1;
                fa[v + n] = u;
                if (match[v] == -1) {
                    return v + n;
                }
                fa[match[v]] = v + n;
                int res = dfs2(match[v]);
                if (res >= 0) {
                    return res;
                }
            }
            else {
                slack[u] = min(slack[u], dt);
            }
        }
    }
    return -1;
}
int munkres()
{
    memset(ly, 0, sizeof(ly));
    for (int u = 0; u < n; ++u) {
        lx[u] = -1;
        for (int v = 0; v < n; ++v) {
            lx[u] = max(lx[u], g[u][v]);
        }
    }
    memset(match, -1, sizeof(match));
    for (int u = 0; u < n; ++u) {
        memset(visx, 0, sizeof(visx));
        memset(visy, 0, sizeof(visy));
        memset(slack, 0x3F, sizeof(slack));
        memset(fa, -1, sizeof(fa));

        bool first = true;
        int leaf = -1;

        while (1) {
            if (first) {
                leaf = dfs2(u);
                first = false;
            }
            else {
                for (int i = 0; i < n; ++i) {
                    if (slack[i] == 0) {
                        slack[i] = 0x3F3F3F3F;
                        leaf = dfs2(i);
                        if (leaf >= 0) {
                            break;
                        }
                    }
                }
            }
            if (leaf >= 0) {
                int p = leaf;
                while (p != -1) {
                    match[p - n] = fa[p];
                    p = fa[fa[p]];
                }
                break;
            }
            else {
                int d = 0x3F3F3F3F;
                for (int i = 0; i < n; ++i) {
                    if (visx[i]) {
                        d = min(d, slack[i]);
                    }
                }
                for (int i = 0; i < n; ++i) {
                    if (visx[i]) {
                        lx[i] -= d;
                        slack[i] -= d;
                    }
                    if (visy[i]) {
                        ly[i] += d;
                    }
                }
            }
        }
        _DEBUG_CMD({
            printf("u: %d, ", u);
            printf("matches: ");
            for (int i = 0; i < n; ++i) {
                printf("%d ", match[i]);
            }
            printf("\n");
        });
    }
    _DEBUG_CMD({
        puts("matches: ");
        for (int i = 0; i < n; ++i) {
            printf("%d ", match[i]);
        }
        printf("\n");
    });

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
            sum += g[match[i]][i];
        }
    }
    return sum;
}

int nx, ny;
const int oo = 0x3F3F3F3F;
int findpath(int x)
{
    int tempDelta;
    visx[x] = true;
    for (int y = 0; y < ny; y++) {
        if (visy[y])
            continue;
        // tempDelta = lx[x] + ly[y] - G[x][y];
        tempDelta = lx[x] + ly[y] - g[x][y];
        if (tempDelta == 0) {
            visy[y] = true;
            fa[y + nx] = x;
            if (match[y] == -1) {
                return y + nx;
            }
            fa[match[y]] = y + nx; //记录交替树的父亲信息（为了区别X，Y集合，Y的点都映射成n+y）
            int res = findpath(match[y]);
            if (res >= 0)
                return res; //返回增广路的末端叶子节点
        }
        else if (slack[x] > tempDelta) //统计以x为准的slack值。
            slack[x] = tempDelta;
    }
    return -1;
}
int KM()
{
    for (int x = 0; x < nx; ++x) {
        for (int i = 0; i < nx; ++i)
            slack[i] = oo;
        for (int i = 0; i < nx + ny; i++)
            fa[i] = -1;
        memset(visx, 0, sizeof(visx));
        memset(visy, 0, sizeof(visy)); //换到外面，可以保留原树
        int fir = 1;
        int leaf = -1;
        while (true) {
            if (fir == 1) {
                leaf = findpath(x);
                fir = 0;
            }
            else {
                for (int i = 0; i < nx; i++) {
                    if (slack[i] == 0) { //只接着搜有新边加入的X点
                        slack[i] = oo;   // slack要重新清空，方以后接着用
                        leaf = findpath(i);
                        if (leaf > 0)
                            break;
                    }
                }
            }
            if (leaf > 0) {
                int p = leaf;
                while (p > 0) {
                    match[p - nx] = fa[p];
                    p = fa[fa[p]]; //顺着记录一路找找上去
                }
                break;
            }
            else {
                int delta = oo;
                for (int i = 0; i < nx; ++i)
                    if (visx[i] && delta > slack[i])
                        delta = slack[i];
                for (int i = 0; i < nx; ++i)
                    if (visx[i]) {
                        lx[i] -= delta;
                        slack[i] -= delta;
                    } // X点的slack要响应改变，slack变0说明有新边加入
                for (int j = 0; j < ny; ++j) {
                    if (visy[j])
                        ly[j] += delta;
                }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < ny; ++i) {
        if (match[i] != -1) {
            sum += g[match[i]][i];
        }
    }
    return sum;
}

int main(int argc, char **avg)
{
    while (~scanf("%d", &n)) {
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &g[i][j]);
            }
        }
        nx = ny = n;
        int ret = munkres();
        // int ret = KM2();
        printf("%d\n", ret);
    }
    return 0;
};

int dfs1(int u)
{
    visx[u] = 1;
    for (int v = 0; v < n; ++v) {
        int dt = lx[u] + ly[v] - g[u][v];
        if (visy[v] == 0 && dt == 0) {
            visy[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
        else {
            slack[v] = min(slack[v], dt);
        }
    }
    return 0;
}

int munkres1()
{
    int sum = 0;
    memset(ly, 0, sizeof(ly));
    for (int u = 0; u < n; ++u) {
        lx[u] = -1;
        for (int v = 0; v < n; ++v) {
            lx[u] = max(lx[u], g[u][v]);
        }
    }
    memset(match, -1, sizeof(match));

    for (int u = 0; u < n; ++u) {
        fill_n(slack, MAXN, 0x3F3F3F3F);
        while (1) {
            int delta = 0x3F3F3F3F;
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if (dfs(u)) {
                break;
            }
            else {
                /*
                for (int i = 0; i < n; ++i) {
                    if (visx[i]) {
                        for (int j = 0; j < n; ++j) {
                            if (visy[i] == 0) {
                                delta = min(delta, lx[i] + ly[j] - g[i][j]);
                            }
                        }
                    }
                }
                */
                for (int j = 0; j < n; ++j) {
                    delta = min(delta, slack[j]);
                }
                if (delta == 0x3F3F3F3F) {
                    return -1; // no perfect match.
                }
                for (int i = 0; i < n; ++i) {
                    if (visx[i]) {
                        lx[i] -= delta;
                    }
                    if (visy[i]) {
                        ly[i] += delta;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
            sum += g[match[i]][i];
        }
    }
    return sum;
}
#endif
#endif
