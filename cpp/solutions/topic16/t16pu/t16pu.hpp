#ifndef _t16pu_20200719_
#define _t16pu_20200719_
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
char sm[MAXN << 1];
int p[MAXN << 1];
int id, mx;

void init_manacher(const char *s, const int len)
{
    sm[0] = '#';
    for (int i = 0; i < len; ++i) {
        sm[(i << 1) + 1] = s[i];
        sm[(i << 1) + 2] = '#';
    }
    sm[(len << 1) + 1] = '\0';
    _DEBUG_CMD(printf("sm:%s\n", sm));
}
int manacher(const char *s, const int len)
{
    int max_match = 0;
    id = mx = 0;
    init_manacher(s, len);
    for (int i = 0; i <= (len << 1); ++i) {
        if (i < mx) {
            p[i] = min(p[2 * id - i], mx - i);
        }
        else {
            p[i] = 1;
        }
        while (i - p[i] >= 0 && i + p[i] <= (len << 1) && sm[i + p[i]] == sm[i - p[i]])
            ++p[i];
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }

        max_match = max(max_match, p[i] - 1);
    }
    _DEBUG_CMD({
        cout << "p[]: ";
        for (int i = 0; i < (len << 1); ++i) {
            cout << p[i] << ' ';
        }
        cout << endl;
    });
    return max_match;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    while (~scanf("%s", str) && string(str) != "END") {
        printf("Case %d: %d\n", ++case_cnt, manacher(str, strlen(str)));
    }
    return 0;
};

#endif
