// #define db
#ifndef _t7_20220724_
#define _t7_20220724_
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

class State {
  public:
    string str;
    int steps;
    State(const string &_str, const int &_steps) : str(_str), steps(_steps) {}
#ifdef db
    string toString() {
        string s(str + " [" + to_string(steps) + "]");
        return s;
    }
#endif
};
string shuffle(const string &s0, const int &c) {
    string newStr(s0.length(), 0);
    for (int i = 0; i < c; i++) {
        newStr[2 * i] = s0[c + i];
        newStr[2 * i + 1] = s0[i];
    }
    return newStr;
}
int bfs(int c, string s1, string s2, string sDest) {
    queue<State> q;
    set<string> visited;
    string s0 = s1 + s2;
#ifdef db
    // cout << "s0[" << s0 << "]" << endl;
#endif
    q.push(State(s0, 0));
    visited.insert(s0);
    while (!q.empty()) {
        State s = q.front();
        q.pop();
#ifdef db
        cout << s.toString() << endl;
#endif
        if (s.str == sDest) {
#ifdef db
            cout << "s.str[" << s.str << "],"
                 << "sDest[" << sDest << "]" << endl;
#endif
            return s.steps;
        }
        string newStr = shuffle(s.str, c);
        if (visited.find(newStr) == visited.end()) {
            q.push(State(newStr, s.steps + 1));
            visited.insert(newStr);
        }
    }
    return -1;
}
int main(int argc, char **argv) {
    int n, c;
    string s1, s2, sDest;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c >> s1 >> s2 >> sDest;
        int steps = bfs(c, s1, s2, sDest);
        cout << i << " " << steps << endl;
    }
    return 0;
};

#endif
