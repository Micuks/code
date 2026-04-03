#if 0
#define TEST
#undef TEST

#define MAX_N 1000
#define INF 40000000

#include <stdio.h>
#include <stdlib.h>

struct platform_type {
    int x1, x2, h;
};

platform_type p[MAX_N + 2];
int cases, n, max_h;
int left[MAX_N + 2], right[MAX_N + 2];

int Min(int a, int b) { return a < b ? a : b; }

int compare(const void *e1, const void *e2)
{
    return ((const platform_type *) e1)->h - ((const platform_type *) e2)->h;
}

int main()
{
    int k;
    scanf("%d", &cases);
    p[0].x1 = -20000;
    p[0].x2 = 20000;
    p[0].h = 0;
    while (cases--) {
        scanf("%d", &n);
        scanf("%d%d%d", &p[n + 1].x1, &p[n + 1].h, &max_h);
        p[n + 1].x2 = p[n + 1].x1;
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &p[i].x1, &p[i].x2, &p[i].h);
        qsort(p, n + 2, sizeof(platform_type), compare);
#ifdef TEST
        for (int i = 0; i <= n + 1; i++)
            printf("%d %d %d\n", p[i].x1, p[i].x2, p[i].h);
#endif
        for (int i = 1; i <= n + 1; i++) {
            k = i - 1;
            left[i] = -1;
            while (k && p[i].h - p[k].h <= max_h) {
                if (p[i].x1 >= p[k].x1 && p[i].x1 <= p[k].x2) {
                    left[i] = p[i].h - p[k].h +
                              Min(left[k] + p[i].x1 - p[k].x1, right[k] + p[k].x2 - p[i].x1);
                    break;
                }
                else
                    k--;
            }
            if (left[i] == -1) {
                if (p[i].h - p[k].h > max_h)
                    left[i] = INF;
                else
                    left[i] = p[i].h;
            }
            k = i - 1;
            right[i] = -1;
            while (k && p[i].h - p[k].h <= max_h) {
                if (p[i].x2 >= p[k].x1 && p[i].x2 <= p[k].x2) {
                    right[i] = p[i].h - p[k].h +
                               Min(left[k] + p[i].x2 - p[k].x1, right[k] + p[k].x2 - p[i].x2);
                    break;
                }
                else
                    k--;
            }
            if (right[i] == -1) {
                if (p[i].h - p[k].h > max_h)
                    right[i] = INF;
                else
                    right[i] = p[i].h;
            }
        }
        printf("%d\n", left[n + 1]);
    }
    return 0;
}

#elif 0
#include <stdio.h>
#include <stdlib.h>

#define MAXN 1010
#define INF 9000000

typedef struct platform {
    int x1;
    int x2;
    int high;
} Platform;

int compare(const void *p, const void *q)
{
    Platform *p1 = (Platform *) p;
    Platform *q1 = (Platform *) q;
    return p1->high - q1->high;
}

int Min(int a, int b) { return (a < b) ? a : b; }

int N, X, Y, MAX;
Platform plat[MAXN];
int dp[MAXN][2]; // dp[i][0]、dp[i][1]分别表示从第i个平台左、右边到地面的最短时间

void LeftMinTime(int i)
{ //计算从平台i左边到地面的最短时间
    int k = i - 1;
    while (k > 0 && plat[i].high - plat[k].high <= MAX) {
        //如果平台i左边下面有平台，且两者相距不超过MAX
        if (plat[i].x1 >= plat[k].x1 && plat[i].x1 <= plat[k].x2) {
            dp[i][0] = plat[i].high - plat[k].high +
                       Min(plat[i].x1 - plat[k].x1 + dp[k][0], plat[k].x2 - plat[i].x1 + dp[k][1]);
            return;
        }
        else
            --k;
    }
    //如果平台i左边下面没有平台，或者两者相距超过了MAX
    if (plat[i].high - plat[k].high > MAX)
        dp[i][0] = INF;
    else
        dp[i][0] = plat[i].high;
}

void RightMinTime(int i)
{ //计算从平台i右边到地面的最短时间
    int k = i - 1;
    while (k > 0 && plat[i].high - plat[k].high <= MAX) {
        //如果平台i右边下面有平台，且两者相距不超过MAX
        if (plat[i].x2 >= plat[k].x1 && plat[i].x2 <= plat[k].x2) {
            dp[i][1] = plat[i].high - plat[k].high +
                       Min(plat[i].x2 - plat[k].x1 + dp[k][0], plat[k].x2 - plat[i].x2 + dp[k][1]);
            return;
        }
        else
            --k;
    }
    //如果平台i右边下面没有平台，或者两者相距超过了MAX
    if (plat[i].high - plat[k].high > MAX)
        dp[i][1] = INF;
    else
        dp[i][1] = plat[i].high;
}

int ShortestTime()
{
    int i, j;

    for (i = 1; i <= N + 1; ++i) {
        LeftMinTime(i);
        RightMinTime(i);
    }
    return Min(dp[N + 1][0], dp[N + 1][1]);
}

