#ifndef _t16po_20200714_
#define _t16po_20200714_
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

const int MAXN = 2e6 + 3;
char str[MAXN];
int nxt[MAXN];
int slen;

int get_max()
{
    int i = 0, j = 1;
    while (i < slen && j < slen) {
        int k = 0;
        while (k < slen && str[i + k] == str[j + k])
            ++k;
        if (k >= slen)
            break;
        if (str[i + k] < str[j + k])
            i += k + 1;
        else
            j += k + 1;
        if (i == j)
            ++j;
    }
    return min(i, j);
}
int get_min()
{
    int i = 0, j = 1;
    while (i < slen && j < slen) {
        int k = 0;
        while (k < slen && str[i + k] == str[j + k])
            ++k;
        if (k >= slen)
            break;
        if (str[i + k] > str[j + k])
            i += k + 1;
        else
            j += k + 1;
        if (i == j)
            ++j;
    }
    return min(i, j);
}

void get_next()
{
    int j = nxt[0] = -1;
    int i = 0;
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
        slen = strlen(str);
        get_next();
        strncpy(str + slen, str, slen);
        int min_pos = get_min();
        int max_pos = get_max();
        int rep = slen % (slen - nxt[slen]) == 0 ? slen / (slen - nxt[slen]) : 1;
        printf("%d %d %d %d\n", min_pos + 1, rep, max_pos + 1, rep);
    }
    return 0;
};

#endif
