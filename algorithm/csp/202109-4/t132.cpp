// #define DEBUG
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    int n, k;
    vector<double> ps;
    int *collected;
    double expectation;

  public:
    Solution(int n, int k, vector<double> &ps)
        : n(n), k(k), ps(ps), expectation(0) {
        collected = (int *)malloc(ps.size() * sizeof(int));
        memset(collected, 0, ps.size() * sizeof(int));
    }
    void dfs(int t);
    bool end(int t);
    const double getExp() const { return expectation; }
};

void Solution::dfs(int t) {
    if (end(t)) {
        double thisExp = 1;
        for (int i = 0; i < n; i++) {
            if (!collected[i]) {
                continue;
            }
            double po = pow(ps[i], collected[i]);
            thisExp *= po;
        }
        thisExp *= t;
        expectation += thisExp;
        return;
    }
    for (int i = 0; i < n; i++) {
        collected[i]++;
        dfs(t + 1);
        collected[i]--;
    }
}

bool Solution::end(int t) {
    if (t < n) {
        // Less than n times of fetching cards.
        return false;
    }

    // O(n)
    int not_collected = 0;
    int coins = 0;
    for (int i = 0; i < n; i++) {
        if (collected[i] == 0) {
            not_collected++;
        } else if (collected[i] > 1) {
            coins += (collected[i] - 1);
        }
    }
    if (coins / k >= not_collected) {
        return true;
    }

    return false;
}

int main() {
    int n, k;
    vector<double> ps;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        double tmp;
        cin >> tmp;
        ps.push_back(tmp);
    }

    Solution s(n, k, ps);
    s.dfs(0);
    cout << s.getExp() << endl;

    return 0;
}