int main()
{
    int t;
    int i;
    while (scanf("%d", &t) != EOF) {
        while (t-- != 0) {
            scanf("%d%d%d%d", &N, &X, &Y, &MAX);
            for (i = 1; i <= N; ++i) {
                scanf("%d%d%d", &plat[i].x1, &plat[i].x2, &plat[i].high);
            }
            plat[0].high = 0;
            plat[0].x1 = -20000;
            plat[0].x2 = 20000;
            plat[N + 1].high = Y;
            plat[N + 1].x1 = X;
            plat[N + 1].x2 = X;
            //根据平台高度按从低到高排序
            qsort(plat, N + 2, sizeof(Platform), compare);
            printf("%d\n", ShortestTime());
        }
    }

    return 0;
}
#else
#ifndef _t12pm_20200325_
#define _t12pm_20200325_
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
#define _DEBUG_CMD(cmd)                                                                            \
    do {                                                                                           \
        ;                                                                                          \
    } while (false)

const int MAXN = 1 << 10;
const int MAXW = 4e4 + 9;
// const int OFFSET = 2e4;
const int OFFSET = 0;
const int INF = 0x3F3F3F3F;
int test_case;
int drop_t[MAXN][2];
int n, x, y, max_h;

struct Bar {
    int x1;
    int x2;
    int h;
    bool operator<(const Bar &bar) const { return h < bar.h; }
};

Bar b[MAXN];

void solve(int x, int y, int t, vector<int> &td)
{
    Bar tmp;
    tmp.h = y;
    tmp.x1 = x;
    tmp.x2 = x;

    Bar *bp_s = upper_bound(b, b + n, tmp);
    Bar *bp = bp_s;
    if (bp - b == n) {
        bp = bp - 1;
    }
    while (y - bp->h <= max_h && bp >= b) {
        if ((x <= bp->x2 && x >= bp->x1 && y - bp->h > 0) ||
            (x < bp->x2 && x > bp->x1 && y - bp->h >= 0)) {
            break;
        }
        --bp;
    }
    int bi = bp - b;
    DEBUG_CMD({
        Bar *bt = bp;
        // printf("bp_s: %p, bp_e: %p, b: %p, b+n: %p\n", bp_s, bp_e, b, b + n);
        printf("in solve, x: %d, y: %d, cur_h: %d, t: %d, bi:%d bar found is listed below\n", x, y,
               y, t, bi);
        while (bt >= b) {
            printf("x1: %d, x2: %d, h: %d\n", bt->x1, bt->x2, bt->h);
            --bt;
        }
    });

    int lt = x - bp->x1;
    int rt = bp->x2 - x;

    if (bi == -1) {
        // no case is less than current node
        // no pltform can hold it, or they are too far away from the mickey.
        if (y <= max_h) {
            // drop to ground directly
            DEBUG_CMD({
                cout << "td push_back " << t + y << endl;
                cout << "y <= max_h  LINE: " << __LINE__ << endl;
            });
            td.push_back(t + y);
        }
        return;
    }
    if (y - bp->h > max_h) {
        return;
    }

    if (bi == 0) {
        if (drop_t[bi][0] > lt + t + y) {
            drop_t[bi][0] = lt + t + y;
            DEBUG_CMD({
                cout << "td push_back " << lt + t + y << " lt: " << lt << " t: " << t << " x: " << x
                     << " y: " << y << endl;
                cout << "drop_t[bi][0] > lt + t + y LINE: " << __LINE__ << " bi: " << bi << endl;
            });
            td.push_back(lt + t + y);
        }
        if (drop_t[bi][1] > rt + t + y) {
            drop_t[bi][1] = rt + t + y;
            DEBUG_CMD({
                cout << "td push_back " << rt + t + y << " rt: " << rt << " t: " << t << " x: " << x
                     << " y: " << y << endl;
                cout << "drop_t[bi][1] > rt + t + y LINE: " << __LINE__ << " bi: " << bi << endl;
            });
            td.push_back(rt + t + y);
        }
        return;
    }
    if (drop_t[bi][0] > lt + t + y - bp->h) {
        drop_t[bi][0] = lt + t + y - bp->h;
        solve(bp->x1, bp->h, t + lt + y - bp->h, td);
    }
    if (drop_t[bi][1] > rt + t + y - bp->h) {
        drop_t[bi][1] = rt + t + y - bp->h;
        solve(bp->x2, bp->h, t + rt + y - bp->h, td);
    }
}

int main(int argc, char **argv)
{
    cin >> test_case;
    while (test_case--) {
        scanf("%d%d%d%d", &n, &x, &y, &max_h);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &b[i].x1, &b[i].x2, &b[i].h);
            b[i].x1 += OFFSET;
            b[i].x2 += OFFSET;
        }
        memset(drop_t, 0x3F, sizeof(drop_t));
        sort(b, b + n);
        DEBUG_CMD({
            for (int i = 0; i < n; ++i) {
                printf("b[%d]: x1: %d, x2: %d, h: %d\n", i, b[i].x1, b[i].x2, b[i].h);
            }
            cout << "x: " << x + OFFSET << " y: " << y << endl;
        });
        vector<int> touch_ground;
        solve(x + OFFSET, y, 0, touch_ground);
        cout << *min_element(touch_ground.begin(), touch_ground.end()) << endl;
        DEBUG_CMD({
            cout << "touch_ground: " << endl;
            for (auto it = touch_ground.begin(); it != touch_ground.end(); ++it) {
                cout << *it << ' ';
            }
            cout << endl << "drop_t: " << endl;
            for (int i = 0; i < n; ++i) {
                cout << drop_t[i][0] << ' ' << drop_t[i][1] << endl;
            }
            cout << endl;
        });
    }
    return 0;
};

#endif
#endif
