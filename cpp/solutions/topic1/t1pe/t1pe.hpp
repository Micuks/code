#ifndef _t1pe_20191204_
#define _t1pe_20191204_
#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

#define MAX_LEN 200
int n;
int rmd[MAX_LEN];
int cycle_section = 1;
char visited[MAX_LEN];

struct State {
    int rem;
    int start;
    string choise;
    State(int r, int s, const string &c) : rem(r), start(s), choise(c) {}
};

string bfs(int rem, int start, string ret)
{
    State s = State(rem, start, "");
    queue<State> mqueue;
    mqueue.push(s);

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        if (s.rem == 0) {
            return s.choise;
        }
        if (rmd[s.start] == 0) {
            string ret(s.start + 1, '0');
            ret[s.start] = '1';
            return ret;
        }
        // don't take this one
        rem = s.rem;
        State res_dontake = State(rem, s.start + 1, s.choise + "0");
        // take this one
        rem = rem - rmd[s.start];
        if (rem < 0) {
            rem = rem + n;
        }
        State res_take = State(rem, s.start + 1, s.choise + "1");

        assert(res_dontake.rem >= 0 && res_dontake.rem <= n);
        assert(res_take.rem >= 0 && res_take.rem <= n);
        if (res_dontake.start < MAX_LEN) {
            visited[res_dontake.rem] = 1;
            mqueue.push(res_dontake);
        }

        if (visited[res_take.rem] == 0 && res_take.start < MAX_LEN) {
            visited[res_take.rem] = 1;
            mqueue.push(res_take);
        }
    }
    return "deliaf";
}

int main(int argc, char **argv)
{
    while (cin >> n && n != 0) {
        memset(visited, 0, sizeof(char) * MAX_LEN);
        long powf10 = 1;
        for (int i = 0; i < MAX_LEN; ++i) {
            rmd[i] = static_cast<int>(powf10 % n);
            powf10 = (powf10 * 10) % n;
        }
        for (int i = 1; i < MAX_LEN; ++i) {
            if (rmd[i] == rmd[1]) {
                cycle_section = i - 1;
                break;
            }
        }
        string res = bfs(n, 0, "");
        reverse(res.begin(), res.end());
        cout << res << endl;
    }
    return 0;
};

#endif
