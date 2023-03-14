// #define DEBUG
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#ifdef DEBUG
#include "debug.h"
#else
#define deb(x...)
#endif // DEBUG

using namespace std;

typedef vector<vector<int>> t_Matrix;

class Matrix {
  public:
    Matrix(int size = 8) : size(size) {
        for (int i = 0; i < size; i++) {
            matrix.push_back(vector<int>());
            for (int j = 0; j < size; j++) {
                matrix.at(i).push_back(0);
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
    Matrix &&result = Matrix();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = (*this)[i][j] * mb[i][j];
        }
    }
    return std::move(result);
}

Matrix Matrix::DCT() const {
    Matrix &&result = Matrix();
    auto alpha = [](int u) { return (u == 0) ? sqrt(1.0 / 2) : 1.0; };

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double tmp = 0;
            for (int u = 0; u < size; u++) {
                for (int v = 0; v < size; v++) {
                    tmp += alpha(u) * alpha(v) * (*this)[u][v] *
                           cos(M_PI / 8 * u * (i + 1.0 / 2)) *
                           cos(M_PI / 8 * v * (j + 1.0 / 2));
                }
            }
            result[i][j] = (int)(tmp / 4 + 128.5);
        }
    }
    return std::move(result);
}

vector<int> &Matrix::operator[](const int &idx) { return matrix[idx]; }
const vector<int> &Matrix::operator[](const int &idx) const {
    return matrix[idx];
}

const string Matrix::toString() {
    int width = 3;
    stringstream ss;
    // ss << endl;
    for (auto &a : matrix) {
        for (auto &b : a) {
            ss << setw(width) << b << " ";
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
            int &&tmp = 0;
            cin >> tmp;
            Q[i][j] = std::move(tmp);
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

    // Load M data into M matrix
    int k = 0;
    for (int m = 0; m <= 7; m++) {
        if (m & 1) {
            for (int i = 0; i <= m; i++) {
                int j = -1 * i + m;
                M[i][j] = data[k++];
            }
        } else {
            for (int i = m; i >= 0; i--) {
                int j = -1 * i + m;
                M[i][j] = data[k++];
            }
        }
    }

    deb("n[%d], T[%d]\n", n, T);
    deb(n << T);
    deb(M.toString().c_str());

    // Multiply M with Q
    Matrix result;
    result = M.mul(Q);
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            result[i][j] = M[i][j] * Q[i][j];
        }
    }

    // Discrete cosine transform
    result = result.DCT();

    cout << result.toString();

    return 0;
}
