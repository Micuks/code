#ifndef _t15pk_20210718_
#define _t15pk_20210718_
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

typedef long long ll;
const int MAXD = 1 << 5;  // lg(10^19) = 19 < 32
const int MAXS = 1 << 16; // 3**10 = 59049 < 2**16
int pow3[1 << 4];
ll dp[MAXD][MAXS];
int t;
ll A, B;

int digits[MAXD], dcnt;
void split_number(ll x)
{
    dcnt = 0;
    while (x) {
        digits[dcnt++] = x % 10;
        x /= 10;
    }
}

bool state_valid(int s)
{
    bool valid = true;
    for (int i = 0; i <= 9; ++i) {
        int sbit = (s / pow3[i]) % 3;
        if (i % 2) {
            if (sbit == 1) {
                valid = false;
                break;
            }
        }
        else {
            if (sbit == 0 || sbit == 1) {
            }
            else {
                valid = false;
                break;
            }
        }
    }
    return valid;
}

int alter_state(int s, int n)
{
    int sbit = (s / pow3[n]) % 3;
    switch (sbit) {
        case 0:
            sbit = 1;
            break;
        case 1:
            sbit = 2;
            break;
        case 2:
            sbit = 1;
            break;
    }
    return (s / pow3[n + 1]) * pow3[n + 1] + sbit * pow3[n] + s % pow3[n];
}

ll dfs(int pos, int state, bool upper_limit, bool zero)
{
    if (pos == -1) {
        return state_valid(state) ? 1 : 0;
    }
    if (upper_limit == false && zero == false && dp[pos][state] != -1) {
        return dp[pos][state];
    }
    ll ret = 0;
    int upper_bound = upper_limit ? pos[digits] : 9;
    for (int i = 0; i <= upper_bound; ++i) {
        if (i == 0 && zero) {
            ret += dfs(pos - 1, state, upper_limit && i == upper_bound, true);
        }
        else {
            int newstate = alter_state(state, i);
            ret += dfs(pos - 1, newstate, upper_limit && i == upper_bound, false);
        }
        /*
        if (zero) {
            ret += dfs(pos - 1, state, upper_limit && i == upper_bound, i == 0);
        }
        else {
            int newstate = alter_state(state, i);
            ret += dfs(pos - 1, newstate, upper_limit && i == upper_bound, false);
        }
        */
    }
    if (upper_limit == false && zero == false) {
        dp[pos][state] = ret;
    }
    return ret;
}

ll solve(ll x)
{
    split_number(x);
    return dfs(dcnt - 1, 0, true, true);
}

int main(int argc, char **argv)
{
    memset(dp, -1, sizeof(dp));
    pow3[0] = 1;
    for (int i = 1; i < (1 << 4); ++i) {
        pow3[i] = pow3[i - 1] * 3;
    }
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &A, &B);
        printf("%lld\n", solve(B) - solve(A - 1));
    }
    return 0;
};

#endif
