#if 0
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX 1000
#define INF 1000000000
//#define min(a, b) ((a) < (b) ? (a) : (b))

struct point {

    int x, y;
} p[MAX];
int cost[MAX][MAX], n, m;
int dp[MAX][MAX];

int abs(int x) { return x < 0 ? -x : x; }
point save[400], temp[400];
int xmult(point p1, point p2, point p0)
{

    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
bool cmp(const point &a, const point &b)
{

    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}
int Graham(point *p, int n)
{

    int i;
    sort(p, p + n, cmp);
    save[0] = p[0];
    save[1] = p[1];
    int top = 1;
    for (i = 0; i < n; i++) {

        while (top && xmult(save[top], p[i], save[top - 1]) >= 0)
            top--;
        save[++top] = p[i];
    }

    int mid = top;
    for (i = n - 2; i >= 0; i--) {

        while (top > mid && xmult(save[top], p[i], save[top - 1]) >= 0)
            top--;
        save[++top] = p[i];
    }
    return top;
}
int Count(point a, point b) { return (abs(a.x + b.x) * abs(a.y + b.y)) % m; }

int main()
{
    int i, j, k, r, u;

    while (scanf("%d%d", &n, &m) != EOF) {

        for (i = 0; i < n; ++i)
            scanf("%d%d", &p[i].x, &p[i].y);

        int tot = Graham(p, n); //求凸包
        if (tot < n)
            printf("I can't cut.\n");
        else {

            memset(cost, 0, sizeof(cost));
            for (i = 0; i < n; ++i)
                for (j = i + 2; j < n; ++j)
                    cost[i][j] = cost[j][i] = Count(save[i], save[j]);

            for (i = 0; i < n; ++i) {

                for (j = 0; j < n; ++j)
                    dp[i][j] = INF;
                dp[i][(i + 1) % n] = 0;
            }
            for (i = n - 3; i >= 0; --i) //注意这三个for循环的顺序
                for (
                    j = i + 2; j < n;
                    ++j) //因为要保证在算dp[i][j]时dp[i][k]和dp[k][j]时已经计算，所以i为逆序，j要升序
                    for (k = i + 1; k <= j - 1; ++k)
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + cost[i][k] + cost[k][j]);

            /*
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    printf("%d ", dp[i][j] == INF ? -1 : dp[i][j]);
                }
                printf("\n");
            }
            */
            printf("%d\n", dp[0][n - 1]);
        }
    }
}

#else
#ifndef _t22pa_20210916_
#define _t22pa_20210916_
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

const long long INF = 0x3F3F3F3F3F3F3F3F;
const int MAXN = 1 << 10;
struct Point {
    int x, y;
    bool operator<(const Point &p) const
    {
        /*
        if (y != p.y) {
            return y < p.y;
        }
        return x > p.x;
        */
        if (x != p.x) {
            return x < p.x;
        }
        return y > p.y;
    }
    bool operator!=(const Point &p) const { return *this < p || p < *this; }
    bool operator==(const Point &p) const { return !(*this != p); };
};
Point pts[MAXN];
int N, p;
struct PtsCmp1 {
    bool operator()(const Point &p1, const Point &p2) const
    {
        Point np1 = Point{p1.x - pts[0].x, p1.y - pts[0].y};
        Point np2 = Point{p2.x - pts[0].x, p2.y - pts[0].y};
        return np1.x * np2.y - np1.y * np2.x < 0;
    }
};
struct PtsCmp2 {
    bool operator()(const Point &p1, const Point &p2) const
    {
        Point np1 = Point{p1.x - pts[0].x, p1.y - pts[0].y};
        Point np2 = Point{p2.x - pts[0].x, p2.y - pts[0].y};
        // return np1.x * np2.y - np1.y * np2.x < 0;
        return np1.y / sqrt(np1.x * np1.x + np1.y * np1.y) <
               np2.y / sqrt(np2.x * np2.x + np2.y * np2.y);
    }
};
struct PtsCmp {
    const Point pt;
    PtsCmp(const Point &p) : pt(p) {}
    bool operator()(const Point &p1, const Point &p2) const
    {
        Point np1 = Point{p1.x - pt.x, p1.y - pt.y};
        Point np2 = Point{p2.x - pt.x, p2.y - pt.y};
        return np1.y / sqrt(double(np1.x) * np1.x + (double) np1.y * np1.y) <
               np2.y / sqrt(double(np2.x) * np2.x + (double) np2.y * np2.y);
    }
};

