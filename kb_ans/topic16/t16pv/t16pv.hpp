#ifndef _t16pv_20200719_
#define _t16pv_20200719_
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

const int MAXN = 1e5 + 3;
unsigned char h[MAXN], mh[MAXN << 1];
int p[MAXN << 1];
int mx, id;
int T, n;

const unsigned char ori = 49;
void init_manacher(unsigned char const s[], int len)
{
    mh[0] = ori;
    for (int i = 0; i < len; ++i) {
        mh[(i << 1) + 1] = s[i];
        mh[(i << 1) + 2] = ori;
    }
    mh[(len << 1) + 1] = '\0';
    _DEBUG_CMD({
        cout << "mh[]: ";
        for (int i = 0; i <= (len << 1); ++i) {
            printf("%d ", int(mh[i]));
        }
        cout << endl;
    });
}

int manacher(unsigned char const s[], int len)
{
    mx = id = 0;
    int max_match = 0;
    init_manacher(s, len);
    int slen = len << 1;
    for (int i = 0; i <= slen; ++i) {
        if (i < mx) {
            p[i] = min(p[2 * id - i], mx - i);
        }
        else {
            p[i] = 1;
        }
        while (i - p[i] >= 0 && i + p[i] <= slen && mh[i + p[i]] == mh[i - p[i]]) {
            if (mh[i - p[i]] == ori) {
                ++p[i];
            }
            else if (mh[i - p[i]] <= mh[i - p[i] + 2]) {
                ++p[i];
            }
            else {
                break;
            }
        }
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
        max_match = max(max_match, p[i] - 1);
    }
    _DEBUG_CMD({
        cout << "p[]: ";
        for (int i = 0; i <= slen; ++i) {
            cout << p[i] << ' ';
        }
        cout << endl;
    });
    return max_match;
}

// int lis() {}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%hhu", &h[i]);
        }
        h[n] = '\0';
        // printf("%d\n", manacher(h, strlen((const char *) h)));
        printf("%d\n", manacher(h, n));
    }
    return 0;
};

#endif
