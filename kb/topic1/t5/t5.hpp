#ifndef _t5_20220723_
#define _t5_20220723_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 1000000;
int r[MAXN];

int bfs(const int &n) {
    memset(r, -1, sizeof(r));
    r[1] = 1;
    int idx = 2;
    while (r[idx - 1] != 0 && r[idx - 2] != 0) {
        r[idx] = (r[idx / 2] * 10 % n) % n;
        r[idx + 1] = (r[idx] + 1) % n;
        idx += 2;
    }
    return (r[idx - 1] == 0) ? idx - 1 : idx - 2;
}

void printArray(const int &len, const int *arr) {
    for (int i = 0; i <= len; i++) {
        printf(!i + " %d", arr[i]);
    }
    putchar('\n');
}

int main(int argc, char **argv) {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        int result = bfs(n);
#ifdef D
        printArray(result, r);
#endif
        int cnt = 0;
        while (result) {
            r[cnt++] = result & 0x1;
            result >>= 1;
        }
        while (cnt) {
            printf("%d", r[--cnt]);
        }
        putchar('\n');
    }
    return 0;
};

#endif
