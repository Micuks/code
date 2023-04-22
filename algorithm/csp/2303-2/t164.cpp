// #define DEBUG

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

#ifdef DEBUG
#include "debug.h"
#else
#define deb(x...)
#endif

using namespace std;

int n, m, k;

bool affordable(int middle, int n, vector<int> &_t, vector<int> &_c,
                vector<int> &indices) {
    auto t = [&](int idx) -> int { return _t.at(indices.at(idx)); };
    auto c = [&](int idx) -> int { return _c.at(indices.at(idx)); };

    int total_cost = 0;
    deb(middle);
    for (int i = n - 1; i >= 0 && t(i) >= middle; i--) {
        auto this_time = t(i);
        auto this_cost = c(i) * (this_time - middle);
        total_cost += this_cost;
        deb(i, this_time, this_cost, total_cost);
        if (total_cost > m) {
            return false;
        }
    }
    return (total_cost <= m);
}

int bsearch(int low, int high, vector<int> &_t, vector<int> &_c,
            vector<int> &indices, int n, int m, int k) {
    int current_ans = INT32_MAX;
    int middle;
    auto get_middle = [&](int low, int high) -> int {
        // return _t.at(indices.at((low + high) / 2));
        return (low + high) / 2;
    };
    while (high > low) {
        deb(high, low);
        middle = get_middle(low, high);
        if (affordable(middle, n, _t, _c, indices)) {
            current_ans = middle;
            high = middle;
        } else {
            low = middle + 1;
        }
        deb(middle, current_ans);
        if (current_ans <= k)
            return k;
    }

    return current_ans;
}

int main(int argc, char *argv[]) {
    vector<int> _t, _c;
    cin >> n >> m >> k;
    deb(n, m, k);
    for (int i = 0; i < n; i++) {
        int time, cost;
        cin >> time >> cost;
        _t.push_back(time);
        _c.push_back(cost);
    }
    // sort t and c based on t
    vector<int> indices(_t.size());
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(),
         [&](int a, int b) -> bool { return _t[a] < _t[b]; });
    auto t = [&](int idx) -> int { return _t.at(indices.at(idx)); };
    auto c = [&](int idx) -> int { return _c.at(indices.at(idx)); };

    for (int i = 0; i < n; i++) {
        deb(t(i), c(i));
    }

    int low = 0, high = t(n - 1);
    // int low = 0, high = n;
    int result = bsearch(low, high, _t, _c, indices, n, m, k);
    cout << result << endl;
    return 0;
}
