#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<int> A;
    int n, N;
    int sum;

  public:
    Solution(int n, int N, vector<int> &A) : n(n), N(N), A(A), sum(0) {}
    int solve();
};

int Solution::solve() {
    sum = 0;
    int i = 0, j = 0;
    // i iterates through A, j iterates through 0...N-1
    while (i < n && j < N) {
        if (j >= A[i] && j < A[i + 1]) {
            sum += i;
            j++;
        } else if (j < A[i]) {
            j++;
        } else if (j >= A[i + 1]) {
            i++;
        }
    }

    if (i >= n) {
        while (j < N) {
            sum += n;
            j++;
        }
    }

    // cout << "j[" << j << "], i[" << i << "]" << endl;

    return sum;
}

int main() {
    int n, N;
    cin >> n >> N;
    vector<int> A;
    A.push_back(0);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        A.push_back(tmp);
    }

    Solution s(n, N, A);
    cout << s.solve() << endl;
    return 0;
}
