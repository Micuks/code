#ifndef _t18pq_20210817_
#define _t18pq_20210817_
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
#include <stack>
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

typedef unsigned long long ull;
const int MAXN = 1e5 + 3;
ull h[MAXN];
ull bin[MAXN];
const int base = 131;
char s[MAXN];
int pos[MAXN];
int n, m;

void init()
{
    h[0] = 0;
    bin[0] = 1;
    n = strlen(s + 1);
    _DEBUG_CMD(printf("s:%s n:%d\n", s + 1, n););
    for (int i = 1; i <= n; ++i)
        h[i] = h[i - 1] * base + s[i];
    // for (int i = 1; i <= MAXN; ++i) // wrong
    for (int i = 1; i < MAXN; ++i)
        bin[i] = bin[i - 1] * base, pos[i] = i;
}

void change(char c, int x)
{
    //*
    for (int i = n + 1; i > x; --i) {
        s[i] = s[i - 1];
    }
    s[x] = c;
    ++n;
    for (int i = x; i <= n; ++i)
        h[i] = h[i - 1] * base + s[i];
    for (int i = n; i >= 1; --i)
        if (pos[i] >= x)
            ++pos[i];
        else
            break;
    //*/
    /*
    for (int i = n + 1; i > x; i--)
        s[i] = s[i - 1];
    s[x] = c;
    n++;
    for (int i = x; i <= n; i++)
        h[i] = h[i - 1] * base + s[i];
    for (int i = n; i >= 1; i--)
        if (pos[i] >= x)
            pos[i]++;
        else
            break;
    */
}
ull get(int l, int r) { return h[r] - h[l - 1] * bin[r - l + 1]; }
int solve(int l, int r)
{
    if (l > r)
        swap(l, r);
    int lb = 0, ub = n - r + 1;
    int mid = (lb + ub) / 2 + 1;
    while (lb < ub) {
        if (get(l, l + mid - 1) == get(r, r + mid - 1)) {
            lb = mid;
        }
        else {
            ub = mid - 1;
        }
        mid = (lb + ub) / 2 + 1;
    }
    return lb;
}

int main(int argc, char **argv)
{
    memset(s, 0, sizeof(s));
    scanf("%s", s + 1);
    init();
    scanf("%d", &m);
    _DEBUG_CMD(printf("get %s on %d ops\n", s + 1, m));
    while (m--) {
        char ch[2];
        scanf("%s", ch);
        _DEBUG_CMD(printf("m:%d ch:%s\n", m, ch));
        if (ch[0] == 'Q') {
            int l, r;
            scanf("%d%d", &l, &r);
            _DEBUG_CMD(printf("m:%d Q %d %d\n", m, l, r));
            printf("%d\n", solve(pos[l], pos[r]));
        }
        else {
            char c[2];
            int a;
            scanf("%s%d", c, &a);
            _DEBUG_CMD(printf("m:%d I %c %d\n", m, c[0], a));
            a = min(a, n + 1);
            change(c[0], a);
        }
    }
    return 0;
};

#endif
