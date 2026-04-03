#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    const int getMax() const { return max; }
    const int getMin() const { return min; }
    Solution(int n, vector<int> b) : n(n), b(b) {
        max = min = 0;
        calculate();
    }

  private:
    int n;
    int max;
    int min;
    std::vector<int> a, b;
    void calculate();
};

void Solution::calculate() {
    // Calculate max and min of A.
    int curr_max = INT_MIN;
    int prev_max = INT_MIN;
    for (auto num : b) {
        // First calculate max.
        curr_max = num > curr_max ? num : curr_max;
        max += curr_max;
        // Then calculate min.
        if (curr_max > prev_max) {
            // Current number could only be the new max.
            min += curr_max;
        } else {
            // Current number can be 0.
            min += 0;
        }
        prev_max = curr_max;
    }
}

int main() {
    int n;
    std::vector<int> b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        b.push_back(tmp);
    }
    Solution solution(n, b);
    cout << solution.getMax() << endl << solution.getMin();
    return 0;
}
