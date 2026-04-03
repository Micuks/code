#if 0

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 1e4 + 111;

int p[MAXN], rel[MAXN], temp[MAXN], l[MAXN], r[MAXN], cnt; // p:根节点; rel:到根节点的奇偶关系
bool odd[MAXN];

int findPos(int x) // 查询坐标在离散后的位置
{
    int s = 0, e = cnt, mid;
    while (s < e) {
        mid = (s + e) / 2;
        if (temp[mid] == x)
            return mid;
        else if (temp[mid] < x)
            s = mid + 1;
        else
            e = mid;
    }
    return -1;
}

int find(int x)
{
    if (p[x] == x)
        return x;
    int t = p[x];
    p[x] = find(p[x]); // 更新x和根结点的关系
    rel[x] ^= rel[t];  // 例如原本是A->B，现在是A->B->C
    return p[x];       // rel[A](A->C) = rel[A](A->B)^rel[B](B->C)
                       // 奇偶性相同就是0，不同就是1.用异或刚好满足这个条件
}

int main()
{
    int len, n, a, b;
    while (~scanf("%d", &len)) {
        cnt = 0;
        char s[5];
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) // l、r数组存查询区间
        {
            scanf("%d%d%s", &a, &b, s);
            l[i] = --a;
            r[i] = b;
            odd[i] = (s[0] == 'o');
            temp[cnt++] = a;
            temp[cnt++] = b;
        }
        sort(temp, temp + cnt);
        cnt = unique(temp, temp + cnt) - temp; // 坐标离散化
        for (int i = 0; i <= cnt; ++i)
            p[i] = i, rel[i] = 0;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int u = findPos(l[i]), v = findPos(r[i]);
            int ru = find(u), rv = find(v);
            if (ru == rv) // 如果根结点相同，进入判断
            {
                if ((rel[u] ^ rel[v]) != odd[i])
                    break;
                ++ans;
            }
            else {
                if (odd[i]) // 如果区间是奇数
                {
                    p[ru] = rv;
                    rel[ru] =
                        rel[u] ^ rel[v] ^ 1; // 这里的更新可以具体假设rel的关系，发现就是这样XD
                }
                else {
                    p[ru] = rv;
                    rel[ru] = rel[u] ^ rel[v]; // 理由同上
                }
                ++ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
#else
#ifndef _t5ph_20200103_
#define _t5ph_20200103_
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

map<int, int> f;
map<int, int> v;
int array_max = 0;
int q_cnt;

int find(int x)
{
    if (f.find(x) == f.end()) {
        v[x] = 0;
        return f[x] = x;
    }
    if (f[x] == x) {
        return x;
    }
    int tmp = find(f[x]);
    v[x] = (v[f[x]] + v[x]) % 2;
    return f[x] = tmp;
}

bool union_set(int x, int y, int s)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        if (abs(v[y] - v[x]) != s) {
            return false;
        }
    }
    // v[yroot] = (v[x] - v[y] + s + 2) % 2;
    v[yroot] = v[x] ^ v[y] ^ s;
    f[yroot] = xroot;
    return true;
}

int main(int argc, char **argv)
{
    cin >> array_max;
    cin >> q_cnt;
    int s, e;
    char buf[32];
    bool res = true;
    for (int i = 0; i < q_cnt; ++i) {
        scanf("%d%d%s", &s, &e, buf);
        if (buf[0] == 'o') {
            res = union_set(s - 1, e, 1);
        }
        else {
            res = union_set(s - 1, e, 0);
        }
        if (!res) {
            cout << i << endl;
            res = false;
            DEBUG_CMD({
                for (int i = 0; i < 10; ++i) {
                    if (v.find(i) != v.end()) {
                        cerr << "v[" << i << "]: " << v[i];
                    }
                    if (f.find(i) != f.end()) {
                        cerr << " f[" << i << "]: " << f[i] << endl;
                    }
                }
            });
            break;
        }
    }
    if (res) {
        cout << q_cnt << endl;
    }
    return 0;
};

#endif
#endif
