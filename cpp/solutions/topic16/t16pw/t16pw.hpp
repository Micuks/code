#ifndef _t16pw_20200720_
#define _t16pw_20200720_
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

const int MAXN = 2e5 + 3;
const char ori = 'a';
const int offset = 'z' - 'a' + 1;
char st;
char str[MAXN];
int slen;
char sm[MAXN << 1];
int p[MAXN << 1];
int bid, bmx;

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
    _DEBUG_CMD(printf("manacher init s:%s\n", sm));
    int id, mx;
    id = mx = 0;
    int sslen = slen << 1;
    for (int i = 0; i <= sslen; ++i) {
        if (i < mx) {
            p[i] = min(p[2 * id - i], mx - i);
        }
        else {
            p[i] = 1;
        }

        while (i - p[i] >= 0 && sm[i - p[i]] == sm[i + p[i]])
            ++p[i];

        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (p[i] > bmx) {
            bmx = p[i];
            bid = i;
        }
    }
    _DEBUG_CMD({
        printf("sm: ");
        for (int i = 0; i < sslen; ++i) {
            printf("%c ", sm[i]);
        }
        printf("\n");
        printf("p: ");
        for (int i = 0; i < sslen; ++i) {
            printf("%d ", p[i]);
        }
        printf("\n");
    });
    return bmx - 1;
}

void convert()
{
    char m[1 << 8];
    for (int i = 'a'; i <= 'z'; ++i) {
        int c = st + i - ori;
        c = c < 'a' ? c + offset : c;
        c = c > 'z' ? c - offset : c;
        _DEBUG_CMD(printf("i:%d, c:%d\n", i, c));
        m[c] = i;
    }
    _DEBUG_CMD({
        for (int i = 'a'; i <= 'z'; ++i) {
            printf("%c-->%c(%d)\n", i, m[i], int(m[i]));
        }
    });
    for (int i = 0; i < slen; ++i) {
        str[i] = m[str[i]];
    }
}

int main(int argc, char **argv)
{
    while (~scanf("%c %s\n", &st, str)) {
        bid = bmx = 0;
        slen = strlen(str);
        _DEBUG_CMD(printf("before conversion: %s\n", str));
        convert();
        _DEBUG_CMD(printf("after conversion: %s %d\n", str, str[2]));
        int res = manacher();
        _DEBUG_CMD(printf("res:%d\n", res));
        if (res < 2) {
            printf("No solution!\n");
        }
        else {
            int s, e;
            if (bid % 2 != 0) {
                s = bid / 2 - (bmx - 1) / 2;
                e = bid / 2 + (bmx - 1) / 2;
            }
            else {
                s = bid / 2 - (bmx - 1) / 2;
                e = bid / 2 + (bmx - 1) / 2 - 1;
            }
            _DEBUG_CMD(printf("bid:%d, bmx:%d\n", bid, bmx));
            printf("%d %d\n", s, e);
            printf("%s\n", string(str).substr(s, e - s + 1).c_str());
        }
    }
    return 0;
};

#endif
