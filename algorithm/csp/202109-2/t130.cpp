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
    static const int MAXN = 2e4;
    int count[MAXN];
    int ans;

  public:
    Solution(int n, vector<int> a, int aMax, int aMin)
        : n(n), a(a), aMax(aMax), aMin(aMin) {
        memset(count, 0, (aMax - aMin + 1) * sizeof(int));
    }
    int solve();
};

int Solution::solve() {
    n = unique(a.begin(), a.end()) - a.begin();

    if (a[0] > a[1]) {
        count[a[0]]++;
    } else if (a[0] < a[1]) {
        count[a[0]]--;
    }
    if (a[n - 1] > a[n - 2]) {
        count[a[n - 1]]++;
    } else if (a[n - 1] < a[n - 2]) {
        count[a[n - 1]]--;
    }

    for (int i = 1; i < n - 1; i++) {
        if (a[i - 1] < a[i] && a[i] > a[i + 1]) {
            count[a[i]]++;
        } else if (a[i - 1] > a[i] && a[i + 1] > a[i]) {
            count[a[i]]--;
        }
    }

    ans = 0;
    int tmp = 0;
    for (int num = aMax; num >= aMin; num--) {
        tmp = tmp + count[num];
        ans = ans > tmp ? ans : tmp;
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
    cout << s.solve() << endl;

    return 0;
}
