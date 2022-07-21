#ifndef _t12pc_20200120_
#define _t12pc_20200120_
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

int n;
struct Block {
    int x, y, z;
    Block(int x = 0, int y = 0, int z = 0) : x(max(x, y)), y(min(x, y)), z(z) {}
    Block &operator=(const Block b)
    {
        x = b.x;
        y = b.y;
        z = b.z;
        return *this;
    }
    bool operator<(const Block &b) const
    {
        if (x < b.x) {
            return true;
        }
        else if (x == b.x) {
            return y < b.y;
        }
        else {
            return false;
        }
    }
    bool fit_on(const Block &b) const { return x < b.x && y < b.y; }
    friend ostream &operator<<(ostream &os, const Block &b)
    {
        os << "x:" << b.x << " y:" << b.y << ' ' << b.z;
        return os;
    }
};
vector<Block> blocks;
bool sorter(const Block &b1, const Block &b2) { return b2 < b1; }

int main(int argc, char **argv)
{
    int x, y, z;
    int case_cnt = 0;
    while (~scanf("%d", &n) && n != 0) {
        blocks.clear();
        blocks.reserve(n * 3 + 1);
        blocks.push_back(Block(1e9, 1e9, 0));

        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            blocks.push_back(Block(x, y, z));
            blocks.push_back(Block(y, z, x));
            blocks.push_back(Block(z, x, y));
        }
        sort(blocks.rbegin(), blocks.rend());
        _DEBUG_CMD({
            cout << "blocks after sort: ";
            for (int i = 0; i < blocks.size(); ++i) {
                cout << blocks[i] << '\n';
            }
            cout << endl;
        });
        vector<int> dp(3 * n + 1);
        dp[0] = blocks[0].z;
        for (int i = 1; i <= 3 * n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (blocks[i].fit_on(blocks[j])) {
                    dp[i] = max(dp[i], dp[j] + blocks[i].z);
                }
            }
        }
        _DEBUG_CMD({
            cout << "blks files: " << endl;
            for (int i = 0; i <= 3 * n; ++i) {
                cout << dp[i] << " ";
            }
            cout << endl;
        });
        _DEBUG_CMD({
            cout << "blocks[4]: " << blocks[4] << " blocks[3]: " << blocks[3]
                 << " blocks[4] < blocks[3]: " << bool(blocks[4] < blocks[3]) << endl;
        });
        printf("Case %d: maximum height = %d\n", ++case_cnt, *max_element(dp.begin(), dp.end()));
    }
    return 0;
};

#endif
