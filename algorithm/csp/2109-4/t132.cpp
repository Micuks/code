// #define DEBUG
#include <bitset>
#include<iomanip>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

static const int MAXN = 16;
static const int MAXK = 5;
double state[1 << MAXN][MAXN * MAXK];

class Solution {
    int n, k;
    vector<double> ps;
    double expectation;

    int coins;
    int remains;

    // double state[1 << MAXN][MAXN * MAXK];
    double dp(int t);

  public:
    Solution(int n, int k, vector<double> &ps)
        : n(n), k(k), ps(ps), expectation(-1), coins(0), remains(n) {
        memset(state, -1, sizeof(state));
    }
    double dp() {
        if (expectation == -1) {
            expectation = dp(0);
            return expectation;
        }
        return expectation;
    }
};

double Solution::dp(int t) {
    // t: cards fetched in binary encoding.
    #ifdef DEBUG
    cout << hex << "t[" << bitset<16>(t) << "]"
         << "coins[" << coins << "]"
         << "remains[" << remains << "]" << endl;
         #endif
    double &curr_exp = state[t][coins];

    if (curr_exp >= static_cast<double>(0)) {
        return curr_exp;
    } else if (coins >= remains * k) {
        return 0;
    }

    curr_exp = 0;
    for (int i = 0; i < n; i++) {
        if ((t >> i) & 1) {
            coins++;
            curr_exp += ps[i] * (dp(t) + 1);
            coins--;
        } else {
            remains--;
            curr_exp += ps[i] * (dp(t | (1 << i)) + 1);
            remains++;
        }
    }

    #ifdef DEBUG
    cout << "t[" << bitset<16>(t) << "]: " << dec << curr_exp << endl;
    #endif
    return curr_exp;
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
    cout << fixed<<setprecision(10)<<s.dp() << endl;

    return 0;
}
