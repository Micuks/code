#if 0
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

#define inf 100000000

int const maxn = 16;

struct node
{
    int t,s;  //分别代表当前状态下的时间以及罚时
    int p,N;  //p和N用来记录完成作业的次序
}dp[1<<maxn];

int d[maxn],c[maxn];  //deal和const
char name[maxn][105];

int main()
{
    int t,N,s;//s是当前的状态
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&N);
        for(int i = 0 ; i < N ; i++)
        {
            scanf("%s%d%d",name[i],&d[i],&c[i]);
        }
        s = 1<<N ;
        for(int i = 1 ; i < s ; i++)
        {
            //i为当前状态
            dp[i].s = inf ;
            for(int j = N-1 ; j >= 0 ; j--)
            {
                int t = 1<<j ;  //j的状态
                if(i&t)
                {
                    int p = i - t ;                  //p为i出去j之前的状态
                    int so = dp[p].t + c[j] - d[j] ; //当前时间加上所需时间减去截止时间
                    if(so<0)so=0;                    //此时说明没有超出截止时间
                    if(dp[p].s+so < dp[i].s)
                    {
                        //如果前一个状态所花的时间和当前状态花的时间小于  已经确定的值，那么这样一种方法更省时
                        dp[i].s = dp[p].s+so;
                        dp[i].t = dp[p].t+c[j];
                        dp[i].N = j ;
                        dp[i].p = p ;
                    }
                }
            }
        }
        s--;
        printf("%d\N",dp[s].s);
        stack <int> S;
        while(s)
        {
            S.push(dp[s].N);
            s = dp[s].p;
        }
        while(!S.empty())
        {
            printf("%s\N",name[S.top()]);
            S.pop();
        }
    }
    return 0;
}
#else
#ifndef _t12pd_20200121_
#define _t12pd_20200121_
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

int T, N;
// map<string, int> dp;
struct Course {
    string cname;
    int ddl, cost;
    Course(const string &cname = "", int ddl = 0, int cost = 0) : cname(cname), ddl(ddl), cost(cost)
    {
    }
    Course &operator=(const Course &c)
    {
        cname = c.cname;
        ddl = c.ddl;
        cost = c.cost;
    }
    bool operator<(const Course &c) const
    {
        if (this->ddl < c.ddl) {
            return true;
        }
        else if (this->ddl == c.ddl) {
            if (this->cost > c.cost) {
                return true;
            }
            else if (this->cost == c.cost) {
                return this->cname < c.cname;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
};

const int INF = 0x3F3F3F3F;
const int MAXN = 16;
struct State {
    int prev, select;
    int tc, t;
} state[1 << MAXN];
// int dp[MAXN];

int main(int argc, char **argv)
{
    cin >> T;
    while (T--) {
        char cname[128];
        int d, c;
        cin >> N;
        vector<Course> courses;
        courses.reserve(N);
        for (int i = 0; i < N; ++i) {
            scanf("%s%d%d", cname, &d, &c);
            courses.push_back(Course(cname, d, c));
        }
        memset(state, 0, sizeof(state));
        for (int i = 1; i < (1 << N); ++i) {
            state[i].tc = INF;
        }
        for (int i = 0; i < (1 << N); ++i) {
            // int pos = i == 0 ? 0 : (1 << i);
            for (int j = 0; j < N; ++j) {
                int pos = (1 << j);
                if (!(pos & i)) {
                    const Course &c = courses[j];
                    int new_idx = pos + i;
                    int new_t = state[i].t + c.cost;
                    int new_tc = state[i].tc;
                    new_tc += (state[i].t + c.cost > c.ddl) ? (state[i].t + c.cost - c.ddl) : 0;
                    _DEBUG_CMD({
                        if (i == 0 && pos == 1 && false) {
                            printf("i==0, pos == 1, new_idx:%d, state[%d].tc:%d, new_tc:%d\n",
                                   new_idx, new_idx, state[new_idx].tc, new_tc);
                        }
                        if ((i == 3 && pos == 4) || (i == 5 && pos == 2)) {
                            printf("i==%d, pos == %d, new_idx:%d, state[%d].tc:%d, new_tc:%d\n", i,
                                   pos, new_idx, new_idx, state[new_idx].tc, new_tc);
                        }
                    });
                    if (state[new_idx].tc > new_tc ||
                        (state[new_idx].tc == new_tc &&
                         (c.cname > courses[state[new_idx].select].cname || i == 0))) {
                        state[new_idx].prev = i;
                        state[new_idx].tc = new_tc;
                        state[new_idx].t = new_t;
                        state[new_idx].select = j;
                    }
                }
            }
        }
        _DEBUG_CMD({
            for (int i = 0; i < N; ++i) {
                printf("courses[%d]: name: %s cost: %d ddl: %d\n", i, courses[i].cname.c_str(),
                       courses[i].cost, courses[i].ddl);
            }
            for (int i = 0; i < (1 << N); ++i) {
                printf("state[%d]: prev:%d select:%d tc:%d t:%d\n", i, state[i].prev,
                       state[i].select, state[i].tc, state[i].t);
            }
            printf("1<<N:%d state[1<<N - 1].select:%d\n", (1 << N), state[(1 << N) - 1].select);
        });
        // int start = state[((1 << N) - 1)].select;
        int start = (1 << N) - 1;
        stack<int> mstack;
        printf("%d\n", state[start].tc);
        do {
            // mstack.push(start);
            mstack.push(state[start].select);
            start = state[start].prev;
        } while (start != 0);
        while (!mstack.empty()) {
            int prev = mstack.top();
            printf("%s\n", courses[prev].cname.c_str());
            mstack.pop();
        }
    }
    return 0;
};

#endif
#endif
