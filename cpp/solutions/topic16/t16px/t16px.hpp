#ifndef _t16px_20200720_
#define _t16px_20200720_
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

const int MAXN = 110000 + 3;
char str[MAXN];
char sm[MAXN << 1];
int p[MAXN << 1];
int slen;

void manacher_init()
{
    sm[0] = '#';
    for (int i = 0; i < slen; ++i) {
        sm[(i << 1) + 1] = str[i];
        sm[(i << 1) + 2] = '#';
    }
    sm[(slen << 1) + 1] = '\0';
}

int manacher()
{
    manacher_init();
    int id, mx, best_match = 0;
    id = mx = 0;
    int sslen = slen << 1;
    for (int i = 0; i <= sslen; ++i) {
        if (i < mx) {
            p[i] = min(p[2 * id - i], mx - i);
        }
        else {
            p[i] = 1;
        }
        while (i - p[i] >= 0 && sm[i + p[i]] == sm[i - p[i]])
            ++p[i];

        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
        best_match = max(best_match, p[i]);
    }
    return best_match - 1;
}

int main(int argc, char **argv)
{
    while (~scanf("%s", str)) {
        slen = strlen(str);
        printf("%d\n", manacher());
        string discard;
        getline(cin, discard);
    }
    return 0;
};

#endif
