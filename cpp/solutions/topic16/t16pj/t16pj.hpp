#ifndef _t16pj_20200707_
#define _t16pj_20200707_
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

const int MAXN = 5e4 + 13;

char s1[MAXN];
char s2[MAXN];
char s3[MAXN << 1];
int s1len, s2len, s3len;
int nxt[MAXN << 1];

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    while (i <= s3len) {
        if (j == -1 || s3[i] == s3[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int main(int argc, char **argv)
{
    while (scanf("%s%s", s1, s2) == 2) {
        s1len = strlen(s1);
        s2len = strlen(s2);
        string st = (s1);
        st.append(s2);
        strncpy(s3, &st[0], st.size());
        s3[st.size()] = '\0';
        s3len = strlen(s3);

        build_next();
        _DEBUG_CMD({
            printf("next[]: ");
            for (int i = 0; i < s2len; ++i) {
                printf(" %d", nxt[i]);
            }
            printf("\n");
        });
        if (nxt[s3len] != 0) {
            // TODO: fix me
            int min_len = min(min(nxt[s3len], s2len), s1len);
            string ans = string(s1).substr(0, min_len);
            printf("%s %d\n", ans.c_str(), min_len);
        }
        else {
            printf("0\n");
        }
    }
    return 0;
};

#endif
