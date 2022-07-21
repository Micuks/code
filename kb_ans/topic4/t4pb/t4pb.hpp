#ifndef _t4pb_20191211_
#define _t4pb_20191211_
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

typedef pair<int, int> point_t;
const int MAX = 0x3F3F3F3F;
const int MAX_EDGE = 200000;
const int MAX_NODE = 1000;
int head[MAX_NODE];
template <typename T> struct Edge {
    int to;
    int next;
    T val;
};
Edge<point_t> edge[MAX_EDGE];
size_t edge_cnt = 0;

template <typename T> void add_edge(int from, int to, const T &val)
{
    edge[edge_cnt].to = to;
    edge[edge_cnt].next = head[from];
    edge[edge_cnt].val = val;
    head[from] = edge_cnt++;

    edge[edge_cnt].to = from;
    edge[edge_cnt].next = head[to];
    edge[edge_cnt].val = val;
    head[to] = edge_cnt++;
}

int visited[MAX_NODE];
float dist[MAX_NODE];
void initial()
{
    edge_cnt = 0;
    memset(visited, 0, sizeof(int) * MAX_NODE);
    memset(head, -1, sizeof(int) * MAX_NODE);
}

float dijkstra(int node_cnt)
{
    // int i = 1;
    visited[0] = 1;
    int n = head[0];
    while (n != -1) {
        dist[edge[n].to] =
            sqrt(edge[n].val.first * edge[n].val.first + edge[n].val.second * edge[n].val.second);
        n = edge[n].next;
    }
    for (int i = 1; i < node_cnt; ++i) {
        float min_val = MAX;
        int idx;
        for (int j = 0; j < node_cnt; ++j) {
            if (!visited[j] && dist[j] < min_val) {
                min_val = dist[j];
                idx = j;
            }
        }
        visited[idx] = 1;
        for (int j = 0; j < node_cnt; ++j) {
            if (j == idx) {
                continue;
            }
            int edge_idx_2_j = head[idx];
            while (edge_idx_2_j != -1 && edge[edge_idx_2_j].to != j) {
                edge_idx_2_j = edge[edge_idx_2_j].next;
            }
            assert(edge_idx_2_j != -1);
            float dist_idx_2_j =
                sqrt(edge[edge_idx_2_j].val.first * edge[edge_idx_2_j].val.first +
                     edge[edge_idx_2_j].val.second * edge[edge_idx_2_j].val.second);
            if (!visited[j] && dist[j] > max(dist_idx_2_j, dist[idx])) {
                dist[j] = max(dist_idx_2_j, dist[idx]);
            }
        }
    }
    return dist[1];
}

int main(int argc, char **argv)
{
    int n;
    int case_cnt = 1;
    while (cin >> n && n != 0) {
        initial();
        int xi, yi;
        for (int i = 0; i < n; ++i) {
            cin >> xi >> yi;
            Edge<point_t> &e = edge[edge_cnt];
            e.to = edge_cnt;
            e.next = -1;
            e.val = point_t(xi, yi);
            head[edge_cnt] = edge_cnt++;
        }
        int added_edge_cnt = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                add_edge(i, j,
                         point_t(edge[i].val.first - edge[j].val.first,
                                 edge[i].val.second - edge[j].val.second));
                added_edge_cnt++;
            }
        }
        float distance = dijkstra(n);
        printf("Scenario #%d\n", case_cnt++);
        printf("Frog Distance = %.3f\n\n", distance);
    }
    return 0;
};

#endif
