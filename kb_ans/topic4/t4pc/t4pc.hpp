#ifndef _t4pc_20191214_
#define _t4pc_20191214_
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

struct Edge {
    int to;
    int next;
    int val;
};
const int MAX = 0x3F3F3F3F;
const size_t MAX_NODE_CNT = 1024;
const size_t MAX_EDGE_CNT = MAX_NODE_CNT * MAX_NODE_CNT;
Edge edge[MAX_EDGE_CNT];
int head[MAX_NODE_CNT];
int visited[MAX_NODE_CNT];
int max_weight[MAX_NODE_CNT];
int edge_cnt = 0;
int roadmap[MAX_NODE_CNT][MAX_NODE_CNT];

void init()
{
    edge_cnt = 0;
    memset(head, -1, sizeof(int) * MAX_NODE_CNT);
    memset(visited, 0, sizeof(int) * MAX_NODE_CNT);
    memset(max_weight, 0, sizeof(int) * MAX_NODE_CNT);
    memset(roadmap, 0, sizeof(int) * MAX_NODE_CNT * MAX_NODE_CNT);
}

void add_edge(int u, int v, int val)
{
    roadmap[u][v] = val;
    roadmap[v][u] = val;

    edge[edge_cnt].to = v;
    edge[edge_cnt].next = head[u];
    edge[edge_cnt].val = val;
    head[u] = edge_cnt;
    ++edge_cnt;

    edge[edge_cnt].to = u;
    edge[edge_cnt].next = head[v];
    edge[edge_cnt].val = val;
    head[v] = edge_cnt;
    ++edge_cnt;
}

int dijkstra(int nc, int ec)
{
    visited[1] = 1;
    int n = head[1];
    while (n != -1) {
        max_weight[edge[n].to] = max(max_weight[edge[n].to], edge[n].val);
        n = edge[n].next;
    }
    for (int i = 1; i < nc; ++i) {
        int max_capacity = 0;
        int idx;
        for (int j = 1; j <= nc; ++j) {
            if (!visited[j] && max_weight[j] > max_capacity) {
                idx = j;
                max_capacity = max_weight[j];
            }
        }
        visited[idx] = 1;
        for (int j = 1; j <= nc; ++j) {
            if (j == idx) {
                continue;
            }
            int dis_idx_to_j = 1;
            /*
            n = head[idx];
            while (n != -1) {
                if (edge[n].to == j && edge[n].val > dis_idx_to_j) {
                    dis_idx_to_j = edge[n].val;
                }
                n = edge[n].next;
            }
            */
            if (!visited[j] && dis_idx_to_j != 0 &&
                max_weight[j] < min(max_capacity, roadmap[idx][j])) {
                max_weight[j] = min(max_capacity, roadmap[idx][j]);
            }
        }
    }
    return max_weight[nc];
}

int main(int argc, char **argv)
{
    int case_cnt;
    int ec, nc;
    int s, e, val;
    cin >> case_cnt;
    for (int i = 0; i < case_cnt; ++i) {
        init();
        cin >> nc >> ec;
        for (int j = 0; j < ec; ++j) {
            scanf("%d%d%d", &s, &e, &val);
            /// cin >> s >> e >> val;
            add_edge(s, e, val);
        }
        int res = dijkstra(nc, ec);
        printf("Scenario #%d:\n%d\n\n", i + 1, res);
    }
    return 0;
};

#endif
