#ifndef _t16pk_20200707_
#define _t16pk_20200707_
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

const int mod = 1e4 + 7;
const int MAXN = 2e5 + 3;
int nxt[MAXN];
int nacc[MAXN];
char s[MAXN];
int slen, t;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    while (i <= slen) {
        if (j == -1 || s[i] == s[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int acc_next()
{
    int res = slen;
    memset(nacc, 0, sizeof(nacc));
    for (int i = 1; i <= slen; ++i) {
        if (nxt[i] != 0) {
            nacc[i] = (nacc[nxt[i]] + 1) % mod;
        }
        else {
            nacc[i] = 0;
        }
    }

    return accumulate(&nacc[1], &nacc[slen + 1], res) % mod;
}

int main(int argc, char **argv)
{
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &slen);
        scanf("%s", s);
        build_next();
        int res = acc_next();
        printf("%d\n", res);
    }
    return 0;
};

#endif
