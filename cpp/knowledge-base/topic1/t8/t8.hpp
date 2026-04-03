// #define db
#ifndef _t8_20220725_
#define _t8_20220725_
#include <algorithm>
#include <assert.h>
#include <climits>
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

int MAXN = INT_MAX;
int aMax, bMax;
string msg[] = {" ", "FILL(", "DROP(", "POUR("};

class Status {
  public:
    int a;
    int b;
    int steps;
    vector<pair<int, int> > details;
    Status(const int &_a, const int &_b, const int &_steps,
           const vector<pair<int, int> > &_details)
        : a(_a), b(_b), steps(_steps), details(_details) {}
    Status(const int &_a, const int &_b, const int &_steps)
        : a(_a), b(_b), steps(_steps) {}
    Status(const Status &_status)
        : a(_status.a), b(_status.b), steps(_status.steps),
          details(_status.details) {}
    pair<int, int> getPair() { return make_pair(a, b); }
    void fill(const int &idx);
    void drop(const int &idx);
    void pour(const int &idx);
    friend ostream &operator<<(ostream &os, const Status &st);
};
void Status::fill(const int &idx) {
    steps++;
    if (idx == 1) {
        a = aMax;
        details.push_back(make_pair(1, 1));
    } else {
        b = bMax;
        details.push_back(make_pair(1, 2));
    }
}
void Status::drop(const int &idx) {
    steps++;
    if (idx == 1) {
        a = 0;
        details.push_back(make_pair(2, 1));
    } else {
        b = 0;
        details.push_back(make_pair(2, 2));
    }
}
void Status::pour(const int &idx) { // pour from idx to another
    steps++;
    if (idx == 1) {
        int sum = a + b;
        if (sum <= bMax) {
            a = 0;
            b = sum;
        } else {
            b = bMax;
            a = sum - bMax;
        }

        details.push_back(make_pair(3, 1));
    } else {
        int sum = a + b;
        if (sum <= aMax) {
            a = sum;
            b = 0;
        } else {
            a = aMax;
            b = sum - aMax;
        }

        details.push_back(make_pair(3, 2));
    }
}
ostream &operator<<(ostream &os, const Status &st) {
    if (st.steps == MAXN) {
        os << "impossible" << endl;
        return os;
    }
    os << st.steps << endl;
#ifdef db
    cout << "a[" << st.a << "]"
         << "b[" << st.b << "]" << endl;
    for (int i = 0; i < st.details.size(); i++) {
        const pair<int, int> &iter = st.details[i];
        cout << "(" << iter.first << "," << iter.second << ")" << endl;
    }
#endif
    for (int i = 0; i < st.details.size(); i++) {
        const pair<int, int> &iter = st.details[i];
        os << msg[iter.first] << iter.second;
        if (iter.first == 3) {
            os << "," << ((iter.second == 1) ? 2 : 1);
        }
        os << ")" << endl;
    }
    return os;
}
Status bfs(int c) {
    queue<Status> q;
    set<pair<int, int> > visited;
    q.push(Status(0, 0, 0));
    visited.insert(make_pair(0, 0));
    while (!q.empty()) {
        Status s = q.front();
        q.pop();
        if (s.a == c || s.b == c) {
            return s;
        }
        for (int i = 1; i <= 2; i++) {
            Status tmp = Status(s);
            tmp.fill(i);
            if (visited.find(tmp.getPair()) == visited.end()) {
#ifdef db
                cout << "---fill\n" << tmp << "---\n";
#endif
                visited.insert(tmp.getPair());
                q.push(tmp);
            }
            tmp = Status(s);
            tmp.drop(i);
            if (visited.find(tmp.getPair()) == visited.end()) {
#ifdef db
                cout << "---drop\n" << tmp << "---\n";
#endif
                visited.insert(tmp.getPair());
                q.push(tmp);
            }
            tmp = Status(s);
            tmp.pour(i); // pour from i to another
            if (visited.find(tmp.getPair()) == visited.end()) {
#ifdef db
                cout << "---pour\n" << tmp << "---\n";
#endif
                visited.insert(tmp.getPair());
                q.push(tmp);
            }
        }
    }
    return Status(0, 0, MAXN);
}
int main(int argc, char **argv) {
    int c;
    cin >> aMax >> bMax >> c;
    Status result = bfs(c);
    cout << result;
    return 0;
};

#endif
