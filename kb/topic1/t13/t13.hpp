// #define db
#ifndef _t13_20220731_
#define _t13_20220731_
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
#include <stack>
#include <string>
#include <vector>
using namespace std;

class State {
  public:
    int s;
    int n;
    int m;
    int steps;
    State(int _s, int _n, int _m, int _st = 0)
        : s(_s), n(_n), m(_m), steps(_st) {}
    State(const State &oldS)
        : s(oldS.s), n(oldS.n), m(oldS.m), steps(oldS.steps) {}
    void operator=(const State &oldS) {
        s = oldS.s;
        n = oldS.n;
        m = oldS.m;
        steps = oldS.steps;
    }
    inline bool isEqual(const int target) {
        return ((s == target && n == target) || (s == target && m == target) ||
                (n == target && m == target));
    }
};
ostream &operator<<(ostream &os, const State &S) {
    os << "(" << S.s << ", " << S.n << ", " << S.m << ")";
    return os;
}
#define out_state_return_partial(X)                                            \
    if (ls.X < rs.X)                                                           \
        return true;                                                           \
    if (ls.X > rs.X)                                                           \
        return false;
bool operator<(const State &ls, const State &rs) {
    out_state_return_partial(s);
    out_state_return_partial(n);
    out_state_return_partial(m);
    return false;
}
#define pour(X, Y, XMAX, YMAX)                                                 \
    do {                                                                       \
        if (X + Y > YMAX) {                                                    \
            X = X + Y;                                                         \
            Y = YMAX;                                                          \
            X = X - Y;                                                         \
        } else {                                                               \
            Y = X + Y;                                                         \
            X = 0;                                                             \
        }                                                                      \
    } while (0)
template <typename t> void printStack(const queue<t> st) {
    queue<t> newst(st);
#ifdef db
    cout << "size[" << newst.size() << "]" << endl;
#endif
    while (!newst.empty()) {
        auto &a = newst.front();
        newst.pop();
        cout << a << ' ';
    }
    cout << endl;
}
int bfs(const int sMax, const int nMax, const int mMax) {
    if (sMax % 2 == 1)
        return -1;
    queue<State> st;
    set<State> visited;
#ifdef db
    cout << "sMax[" << sMax << "], nMax[" << nMax << "], mMax[" << mMax << "]"
         << endl;
#endif
    visited.insert(State(sMax, 0, 0));
    st.push(State(sMax, 0, 0));
    while (!st.empty()) {
        State t = st.front();
        st.pop();
#ifdef db
        cout << "t: ";
        cout << t << endl;
        cout << "---before" << endl;
        printStack(st);
        cout << "stack---" << endl;
#endif
        if (t.isEqual(sMax / 2)) {
#ifdef db
            cout << t << " equal" << endl;
#endif
            return t.steps;
        }
        State ns(t);
        pour(ns.s, ns.n, sMax, nMax); // steps+1
        ns.steps++;
        if (visited.find(ns) == visited.end()) {
            visited.insert(State(ns.s, ns.n, ns.m)); // ignore steps
            st.push(ns);
        }
        ns = t;
        pour(ns.s, ns.m, sMax, mMax);
        ns.steps++;
        if (visited.find(ns) == visited.end()) {
            visited.insert(State(ns.s, ns.n, ns.m)); // ignore steps
            st.push(ns);
        }
        ns = t;
        pour(ns.n, ns.s, nMax, sMax);
        ns.steps++;
        if (visited.find(ns) == visited.end()) {
            visited.insert(State(ns.s, ns.n, ns.m)); // ignore steps
            st.push(ns);
        }
        ns = t;
        pour(ns.n, ns.m, nMax, mMax);
        ns.steps++;
        if (visited.find(ns) == visited.end()) {
            visited.insert(State(ns.s, ns.n, ns.m)); // ignore steps
            st.push(ns);
        }
        ns = t;
        pour(ns.m, ns.s, mMax, sMax);
        ns.steps++;
        if (visited.find(ns) == visited.end()) {
            visited.insert(State(ns.s, ns.n, ns.m)); // ignore steps
            st.push(ns);
        }
        ns = t;
        pour(ns.m, ns.n, mMax, nMax);
        ns.steps++;
        if (visited.find(ns) == visited.end()) {
            visited.insert(State(ns.s, ns.n, ns.m)); // ignore steps
            st.push(ns);
        }
#ifdef db
        cout << "---after" << endl;
        printStack(st);
        cout << "stack---" << endl;
#endif
    }
    return -1;
}
int main(int argc, char **argv) {
    int s, n, m;
    while (cin >> s >> n >> m && s != 0 && n != 0 && m != 0) {
        int result = bfs(s, n, m);
        if (result == -1) {
            cout << "NO" << endl;
        } else
            cout << result << endl;
    }
    return 0;
}

#endif
