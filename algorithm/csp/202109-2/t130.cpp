#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int n;
    vector<int> a;
    int aMax;
    int aMin;
    int solve();

  public:
    Solution(int n, vector<int> a, int aMax, int aMin)
        : n(n), a(a), aMax(aMax), aMin(aMin) {
        ans = solve();
    }
    int ans;
};

int Solution::solve() {
    ans = INT_MIN;
    for (int p = aMin; p <= aMax; p++) {
        int cnt = 0;
        int flag = 0;
        for (int i = 0; i < a.size(); i++) {
            if (flag == 1) {
                if (a[i] > p) {
                    flag = 1;
                } else {
                    flag = 0;
                }
            } else if (flag == 0) {
                if (a[i] > p) {
                    flag = 1;
                    cnt++;
                }
            }
        }
        ans = cnt > ans ? cnt : ans;
    }
    return ans;
}

int main() {
    int n;
    vector<int> a;
    int aMax = INT_MIN;
    int aMin = INT_MAX;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;

        aMax = aMax > tmp ? aMax : tmp;
        aMin = aMin < tmp ? aMin : tmp;

        a.push_back(tmp);
    }

    Solution s(n, a, aMax, aMin);
    cout << s.ans << endl;

    return 0;
}
