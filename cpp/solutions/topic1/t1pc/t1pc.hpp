#ifndef _t1pc_20191204_
#define _t1pc_20191204_
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

int N, K;
int number_line[1000001];

bool valid(int pos) { return pos >= 0 && pos < 1000001; }

void bfs()
{
    queue<pair<int, int>> mqueue;
    pair<int, int> s = pair<int, int>(N, 0);
    mqueue.push(s);
    while (!mqueue.empty()) {
        s = mqueue.front();
        mqueue.pop();

        if (s.first == K && number_line[K] != -1) {
            return;
        }
        int tc = s.second;
        int teleport_end = s.first * 2;
        int walking_end_right = s.first + 1;
        int walking_end_left = s.first - 1;
        if (valid(teleport_end) && number_line[teleport_end] == -1) {
            number_line[teleport_end] = tc + 1;
            mqueue.push(pair<int, int>(teleport_end, tc + 1));
        }
        if (valid(walking_end_right) && number_line[walking_end_right] == -1) {
            number_line[walking_end_right] = tc + 1;
            mqueue.push(pair<int, int>(walking_end_right, tc + 1));
        }
        if (valid(walking_end_left) && number_line[walking_end_left] == -1) {
            number_line[walking_end_left] = tc + 1;
            mqueue.push(pair<int, int>(walking_end_left, tc + 1));
        }
    }
}

int main(int argc, char **argv)
{
    cin >> N >> K;
    memset(number_line, -1, sizeof(int) * 1000001);
    number_line[N] = 0;
    bfs();
    cout << number_line[K] << endl;
    return 0;
};

#endif
