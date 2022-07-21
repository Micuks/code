#ifndef _t16pi_20200704_
#define _t16pi_20200704_
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

const int MAXN = 1 << 6;
const int MAXM = 1 << 4;
const int N = 60;
int nxt[MAXN];
char sequence[MAXM][MAXN];
char str[MAXN];
char max_match[MAXN];
int max_match_cnt;
int slen;

int n, m;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
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

int kmp(const char *s)
{
    int res = 0;
    int search_len = strlen(s);
    int match_size = 0;
    int i = 0;
    // for (int i = 0; i < search_len; ++i) {
    while (i < search_len) {
        if (match_size == -1 || s[i] == str[match_size]) {
            ++match_size;
            ++i;
            res = max(res, match_size);
        }
        else {
            match_size = nxt[match_size];
        }
    }
    return res;
}

int main(int argc, char **argv)
{
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%s", sequence[i]);
        }
        _DEBUG_CMD({
            for (int i = 0; i < m; ++i) {
                printf("%s\n", sequence[i]);
            }
        });
        max_match_cnt = 0;
        for (int i = 0; i < N; ++i) {
            int mcnt = N;
            int j = N - i;
            strncpy(str, &sequence[0][i], j);
            str[j] = '\0';
            build_next();
            _DEBUG_CMD(printf("MAXN:%d MAXM:%d i:%d, j:%d str:%s sequence[0][i]:%s \n", MAXN, MAXM,
                              i, j, str, &sequence[0][i]));

            for (int k = 1; k < m; ++k) {
                _DEBUG_CMD({ mcnt != 0 && mcnt != 60 && printf("mcnt before calc:%d\n", mcnt); });
                int match_len = kmp(sequence[k]);

                mcnt = min(mcnt, match_len);
                DEBUG_CMD({
                    if (match_len == 0) {
                    }
                });
                _DEBUG_CMD({ mcnt != 0 && mcnt != 60 && printf("mcnt after calc:%d\n", mcnt); });
            }
            _DEBUG_CMD(printf("mcnt:%d max_match_cnt:%d\n", mcnt, max_match_cnt));
            if (mcnt > max_match_cnt ||
                (mcnt == max_match_cnt && string(str).compare(string(max_match)) < 0)) {
                strncpy(max_match, str, mcnt);
                max_match[mcnt] = '\0';
                max_match_cnt = mcnt;
            }
        }
        int mlen = strlen(max_match);
        assert(mlen == max_match_cnt);
        if (mlen < 3) {
            printf("no significant commonalities\n");
        }
        else {
            printf("%s\n", max_match);
        }
    }
    return 0;
};

#endif
