#if 0
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 400000 + 10;
const int maxe = 1000000 + 10;
char s1[maxn];
int len;
int nextv[maxn];
int ans[maxn];
void getnext()
{
    int i = 0, j = -1;
    nextv[0] = -1;
    while (i < len) {
        if (j == -1 || s1[j] == s1[i]) {
            nextv[++i] = ++j;
        }
        else
            j = nextv[j];
    }
}
int main()
{
    int n;
    while (scanf("%s", s1) != EOF) {
        // memset(nextv,0,sizeof(nextv));
        len = strlen(s1);
        getnext();
        int tmp = len;
        ans[0] = len;
        int cnt = 1;
        while (nextv[tmp] != 0) {
            ans[cnt++] = nextv[tmp];
            tmp = nextv[tmp];
        }
        for (int i = cnt - 1; i > 0; i--)
            printf("%d ", ans[i]);
        printf("%d\n", ans[0]);
    }
    return 0;
}

#else
#ifndef _t16ph_20200704_
#define _t16ph_20200704_
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

const int MAXN = 4e5 + 9;
int nxt[MAXN];
int slen;
char str[MAXN];
int pplen[MAXN];
int ppsize = 0;

void build_next()
{
    int j = nxt[0] = -1;
    int i = 0;
    slen = strlen(str);
    while (i <= slen) {
        if (j == -1 || str[i] == str[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

void print_ans(int idx)
{
    int pos = nxt[idx];
    _DEBUG_CMD(
        { printf("line:%d idx:%d pos: %d nxt[pos]:%d\n", __LINE__, idx, idx, pos, nxt[pos]); });
    if (pos == -1) {
        return;
    }
    print_ans(pos);
    pplen[ppsize++] = idx;
}

int main(int argc, char **argv)
{
    while (~scanf("%s", str)) {
        build_next();
        ppsize = 0;
        print_ans(slen);
        // pplen[ppsize++] = slen;
        int i = 0;
        for (; i < ppsize - 1; ++i) {
            printf("%d ", pplen[i]);
        }
        printf("%d\n", pplen[i]);
    }
    return 0;
};

#endif
#endif
