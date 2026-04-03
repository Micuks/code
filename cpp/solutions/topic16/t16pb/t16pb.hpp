#if 0
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

char text[1000010];
char patten[10010];
int nex[10010];
void getNext()
{
    int len = strlen(patten);
    nex[0] = -1;
    int k = -1, j = 0;
    while (j < len) {
        if (k == -1 || patten[j] == patten[k]) {
            k++;
            j++;
            nex[j] = k;
        }
        else {
            k = nex[k];
        }
    }
}
int kmp()
{
    int i = 0, j = 0, ans = 0;
    int lenp = strlen(patten); ///模式串的长度
    int lent = strlen(text);   ///文本串的查改都
    while (i < lent) {
        if (j == -1 || text[i] == patten[j]) {
            i++;
            j++;
        }
        else
            j = nex[j];
        if (j == lenp) {
            ans++;
        }
    }
    return ans;
}
int main()
{
    int T;
    scanf("%d", &T); /// T组测试数据
    while (T--) {
        scanf("%s", patten);
        scanf("%s", text);
        getNext();
        printf("strlen(%s): %u\n", patten, strlen(patten));
        for (int i = 0; i <= strlen(patten); ++i) {
            printf("%d ", nex[i]);
        }
        printf("\n");
        int ans = kmp();
        printf("%d\n", ans);
    }
    return 0;
}

#else
#ifndef _t16pb_20200623_
#define _t16pb_20200623_
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

const int MAXW = 1e4 + 7;
const int MAXT = 1e6 + 3;
int nxt[MAXW];
// string W, T;
char W[MAXW];
char T[MAXT];
int wlen, tlen;

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    int len = wlen;
    // while (i < len) {
    // for (i = 0; i < len; ++i) {
    while (i < len) {
        if (j == -1 || W[i] == W[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int kmp()
{
    int res = 0;
    int i = 0;
    int j = 0;
    while (i < tlen) {
        if (j == -1 || T[i] == W[j]) {
            _DEBUG_CMD({ printf("T[i:%d]:%c T[j:%d]:%c\n", i, T[i], j, W[j]); });
            ++i;
            ++j;
        }
        else {
            j = nxt[j];
        }
        if (j == wlen) {
            ++res;
        }
    }
    return res;
}

int main(int argc, char **argv)
{
    int case_cnt;
    // cin >> case_cnt;
    scanf("%d", &case_cnt);
    // cout << "case_cnt:" << case_cnt << endl;
    while (case_cnt--) {
        // cin >> W >> T;
        scanf("%s", W);
        scanf("%s", T);
        wlen = strlen(W);
        tlen = strlen(T);
        // cout << "W:" << W << " T:" << T << endl;
        build_next();
        _DEBUG_CMD({
            for (int i = 0; i <= wlen; ++i) {
                printf("%d ", nxt[i]);
            }
            printf("\n");
            for (int i = 0; i < wlen; ++i) {
                printf("%c ", W[i]);
            }
            printf("\n");
        });
        // cout << "build next is done" << endl;
        printf("%d\n", kmp());
    }
    return 0;
};

#endif
#endif
