#if 0
//#define DEBUG
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

#include <cstring>
#include <iostream>
#include <map>
using namespace std;
const int MAXN = 1000;
int bag[MAXN][2]; // bag[i][0]表示第i(重新编号了)个连通分量的0类人的个数,bag[i][1]表1类人
map<int, int> mp;        //用来将老的连通分量编号映射bag中的新编号
int cnt;                 //一共有cnt个分量
int insert(int x, int b) //连通分量x,与x的关系是b(0表示同类,1表示异类)
{
    if (mp.find(x) == mp.end())
        mp[x] = ++cnt;
    bag[mp[x]][b]++; //该分量的b类人加1
    return mp[x];
}
int F[MAXN];
int v[MAXN]; //表示i与根的关系
int findset(int i)
{
    if (F[i] == -1)
        return i;
    int temp = findset(F[i]);
    v[i] = (v[i] + v[F[i]]) % 2;
    return F[i] = temp;
}
void bind(int i, int j, int temp)
{
    int fa = findset(i);
    int fb = findset(j);
    if (fa != fb) {
        F[fb] = fa;
        v[fb] = (v[i] + v[j] + temp) % 2;
    }
}
int d[MAXN][310]; // DP
int main()
{
    int n, p1, p2;
    while (scanf("%d%d%d", &n, &p1, &p2) == 3) {
        if (n == 0 && p1 == 0 && p2 == 0)
            break;
        cnt = 0;
        mp.clear();
        memset(bag, 0, sizeof(bag));
        memset(F, -1, sizeof(F));
        memset(v, 0, sizeof(v));
        memset(d, 0, sizeof(d));
        while (n--) {
            int a, b, temp;
            char str[10];
            scanf("%d%d%s", &a, &b, str);
            if (str[0] == 'y')
                temp = 0;
            else if (str[0] == 'n')
                temp = 1;
            int fa = findset(a);
            int fb = findset(b);
            if (fa != fb) //不同分量
                bind(a, b, temp);
            ;
        }
        for (int i = 1; i <= p1 + p2; i++) //将1到p1+p2所有点重新编号
        {
            int fi = findset(i);
            insert(fi, v[i]);
        }
        DEBUG_CMD({
            cerr << "f[i]: ";
            for (int i = 1; i <= p1 + p2; ++i) {
                cerr << F[i] << ' ';
            }
            cerr << endl;
            cerr << "v[i]: ";
            for (int i = 1; i <= p1 + p2; ++i) {
                cerr << v[i] << ' ';
            }
            cerr << endl;
        });
        d[0][0] = 1;                   //初值
        for (int i = 1; i <= cnt; i++) //连通分量编号从1到cnt
        {
            for (int j = 0; j <= p1; j++) {
                if (j >= bag[i][0])
                    d[i][j] = d[i - 1][j - bag[i][0]];
                if (j >= bag[i][1])
                    d[i][j] += d[i - 1][j - bag[i][1]];
            }
        }
        // printf("###%d\n",d[cnt][p1]);

        if (d[cnt][p1] == 1) //能区分出
        {
            int j = p1;
            int choose[MAXN]; // choose[i]=1/0表示第i(重新编号)个连通分量选择第0类还是选第1类
            memset(choose, -1, sizeof(choose));
            for (int k = cnt; k >= 1; k--) //逆推找出choose
            {
                if (d[k][j] == d[k - 1][j - bag[k][0]]) {
                    choose[k] = 0;
                    j = j - bag[k][0];
                }
                else if (d[k][j] == d[k - 1][j - bag[k][1]]) {
                    choose[k] = 1;
                    j = j - bag[k][1];
                }
            }
            for (int i = 1; i <= p1 + p2; i++) {
                int fa = findset(i); //找出分量的编号fa
                int num = mp[fa];    //找出fa重新编号后的编号 num
                if (v[i] == choose[num])
                    printf("%d\n", i);
            }
            printf("end\n");
        }
        else {
            printf("no\n");
        }
    }
    return 0;
}
#else
#ifndef _t5pf_20191231_
#define _t5pf_20191231_
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
//#define DEBUG
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
int n, p1, p2;
int p[MAXN];
int v[MAXN];
int dp[MAXN][MAXN];
int bag[MAXN][2];

int find(int x)
{
    if (p[x] == x) {
        return p[x];
    }
    int tmp = find(p[x]);
    if (v[x]) {
        v[x] = v[p[x]];
    }
    else {
        v[x] = v[p[x]] ? 0 : 1;
    }
    // v[x] = v[p[x]] ^ v[x];
    return p[x] = tmp;
}

int union_set(int x, int y, int s)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        return xroot;
    }
    v[yroot] = v[y] ^ v[x] ^ s;
    p[yroot] = xroot;
    return xroot;
}

int same_group(int x, int y) { return find(x) == find(y); }

int main(int argc, char **argv)
{
    int x, y;
    char a[128];
    while (cin >> n >> p1 >> p2 && n + p1 + p2 != 0) {
        _DEBUG_CMD({ cerr << "n: " << n << " p1: " << p1 << " p2: " << p2 << endl; });
        memset(dp, 0, sizeof(dp));
        memset(bag, 0, sizeof(bag));
        for (int i = 1; i <= p1 + p2; ++i) {
            p[i] = i;
            v[i] = 1;
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%s", &x, &y, a);
            if (strcmp(a, "yes") == 0) {
                union_set(x, y, 1);
            }
            else {
                union_set(x, y, 0);
            }
        }
        map<int, int> res_map;
        int group_cnt = 1;

        for (int i = 1; i <= p1 + p2; ++i) {
            int x_pos = find(i);
            if (res_map.find(x_pos) == res_map.end()) {
                res_map[x_pos] = group_cnt++;
            }
            if (v[i]) {
                bag[res_map[x_pos]][1]++;
            }
            else {
                bag[res_map[x_pos]][0]++;
            }
        }
        dp[0][0] = 1;
        for (int i = 1; i < group_cnt; ++i) {
            for (int j = 0; j <= p1 + p2; ++j) {
                if (j >= bag[i][0])
                    dp[i][j] += dp[i - 1][j - bag[i][0]];
                if (j >= bag[i][1])
                    dp[i][j] += dp[i - 1][j - bag[i][1]];
                // dp[i][j] = dp[i - 1][j - bag[i][0]] + dp[i - 1][j - bag[i][1]];
            }
        }
        DEBUG_CMD({
            cerr << "f[i]: ";
            for (int i = 1; i <= p1 + p2; ++i) {
                cerr << p[i] << ' ';
            }
            cerr << endl;
            cerr << "v[i]: ";
            for (int i = 1; i <= p1 + p2; ++i) {
                cerr << v[i] << ' ';
            }
            cerr << endl;
        });
        if (dp[group_cnt - 1][p1] == 1) {
            int j = p1;
            int choose[MAXN];
            for (int k = group_cnt - 1; k >= 1; --k) {
                if (dp[k][j] == dp[k - 1][j - bag[k][0]]) {
                    choose[k] = 0;
                    j = j - bag[k][0];
                }
                else if (dp[k][j] == dp[k - 1][j - bag[k][1]]) {
                    choose[k] = 1;
                    j = j - bag[k][1];
                }
            }
            for (int i = 1; i <= p1 + p2; ++i) {
                int p = find(i);
                int num = res_map[p];
                if (v[i] == choose[num]) {
                    printf("%d\n", i);
                }
            }
            printf("end\n");
        }
        else {
            printf("no\n");
        }
    }
    return 0;
};

#endif
#endif
