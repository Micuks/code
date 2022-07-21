#ifndef _t14pk_20200512_
#define _t14pk_20200512_
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
#include <stack>
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

int T;
long long b;
string a;

const char *divisible = "divisible";
const char *ndivisible = "not divisible";

const char *solve()
{
    stack<int> s;
    if (a[0] != '-') {
        s.push(a[0] - '0');
    }
    for (int i = 1; i < a.size(); ++i) {
        s.push(a[i] - '0');
    }
    b = b < 0 ? -b : b;
    const long long k = 1000000000;
    long long mod = 1;
    long long res = 0;
    int pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    while (!s.empty()) {
        int num = 0;
        for (int i = 0; i < 9 && !s.empty(); ++i) {
            num += s.top() * pow10[i];
            s.pop();
        }
        res = (res + num * mod) % b;
        mod = (mod * k) % b;
    }
    if (res == 0) {
        return divisible;
    }
    return ndivisible;
    /*
    if (a[0] == '-') {
        a = string(a.begin() + 1, a.end());
    }
    long long res = a[0] - '0';
    long long mod = 1;
    b = b < 0 ? -b : b;
    for (int i = 1; i < a.size(); ++i) {
        // res = (res + (a[i] - '0') * mod) % b;
        res = (res * 10 + (a[i] - '0')) % b;
        // mod = (mod * 10) % b;
    }
    if (res == 0) {
        return divisible;
    }
    */
    return ndivisible;
}

int main(int argc, char **argv)
{
    int case_cnt = 0;
    cin >> T;
    while (T--) {
        cin >> a >> b;
        printf("Case %d: %s\n", ++case_cnt, solve());
    }
    return 0;
};

#endif
