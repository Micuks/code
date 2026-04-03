#ifndef _t16pz_20200721_
#define _t16pz_20200721_
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
char str[MAXN];
int slen;
int nxt[MAXN];
int N;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
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
    scanf("%d", &N);
    while (N--) {
        scanf("%s\n", str);
        slen = strlen(str);
        build_next();
        int mm = nxt[slen];
        while (true) {
            bool ans = false;
            for (int i = mm; i <= slen - mm; ++i) {
                if (mm == -1) {
                    break;
                }
                if (nxt[i] >= mm) {
                    ans = true;
                }
            }
            if (ans) {
                printf("%d\n", mm);
                break;
            }
            else {
                if (mm == -1) {
                    printf("0\n");
                    break;
                }
                else {
                    mm = nxt[mm];
                }
            }
        }
    }
    return 0;
};

#endif
