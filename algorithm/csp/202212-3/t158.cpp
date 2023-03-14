// #define DEBUG
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

#ifdef DEBUG
#include "debug.h"
#else
#define deb(x...)
#endif // DEBUG

const double PI = acos(-1);

using namespace std;

typedef vector<vector<int>> t_Matrix;

class Matrix {
  public:
    Matrix(int s = 8) : size(s) {
        for (int i = 0; i < size; i++) {
            matrix.push_back(vector<int>());
            for (int j = 0; j < size; j++) {
                matrix[i].push_back(0);
            }
        }
    }
    vector<int> &operator[](const int &idx);
    const vector<int> &operator[](const int &idx) const;
    const string toString();
    Matrix mul(const Matrix &mb);
    Matrix DCT() const;

  private:
    t_Matrix matrix;
    int size;
};

Matrix Matrix::mul(const Matrix &mb) {
    Matrix result = Matrix();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = (*this)[i][j] * mb[i][j];
        }
    }
    return result;
}

Matrix Matrix::DCT() const {
    Matrix result = Matrix();
    auto alpha = [](int u) { return (u == 0) ? sqrt(1.0 / 2) : 1.0; };

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double tmp = 0.0;
            for (int u = 0; u < size; u++) {
                for (int v = 0; v < size; v++) {
                    tmp += alpha(u) * alpha(v) * (*this)[u][v] *
                           cos((PI / 8) * u * (i + 1.0 / 2)) *
                           cos((PI / 8) * v * (j + 1.0 / 2));
                }
            }
            result[i][j] = static_cast<int>(tmp / 4 + 128.5);
            result[i][j] = (result[i][j] < 0) ? 0 : result[i][j];
            result[i][j] = (result[i][j] > 255) ? 255 : result[i][j];
        }
    }
    return result;
}

vector<int> &Matrix::operator[](const int &idx) { return matrix[idx]; }
const vector<int> &Matrix::operator[](const int &idx) const {
    return matrix[idx];
}

const string Matrix::toString() {
    stringstream ss;
    for (auto &a : matrix) {
        for (auto &b : a) {
            ss << b << " ";
        }
        ss << endl;
    }
    return ss.str();
}

int main() {
    Matrix Q, M;
    // Read Q and initialize M
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int tmp = 0;
            cin >> tmp;
            Q[i][j] = tmp;
            M[i][j] = 0;
        }
    }
    deb(Q.toString().c_str());

    // Read n, T and M data
    int n, T;
    cin >> n >> T;
    vector<int> data;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        data.push_back(tmp);
    }

    // Step 3: Load M data into M matrix
    int k = 0;
    for (auto m = 0; m <= 7 && k <= n; m++) {
        if (m & 1) {
            int i = 0;
            int j = m - i;
            while (j >= 0) {
                M[i++][j--] = data[k++];
            }
        } else {
            int j = 0;
            int i = m - j;
            while (i >= 0) {
                M[i--][j++] = data[k++];
            }
        }
    }

    for (auto m = 8; m <= 15 && k <= n; m++) {
        if (m & 1) {
            int j = 7;
            int i = m - j;
            while (i <= 7) {
                M[i++][j--] = data[k++];
            }
        } else {
            int i = 7;
            int j = m - i;
            while (j <= 7) {
                M[i--][j++] = data[k++];
            }
        }
    }

    deb("n[%d], T[%d]\n", n, T);
    deb(M.toString().c_str());
    if (T == 0) {
        cout << M.toString();
        return 0;
    }

    // Step 4.Multiply M with Q
    Matrix result;
    result = M.mul(Q);
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            result[i][j] = M[i][j] * Q[i][j];
        }
    }

    if (T == 1) {
        cout << result.toString();
        return 0;
    }

    // Step 5,6: Discrete cosine transform
    result = result.DCT();

    cout << result.toString();

    return 0;
}
