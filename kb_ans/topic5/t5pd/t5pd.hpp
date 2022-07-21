#if 0
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define fuck(x) cout << "[" << x << "]";
#define FIN freopen("input.txt", "r", stdin);
#define FOUT freopen("output.txt", "w+", stdout);
//#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int MX = 2e5 + 5;
int P[MX], val[MX];
int find(int x)
{
    if (P[x] == x)
        return x;
    int p = find(P[x]);
    val[x] += val[P[x]];
    return P[x] = p;
}
int solve(int l, int r, int s)
{
    int u = find(l), v = find(r);
    if (u != v) {
        P[v] = u;
        val[v] = s + val[l] - val[r];
        return 0;
    }
    else
        return s != val[r] - val[l];
}
int main()
{
    int n, m; // FIN;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i <= n; i++) {
            P[i] = i;
            val[i] = 0;
        }
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            int l, r, s;
            scanf("%d%d%d", &l, &r, &s);
            l--;
            ans += solve(l, r, s);
        }
        printf("%d\n", ans);
    }
    return 0;
}
#else
#ifndef _t5pd_20191230_
#define _t5pd_20191230_
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

const int MAXN = 200000 + 3;
int N, M;
int p[MAXN];
int v[MAXN];

int find(int x)
{
    if (p[x] == x) {
        return p[x];
    }
    int pid = find(p[x]);
    // v[x] += v[pid];
    v[x] += v[p[x]];
    return p[x] = pid;
}

int union_set(int x, int y, int s)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot != yroot) {
        p[yroot] = xroot;
        v[yroot] = s + v[x] - v[y];
        return 0;
    }
    return s != v[y] - v[x];
}

int main(int argc, char **argv)
{
    int a, b, s;
    while (cin >> N >> M) {
        for (int i = 0; i <= N; ++i) {
            p[i] = i;
            v[i] = 0;
        }
        int ans = 0;
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &a, &b, &s);
            ans += union_set(a - 1, b, s);
        }
        cout << ans << endl;
    }
    return 0;
};

#endif
#endif
