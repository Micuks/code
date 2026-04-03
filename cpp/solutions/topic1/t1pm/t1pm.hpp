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

#define return_on_partial_order(x)                                                                 \
    if (this->x < s1.x)                                                                            \
        return true;                                                                               \
    if (this->x > s1.x)                                                                            \
        return false;
struct State {
    int td;
    int tc;
    int s_rem;
    int n_rem;
    int m_rem;
    State(int td, int tc, int s_rem, int n_rem, int m_rem)
        : td(td), tc(tc), s_rem(s_rem), n_rem(n_rem), m_rem(m_rem)
    {
    }
    bool operator<(const State &s1) const
    {
        return_on_partial_order(s_rem);
        return_on_partial_order(n_rem);
        return_on_partial_order(m_rem);
        return false;
    }
};

int bfs(int sc, int n, int m)
{
    if (sc % 2) {
        return -1;
    }
    int target = sc / 2;
    int can_pour = 0;
    queue<State> mqueue;
    State s(0, 0, sc, 0, 0);
    set<State> travelled;
    mqueue.push(s);

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        if (travelled.find(s) != travelled.end()) {
            continue;
        }
        travelled.insert(s);

        if ((s.s_rem == target && s.n_rem == target) || (s.s_rem == target && s.m_rem == target) ||
            (s.n_rem == target && s.m_rem == target)) {
            return s.tc;
        }
        /*
        if (s.td == target) {
            return s.tc + static_cast<int>(s.s_rem != 0) + static_cast<int>(s.n_rem != 0) +
                   static_cast<int>(s.m_rem != 0);
        }
        */
        // DROP
        /*
        if (s.s_rem + s.td <= target) {
            mqueue.push(State(s.s_rem + s.td, s.tc + 1, 0, s.n_rem, s.m_rem));
        }
        if (s.n_rem + s.td <= target) {
            mqueue.push(State(s.n_rem + s.td, s.tc + 1, s.s_rem, 0, s.m_rem));
        }
        if (s.m_rem + s.td <= target) {
            mqueue.push(State(s.m_rem + s.td, s.tc + 1, s.s_rem, s.n_rem, 0));
        }
        */
        // POUR
        // s -> n
        can_pour = min(s.s_rem, n - s.n_rem);
        mqueue.push(State(s.td, s.tc + 1, s.s_rem - can_pour, s.n_rem + can_pour, s.m_rem));
        // s -> m
        can_pour = min(s.s_rem, m - s.m_rem);
        mqueue.push(State(s.td, s.tc + 1, s.s_rem - can_pour, s.n_rem, s.m_rem + can_pour));
        // n -> s
        can_pour = min(sc - s.s_rem, s.n_rem);
        mqueue.push(State(s.td, s.tc + 1, s.s_rem + can_pour, s.n_rem - can_pour, s.m_rem));
        // n -> m
        can_pour = min(s.n_rem, m - s.m_rem);
        mqueue.push(State(s.td, s.tc + 1, s.s_rem, s.n_rem - can_pour, s.m_rem + can_pour));
        // m -> s
        can_pour = min(sc - s.s_rem, s.m_rem);
        mqueue.push(State(s.td, s.tc + 1, s.s_rem + can_pour, s.n_rem, s.m_rem - can_pour));
        // m -> n
        can_pour = min(n - s.n_rem, s.m_rem);
        mqueue.push(State(s.td, s.tc + 1, s.s_rem, s.n_rem + can_pour, s.m_rem - can_pour));
        // POUR
    }

    return -1;
}

int main(int argc, char **argv)
{
    int s, n, m;
    while (cin >> s >> n >> m && s != 0 && n != 0 && m != 0) {
        int ret = bfs(s, n, m);
        if (ret == -1) {
            cout << "NO" << endl;
        }
        else {
            cout << ret << endl;
        }
    }
    return 0;
};

#endif