bool left_turn(const Point &p1, const Point &p2, const Point &p3)
{
    Point v1 = Point{p2.x - p1.x, p2.y - p1.y};
    Point v2 = Point{p3.x - p2.x, p3.y - p2.y};
    return v1.x * v2.y - v1.y * v2.x > 0;
}
int convex_hull()
{
    int lb = 0;
    for (int i = 1; i < N; ++i) {
        if (pts[i] < pts[lb]) {
            lb = i;
        }
    }
    if (lb != 0) {
        swap(pts[lb], pts[0]);
    }
    PtsCmp cmp(pts[0]);
    sort(pts + 1, pts + N, cmp);
    _DEBUG_CMD({
        for (int i = 2; i < N; ++i) {
            /*
            printf("pts:(%d,%d)<(%d,%d), bool:%d\n", pts[i - 1].x, pts[i - 1].y, pts[i].x,
               pts[i].y, (int) cmp(pts[i - 1], pts[i]));
            */
            printf("dt:(%d,%d)%.4lf<(%d,%d)%.4lf\n", pts[i - 1].x - pts[0].x,
                   pts[i - 1].y - pts[0].y,
                   (double) (pts[i - 1].y - pts[0].y) /
                       sqrt((double) (pts[i - 1].x - pts[0].x) * (pts[i - 1].x - pts[0].x) +
                            ((double) pts[i - 1].y - pts[0].y) * (pts[i - 1].y - pts[0].y)),
                   pts[i].x - pts[0].x, pts[i].y - pts[0].y,
                   (double) (pts[i].y - pts[0].y) /
                       sqrt((double) (pts[i].x - pts[0].x) * (pts[i].x - pts[0].x) +
                            ((double) pts[i].y - pts[0].y) * (pts[i].y - pts[0].y)));
        }
    });
    // stack<Point> sp;
    Point sp[MAXN];
    int spi = 0;
    sp[spi++] = pts[0];
    sp[spi++] = pts[1];
    // sp[spi++] = pts[2];

    for (int i = 2; i < N; ++i) {
        while (spi >= 2 && left_turn(sp[spi - 2], sp[spi - 1], pts[i]) == false) {
            --spi;
        }
        sp[spi++] = pts[i];
    }

    return spi;
}

long long dp[MAXN][MAXN];
long long cost(const Point &p1, const Point &p2)
{
    int idx1 = &p1 - pts;
    int idx2 = &p2 - pts;
    long long sx = abs(p1.x + p2.x);
    long long sy = abs(p1.y + p2.y);
    _DEBUG_CMD({ printf("dist(%d,%d):%lld\n", idx1, idx2, (sx * sy) % p); });
    if (((idx1 + 1 - idx2) % N) == 0) {
        return 0;
    }
    return (sx * sy) % p;
}
long long solve(int i, int j)
{
    assert(i < j);
    if (dp[i][j] != INF) {
        return dp[i][j];
    }
    if (((i + 1 - j) % N) == 0) {
        return dp[i][j] = 0;
    }
    long long ans = INF;
    for (int k = i + 1; k < j; ++k) {
        // long long dt = pts[i] == pts[j] ? 0 : cost(pts[i], pts[k]) + cost(pts[j], pts[k]);
        long long dt = pts[i] == pts[j] ? 0 : cost(pts[i], pts[k]) + cost(pts[k], pts[j]);
        // long long dt = cost(pts[i], pts[k]) + cost(pts[j], pts[k]);
        long long sv = ans = min(ans, solve(i, k) + solve(k, j) + dt);
    }
    return dp[i][j] = ans;
}

int main(int argc, char **argv)
{
    // printf("inf:%lld\n", INF);
    while (~scanf("%d%d", &N, &p)) {
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &pts[i].x, &pts[i].y);
        }
        int cv_cnt = convex_hull();
        memcpy(pts + N, pts, sizeof(Point) * N);
        if (cv_cnt != N) {
            _DEBUG_CMD({
                printf("pts: \n");
                for (int i = 0; i < N; ++i) {
                    printf("%d,%d\n", pts[i].x, pts[i].y);
                }
                printf("\n");
            });
            _DEBUG_CMD(printf("cv_cnt:%d N:%d\n", cv_cnt, N));
            printf("I can't cut.\n");
            continue;
        }
        memset(dp, 0x3F, sizeof(dp));
#define ITERATIVE true
#ifdef ITERATIVE
        for (int i = 0; i < N; ++i) {
            dp[i][(i + 1) % N] = 0;
        }

        _DEBUG_CMD({
            printf("N:%d\n", N);
            printf("dp: \n");
            for (int i = 0; i < 2 * N; ++i) {
                for (int j = 0; j < 2 * N; ++j) {
                    printf("%lld ", dp[i][j]);
                }
                printf("\n");
            }
        });

        for (int i = 2; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                // int inext = (j +i) % (2 * N)
                for (int k = 1; k < i; ++k) {
                    long long newcost = dp[j][j + k] + dp[j + k][j + i] + cost(pts[j], pts[j + k]) +
                                        cost(pts[j + k], pts[j + i]);
                    _DEBUG_CMD({
                        printf("i:%d,j:%d,k:%d, old:[%d,%d]: %lld, [%d,%d]:%lld + "
                               "[%d,%d]:%lld cost:%lld\n",
                               i, j, k, j, j + i, dp[j][j + i], j, j + k, dp[j][j + k], j + k,
                               j + i, dp[j + k][j + i], cost(pts[j], pts[j + k]));
                    });
                    dp[j][j + i] = min(dp[j][j + i], newcost);
                }
            }
        }

        _DEBUG_CMD({
            printf("iterative dp matrix:\n");
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    printf("%lld ", dp[i][j] == INF ? -1 : dp[i][j]);
                }
                printf("\n");
            }
        });
        long long ans = dp[0][N - 1];
        /*
        for (int i = 0; i <= N; ++i) {
            _DEBUG_CMD(printf("dp[%d][%d]:%lld\n", i, i + N - 1, dp[i][i + N - 1]));
            ans = min(ans, dp[i][i + N - 1]);
        }
        */
#else
        long long ans = solve(0, N - 1);
        _DEBUG_CMD({
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    printf("%lld ", dp[i][j] == INF ? -1 : dp[i][j]);
                }
                printf("\n");
            }
        });
#endif
        printf("%lld\n", ans);
    }
    return 0;
};

#endif
#endif
