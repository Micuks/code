#ifndef _t1ph_20191205_
#define _t1ph_20191205_
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
    vector<string> ops;
    int a_rem;
    int b_rem;
    State(vector<string> ret, int a, int b) : ops(ret), a_rem(a), b_rem(b) {}
    bool operator<(const State &s1) const
    {
        if (this->a_rem < s1.a_rem) {
            return true;
        }
        else if (this->a_rem > s1.a_rem) {
            return false;
        }
        else {
            if (this->b_rem < s1.b_rem) {
                return true;
            }
            else if (this->b_rem > s1.b_rem) {
                return false;
            }
        }
        return false;
    }
};

vector<string> bfs(int a, int b, int c)
{
    queue<State> mqueue;
    State s(vector<string>(), 0, 0);
    set<State> travelled;
    mqueue.push(s);
    char buf[1024];

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        if (travelled.find(s) != travelled.end()) {
            continue;
        }
        travelled.insert(s);

        if (s.a_rem == c || s.b_rem == c) {
            return s.ops;
        }
        vector<string> ops;
        int can_pour;

        // FILL
        ops = s.ops;
        ops.push_back("FILL(1)");
        mqueue.push(State(ops, a, s.b_rem));

        ops = s.ops;
        ops.push_back("FILL(2)");
        mqueue.push(State(ops, s.a_rem, b));

        // DROP
        ops = s.ops;
        ops.push_back("DROP(1)");
        mqueue.push(State(ops, 0, s.b_rem));

        ops = s.ops;
        ops.push_back("DROP(2)");
        mqueue.push(State(ops, s.a_rem, 0));

        // POUR
        ops = s.ops;
        ops.push_back("POUR(1,2)");
        can_pour = min(s.a_rem, b - s.b_rem);
        mqueue.push(State(ops, s.a_rem - can_pour, s.b_rem + can_pour));

        ops = s.ops;
        can_pour = min(a - s.a_rem, s.b_rem);
        ops.push_back("POUR(2,1)");
        mqueue.push(State(ops, s.a_rem + can_pour, s.b_rem - can_pour));
    }

    return vector<string>();
}

int main(int argc, char **argv)
{
    int a, b, c;
    cin >> a >> b >> c;
    vector<string> ret = bfs(a, b, c);
    if (ret.size() == 0) {
        cout << "impossible" << endl;
        return 0;
    }
    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    return 0;
};

#endif
