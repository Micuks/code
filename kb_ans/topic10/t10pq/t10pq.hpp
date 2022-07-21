#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#define INF 1e9
using namespace std;
const int maxn = 200 + 5;
static int rmtcnt = 0;

struct Max_Match {
    int n, W[maxn][maxn];
    int Lx[maxn], Ly[maxn];
    bool S[maxn], T[maxn];
    int left[maxn];

    bool match(int i)
    {
        ++rmtcnt;
        S[i] = true;
        for (int j = 1; j <= n; j++)
            if (Lx[i] + Ly[j] == W[i][j] && !T[j]) {
                T[j] = true;
                if (left[j] == -1 || match(left[j])) {
                    left[j] = i;
                    return true;
                }
            }
        return false;
    }

    void update()
    {
        int a = 1 << 30;
        for (int i = 1; i <= n; i++)
            if (S[i])
                for (int j = 1; j <= n; j++)
                    if (!T[j])
                        a = min(a, Lx[i] + Ly[j] - W[i][j]);
        for (int i = 1; i <= n; i++) {
            if (S[i])
                Lx[i] -= a;
            if (T[i])
                Ly[i] += a;
        }
    }

    int solve(int n)
    {
        this->n = n;
        memset(left, -1, sizeof(left));
        for (int i = 1; i <= n; i++) {
            Lx[i] = Ly[i] = 0;
            for (int j = 1; j <= n; j++)
                Lx[i] = max(Lx[i], W[i][j]);
        }

        static int wtcnt = 0;
        static int mtcnt = 0;
        for (int i = 1; i <= n; i++) {
            while (true) {
                ++wtcnt;
                for (int j = 1; j <= n; j++)
                    S[j] = T[j] = false;
                if (match(i)) {
                    ++mtcnt;
                    break;
                }
                else
                    update();
            }
        }
        printf("wtcnt: %d, mtcnt: %d, rmtcnt: %d\n", wtcnt, mtcnt, rmtcnt);

        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans += W[left[i]][i];
        return -ans;
    }
} KM;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                KM.W[i][j] = -INF;
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            KM.W[u][v] = max(KM.W[u][v], -w);
        }
        printf("%d\n", KM.solve(n));
    }
    return 0;
}

#else
#ifndef _t10pq_20210616_
#define _t10pq_20210616_
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

const int MAXN = 1 << 8;
const int MAXM = 3e4 + 3;
int T, N, M;

int g[MAXN][MAXN];
int lx[MAXN], ly[MAXN];
int visx[MAXN], visy[MAXN];
int match[MAXN];
int slack[MAXN];

static int rmtcnt = 0;
int dfs(int u)
{
    ++rmtcnt;
    visx[u] = 1;
    for (int v = 1; v <= N; ++v) {
        if (g[u][v] == 1) {
            continue;
        }
        if (visy[v]) {
            continue;
        }
        int dt = lx[u] + ly[v] - g[u][v];
        if (dt == 0) {
            visy[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
        // slack[v] = min(slack[v], dt);
        //*
        else {
            slack[v] = min(slack[v], dt);
        }
        //*/
    }
    return 0;
}

int KM()
{
    static int wtcnt = 0;
    static int mtcnt = 0;
    // memset(match, -1, sizeof(match));
    // memset(ly, 0, sizeof(ly));
    fill_n(match, N + 1, -1);
    fill_n(ly, N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        lx[i] = -0x3F3F3F3F;
        for (int j = 1; j <= N; ++j) {
            if (g[i][j] != 0) {
                lx[i] = max(lx[i], g[i][j]);
            }
        }
    }
    for (int u = 1; u <= N; ++u) {
        _DEBUG_CMD({ printf("in km u=%d\n", u); });
        fill_n(slack, MAXN, 0x3F3F3F3F);
        while (true) {
            ++wtcnt;
            // memset(visx, 0, sizeof(visx));
            // memset(visy, 0, sizeof(visy));
            fill_n(visx, N + 1, 0);
            fill_n(visy, N + 1, 0);
            if (dfs(u) != 0) {
                ++mtcnt;
                break;
            }
            int d = 0x3F3F3F3F;
            for (int i = 1; i <= N; ++i) {
                if (!visy[i]) {
                    d = min(d, slack[i]);
                }
            }
            _DEBUG_CMD({
                printf("u: %d, d: %d\n", u, d);
                printf("lx: ");
                for (int i = 1; i <= N; ++i) {
                    printf("%d ", lx[i]);
                }
                printf("\nly: ");
                for (int i = 1; i <= N; ++i) {
                    printf("%d ", ly[i]);
                }
                printf("\n");
            });
            for (int i = 1; i <= N; ++i) {
                if (visx[i]) {
                    lx[i] -= d;
                }
            }
            for (int i = 1; i <= N; ++i) {
                if (visy[i]) {
                    ly[i] += d;
                }
                else {
                    slack[i] -= d;
                }
            }
        }
    }
    _DEBUG_CMD(printf("wtcnt: %d mtcnt: %d rmtcnt:%d\n", wtcnt, mtcnt, rmtcnt));

    int res = 0;
    for (int i = 1; i <= N; ++i) {
        if (match[i] != -1) {
            res += g[match[i]][i];
        }
    }
    return -res;
}

int main(int argc, char **argv)
{
    int u, v, w;
    // cin >> T;
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        // memset(g, 0, sizeof(g));
        // fill_n(g, sizeof(g) / sizeof(int), 1);
        for (int i = 0; i < MAXN; ++i) {
            fill_n(g[i], sizeof(g[i]) / sizeof(int), 1);
        }
        scanf("%d%d", &N, &M);
        for (int j = 0; j < M; ++j) {
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = g[u][v] == 1 ? -w : max(-w, g[u][v]);
        }
        int res = KM();
        printf("%d\n", res);
    }
    return 0;
};

#endif
#endif
