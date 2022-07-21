#if 0
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 1000000 + 10;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n, m, cnt;
int head[maxn];
int a[maxn][3];
LL dis[maxn];
bool vis[maxn];
struct Edge {
    int u, v, w, next;
} edge[maxn];
struct Node {
    int u, d;
    Node(int u, int d) : u(u), d(d) {}
    bool operator<(const Node &p) const { return d > p.d; }
};
void Init()
{
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        vis[i] = false;
        dis[i] = INF;
    }
}
void addEdge(int u, int v, int w)
{
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}
LL Dijkstra()
{
    priority_queue<Node> q;
    q.push(Node(1, 0));
    // vis[1]=true;
    dis[1] = 0;
    while (!q.empty()) {

        Node p = q.top();
        q.pop();
        int u = p.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        // cout << "[u]:" << u << endl;
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].v;
            int w = edge[i].w;
            if (!vis[v] && dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(Node(v, dis[v]));
            }
        }
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dis[i];
        cout << dis[i] << ' ';
    }
    cout << endl;
    return ans;
}

int main()
{
    int T;
    // freopen("H.txt","r",stdin);
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        Init();
        for (int i = 0; i < m; i++) {
            // cin>>a[i][0]>>a[i][1]>>a[i][2];
            scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
            /*
            printf("before insert, a[%d][0]:%d, a[%d][1]:%d, a[%d][2]:%d, cnt:%d head[u]:%d\n", i,
                   a[i][0], i, a[i][1], i, a[i][2], cnt, head[a[i][0]]);
                   */
            addEdge(a[i][0], a[i][1], a[i][2]);
            // printf("after insert: head[%d]: %d, cnt:%d\n", a[i][0], head[a[i][0]], cnt);
        }
        /*
        cout << "show all the edges\n";
        for (int i = 1; i <= n; ++i) {
            // cout << "conect to node " << i << endl;
            for (int h = head[i]; h != -1; h = edge[h].next) {
                cout << "u: " << edge[h].u << " v: " << edge[h].v << " w: " << edge[h].w << ' ';
            }
            cout << endl;
        }
        */
        LL ans = Dijkstra();
        Init();
        for (int i = 0; i < m; i++) {
            addEdge(a[i][1], a[i][0], a[i][2]);
        }
        ans += Dijkstra();
        // cout << ans << endl;
    }
    return 0;
}

#endif
#if 0
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 1000000 + 10;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
struct node {
    int to, next, w;
} edge[maxn];
int head[maxn];
int a[maxn][3];
LL dis[maxn];
bool vis[maxn];
int cnt;
void addEdge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}
void Init()
{
    cnt = 0;
    memset(head, -1, sizeof(head));
    memset(vis, false, sizeof(vis));
    for (int i = 0; i <= n; i++)
        dis[i] = INF;
}
LL spfa()
{
    queue<int> q;
    q.push(1);
    vis[1] = true;
    dis[1] = 0;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        vis[p] = false;
        cout << "[u]:" << p << endl;
        //注意spfa的vis和dijstra的不同点，
        //前者是判断是否在queue里而已
        //后者是判断是否已经是最优的点。
        for (int i = head[p]; i != -1; i = edge[i].next) {
            int to = edge[i].to;
            int w = edge[i].w;
            if (dis[to] > dis[p] + w) {
                dis[to] = dis[p] + w;
                if (!vis[to]) {
                    q.push(to);
                    vis[to] = true;
                }
            }
        }
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dis[i];
        cout << dis[i] << ' ';
    }
    cout << endl;
    return ans;
}
int main()
{
    int T;
    // freopen("data/1511.txt","r",stdin);
    cin >> T;
    int x, y, z;
    while (T--) {
        cin >> n >> m;
        Init();
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
            addEdge(a[i][0], a[i][1], a[i][2]);
        }
        LL ans = spfa();
        Init();
        for (int i = 0; i < m; i++) {
            addEdge(a[i][1], a[i][0], a[i][2]);
        }
        ans += spfa();
        // cout<<ans<<endl;
    }
    return 0;
}
#endif

//#define _t4pj_20191222_
#ifndef _t4pj_20191222_
#define _t4pj_20191222_
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

// const int MAXN = 1e6 + 7;
const int MAXN = 1000000 + 10;
int N, P, Q;
int ihead[MAXN];
int ohead[MAXN];

int ivisited[MAXN];
long long id[MAXN];
int ovisited[MAXN];
long long od[MAXN];

int line_cnt = 0;
struct BusStop {
    int u;
    int v;
    long long cost;
    int inext;
    int onext;
    bool operator<(const BusStop &s) const { return cost > s.cost; }
} bs[MAXN];

void add_edge(int u, int v, int cost)
{
    bs[line_cnt].inext = ihead[u];
    bs[line_cnt].onext = ohead[v];
    bs[line_cnt].u = u;
    bs[line_cnt].v = v;
    bs[line_cnt].cost = cost;
    ohead[v] = line_cnt;
    ihead[u] = line_cnt++;
}
long long int spfa()
{
    queue<int> q;
    q.push(0);
    ivisited[0] = true;
    id[0] = 0;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        ivisited[p] = false;
        //注意spfa的vis和dijstra的不同点，
        //前者是判断是否在queue里而已
        //后者是判断是否已经是最优的点。
        for (int i = ihead[p]; i != -1; i = bs[i].inext) {
            int to = bs[i].v;
            long long w = bs[i].cost;
            if (id[to] > id[p] + w) {
                id[to] = id[p] + w;
                if (!ivisited[to]) {
                    q.push(to);
                    ivisited[to] = true;
                }
            }
        }
    }
    q.push(0);
    ovisited[0] = true;
    od[0] = 0;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        ovisited[p] = false;
        //注意spfa的vis和dijstra的不同点，
        //前者是判断是否在queue里而已
        //后者是判断是否已经是最优的点。
        for (int i = ohead[p]; i != -1; i = bs[i].onext) {
            int to = bs[i].u;
            long long w = bs[i].cost;
            if (od[to] > od[p] + w) {
                od[to] = od[p] + w;
                if (!ovisited[to]) {
                    q.push(to);
                    ovisited[to] = true;
                }
            }
        }
    }
    return 0;
}

