#ifndef _t16pc_20200624_
#define _t16pc_20200624_
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

const int MAXN = 1 << 10;
char s[MAXN];
char t[MAXN];
int slen, tlen;
int nxt[MAXN];

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    while (i < tlen) {
        if (j == -1 || t[i] == t[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int kmp()
{
    int ret = 0;
    int i = 0, j = 0;
    while (i < slen) {
        if (j == -1 || s[i] == t[j]) {
            ++i;
            ++j;
        }
        else {
            j = nxt[j];
        }
        if (j == tlen) {
            ++ret;
            j = 0;
        }
    }
    return ret;
}

int main(int argc, char **argv)
{
    while (scanf("%s%s", s, t) == 2) {
        slen = strlen(s);
        tlen = strlen(t);
        build_next();
        // printf("s:%s t:%s slen:%d tlen:%d\n", s, t, slen, tlen);
        printf("%d\n", kmp());
    }
    return 0;
};

#endif
