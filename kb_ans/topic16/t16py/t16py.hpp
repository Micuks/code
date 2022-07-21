#ifndef _t16py_20200721_
#define _t16py_20200721_
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

const char *st = "doge";
const int MAXN = (1 << (6 + 10)) + (1 << 12);
int nxt[MAXN], slen;
int cnt;
string str;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    const char mask = ~(1 << 5);
    _DEBUG_CMD(printf("mask: %x\n", mask));
    int st_len = strlen(st);
    cnt = 0;
    while (i <= slen) {
        if (j == -1 || (str[i] & mask) == (str[j] & mask)) {
            nxt[++i] = ++j;
            if (j == st_len) {
                ++cnt;
            }
        }
        else {
            j = nxt[j];
        }
    }
}

int main(int argc, char **argv)
{
    std::istreambuf_iterator<char> b(std::cin), e;
    str = string(b, e);
    str = st + str;
    slen = str.size();
    build_next();
    _DEBUG_CMD({
        for (int i = 0; i <= slen; ++i) {
            printf("%d ", nxt[i]);
        }
        printf("\n");
    });
    printf("%d\n", cnt);
    return 0;
};

#endif
