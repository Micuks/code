#include <climits>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#define int int64_t
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
    int dr = r;
    int ddr = 0;
    int flag = 0;
    // i iterates through A, j iterates through 0...N-1
    for (i = 0; i <= n; i++) {
        f = i;

        for (j = A[i]; j < A[i + 1]; j += dr) {
            if (flag) {
                dr = ddr;
                flag = 0;
            } else {
                dr = r;
            }

            g = j / r;
            if (j + dr <= A[i + 1]) {
                err += abs(f - g) * dr;
            } else {
                err += abs(f - g) * (A[i + 1] - j);
                ddr = dr - (A[i + 1] - j);
                flag = 1;
            }
        }
    }

    return err;
}

#undef int
int main() {
#define int int64_t
    int n, N;
    cin >> n >> N;
    vector<int> A;
    A.push_back(0);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        A.push_back(tmp);
    }
    A.push_back(N);

    Solution s(n, N, A);
    cout << s.solve() << endl;

    return 0;
}
