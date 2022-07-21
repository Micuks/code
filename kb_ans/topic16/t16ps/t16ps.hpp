#ifndef _t16ps_20200716_
#define _t16ps_20200716_
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

const int MAXN = 5e5 + 9;
int T;
int val[1 << 5];
int slen;
int nslen;
char str[MAXN << 1], aug_str[MAXN << 1];
int p[MAXN << 1];
int acc[MAXN << 1];
int id;

void augment_string()
{
    nslen = (slen << 1);
    memset(aug_str, '#', nslen + 1);
    for (int i = 0; i < slen; ++i)
        aug_str[(i << 1) + 1] = str[i];
    aug_str[nslen + 1] = 0;
}

void manacher()
{
    int mx = 0;
    id = 0;
    for (int i = 0; i < nslen; ++i) {
        if (mx > i)
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1;

        while (i - p[i] >= 0 && aug_str[i - p[i]] == aug_str[i + p[i]])
            ++p[i];
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 26; ++i) {
            scanf("%d", &val[i]);
        }
        scanf("%s", str);
        slen = strlen(str);
        memset(acc, 0, sizeof(acc));
        for (int i = 1; i <= slen; ++i) {
            acc[i] = acc[i - 1] + val[str[i - 1] - 'a'];
        }
        _DEBUG_CMD({
            cout << "acc[]: ";
            for (int i = 0; i <= slen; ++i) {
                cout << acc[i] << ' ';
            }
            cout << endl;
        });

        augment_string();
        manacher();

        _DEBUG_CMD({
            cout << "aug_str[]:";
            for (int i = 0; i <= nslen; ++i) {
                cout << aug_str[i] << ' ';
            }
            cout << endl;
            cout << "p[]:";
            for (int i = 0; i <= nslen; ++i) {
                cout << p[i] << ' ';
            }
            cout << endl;
        });

        int max_val = -0x3F3F3F3F;

        for (int i = 2; i < nslen; i += 2) {
            int fpc = i / 2;
            int spc = (nslen + i) / 2;
            // int fpd = (i / 2) % 2 == 0 ? i / 2 - 1 : i / 2;
            int fpd = i / 2;
            // int spd = spc % 2 == 0 ? (nslen - i) / 2 : (nslen - i) / 2 - 1;
            int spd = (nslen - i) / 2;

            // int fp = p[i / 2] >= (i / 2) ? acc[i / 2] : 0;
            // int sp = p[(nslen + i) / 2] >= ((nslen - i) / 2) ? acc[slen] - acc[i / 2] : 0;
            int fp = p[fpc] >= fpd ? acc[fpc] : 0;
            int sp = p[spc] >= spd ? acc[slen] - acc[fpc] : 0;
            int cur_val = fp + sp;
            _DEBUG_CMD(printf(
                "i:%d fp:%d sp:%d max_val:%d fpc:%d p[%d]:%d fpd:%d spc:%d p[%d]:%d spd:%d\n", i,
                fp, sp, max_val, fpc, fpc, p[fpc], fpd, spc, spc, p[spc], spd));
            max_val = max(max_val, cur_val);
        }
        printf("%d\n", max_val);
    }
    return 0;
};

#endif
