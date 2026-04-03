#ifndef _t12pl_20200325_
#define _t12pl_20200325_
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

const int MAXN = 1024;
char s[MAXN];
char t[MAXN];
// string s, t;
int dp[MAXN][MAXN];
int s_len, t_len;

int solve(int s_len, int t_len)
{
    // cout << "strlen(s): " << s_len << endl;
    if ((s_len < 0) || (t_len < 0)) {
        // return 0;
        return 0;
    }
    if (dp[s_len][t_len] != -1) {
        return dp[s_len][t_len];
    }
    /*
    if (s_len == 0 && t_len == 0) {
        return dp[s_len][t_len];
    }
    */
    dp[s_len][t_len] = max(solve(s_len - 1, t_len), solve(s_len, t_len - 1));
    if (s[s_len] == t[t_len]) {
        dp[s_len][t_len] = max(dp[s_len][t_len], solve(s_len - 1, t_len - 1) + 1);
    }
    return dp[s_len][t_len];
}

int main(int argc, char **argv)
{
    // while (~scanf("%s%s", s, t)) {
    while (cin >> s >> t) {
        memset(dp, -1, sizeof(dp));
        s_len = strlen(s);
        t_len = strlen(t);
        /*
        if (string(s).find(t[0]) != string::npos) {
            for (int i = 1; i < MAXN; ++i) {
                dp[i][0] = 1;
            }
        }
        if (string(t).find(s[0]) != string::npos) {
            for (int i = 1; i < MAXN; ++i) {
                dp[0][i] = 1;
            }
        }
        */
        // dp[0][0] = 0;
        // printf("s_len pos: %x\n", s[s_len]);
        printf("%d\n", solve(s_len - 1, t_len - 1));
    }
    return 0;
};

#endif
