#if 0
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
char s[105];
int dp[105][105];
bool check(int l, int r)
{
    if (s[l] == '(' && s[r] == ')')
        return true;
    if (s[l] == '[' && s[r] == ']')
        return true;
    return false;
}
int main()
{
    while (scanf("%s", s) && s[0] != 'e') {
        memset(dp, 0, sizeof(dp));
        int len, i, j, k;
        for (len = 2; len <= strlen(s); len++) {
            for (i = 0; i + len - 1 <= strlen(s) - 1; i++) {
                int j = i + len - 1;
                if (check(i, j)) {
                    dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
                }
                for (k = i; k <= j - 1; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        cout << dp[0][strlen(s) - 1] << endl;
    }
    return 0;
}

#else
#ifndef _t22pc_20210923_
#define _t22pc_20210923_
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

const int INF = 0x3F3F3F3F;
const int MAXN = 1 << 7;
char brackets[MAXN];
int dp[MAXN][MAXN], blen;

bool check_pair(int i, int j)
{
    bool ret =
        (brackets[i] == '(' && brackets[j] == ')') || (brackets[i] == '[' && brackets[j] == ']');
    _DEBUG_CMD(
        printf("test brackets[%d]:%c [%d]:%c ans:%d\n", i, brackets[i], j, brackets[j], int(ret)));
    return ret;
}

void debug_print()
{
    for (int i = 0; i < blen; ++i) {
        for (int j = 0; j < blen; ++j) {
            printf("%2d ", dp[i][j]);
        }
        printf("\n");
    }
}
int main(int argc, char **argv)
{
    while (~scanf("%s", brackets) && strcmp(brackets, "end") != 0) {
        memset(dp, 0, sizeof(dp));
        blen = strlen(brackets);
        for (int k = 1; k < blen; ++k) {
            for (int i = 0; i < blen; ++i) {
                int max_pair = 0;
                if (i + k >= blen) {
                    continue;
                }
                if (check_pair(i, i + k)) {
                    max_pair = max(max_pair, dp[i + 1][i + k - 1] + 1);
                }
                for (int j = i; j < i + k; ++j) {
                    /*
                    if (check_pair(i, j)) {
                        max_pair = max(max_pair, dp[i + 1][j - 1] + 1);
                    }
                    */
                    max_pair = max(max_pair, dp[i][j] + dp[j + 1][i + k]);
                    assert(i <= j);
                    assert(j + 1 <= i + k);
                }
                max_pair = max(max_pair, dp[i + 1][i + k]);
                dp[i][i + k] = max_pair;
            }
        }
        _DEBUG_CMD({ debug_print(); });
        printf("%d\n", dp[0][blen - 1] * 2);
    }
    return 0;
};

#endif
#endif
