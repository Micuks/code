#if 0
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 500 + 100;
const int MAXM = 2000 + 100;
int F[MAXN]; //父节点
int v[MAXN]; // v[i]=x表示节点i与其父节点的大小关系

int findset(int i)
{
    if (F[i] == -1)
        return i;
    int temp = findset(F[i]);
    v[i] += v[F[i]];
    v[i] %= 3;
    return F[i] = temp;
}
void bind(int i, int j, int temp)
{
    int fa = findset(i);
    int fb = findset(j);
    if (fa != fb) {
        F[fb] = fa;
        v[fb] = (v[i] - temp - v[j] + 3 * 3) % 3;
    }
}
struct command {
    int a, temp, b;
} coms[MAXM];
bool judge[MAXN]; // judge[i]=true 表示i可以作为裁判
int pos[MAXN];    //保存在第几步可判断i是裁判
int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {

        for (int i = 0; i < m; i++) {
            char c;
            scanf("%d%c%d", &coms[i].a, &c, &coms[i].b);
            if (c == '=')
                coms[i].temp = 0;
            else if (c == '>')
                coms[i].temp = 1;
            else if (c == '<')
                coms[i].temp = 2;
        }

        memset(
            pos, -1,
            sizeof(
                pos)); // pos[i]=x表示i作为裁判的时候,第x位置会出问题,如果x=-1则表示i左裁判不会出问题
        memset(judge, 1, sizeof(judge));
        for (int i = 0; i < n; i++) //假设i为裁判
        {
            memset(F, -1, sizeof(F));
            memset(v, 0, sizeof(v));
            for (int j = 0; j < m; j++) {
                int a, b, temp;
                a = coms[j].a;
                b = coms[j].b;
                temp = coms[j].temp;
                if ((a == i || b == i)) //有关i的命令都跳过
                    continue;
                else // ab不含裁判i
                {
                    int fa = findset(a);
                    int fb = findset(b);
                    if (fa == fb) //同一分量
                    {
                        if ((v[b] + temp) % 3 != v[a]) //不合法
                        {
                            judge[i] = false;
                            pos[i] = j + 1;
                            // printf("pos[%d]=%d\n",i,j);
                            break;
                        }
                    }
                    else //不同连通分量
                    {
                        bind(a, b, temp);
                    }
                }
            }
        }
        int tot = 0; //记录有多少个裁判
        int judge_i;
        int max_p = 0; //所有出错裁判的最大错误位置
        for (int i = 0; i < n; i++) {
            if (judge[i]) // i可以作为裁判
            {
                tot++;
                judge_i = i;
            }
            else
                max_p = max(max_p, pos[i]); //找到所有出错裁判的最大错误位置
        }
        if (tot == 0)
            printf("Impossible\n");
        else if (tot == 1)
            printf("Player %d can be determined to be the judge after %d lines\n", judge_i, max_p);
        else if (tot > 1)
            printf("Can not determine\n");
    }
    return 0;
}

#else
#ifndef _t5pk_20200105_
#define _t5pk_20200105_
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

const int MAXN = 512;
const int MAXQ = 2048;
int N, M;
int f[MAXN], v[MAXN], jflag[MAXN];
int ff[MAXN], vv[MAXN];
int A[MAXQ], B[MAXQ], D[MAXQ];

int findf(int x)
{
    if (ff[x] == x) {
        return x;
    }
    int tmp = findf(ff[x]);
    vv[x] = vv[ff[x]] + vv[x];
    return ff[x] = tmp;
}

bool union_setv(int x, int y, int relation)
{
    int xroot = findf(x);
    int yroot = findf(y);
    if (xroot == yroot) {
        return (vv[x] - vv[y] + relation + 3) % 3 == 0;
    }
    vv[yroot] = (vv[x] - vv[y] + relation + 3) % 3;
    ff[yroot] = xroot;
    return true;
}

int find(int x)
{
    if (f[x] == x) {
        return x;
    }
    int tmp = find(f[x]);
    v[x] = v[f[x]] + v[x];
    return f[x] = tmp;
}

bool union_set(int x, int y, int relation)
{
    int xroot = find(x);
    int yroot = find(y);
    if (xroot == yroot) {
        return (v[x] - v[y] + relation + 3) % 3 == 0;
    }
    v[yroot] = (v[x] - v[y] + relation + 3) % 3;
    f[yroot] = xroot;
    return true;
}

bool is_zero(int x) { return x == 0; }
void init()
{
    for (int i = 0; i <= N; ++i) {
        f[i] = i;
        ff[i] = i;
        v[i] = 0;
        vv[i] = 0;
    }
}

int main(int argc, char **argv)
{
    int a, b;
    char rel;
    while (cin >> N >> M) {
        int err_cnt[MAXN];
        int first_conflict_detected_cnt = 0;
        int available_judge_cnt = 0;
        int judge_idx = 0;
        int judge_pos = 0;
        int judge_err_idx = 0;
        memset(err_cnt, 0, sizeof(err_cnt));
        for (int i = 0; i < M; ++i) {
            int prev_cmp = i;
            int prev_rel = 0;
            scanf("%d%c%d", &A[i], &rel, &B[i]);
            switch (rel) {
                case '=':
                    D[i] = 0;
                    break;
                case '>':
                    D[i] = -1;
                    break;
                case '<':
                    D[i] = 1;
                    break;
            }
        }
        for (int i = 0; i < N; ++i) {
            bool available = true;
            init();
            for (int j = 0; j < M; ++j) {
                if (A[j] == i || B[j] == i) {
                    continue;
                }
                if (!union_set(A[j], B[j], D[j]) && available) {
                    available = false;
                    err_cnt[i] = j + 1;
                    break;
                }
            }
            if (available) {
                judge_idx = i;
                _DEBUG_CMD({
                    cout << "judge " << i << "," << judge_idx << " is available";
                    cout << "first_conflict_detected_cnt: " << first_conflict_detected_cnt << endl;
                });
                ++available_judge_cnt;
            }
        }
        int err_idx = 0;
        for (int i = 0; i < N; ++i) {
            err_idx = max(err_idx, err_cnt[i]);
        }
        if (available_judge_cnt == 0) {
            printf("Impossible\n");
        }
        else if (available_judge_cnt == 1) {
            printf("Player %d can be determined to be the judge after %d lines\n", judge_idx,
                   err_idx);
        }
        else {
            printf("Can not determine\n");
        }
    };
    return 0;
};

#endif
#endif
