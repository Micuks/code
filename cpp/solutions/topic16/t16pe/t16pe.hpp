#ifndef _t16pe_20200703_
#define _t16pe_20200703_
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
int nxt[MAXN];
int n = 0;

void build_next()
{
    int j = nxt[0] = -1;
    int i = 0;
    while (i <= n) {
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
    int case_cnt = 0;
    while (~scanf("%d", &n) && n != 0) {
        scanf("%s", str);
        build_next();
        _DEBUG_CMD({
            printf("next: ");
            for (int i = 0; i <= n; ++i) {
                printf(" %d", nxt[i]);
            }
            printf("\n");
        });
        printf("Test case #%d\n", ++case_cnt);
        for (int i = 1; i <= n; ++i) {
            int len = i - nxt[i];
            _DEBUG_CMD({ printf("nxt[%d]:%d, len:%d\n", i, nxt[i], len); });
            if (nxt[i] != 0 && nxt[i] % len == 0) {
                printf("%d %d\n", i, nxt[i] / len + 1);
            }
        }
        printf("\n");
    }
    return 0;
};

#endif
