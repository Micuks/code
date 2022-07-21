#ifndef _t16pf_20200703_
#define _t16pf_20200703_
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
int slen;
string s;

void build_next()
{
    int j = nxt[0] = -1;
    int i = 0;
    slen = s.size();
    while (i < slen) {
        if (j == -1 || s[i] == s[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int main(int argc, char **argv)
{
    while (cin >> s && s.size() != 0) {
        build_next();
        if (nxt[slen] == 0) {
            printf("%d\n", slen);
        }
        else {
            int len = slen - nxt[slen];
            // assert(nxt[slen] <= len);
            printf("%d\n", len);
        }
    }
    return 0;
};

#endif
