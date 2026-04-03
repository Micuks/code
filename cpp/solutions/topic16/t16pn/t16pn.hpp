#ifndef _t16pn_20200710_
#define _t16pn_20200710_
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

const int MAXN = 4e3 + 3;
int tn;
char tms[MAXN][1 << 8];

char bm[1 << 8];
int bl;

int nxt[MAXN];
int slen;

void shift_left(char *const s)
{
    int k = 0;
    while (s[k] != '\0') {
        s[k] = s[k + 1];
        ++k;
    }
}

void build_next()
{
    const char *p = tms[0];
    int i = 0;
    int j = nxt[0] = -1;
    while (i <= slen) {
        if (j == -1 || p[i] == p[j]) {
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
    int i = 0, j = 0;
    int dlen = strlen(s);
    const char *p = tms[0];
    while (i < dlen && j < slen) {
        if (j == -1 || s[i] == p[j]) {
            ++i;
            ++j;
            res = max(res, j);
        }
        else {
            j = nxt[j];
        }
    }
    // return j;
    return res;
}

int main(int argc, char **argv)
{
    while (~scanf("%d", &tn) && tn != 0) {
        bl = 0;
        for (int i = 0; i < tn; ++i) {
            scanf("%s", tms[i]);
        }
        slen = strlen(tms[0]);
        int loop_cnt = slen;
        for (int i = 0; i < loop_cnt; ++i) {
            slen = strlen(tms[0]);
            build_next();
            int m = 1 << 8;
            for (int j = 1; j < tn; ++j) {
                int res = kmp(tms[j]);
                _DEBUG_CMD(printf("tms[0]:%s tgt s:%s, m:%d, res:%d\n", tms[0], tms[j], m, res));
                m = min(m, res);
            }
            if (m > bl || (m == bl && string(bm) > string(tms[0]).substr(0, m))) {
                bl = m;
                strncpy(bm, tms[0], bl);
                bm[bl] = '\0';
            }
            _DEBUG_CMD(printf("i:%d m: %d tms[0]:%s\n", i, m, tms[0]));
            shift_left(tms[0]);
        }
        if (bl == 0) {
            printf("IDENTITY LOST\n");
        }
        else {
            printf("%s\n", bm);
        }
    }
    return 0;
};

#endif