long long dijkstra()
{
#if 1
    priority_queue<BusStop> mqueue;
    int n = 0;
    /*
    int n = ihead[0];
    while (n != -1) {
        id[bs[n].v] = bs[n].cost;
        n = bs[n].inext;
    }
    n = ohead[0];
    while (n != -1) {
        od[bs[n].u] = bs[n].cost;
        n = bs[n].onext;
    }
    */
    // ivisited[0] = 1;
    id[0] = 0;
    // ovisited[0] = 1;
    od[0] = 0;
    BusStop bs_;
    bs_.u = 0;
    bs_.v = 0;
    bs_.cost = 0;
    mqueue.push(bs_);
    while (!mqueue.empty()) {
        BusStop busstop = mqueue.top();
        mqueue.pop();
        if (ivisited[busstop.u]) {
            continue;
        }
        ivisited[busstop.u] = 1;
        n = ihead[busstop.u];
        while (n != -1) {
            const BusStop &b = bs[n];
            if (!ivisited[b.v] && id[b.v] > id[b.u] + b.cost) {
                id[b.v] = id[b.u] + b.cost;

                BusStop bstp;
                bstp.u = b.v;
                bstp.cost = id[b.v];
                mqueue.push(bstp);
            }
            n = bs[n].inext;
        }
    }

    mqueue.push(bs_);
    while (!mqueue.empty()) {
        BusStop busstop = mqueue.top();
        mqueue.pop();
        if (ovisited[busstop.v]) {
            continue;
        }
        ovisited[busstop.v] = 1;
        n = ohead[busstop.v];
        while (n != -1) {
            const BusStop &b = bs[n];
            if (!ovisited[b.u] && od[b.u] > od[b.v] + b.cost) {
                od[b.u] = od[b.v] + b.cost;

                BusStop bstp;
                bstp.v = b.u;
                bstp.cost = od[b.u];
                mqueue.push(bstp);
            }
            n = bs[n].onext;
        }
    }
    /*
    for (int i = 0; i < P; ++i) {
        int min_val = 0x3F3F3F3F;
        int min_idx;
        for (int j = 0; j < P; ++j) {
            if (!ivisited[j] && (min_val == 0x3F3F3F3F || id[j] < min_val)) {
                min_val = id[j];
                min_idx = j;
            }
        }
        ivisited[min_idx] = 1;

        n = ihead[min_idx];
        while (n != -1) {
            const BusStop &b = bs[n];
            if (!ivisited[b.v] && id[b.v] > id[b.u] + b.cost) {
                id[b.v] = id[b.u] + b.cost;
            }
            n = bs[n].inext;
        }
    }

    for (int i = 0; i < P; ++i) {
        int min_val = 0x3F3F3F3F;
        int min_idx;
        for (int j = 0; j < P; ++j) {
            if (!ovisited[j] && (min_val == 0x3F3F3F3F || od[j] < min_val)) {
                min_val = od[j];
                min_idx = j;
            }
        }
        ovisited[min_idx] = 1;
        n = ohead[min_idx];

        while (n != -1) {
            const BusStop &b = bs[n];
            if (!ovisited[b.u] && od[b.u] > od[b.v] + b.cost) {
                od[b.u] = od[b.v] + b.cost;
            }
            n = bs[n].onext;
        }
    }
    */
    /*
    cerr << "id:\n";
    for (int i = 0; i < P; ++i) {
        cerr << id[i] << ' ';
    }
    cerr << "\nod:\n";
    for (int i = 0; i < P; ++i) {
        cerr << od[i] << ' ';
    }
    cerr << endl;
    */
    /*
    for (int i = 0; i < P; ++i) {
        cout << id[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < P; ++i) {
        cout << od[i] << ' ';
    }
    cout << endl;
    */
#endif
    // spfa();
    long long int res1 = 0;
    for (int i = 0; i < P; ++i) {
        res1 += id[i] + od[i];
    }
    return accumulate(id, id + P, 0ll) + accumulate(od, od + P, 0ll);
    return res1;
    // return accumulate(id, id + P, 0l) + accumulate(od, od + P, 0l);
}

int main(int argc, char **argv)
{
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int u, v, cost;
        memset(ihead, -1, sizeof(ihead));
        memset(ohead, -1, sizeof(ohead));
        memset(ivisited, 0, sizeof(ivisited));
        memset(ovisited, 0, sizeof(ovisited));
        memset(id, 0x3F, sizeof(id));
        memset(od, 0x3F, sizeof(od));
        line_cnt = 0;
        scanf("%d%d", &P, &Q);
        for (int j = 0; j < Q; ++j) {
            scanf("%d%d%d", &u, &v, &cost);
            add_edge(u - 1, v - 1, cost);
        }
        long long total_min_cost = dijkstra();
        cout << total_min_cost << endl;
    }
    return 0;
};

#endif
