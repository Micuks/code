#if 0
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

const int HASH = 10000;
const int N = 10005;
const int M = 20005;

map<int, bool> mp;

int f[N];
int rank[N];
int n, m, Q;
int ans[50005]; // 保存答案

struct Buit {
    int u, v;
} built[M];

struct Query {
    char cmd[10];
    int a, b;
} query[50005];

void make_set()
{
    for (int i = 0; i < n; ++i)
        f[i] = i;
}
int find(int x)
{
    int i, j = x;
    while (j != f[j])
        j = f[j];
    while (x != j) {
        i = f[x];
        f[x] = j;
        x = i;
    }
    return j;
}
void Union(int x, int y)
{
    int a = find(x), b = find(y);
    ;
    if (a == b)
        return;
    if (rank[a] > rank[b])
        f[b] = a;
    else if (rank[a] < rank[b])
        f[a] = b;
    else {
        if (a > b)
            f[a] = b;
        else
            f[b] = a;
    }
}

int main()
{
    bool flag = false;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; ++i)
            scanf("%d", &rank[i]);
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &built[i].u, &built[i].v);
            if (built[i].u > built[i].v) {
                swap(built[i].u, built[i].v);
            }
        }
        scanf("%d", &Q);
        mp.clear();
        for (int i = 0; i < Q; ++i) {
            scanf("%s", query[i].cmd);
            if (query[i].cmd[0] == 'q')
                scanf("%d", &query[i].a);
            else {
                scanf("%d%d", &query[i].a, &query[i].b);
                if (query[i].a > query[i].b)
                    swap(query[i].a, query[i].b);
                mp[query[i].a * HASH + query[i].b] = true;
                ;
            }
        }
        // 合并没有删除的边
        make_set();
        for (int i = 0; i < m; ++i)
            if (!mp[built[i].u * HASH + built[i].v]) {
                Union(built[i].u, built[i].v);
            }
        // 询问
        int k = 0;
        for (int i = Q - 1; i >= 0; --i) {
            if (query[i].cmd[0] == 'q') {
                int fa = find(query[i].a);
                if (rank[fa] > rank[query[i].a])
                    ans[k++] = fa;
                else
                    ans[k++] = -1;
            }
            else {
                Union(query[i].a, query[i].b);
            }
        }
        if (flag)
            puts("");
        else
            flag = true;
        for (int i = k - 1; i >= 0; --i)
            printf("%d\n", ans[i]);
    }
    return 0;
}
#else
#ifndef _t5pl_20200106_
#define _t5pl_20200106_
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

const int MAXN = 5e4 + 21;
int N, M, Q;
int f[MAXN];
int a[MAXN], b[MAXN];
int qa[MAXN], qb[MAXN];
long long p[MAXN];

int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    // int tmp = find(f[x]);
    // p[x] = p[f[x]] + p[x];
    return f[x] = find(f[x]);
}

int union_set(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        return xroot;
    }
    if (p[yroot] > p[xroot] || (p[yroot] == p[xroot] && yroot < xroot)) {
        // p[xroot] = p[y] - p[x];
        return f[xroot] = yroot;
    }
    // p[yroot] = p[x] - p[y];
    return f[yroot] = xroot;
}

void init()
{
    for (int i = 0; i <= N; ++i) {
        f[i] = i;
    }
}

int main(int argc, char **argv)
{
    bool first_line = true;
    while (cin >> N) {
        set<int> brk_con;
        init();
        for (int i = 0; i < N; ++i) {
            scanf("%lld", &p[i]);
        }
        cin >> M;
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &a[i], &b[i]);
        }
        cin >> Q;
        char buf[32];
        vector<int> ans;
        for (int i = 0; i < Q; ++i) {
            scanf("%s", buf);
            if (buf[0] == 'q') {
                scanf("%d", &qa[i]);
                qb[i] = -1;
            }
            else {
                scanf("%d%d", &qa[i], &qb[i]);
                brk_con.insert(qa[i] * 10001 + qb[i]);
                brk_con.insert(qb[i] * 10001 + qa[i]);
            }
        }
        for (int i = 0; i < M; ++i) {
            if (brk_con.find(a[i] * 10001 + b[i]) == brk_con.end()) {
                union_set(a[i], b[i]);
            }
        }
        for (int i = Q - 1; i >= 0; --i) {
            if (qb[i] != -1) {
                union_set(qa[i], qb[i]);
            }
            else {
                int help = find(qa[i]);
                if (help == qa[i] || p[help] <= p[qa[i]]) {
                    ans.push_back(-1);
                }
                else {
                    ans.push_back(help);
                }
            }
        }
        reverse(ans.begin(), ans.end());
        if (!first_line) {
            printf("\n");
        }
        else {
            first_line = false;
        }
        for (int i = 0; i < ans.size(); ++i) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
};

#endif
#endif
