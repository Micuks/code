#if 0
#include <cstring>
#include <iostream>
#include <stdio.h>
using namespace std;
char a[100100]; //创建容纳用的字符串
int ne[100100]; //创建用来记录前缀和的数组
void KMP(int len)
{
    int i, j;
    j = -1;
    ne[0] = -1;
    for (i = 0; i < len;) {
        if (j == -1 || a[i] == a[j])
            ne[++i] = ++j; //如果a[i]和a[j]一样，辣么就用ne数组记录下前缀
        else
            j = ne[j]; //否则的话让j回溯
    }
}
int main()
{
    int T, len, wa;
    scanf("%d", &T);
    while (T--) {
        memset(ne, 0, sizeof(ne)); //把ne数组初始化为 0
        scanf("%s", a);            //输入字符串
        len = strlen(a);           //计算字符串长度
        KMP(len);                  //把字符串长度放进去
        wa = len - ne[len]; //这个wa嘛，就是len去掉最后的后缀所留下的循环节的长度
        printf("wa:%d = len:%d, ne[%d]:%d\n", wa, len, len, ne[len]);
        if (len != wa && len % wa == 0)
            printf("0\n"); //如果这个循环节能被整除，那么就不用添加字符了，就输出 0
        else { //如果需要添加字符，那么ne[len]%wa就是还未形成循环节的字符长度
               //反过来让wa-ne[len]%wa，就能得到我们需要补上的字符数目了
            printf("%d\n", wa - ne[len] % wa);
        }
    }
    return 0;
}
#else
#ifndef _t16pd_20200625_
#define _t16pd_20200625_
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
char s[MAXN];
int nxt[MAXN];
int slen;
int T;

void mystrrev(char *const s)
{
    size_t len = strlen(s);
    size_t i = 0;
    while (i < len) {
        s[i] ^= s[len];
        s[len] ^= s[i];
        s[i] ^= s[len];
        ++i;
        --len;
    }
}

void build_next()
{
    int i = 0;
    int j = nxt[0] = -1;
    while (i < slen) {
        if (j == -1 || s[i] == s[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        slen = strlen(s);
        build_next();
        int loop_len = slen - nxt[slen];
        int min_cost = loop_len - (nxt[slen] % loop_len);
        _DEBUG_CMD({
            printf("slen: %d nxt:", slen);
            for (int i = 0; i <= slen; ++i) {
                printf(" %d", nxt[i]);
            }
            printf("\n");
        });
        if ((nxt[slen] % loop_len) == 0 && nxt[slen] != 0) {
            printf("%d\n", 0);
        }
        else {
            printf("%d\n", min_cost);
        }
    }
    return 0;
};

#endif
#endif
