#if 0

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
/*
 * 使用优先队列优化Dijkstra算法
 * 复杂度O(ElogE)
 * 注意对vector<Edge>E[MAXN]进行初始化后加边
 */
const int INF = 0x3f3f3f3f;
const int MAXN = 30010;
struct qnode {
    int v;
    int c;
    qnode(int _v = 0, int _c = 0) : v(_v), c(_c) {}
    bool operator<(const qnode &r) const { return c > r.c; }
};
struct Edge {
    int v, cost;
    int next;
};
Edge edge[200000];
int tol;
int head[MAXN];
bool vis[MAXN];
int dist[MAXN];
void Dijkstra(int n, int start) //点的编号从1开始
{
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    priority_queue<qnode> que;
    while (!que.empty())
        que.pop();
    dist[start] = 0;
    que.push(qnode(start, 0));
    for (int i = 0; i < n; ++i) {
        cout << "head[" << i << "]: ";
        for (int j = head[i]; j != -1; j = edge[j].next) {
            cout << "v: " << edge[j].v << " c: " << edge[j].cost << ' ';
        }
        cout << endl;
    }
    qnode tmp;
    while (!que.empty()) {
        tmp = que.top();
        que.pop();
        int u = tmp.v;
        if (vis[u])
            continue;
        vis[u] = true;
        cout << "vis[" << u << "] is searched ";
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            int cost = edge[i].cost;
            if (!vis[v] && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                cout << v << ", ";
                que.push(qnode(v, dist[v]));
            }
        }
        cout << " is relaxed\n";
    }
}
void addedge(int u, int v, int w)
{
    edge[tol].v = v;
    edge[tol].cost = w;
    edge[tol].next = head[u];
    head[u] = tol++;
}

int main()
{
    //    freopen("in.txt","r",stdin);
    //    freopen("out.txt","w",stdout);
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        tol = 0;
        memset(head, -1, sizeof(head));
        int A, B, C;
        while (m--) {
            scanf("%d%d%d", &A, &B, &C);
            addedge(A, B, C);
        }
        Dijkstra(n, 1);
        printf("%d\n", dist[n]);
    }
    return 0;
}

#endif
//#define _t4pk_20191223_
#ifndef _t4pk_20191223_
#define _t4pk_20191223_
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
#include <string>
#include <vector>
using namespace std;

const long maxn = 200000 + 7;
long n, m;
long d[maxn];
long vis[maxn];
long head[maxn];
long edge_cnt = 0;

struct edge {
    long u;
    long v;
    long c;
    long next;
} edge[maxn];

struct Situation {
    int u;
    long c;
    bool operator<(const Situation &s) const { return c > s.c; }
};

void add_edge(long u, long v, long c)
{
    edge[edge_cnt].next = head[u];
    edge[edge_cnt].u = u;
    edge[edge_cnt].v = v;
    edge[edge_cnt].c = c;
    head[u] = edge_cnt++;
}

struct cmp {
    bool operator()(long di, long dj) { return d[di] > d[dj]; }
};

long dijkstra()
{
    // priority_queue<long, vector<long>, cmp> pq;
    priority_queue<Situation> pq;
    while (!pq.empty())
        pq.pop();
    d[0] = 0;
    Situation s;
    s.u = 0;
    s.c = 0;
    pq.push(s);
    /*
    for (int i = 0; i < n; ++i) {
        cout << "head[" << i << "]: ";
        for (int j = head[i]; j != -1; j = edge[j].next) {
            cout << "v: " << edge[j].v << " c: " << edge[j].c << ' ';
        }
        cout << endl;
    }
    */
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        // cout << "vis[" << u << "] is searched ";
        for (long h = head[u]; h != -1; h = edge[h].next) {
            long v = edge[h].v;
            long c = edge[h].c;
            if (!vis[v] && d[v] > d[u] + c) {
                d[v] = d[u] + c;
                Situation s;
                s.u = v;
                s.c = d[v];
                // cout << v << ", ";
                pq.push(s);
            }
        }
        // cout << " is relaxed\n";
    }
    /*
    for (int i = 0; i < n; ++i) {
        cout << d[i] << ' ';
    }
    cout << endl;
    */
    return d[n - 1];
}

int main(int argc, char **argv)
{
    int a, b, c;
    memset(vis, 0, sizeof(vis));
    memset(d, 0x3f, sizeof(d));
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        add_edge(a - 1, b - 1, c);
    }
    int res = dijkstra();
    cout << res << endl;
    return 0;
};

#endif
