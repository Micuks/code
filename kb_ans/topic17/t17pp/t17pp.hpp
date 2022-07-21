#ifndef _t17pp_20200822_
#define _t17pp_20200822_
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

int n, m, k;
int dmd[1 << 4];
const int TRIE_WIDTH = 1 << 6; // 50
double distant[TRIE_WIDTH][TRIE_WIDTH];
double xarr[TRIE_WIDTH], yarr[TRIE_WIDTH];
namespace AC {
const int MAXT = 1 << 9; // 500
int trie[MAXT][TRIE_WIDTH], trie_cnt;
int fail[MAXT], val[MAXT];
string dbgstr[MAXT];
void init()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(val, 0, sizeof(val));
    trie_cnt = 0;
    dbgstr[0] = "";
}
void insert(int *s, int len)
{
    int u = 0;
    for (int i = 0; i < len; ++i) {
        if (trie[u][s[i] - 1] == 0) {
            trie[u][s[i] - 1] = ++trie_cnt;
            dbgstr[trie_cnt] = dbgstr[u] + to_string(s[i]) + ", ";
        }
        u = trie[u][s[i] - 1];
    }
    val[u] = 1;
}
void build()
{
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        val[u] |= val[fail[u]];

        for (int i = 0; i < n; ++i) {
            int &n = trie[u][i];
            if (n != 0) {
                fail[n] = trie[fail[u]][i];
                q.push(n);
            }
            else {
                n = trie[fail[u]][i];
            }
        }
    }
}
double query(int dst)
{
    const size_t len = n * (trie_cnt + 1);
    double dist[n][trie_cnt + 1];
    // bool visited[n][trie_cnt + 1];
    fill_n(&dist[0][0], len, 1e30f);
    // fill_n(&visited[0][0], len, false);

    int u = trie[0][0];
    dist[0][u] = 0;

    double ret = 1e30f;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j <= trie_cnt; ++j) {
            /*
            int u = trie[i][j];
            if (val[u] != 0) {
                continue;
            }
            */
            for (int k = i + 1; k < n; ++k) {
                int nu = trie[j][k];
                if (val[nu] != 0) {
                    continue;
                }
                dist[k][nu] = min(dist[k][nu], dist[i][j] + distant[k][i]);
            }
        }
    }

    /*
    int min_idx;
    int min_state;
    double min_dist;


    for (int i = 0; i < len; ++i) {
        min_dist = 1e30f;
        min_idx = TRIE_WIDTH;
        min_state = MAXT;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k <= trie_cnt; ++k) {
                if (!visited[j][k] && min_dist > dist[j][k] && val[k] == 0) {
                    _DEBUG_CMD({
                        printf("failure unexpceted on selecting relaxation node: "
                               "visited[%d][%d]:%d min_dist:%3.2e "
                               "dist[%d][%d]:%3.2e val[%d]:%d\n",
                               j, k, visited[j][k], min_dist, j, k, dist[j][k], k, val[k]);
                    });
                    min_dist = dist[j][k];
                    min_idx = j;
                    min_state = k;
                }
            }
        }
        visited[min_idx][min_state] = true;
        for (int j = 0; j < n; ++j) {
            if (j <= min_idx) {
                continue;
            }
            int nxt_stat = trie[min_state][j];
            int nxt_node = nxt_stat + j * (trie_cnt + 1);

            if (!visited[j][nxt_stat] && val[nxt_stat] == 0 &&
                dist[j][nxt_stat] > min_dist + distant[j][min_idx]) {
                _DEBUG_CMD({
                    printf("on updating node dist: dist[%d][%d]:%3.2e > min_dist:%3.2e + "
                           "distant[%d][%d]:%3.2e val[%d]:%d\n",
                           j, nxt_stat, dist[j][nxt_stat], min_dist, j, min_idx,
                           distant[j][min_idx], nxt_stat, val[nxt_stat]);
                });
                dist[j][nxt_stat] = min_dist + distant[j][min_idx];
            }
        }
    }
    _DEBUG_CMD({
        printf("trie_tree[trie_cnt][n]:\n");
        for (int i = 0; i <= trie_cnt; ++i) {
            printf("dbgstr[%d]:%s ", i, dbgstr[i].c_str());
            for (int j = 0; j < n; ++j) {
                if (trie[i][j]) {
                    printf("trie[%d][%d]:%d ", i, j, trie[i][j]);
                }
            }
            printf("\n");
        }
    });
    _DEBUG_CMD({
        printf("dist[n][trie_cnt+1]: \n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= trie_cnt; ++j) {
                printf("%3.2e ", dist[i][j]);
            }
            printf("\n");
        }
    });
    _DEBUG_CMD({
        printf("val[trie_cnt+1]: \n");
        for (int i = 0; i <= trie_cnt; ++i) {
            printf("%d ", val[i]);
        }
        printf("\n");
    });
    */
    for (int i = 0; i <= trie_cnt; ++i) {
        // const int idx = i + dst * (trie_cnt + 1);
        if (val[i] == 0) {
            _DEBUG_CMD(printf("on searching return value: guess who's shorter? ret:%3.2e, "
                              "dist[%d][%d]:%3.2e\n",
                              ret, dst, i, dist[dst][i]););
            ret = min(ret, dist[dst][i]);
        }
    }

    return ret >= 1e30f ? -1.0f : ret;
}
}; // namespace AC

double get_dist(double x1, double y1, double x2, double y2)
{
    return sqrt(double(x1 - x2) * (x1 - x2) + double(y1 - y2) * (y1 - y2));
}
int main(int argc, char **argv)
{
    _DEBUG_CMD(printf("1e30<3:%d 1e30>=3:%d\n", 1e30f < 3, 1e30f >= 3));
    // while (cin >> n >> m && n && m) {
    while (~scanf("%d%d", &n, &m) && n && m) {
        AC::init();
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &xarr[i], &yarr[i]);
            for (int j = 0; j < i; ++j) {
                distant[i][j] = distant[j][i] = get_dist(xarr[i], yarr[i], xarr[j], yarr[j]);
            }
        }
        _DEBUG_CMD({
            printf("distances[%d][%d]:\n", n, n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j <= i; ++j) {
                    printf("%3.2e ", distant[i][j]);
                }
                printf("\n");
            }
        });
        _DEBUG_CMD({ printf("get dmd:\n"); });
        for (int i = 0; i < m; ++i) {
            scanf("%d", &k);
            for (int j = 0; j < k; ++j) {
                scanf("%d", &dmd[j]);
                _DEBUG_CMD({ printf("dmd[%d]:%d ", j, dmd[j]); });
            }
            AC::insert(dmd, k);
            _DEBUG_CMD({ printf("\n"); });
        }
        AC::build();
        double ret = AC::query(n - 1);
        if (ret == -1.0f) {
            printf("Can not be reached!\n");
        }
        else {
            printf("%.2lf\n", ret);
        }
    }
    return 0;
};

#endif
