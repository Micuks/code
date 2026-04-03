#ifndef _t1pg_20191205_
#define _t1pg_20191205_
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

struct State {
    string s1;
    string s2;
    int step;
    State(string s1, string s2, int step) : s1(s1), s2(s2), step(step) {}
};

int bfs(int step_limit, string s1, string s2, string dst)
{
    State s(s1, s2, 1);
    queue<State> mqueue;
    set<string> travelled;
    mqueue.push(s);
    size_t len_s1 = s1.size();
    size_t len_s2 = s2.size();
    assert(len_s1 == len_s2);

    size_t stack_size = dst.size();
    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        string new_stack(stack_size, 0);
        for (int i = 0; i < len_s1; ++i) {
            new_stack[2 * i] = s.s2[i];
            new_stack[2 * i + 1] = s.s1[i];
        }
        if (new_stack == dst) {
            return s.step;
        }
        if (travelled.find(new_stack) == travelled.end()) {
            mqueue.push(
                State(new_stack.substr(0, len_s1), new_stack.substr(len_s1, len_s1), s.step + 1));
            travelled.insert(new_stack);
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    int N;
    cin >> N;
    string s1;
    string s2;
    string dst;

    int c;
    for (int i = 0; i < N; ++i) {
        cin >> c >> s1 >> s2 >> dst;
        cout << i + 1 << ' ' << bfs(c, s1, s2, dst) << endl;
    }
    return 0;
};

#endif
