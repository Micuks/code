#ifndef _t14pu_20200618_
#define _t14pu_20200618_
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
#define DEBUG_CMD(cmd) \
    do {               \
        cmd;           \
    } while (false)
#else
#define DEBUG_CMD(cmd) \
    do {               \
        ;              \
    } while (false)
#endif
#define _DEBUG_CMD(cmd) \
    do {                \
        ;               \
    } while (false)

const int MAXN = 16000 + 3;
int prime[MAXN];
bool not_prime[MAXN];
int pcnt;

void init_prime()
{
    pcnt = 0;
    memset(not_prime, 0, sizeof(not_prime));
    for (int i = 2; i < MAXN; ++i) {
        if (!not_prime[i]) {
            prime[pcnt++] = i;
        }
        for (int j = 0; j < pcnt && prime[j] * i < MAXN; ++j) {
            not_prime[prime[j] * i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
    not_prime[2] = true;
    not_prime[1] = true;
    not_prime[0] = true;
}

int n;
int main(int argc, char** argv)
{
    init_prime();
    int case_cnt = 1;
    while (cin >> n && n > 0) {
        if (not_prime[n]) {
            printf("%d: no\n", case_cnt++);
        } else {
            printf("%d: yes\n", case_cnt++);
        }
    }
    return 0;
};

#endif
