// #define DEBUG
#include <algorithm>
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
    static const int MAXN = 2e5;
    int count[MAXN];
    int ans;

  public:
    Solution(int n, vector<int> a, int aMax, int aMin)
        : n(n), a(a), aMax(aMax), aMin(aMin) {
        memset(count, 0, MAXN * sizeof(int));
    }
    int solve();
    const int getAns() const { return ans; }
};

int Solution::solve() {
    n = unique(a.begin() + 1, a.begin() + n + 1) - a.begin() - 1;
    a[0] = 0;
    a[n + 1] = 0;
#ifdef DEBUG
    cout << "a: " << endl;
    for (int i = 0; i <= n + 1; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
#endif

    for (int i = 1; i <= n; i++) {
        if (a[i - 1] < a[i] && a[i] > a[i + 1]) {
            count[a[i]]++;
        } else if (a[i - 1] > a[i] && a[i + 1] > a[i]) {
            count[a[i]]--;
        }
    }

    ans = 0;
    int tmp = 0;
    for (int num = aMax; num > 0; num--) {
        tmp = tmp + count[num];
        ans = ans > tmp ? ans : tmp;
#ifdef DEBUG
        cout << num << ": " << tmp << ", count: " << count[num]
             << ", ans: " << ans << endl;
#endif
    }

    return ans;
}

int main() {
    int n;
    vector<int> a;
    int aMax = INT_MIN;
    int aMin = INT_MAX;
    cin >> n;
    a.push_back(0);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;

        aMax = aMax > tmp ? aMax : tmp;
        aMin = aMin < tmp ? aMin : tmp;

        a.push_back(tmp);
    }
    a.push_back(0);

    Solution s(n, a, aMax, aMin);
    cout << s.solve() << endl;

    return 0;
}
