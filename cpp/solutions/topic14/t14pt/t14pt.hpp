#ifndef _t14pt_20200617_
#define _t14pt_20200617_
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

const int MAXN = 64;
long long fibs[MAXN];
string x, y;

void get_fibnacci()
{
    fibs[0] = 1;
    fibs[1] = 2;
    for (int i = 2; i < MAXN; ++i) {
        fibs[i] = fibs[i - 1] + fibs[i - 2];
    }
}

long long fib2dec(string s)
{
    long long ret = 0;
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.size(); ++i) {
        ret += (s[i] - '0') * fibs[i];
    }
    return ret;
}

string dec2fib(long long d)
{
    if (d == 0) {
        return "0";
    }
    long long* ub = upper_bound(&fibs[0], &fibs[MAXN], d);
    size_t rsize = ub - fibs;
    string ret = string(rsize, '0');
    //cout << "d: " << d << " ret: " << ret << " ub-fibs[0]: " << ub - &fibs[0] << endl;
    while (d != 0 && ub >= fibs) {
        if (d >= *ub) {
            d = d - *ub;
            ret[rsize - (ub - fibs) - 1] = '1';
        } else {
            --ub;
        }
    }
    return ret;
}

void print_res(string& fib_x, string& fib_y, string& fib_res)
{
    size_t ts = fib_res.size() + 1 + 1;
    for (int i = fib_x.size(); i < ts; ++i) {
        printf(" ");
    }
    printf("%s\n", fib_x.c_str());
    printf("+");
    for (int i = fib_y.size() + 1; i < ts; ++i) {
        printf(" ");
    }
    printf("%s\n", fib_y.c_str());
    printf("  ");
    for (int i = 2; i < ts; ++i) {
        printf("-");
    }
    printf("\n");
    printf(" ");
    printf(" %s\n", fib_res.c_str());
    printf("\n");
    return;
}

int main(int argc, char** argv)
{
    get_fibnacci();
    while (cin >> x >> y) {
        //cout << "x: " << x << " y: " << y << endl;
        long long lx = fib2dec(x);
        long long ly = fib2dec(y);
        long long lr = lx + ly;
        //cout << "lx: " << lx << " ly: " << ly << " lr: " << lr << endl;
        string fib_res = dec2fib(lr);
        string fib_x = dec2fib(lx);
        string fib_y = dec2fib(ly);
        //cout << "fib_x: " << fib_x << " fib_y: " << fib_y << " fib_res: " << fib_res << endl;
        print_res(fib_x, fib_y, fib_res);
    }
    return 0;
};

#endif
