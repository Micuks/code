#ifndef _t4pe_20191219_
#define _t4pe_20191219_
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

struct ExchangePost {
    int u;
    int v;
    int next;
    double r;
    double c;
    ExchangePost(int u, int v, int next, double r, double c) : u(u), v(v), next(next), r(r), c(c) {}
    ExchangePost() {}
};
const int MAXEP = 1024;
int N, M, S;
double V;
ExchangePost ep[MAXEP];
int head[MAXEP];
int edge_cnt = 0;
int visited[MAXEP];

void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(int) * MAXEP);
    memset(visited, 0, sizeof(int) * MAXEP);
    return;
}

void add_ep(int a, int b, double rab, double cab, double rba, double cba)
{
    ep[edge_cnt].u = a;
    ep[edge_cnt].v = b;
    ep[edge_cnt].next = head[a];
    ep[edge_cnt].r = rab;
    ep[edge_cnt].c = cab;
    head[a] = edge_cnt++;

    ep[edge_cnt].u = b;
    ep[edge_cnt].v = a;
    ep[edge_cnt].next = head[b];
    ep[edge_cnt].r = rba;
    ep[edge_cnt].c = cba;
    head[b] = edge_cnt++;
}

bool dijkstra()
{
    double max_cash[MAXEP];
    // memset(max_cash, 0, sizeof(double) * MAXEP);
    for (int i = 0; i < MAXEP; ++i) {
        max_cash[i] = 0.0f;
    }
    int n = head[S];
    max_cash[S] = V;
    /*
    while (n != -1) {
        max_cash[ep[n].v] = (V - ep[n].c) * ep[n].r;
        n = ep[n].next;
    }
    */
    assert(edge_cnt == 2 * M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < edge_cnt; ++j) {
            if (max_cash[ep[j].u] != 0 &&
                max_cash[ep[j].v] < (max_cash[ep[j].u] - ep[j].c) * ep[j].r) {
                max_cash[ep[j].v] = (max_cash[ep[j].u] - ep[j].c) * ep[j].r;
                if (i == N - 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    int a, b;
    double rab, cab, rba, cba;
    init();
    cin >> N >> M >> S >> V;
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%lf%lf%lf%lf", &a, &b, &rab, &cab, &rba, &cba);
        add_ep(a, b, rab, cab, rba, cba);
    }
    bool res = dijkstra();
    if (res) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
};

#endif