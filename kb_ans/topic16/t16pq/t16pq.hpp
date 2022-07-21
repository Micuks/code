#ifndef _t16pq_20200715_
#define _t16pq_20200715_
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
int slen;
int nxt[MAXN];
int T;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    while (i <= slen) {
        if (j == -1 || str[i] == str[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", str);
        slen = strlen(str);
        build_next();
        vector<int> ans;
        int loop_size = slen - nxt[slen];
        int repeat_size = (slen / loop_size) + (nxt[slen] % loop_size == 0 ? 0 : 1);
        _DEBUG_CMD(printf("slen:%d nxt[%d]: %d loop_size: %d\n", slen, slen, nxt[slen], loop_size));
        _DEBUG_CMD(printf("repeat_size: %d\n", repeat_size));
        // int repeat_size = (slen / loop_size);
        for (int i = 1; i < slen / loop_size; ++i) {
            ans.push_back(i * loop_size);
        }
        int idx = nxt[slen];
        while (idx != -1) {
            ans.push_back(slen - idx);
            idx = nxt[idx];
        }
        ans.push_back(slen);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        printf("Case #%d: %d\n", ++case_cnt, ans.size());
        printf("%d", ans[0]);
        for (int i = 1; i < ans.size(); ++i) {
            printf(" %d", ans[i]);
        }
        printf("\n");
    }
    return 0;
};

#endif
