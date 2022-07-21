#ifndef _t16pm_20200709_
#define _t16pm_20200709_
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
int t, n;
char str[MAXN][MAXN];
// char revstr[MAXN][MAXN];
// char rev[MAXN];
int nxt[MAXN];
int tmplen;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    while (i <= tmplen) {
        if (j == -1 || str[0][i] == str[0][j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int kmp(const char *s)
{
    int res = 0;
    int slen = strlen(s);
    int i = 0, j = -1;
    while (i < slen && j < tmplen) {
        if (j == -1 || s[i] == str[0][j]) {
            ++j;
            ++i;
            res = max(res, j);
        }
        else {
            j = nxt[j];
        }
    }
    return res;
}

int main(int argc, char **argv)
{
    scanf("%d", &t);
    while (t--) {
        int max_prefix = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", str[i]);
        }
        for (int i = 1; i < n; ++i) {
            int len = strlen(str[i]);
            strncpy(str[i + n], str[i], len + 1);
            reverse(&str[i + n][0], &str[i + n][len]);
        }

        tmplen = strlen(str[0]);
        _DEBUG_CMD(printf("tmplen:%d\n", tmplen));
        while (tmplen != 0) {
            build_next();
            int cp = 1 << 10;
            for (int j = 1; j < n; ++j) {
                cp = min(cp, max(kmp(str[j]), kmp(str[j + n])));
            }
            max_prefix = max(max_prefix, cp);

            int k = 0;
            do {
                str[0][k] = str[0][k + 1];
                ++k;
            } while (str[0][k] != '\0');
            --tmplen;
        }

        printf("%d\n", max_prefix);
    }
    return 0;
};

#endif
