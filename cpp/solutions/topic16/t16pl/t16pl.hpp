#if 0
#include <iostream>
#include <string.h>
using namespace std;
char t[100006], s[100006], str1[26];
int nxt[100006], str[1000];
void getnext()
{
    int i = 0, j = -1;
    nxt[0] = -1;
    int len = strlen(s);
    while (i < len) {
        if (j == -1 || s[i] == s[j]) {
            i++;
            j++;
            nxt[i] = j;
        }
        else
            j = nxt[j];
    }
}
int kmp()
{
    int i, j = 0;
    int lent = strlen(t);
    int lens = strlen(s);
    if (lent % 2 == 1)
        i = lent / 2 + 1;
    else
        i = lent / 2;
    while (i < lent && j < lens) {
        if (j == -1 || t[i] == s[j]) {
            i++;
            j++;
        }
        else
            j = nxt[j];
        // printf("%d\n",j);
    }
    return j;
}
int main()
{
    int text;
    scanf("%d", &text);
    while (text--) {
        char ch;
        int i;
        scanf("%s", str1);
        for (i = 0; i < 26; i++) {
            ch = str1[i];
            str[ch] = i;
        }
        scanf("%s", t);
        int lent = strlen(t);
        for (i = 0; i < lent; i++) {
            int temp = str[t[i]];
            s[i] = temp + 'a';
        }
        //  printf("%s\n%s\n",t,s);
        //  printf("%s\n%s\n",t,s);
        getnext();
        int j = kmp();
        if (j * 2 == lent) {
            printf("%s\n", t);
        }
        else {
            int tmp1 = lent - j;
            printf("%s", t);
            for (i = j; i < tmp1; i++)
                printf("%c", s[i]);
            printf("\n");
        }
    }
    return 0;
}
#else
#ifndef _t16pl_20200708_
#define _t16pl_20200708_
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
char table[1 << 10];
char deciphered[MAXN], ori[MAXN];
int slen;
int nxt[MAXN];
int T;

void build_next()
{
    int j = nxt[0] = -1;
    int i = 0;
    while (i <= slen) {
        if (j == -1 || deciphered[i] == deciphered[j]) {
            nxt[++i] = ++j;
        }
        else {
            j = nxt[j];
        }
    }
}

void decipher()
{
    char mapper[1 << 10];
    int table_len = strlen(table);
    for (int i = 0; i < table_len; ++i) {
        mapper[table[i]] = i + 'a';
        // mapper[i + 'a'] = table[i];
    }
    for (int i = 0; i < slen; ++i) {
        deciphered[i] = mapper[ori[i]];
    }
}

int kmp()
{
    int ret = 0;
    int i = slen - slen / 2;
    int j = 0;
    while (i < slen && j < slen) {
        if (j == -1 || ori[i] == deciphered[j]) {
            ++i;
            ++j;
            ret = max(ret, j);
        }
        else {
            j = nxt[j];
        }
    }
    // return ret; //???????????????????????????????????
    return j;
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while (T--) {
        _DEBUG_CMD(printf("case:%d\n", T));
        memset(ori, 0, sizeof(ori));
        memset(deciphered, 0, sizeof(deciphered));
        scanf("%s", table);
        scanf("%s", ori);
        _DEBUG_CMD(printf("table: %s\nori: %s\n", table, ori););
        slen = strlen(ori);
        decipher();
        _DEBUG_CMD(printf("decipher is done, dec:%s\n", deciphered));
        build_next();
        int res = kmp();
        int msg_size = res > slen - res ? res : slen - res;
        _DEBUG_CMD(printf("msg_size:%d res:%d slen:%d\n", msg_size, res, slen));
        int offset = slen - res;
        printf("%s", ori);
        for (int i = res; i < offset; ++i) {
            printf("%c", deciphered[i]);
        }
        printf("\n");

        /*
        for (int i = 0; i < msg_size; ++i) {
            printf("%c", ori[i]);
        }
        for (int i = 0; i < msg_size; ++i) {
            printf("%c", deciphered[i]);
        }
        printf("\n");
        */
    }
    return 0;
};

#endif
#endif
