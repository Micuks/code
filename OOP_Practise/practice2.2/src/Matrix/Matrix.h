#include <iostream>

class Matrix {
    public:
        Matrix();
        Matrix(int rows, int cols);
        Matrix(const Matrix& oldMatrix);
        ~Matrix();

        friend std::istream& operator>>(std::istream& iStr, Matrix& matrix);
        friend std::ostream& operator<<(std::ostream& oStr, const Matrix& matrix);
        Matrix& operator=(const Matrix& rhs);
        Matrix operator+(const Matrix& rhs);
        Matrix operator-(const Matrix& rhs);
    private:
        int mRows;
        int mCols;
        int** pData;
};
