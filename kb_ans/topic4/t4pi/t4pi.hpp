#ifndef _t4pi_20191222_
#define _t4pi_20191222_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 1 << 5;
map<string, int> name2idx;
// int currency_cnt = 0;

struct ExchangeRate {
    int u;
    int v;
    int next;
    float rate;
    ExchangeRate(){};
    ExchangeRate(int u, int v, int next, float rate) : u(u), v(v), next(next), rate(rate){};
} er[MAXN * MAXN];
int n, m;
int head[MAXN];
int edge_cnt = 0;

void add_edge(int u, int v, float rate)
{
    er[edge_cnt].next = head[u];
    er[edge_cnt].u = u;
    er[edge_cnt].v = v;
    er[edge_cnt].rate = rate;
    head[u] = edge_cnt++;
}

bool bellman_ford()
{
    float d[MAXN];
    // memset(d, 0x3F, sizeof(d));
    fill(d, d + MAXN, 1e12);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < edge_cnt; ++j) {
            const ExchangeRate &e = er[j];
            if (d[e.u] != 1e12 && d[e.v] < d[e.u] * e.rate) {
                d[e.v] = d[e.u] * e.rate;
                if (i == n - 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    int case_cnt = 1;
    while (cin >> n && n != 0) {
        string cname;
        string sname, dname;
        float rate;
        name2idx.clear();
        // currency_cnt = 0;
        edge_cnt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < n; ++i) {
            cin >> cname;
            name2idx[cname] = i;
        }
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> sname >> rate >> dname;
            add_edge(name2idx[sname], name2idx[dname], rate);
        }
        bool res = bellman_ford();
        switch (res) {
            case true:
                printf("Case %d: Yes\n", case_cnt++);
                break;
            case false:
                printf("Case %d: No\n", case_cnt++);
                break;
        }
    }
    return 0;
};

#endif
