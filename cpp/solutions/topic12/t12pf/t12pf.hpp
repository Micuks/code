#ifndef _t12pf_20200225_
#define _t12pf_20200225_
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

// const int MAXN = 1e4 + 7;
const int MAXN = 512;
const int CANNOTREACH = 0x3F3F3F3F;
int T;
int E, F;
int N;
int P[MAXN], W[MAXN];
int reachable[10007];

int main(int argc, char **argv)
{
    cin >> T;
    while (T--) {
        int val = 0;
        cin >> E >> F;
        cin >> N;
        // scanf("%d%d%d", &E, &F, &N);
        const int delta = F - E;
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &P[i], &W[i]);
        }
        memset(reachable, 0x3F, sizeof(reachable));
        reachable[0] = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = W[i]; j <= delta; ++j) {
                reachable[j] = min(reachable[j], reachable[j - W[i]] + P[i]);
            }
        }
        _DEBUG_CMD({
            for (int i = 0; i <= delta; ++i) {
                cout << reachable[i] << ' ';
            }
            cout << endl;
        });
        val = reachable[delta];
        if (val != CANNOTREACH) {
            printf("The minimum amount of money in the piggy-bank is %d.\n", val);
        }
        else {
            printf("This is impossible.\n");
        }
    }
    return 0;
};

#endif
