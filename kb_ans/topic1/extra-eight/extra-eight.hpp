#ifndef _extra_eight_20191207_
#define _extra_eight_20191207_
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
#include <sstream>
#include <string>
#include <vector>
using namespace std;

map<string, string> travelled;
struct State {
    string moves;
    string state;
    State(string moves, string state) : moves(moves), state(state) {}
};

// int dirs[][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
// char move_map[] = {'r', 'd', 'u', 'l'};
// char move_map[] = {'u', 'l', 'r', 'd'};

// int dirs[][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
// char move_map[] = {'d', 'r', 'l', 'u'};

int dirs[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
// char move_map[] = {'r', 'l', 'd', 'u'};
char move_map[] = {'l', 'r', 'u', 'd'};
string bfs(string input)
{
    string ret = "unsolvable";
    queue<State> mqueue;
    State s("", input);
    mqueue.push(s);
    travelled[input] = "";

    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        /*
        if (s.state == "12345678x") {
            return s.moves;
        }
        */

        int x_pos = s.state.find('x');
        int xx = x_pos / 3;
        int xy = x_pos % 3;
        // cout << "xx: " << xx << " xy: " << xy << endl;
        for (int i = 0; i < 4; ++i) {
            int newx = xx + dirs[i][0];
            int newy = xy + dirs[i][1];
            int newpos = newx * 3 + newy;
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {
                string new_state = s.state;
                {
                    char t = new_state[x_pos];
                    new_state[x_pos] = new_state[newpos];
                    new_state[newpos] = t;
                }
                if (travelled.find(new_state) == travelled.end()) {
#ifdef DEBUG
                    cout << "old_state: " << s.state << " new_state: " << new_state << " xx: " << xx
                         << " xy: " << xy << " newx: " << newx << " newy: " << newy
                         << " move[i]: " << move_map[i] << endl;
#endif
                    travelled[new_state] = move_map[i] + s.moves;
                    mqueue.push(State(move_map[i] + s.moves, new_state));
                }
            }
        }
    }

    return ret;
}

int main(int argc, char **argv)
{
    string line(128, 0);
    // while (cin.getline(&line[0], 128)) {
    bfs("12345678x");
    while (fgets(&line[0], 127, stdin)) {
        stringstream in(line);
        char input[10];
        for (int i = 0; i < 10; ++i) {
            in >> input[i];
        }
        input[9] = '\0';
        map<string, string>::iterator iter = travelled.find(input);
        if (iter == travelled.end()) {
            cout << "unsolvable" << endl;
        }
        else {
            cout << iter->second << endl;
        }
    }
    return 0;
};

#endif
