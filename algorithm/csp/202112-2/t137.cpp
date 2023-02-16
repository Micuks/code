#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int n, N;
    vector<int> A;
    int err;
    int r;

  public:
    Solution(int n, int N, vector<int> &A) : n(n), N(N), A(A), err(0) {
        r = N / (n + 1);
    }
    int solve();
};

int Solution::solve() {
    err = 0;
    int i = 0, j = 0;
    int f = 0, g = 0;
    // i iterates through A, j iterates through 0...N-1
    while (i < n && j < N) {
        if (j >= A[i] && j < A[i + 1]) {
            f = i;
            g = j / r;
            err += abs(f - g);
            j++;
        } else if (j < A[i]) {
            g = j / r;
            err += abs(f - g);
            j++;
        } else if (j >= A[i + 1]) {
            i++;
        }
    }

    if (i >= n) {
        f = n;
        while (j < N) {
            g = j / r;
            err += abs(f - g);
            j++;
        }
    }

    return err;
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
