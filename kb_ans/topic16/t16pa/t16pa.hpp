#if 0
#include <bits/stdc++.h>
using namespace std;
const int N = 1000050;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int kmpnext[N];
int s[N], t[N];
int slen, tlen;
inline void getnext()
{
    int i, j;
    j = kmpnext[0] = -1;
    i = 0;
    while (i < tlen) {
        if (j == -1 || t[i] == t[j]) {
            kmpnext[++i] = ++j;
        }
        else {
            j = kmpnext[j];
        }
    }
}
inline int kmp_index()
{
    int i = 0, j = 0;
    getnext();
    while (i < slen && j < tlen) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        }
        else
            j = kmpnext[j];
    }
    if (j == tlen)
        return i - tlen;
    else
        return -1;
}
inline int kmp_count()
{
    int ans = 0;
    int i, j = 0;
    if (slen == 1 && tlen == 1) {
        if (s[0] == t[0])
            return 1;
        else
            return 0;
    }
    getnext();
    for (i = 0; i < slen; i++) {
        while (j > 0 && s[i] != t[j])
            j = kmpnext[j];
        if (s[i] == t[j])
            j++;
        if (j == tlen) {
            ans++;
            j = kmpnext[j];
        }
    }
    return ans;
}
int T;
int main()
{
    T = read();
    while (T--) {
        slen = read();
        tlen = read();
        for (int i = 0; i < slen; i++)
            s[i] = read();
        for (int i = 0; i < tlen; i++)
            t[i] = read();
        if (kmp_index() == -1)
            cout << -1 << endl;
        else
            cout << kmp_index() + 1 << endl;
    }
    return 0;
}
#else
#ifndef _t16pa_20200620_
#define _t16pa_20200620_
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

const int MAXN = 1000000 + 3;
const int MAXM = 1e4 + 7;
int n[MAXM], t, alen, blen, match_len;
int a[MAXN], b[MAXM];

void build_next1()
{
    memset(n, 0, sizeof(n));
    for (int i = 1; i < blen; ++i) {
        if (n[i - 1] != 0 && b[n[i - 1] + 1] == b[i]) {
            n[i] = n[i - 1] + 1;
        }
        else if (b[i] == b[0]) {
            n[i] = 1;
        }
        else {
            n[i] = 0;
        }
    }
}
void build_next()
{
    // memset(n, 0, sizeof(n));
    int i = 0;
    int j = n[0] = -1;
    while (i <= blen) {
        if (j == -1 || b[i] == b[j]) {
            n[++i] = ++j;
        }
        else {
            j = n[j];
        }
    }
}

int kmp()
{
    int i = 0, j = 0;
    while (i < alen && j < blen) {
        if (j == -1 || a[i] == b[j]) {
            ++i;
            ++j;
        }
        else {
            j = n[j];
        }
    }
    if (j == blen) {
        return i - j + 1;
    }
    else {
        return -1;
    }
}

int main(int argc, char **argv)
{
    // cin >> t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &alen, &blen);
        // cin >> a >> b;
        for (int i = 0; i < alen; ++i) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < blen; ++i) {
            scanf("%d", &b[i]);
        }
        _DEBUG_CMD({
            printf("a array:");
            for (int i = 0; i < alen; ++i) {
                printf(" %d", a[i]);
            }
            printf("\n");
            printf("b array:");
            for (int i = 0; i < blen; ++i) {
                printf(" %d", b[i]);
            }
            printf("\n");
        });
        build_next();
        _DEBUG_CMD({
            for (int i = 0; i < blen + 1; ++i) {
                printf("no.%d b[%d]:%d n:%d\n", i, i, b[i], n[i]);
            }
        });
        printf("%d\n", kmp());
    }
    return 0;
};

#endif
#endif
