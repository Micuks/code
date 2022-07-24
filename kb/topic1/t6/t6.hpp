#ifndef _t6_20220724_
#define _t6_20220724_
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
const int MAXN = 100000;
int visited[MAXN];
int best_cost = MAXN;

bool isPrime(int num) {
    int n = static_cast<int>(sqrt(num)) + 1;
    for (int i = 2; i < n; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

class State {
  public:
    int number;
    int cost;
    State() : number(-1), cost(0) {}
    State(const int &_number, const int &_cost)
        : number(_number), cost(_cost) {}
    State(const State &_state) : number(_state.number), cost(_state.cost) {}
};

int qpow(int b, int p) {
    int ans = 1;
    while(p) {
        if(p&0x1)
            ans *= b;
        b *= b;
        p>>=1;
    }
    return ans;
}

int ireplace(int num, int offset, int k) {
    offset = qpow(10, offset);
    return num / (offset * 10) * (offset * 10) + num % offset + k * offset;
}

int bfs(int begin, int end) {
    queue<State> q;
    memset(visited, 0, sizeof(visited));
    visited[begin] = 1;
    q.push(State(begin, 0));
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        if (s.number == end) {
            return s.cost;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 10; j++) {
                int a = ireplace(s.number, i, j); //第i 位替换为j
                if (a >= 1000 && a != s.number && !visited[a] && isPrime(a)) {
                    visited[a] = 1;
                    q.push(State(a, s.cost + 1));
                }
            }
        }
    }
    return MAXN;
}

int main(int argc, char **argv) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        best_cost = MAXN;
        int begin, end;
        scanf("%d%d", &begin, &end);
        best_cost = bfs(begin, end);
        if (best_cost < MAXN) {
            cout << best_cost << endl;
        } else {
            cout << "Impossible\n";
        }
    }
    return 0;
};

#endif
