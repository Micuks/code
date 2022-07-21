#ifndef _t5pi_20200103_
#define _t5pi_20200103_
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

const int MAXQ = 1e4 + 7;
const int MAXN = 4e4 + 9;
int N, M, K;
struct Query {
    int f1, f2, q_idx, r_idx, res;
} q[MAXQ];
struct FarmPosition {
    int f1, f2, f1_off, f2_off;
    // let east be adding in f1, west be deducing in f1
    // south be add in f2, north be deducing in f2
} farm_pos[MAXN];
int f[MAXN];
int f1_dis[MAXN];
int f2_dis[MAXN];

/*
struct {
    bool operator()(const Query &q1, const Query &q2) const { return q1.q_idx < q2.q_idx; }
} q_idx_sorter;
struct {
    bool operator()(const Query &q1, const Query &q2) const { return q1.r_idx < q2.r_idx; }
} r_idx_sorter;
*/

bool r_idx_sorter(const Query &q1, const Query &q2) { return q1.r_idx < q2.r_idx; }
bool q_idx_sorter(const Query &q1, const Query &q2) { return q1.q_idx < q2.q_idx; }
int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    int tmp = find(f[x]);
    f1_dis[x] += f1_dis[f[x]];
    f2_dis[x] += f2_dis[f[x]];
    return f[x] = tmp;
}

int union_set(int x, int y, int f1_pos, int f2_pos)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        return xroot;
    }
    f1_dis[yroot] = f1_dis[x] - f1_dis[y] + f1_pos;
    f2_dis[yroot] = f2_dis[x] - f2_dis[y] + f2_pos;
    return f[yroot] = xroot;
}

int search(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot != yroot) {
        return -1;
    }
    return abs(f1_dis[x] - f1_dis[y]) + abs(f2_dis[x] - f2_dis[y]);
}

int main(int argc, char **argv)
{
    int f1, f2, l;
    char direction[128];
    cin >> N >> M;
    for (int i = 0; i <= N; ++i) {
        f[i] = i;
        f1_dis[i] = 0;
        f2_dis[i] = 0;
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d%s", &f1, &f2, &l, direction);
        farm_pos[i].f1 = f1;
        farm_pos[i].f2 = f2;
        switch (direction[0]) {
            case 'E':
                farm_pos[i].f1_off = l;
                farm_pos[i].f2_off = 0;
                break;
            case 'W':
                farm_pos[i].f1_off = -l;
                farm_pos[i].f2_off = 0;
                break;
            case 'S':
                farm_pos[i].f1_off = 0;
                farm_pos[i].f2_off = l;
                break;
            case 'N':
                farm_pos[i].f1_off = 0;
                farm_pos[i].f2_off = -l;
                break;
        }
    }
    cin >> K;
    for (int i = 0; i < K; ++i) {
        scanf("%d%d%d", &q[i].f1, &q[i].f2, &q[i].r_idx);
        q[i].q_idx = i;
    }
    sort(q, q + K, r_idx_sorter);
    DEBUG_CMD({
        cout << "q[i].r_idx: ";
        for (int i = 0; i < K; ++i) {
            cout << q[i].r_idx << ' ';
        }
        cout << endl << "q[i].q_idx: ";
        for (int i = 0; i < K; ++i) {
            cout << q[i].q_idx << ' ';
        }
        cout << endl;
    });
    int cur_q = 0;
    for (int i = 0; i < M; ++i) {
        while (q[cur_q].r_idx < i + 1) {
            q[cur_q].res = search(q[cur_q].f1, q[cur_q].f2);
            cur_q += 1;
        }
        union_set(farm_pos[i].f1, farm_pos[i].f2, farm_pos[i].f1_off, farm_pos[i].f2_off);
    }
    while (q[cur_q].r_idx <= M && cur_q < K) {
        q[cur_q].res = search(q[cur_q].f1, q[cur_q].f2);
        cur_q += 1;
    }
    sort(q, q + K, q_idx_sorter);
    DEBUG_CMD({
        cout << "q[i].r_idx: ";
        for (int i = 0; i < K; ++i) {
            cout << q[i].r_idx << ' ';
        }
        cout << endl << "q[i].q_idx: ";
        for (int i = 0; i < K; ++i) {
            cout << q[i].q_idx << ' ';
        }
        cout << endl;
        cout << "f[i]: ";
        for (int i = 1; i <= N; ++i) {
            cout << f[i] << ' ';
        }
        cout << endl << "q[i].res: ";
        for (int i = 0; i < K; ++i) {
            cout << q[i].res << ' ';
        }
        cout << endl;
    });
    for (int i = 0; i < K; ++i) {
        cout << q[i].res << endl;
    }
    return 0;
};

#endif
