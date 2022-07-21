#ifndef _t21pd_20210829_
#define _t21pd_20210829_
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
int T, N;
int money[MAXN], maxm;
double prob[MAXN], prob_n[MAXN];
double t;

const int MAXM = 1 << 14;
double pnt[MAXM];

int solve()
{
    fill_n(pnt, maxm + 1, 0);
    pnt[0] = 1;
    /*
    for (int i = 0; i < N; ++i) {
        if (pnt[money[i]] < prob_n[i]) {
            pnt[money[i]] = prob_n[i];
        }
    }
    */
    for (int i = 0; i < N; ++i) {
        for (int j = maxm; j >= 0; --j) {
            int mi = money[i];
            if (pnt[j] < pnt[j - mi] * prob_n[i]) {
                pnt[j] = pnt[j - mi] * prob_n[i];
            }
        }
    }

    for (int i = maxm; i >= 0; --i) {
        if (pnt[i] > 1 - t) {
            return i;
        }
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    for (int case_cnt = 1; case_cnt <= T; ++case_cnt) {
        scanf("%lf%d", &t, &N);
        maxm = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d%lf", &money[i], &prob[i]);
            prob_n[i] = 1 - prob[i];
            maxm += money[i];
        }
        int ans = solve();
        printf("Case %d: %d\n", case_cnt, ans);
        _DEBUG_CMD(printf("t:%lf,N:%d, maxm:%d ans:%d\n", t, N, maxm, ans););
        _DEBUG_CMD({
            printf("pnt: ");
            for (int i = 0; i <= maxm; ++i) {
                printf("%.3lf", pnt[i]);
            }
            printf("\n");
        });
    }
    return 0;
};

#endif
