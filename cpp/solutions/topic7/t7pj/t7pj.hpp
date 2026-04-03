#ifndef _t7pj_20201018_
#define _t7pj_20201018_
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
#include <stack>
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

#define mid ((l + r) / 2)
#define lson (now << 1)
#define rson ((now << 1) | 1)
void build(int now, int l, int r) {}
void update(int now, int l, int r) {}
void query(int now, int l, int r) {}
void debug_print(int now, int l, int r, int inc)
{
    for (int i = 0; i < inc; ++i) {
        printf("  ");
    }
    if (l == r) {
        printf("n:%d,%d-%d\n", now, l, r);
    }
    else {
        printf("n:%d,%d-%d\n", now, l, r);
        debug_print(lson, l, mid, inc + 1);
        debug_print(rson, mid + 1, r, inc + 1);
    }
}

const int MAXN = 5e4 + 21;
int T, N, M;
int u, v;
char lazy[MAXN];
int task[MAXN];
int head[MAXN];
int father[MAXN];
struct Employee {
    int v;
    int next;
} emp[MAXN];

int edge_cnt = 0;
void add_subordinate(int u, int v)
{
    father[v] = u;
    emp[edge_cnt].next = head[u];
    emp[edge_cnt].v = v;
    head[u] = edge_cnt++;
}

void init_graph()
{
    memset(head, -1, sizeof(head));
    memset(father, -1, sizeof(father));
    memset(task, -1, sizeof(task));
    memset(lazy, 0, sizeof(lazy));
    edge_cnt = 0;
}

void pushdown(int now)
{
    int fnode = father[now];
    if (fnode != -1) {
        pushdown(fnode);
        // int &ftid = emp[fnode].task;
        int ftid = task[fnode];
        if (ftid != -1 && lazy[fnode]) {
            for (int sub_id = head[fnode]; sub_id != -1; sub_id = emp[sub_id].next) {
                task[emp[sub_id].v] = ftid;
                lazy[emp[sub_id].v] = 1;
            }
            lazy[fnode] = 0;
        }
        // ftid = -1;
    }
}
int query(int now)
{
    pushdown(now);
    return task[now];
    /*
    int fnode = father[now];
    for (int sub_id = head[fnode]; sub_id != -1; sub_id = emp[sub_id].next) {
        if (emp[sub_id].v == now) {
            return task[now];
        }
    }
    return -1;
    */
}

void assign_task(int now, int tid)
{
    pushdown(now);
    task[now] = tid;
    lazy[now] = 1;
    /*
    int fnode = father[now];
    for (int sub_id = head[fnode]; sub_id != -1; sub_id = emp[sub_id].next) {
        if (emp[sub_id].v == now) {
            task[now] = tid;
            return;
        }
    }
    */
}

int main(int argc, char **argv)
{
    cin >> T;
    string op;
    int case_cnt = 0;
    int now, tid;
    while (T--) {
        scanf("%d", &N);
        init_graph();
        for (int i = 1; i < N; ++i) {
            scanf("%d%d", &u, &v);
            add_subordinate(v, u);
        }
        _DEBUG_CMD({
            printf("father[%d]:%d\n", 3, father[3]);
            for (int sub_id = head[father[3]]; sub_id != -1; sub_id = emp[sub_id].next) {
                printf("emp[%d]:%d, task:%d\n", sub_id, emp[sub_id].v, task[emp[sub_id].v]);
            }
        });
        scanf("%d", &M);
        printf("Case #%d:\n", ++case_cnt);
        for (int i = 0; i < M; ++i) {
            cin >> op;
            _DEBUG_CMD(printf("get an op:%s\n", op.c_str()));
            if (op[0] == 'C') {
                cin >> now;
                printf("%d\n", query(now));
            }
            else {
                cin >> now >> tid;
                assign_task(now, tid);
            }
            _DEBUG_CMD({
                if (i == 2) {
                    printf("father[%d]:%d\n", 3, father[3]);
                    for (int sub_id = head[father[3]]; sub_id != -1; sub_id = emp[sub_id].next) {
                        printf("emp[%d]:%d, task:%d\n", sub_id, emp[sub_id].v, task[emp[sub_id].v]);
                    }
                }
            });
        }
    }
    return 0;
};

#endif
