#ifndef _t16pg_20200703_
#define _t16pg_20200703_
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

const int MAXN = 1e6 + 3;
int nxt[MAXN];
char str[MAXN];
int slen;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    slen = strlen(str);
    while (i <= slen) {
        if (j == -1 || str[i] == str[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int main(int argc, char **argv)
{
    while (~scanf("%s", str)) {
        if (strcmp(str, ".") == 0) {
            break;
        }
        build_next();
        int len = slen - nxt[slen];
        int n = 1;
        // if (nxt[slen] != 0 && len % nxt[slen] == 0) { // wa
        if (nxt[slen] != 0 && slen % len == 0) { // ac
                                                 // if (slen % len == 0) { // ac
            n = slen / len;
        }
        _DEBUG_CMD({
            printf("next:");
            for (int i = 0; i <= slen; ++i) {
                printf(" %d", nxt[i]);
            }
            printf("\n");
            printf("n:%d nxt[%d]: %d slen:%d len:%d\n", n, slen, nxt[slen], slen, len);
            printf("next[%d]:%d ? 0, slen(%d) %% len(%d): %d\n", slen, nxt[slen], slen, len,
                   slen % len);
            if (nxt[slen] != 0) {
                printf("len:%d %% nxt[%d]:%d: %d\n", len, slen, nxt[slen], len % nxt[slen]);
            }
            else {
                printf("nxt[%d]:0\n", slen);
            }
        });
        /*
        if (len != 0) {
            n = slen / len;
        }
        else {
            n = 1;
        }
        */
        printf("%d\n", n);
    }
    return 0;
};

#endif
