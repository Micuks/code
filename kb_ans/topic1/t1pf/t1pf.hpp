#ifndef _t1pf_20191205_
#define _t1pf_20191205_
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
#include <vector>
using namespace std;

int ori[101];
int dst[101];
char prime[10000];
char visited[10000];
int n;

struct State {
    State(int time, int count) : tc(time), cur(count) {}
    int tc;
    int cur;
};

int bfs(int case_idx)
{
    int tc = 0;
    int start = ori[case_idx];
    int end = dst[case_idx];
    queue<State> mqueue;
    visited[start] = -1;
    State s = State(0, start);
    mqueue.push(s);

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        if (s.cur == end) {
            return s.tc;
        }
        int offset = 1;
        for (int i = 0; i < 4; ++i) {
            int cur = s.cur;
            int digit = ((cur / offset) % 10);
            for (int j = 0; j < 10; ++j) {
                int new_cur = cur - digit * offset + j * offset;
                if (new_cur != cur && prime[new_cur] && visited[new_cur] == 0 && new_cur >= 1000) {
                    visited[new_cur] = s.tc + 1;
                    mqueue.push(State(s.tc + 1, new_cur));
                }
            }
            offset = offset * 10;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    cin >> n;
    memset(prime, 0, 10000);
    for (int i = 2; i < 10000; ++i) {
        int upper_limit = static_cast<int>(sqrt(i));
        int is_prime = 1;
        for (int j = 2; j <= upper_limit; ++j) {
            if (prime[j] && (i % j) == 0)
                is_prime = 0;
        }
        prime[i] = is_prime;
    }
    for (int i = 0; i < n; ++i) {
        cin >> ori[i] >> dst[i];
        memset(visited, 0, 10000);
        cout << bfs(i) << endl;
    }
    return 0;
};

#endif
