#ifndef _t14pb_20200406_
#define _t14pb_20200406_
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
#define INF 0x3F3F3F3F
#define DEBUG
#ifdef _DEBUG
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

const int MAXP = 5e5 + 3;
int not_prime[MAXP];
int prime[MAXP];
int pf_cnt[MAXP];
int ne[MAXP];
int pcnt;

void init_prime(const long long maxp = MAXP)
{
    memset(not_prime, 0, sizeof(not_prime));
    memset(pf_cnt, 0, sizeof(pf_cnt));
    pcnt = 0;

    for (int i = 2; i < maxp; ++i) {
        if (not_prime[i] == 0) {
            pcnt[prime] = i;
            ++pcnt;
            pf_cnt[i] = 1;
        }
        for (int j = 0; j < pcnt && static_cast<long long>(i) * prime[j] < maxp; ++j) {
            not_prime[i * prime[j]] = 1;
            pf_cnt[i * prime[j]] = pf_cnt[i] + 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }

    _DEBUG_CMD({
        cout << "total prime numbers between 1 to " << MAXP << " is: " << pcnt << endl;
        for (int i = 0; i < pcnt; ++i) {
            printf("prime[%d]: %d\n", i, prime[i]);
        }
    });
}

const int MAXN = 4e4 + 9;
int T, N;
int numbers[MAXN];
int head[MAXN];

int edge_cnt;
struct Edge {
    int u;
    int v;
    int next;
};
vector<Edge> edge;

void init_graph()
{
    // fill_n(head, MAXN, -1);
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
    edge.clear();
    edge.reserve(1e6 + 10);
}

void add_edge(int u, int v)
{
    edge.push_back(Edge{u, v, head[u]});
    head[u] = edge_cnt++;

    // edge.push_back(Edge{v, u, head[v]});
    // head[v] = edge_cnt++;
}

int calc_prime_pow(int x) { return pf_cnt[x]; }

bool visited[MAXN];
int dx[MAXN], dy[MAXN], mx[MAXN], my[MAXN];

bool bfs_hk()
{
    int dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    queue<int> mq;
    // fill_n(dx, N, -1);
    // fill_n(dy, N, -1);
    for (int i = 0; i < N; ++i) {
        if (mx[i] == -1) {
            mq.push(i);
            dx[i] = 0;
        }
    }
    while (!mq.empty()) {
        int u = mq.front();
        mq.pop();
        if (dx[u] > dis) {
            break;
        }
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (my[v] == -1) {
                    dis = dy[v];
                }
                else {
                    dx[my[v]] = dy[v] + 1;
                    mq.push(my[v]);
                }
            }
        }
    }
    return dis != INF;
}
int dfs_hk(int u)
{
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (!visited[v] && dy[v] == dx[u] + 1) {
            visited[v] = true;
            if (my[v] == -1 || dfs_hk(my[v])) {
                my[v] = u;
                mx[u] = v;
                return 1;
            }
        }
    }
    return 0;
}

int hopcroft_karp_algo()
{
    int sum = 0;
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    // fill_n(mx, N, -1);
    // fill_n(my, N, -1);
    while (bfs_hk()) {
        for (int i = 0; i < N; ++i) {
            if (mx[i] == -1) {
                memset(visited, 0, sizeof(visited));
                // fill_n(visited, N, 0);
                sum = sum + dfs_hk(i);
            }
        }
    }
    return sum;
}

int pvc = 0;
int pv[MAXP];
int get_prime_factor(int x)
{
    int pi = 0;
    pvc = 0;
    if (!not_prime[x]) {
        return pvc;
    }
    while (prime[pi] <= x) {
        if (x % prime[pi] == 0) {
            pv[pvc++] = prime[pi];
            while (x % prime[pi] == 0)
                x = x / prime[pi];
        }
        ++pi;
    }
    return pvc;
}
int get_prime_factor3(int x)
{
    int pi = 0;
    pvc = 0;
    if (!not_prime[x]) {
        return pvc;
    }
    int pix = prime[pi];
    while (pix <= x) {
        if (x % pix == 0) {
            pv[pvc++] = pix;
            while (x % pix == 0)
                x = x / pix;
        }
        pix = prime[++pi];
    }
    return pvc;
}
int get_prime_factor2(int x)
{
    pvc = 0;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            pv[pvc++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1)
        pv[pvc++] = x;
    return pvc;
}

bool partition_function(int x) { return pf_cnt[x] % 2 == 0; }

int main(int argc, char **argv)
{
    init_prime();
    cin >> T;
    int case_cnt = 0;
    while (T--) {
        cin >> N;
        long maxn = 0;
        memset(ne, 0, sizeof(ne));
        for (int i = 0; i < N; ++i) {
            scanf("%d", &numbers[i]);
        }
        // int *p = partition(&numbers[0], &numbers[N], partition_function);
        // int max_x = p - &numbers[0];
        for (int i = 0; i < N; ++i) {
            ne[numbers[i]] = i + 1;
            maxn = max(maxn, long(numbers[i]));
        }
        init_graph();

        for (int i = 0; i < N; ++i) {
            /*
            if (numbers[i] == 1) {
                for (int j = 0; prime[j] <= maxn; ++j) {
                    if (ne[prime[j]] != 0) {
                        add_edge(i, ne[prime[j]] - 1);
                    }
                }
                continue;
            }
            */
            // int pvc = get_prime_factor(numbers[i]);
            // const int ni = numbers[i];
            int pvc = get_prime_factor2(numbers[i]);
            DEBUG_CMD({ printf("prime factors of %d\n", numbers[i]); });
            for (int j = 0; j < pvc; ++j) {
                DEBUG_CMD({ printf("%d ", pv[j]); });
                if (ne[numbers[i] / pv[j]] != 0) {
                    if (pf_cnt[numbers[i]] % 2 == 0) {
                        add_edge(ne[numbers[i] / pv[j]] - 1, i);
                    }
                    else {
                        add_edge(i, ne[numbers[i] / pv[j]] - 1);
                    }
                }
            }
            DEBUG_CMD({ printf("\n"); });
        }
        _DEBUG_CMD({ cout << "__LINE__: " << __LINE__ << "N: " << N << endl; });
        // int hm = hopcroft_karp_algo(max_x);
        int hm = hopcroft_karp_algo();
        DEBUG_CMD({
            printf("hm for n: %d is %d\n", case_cnt + 1, hm);
            printf("max_edge: %d max_x: %d \n", edge_cnt, 0);
            cout << "first half: " << endl;
            for (int i = 0; i < N; ++i) {
                cout << numbers[i] << ' ';
            }
            cout << endl << "edges: " << endl;
            for (int i = 0; i < edge_cnt; ++i) {
                cout << "from: " << numbers[edge[i].u] << " to: " << numbers[edge[i].v] << endl;
            }
            printf("pf_cnt[42]: %d, pf_cnt[84]: %d\n", pf_cnt[42], pf_cnt[84]);
        });
        printf("Case %d: %d\n", ++case_cnt, N - hm);
    }
    return 0;
};

#endif
