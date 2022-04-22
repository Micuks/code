#include "Matrix.h"

Matrix::Matrix() {
    mRows = 0;
    mCols = 0;
    pData = nullptr;
}

Matrix::Matrix(int rows, int cols) {
    mRows = rows;
    mCols = cols;
    pData = new int*[rows];
    for(int i = 0; i < rows; i++) {
        pData[i] = new int[cols];
    }
}

Matrix::Matrix(const Matrix& oldMatrix) {
    if(this == &oldMatrix) {
        std::cout << "this == &oldMatrix\n";
    }

    mRows = oldMatrix.mRows;
    mCols = oldMatrix.mCols;
    pData = new int*[mRows];

    for(int i = 0; i < mRows; i++) {
        pData[i] = new int[mCols];
    }

    for(int i = 0; i < mRows; i++) {
        for(int j = 0; j < mCols; j++) {
            pData[i][j] = oldMatrix.pData[i][j];
        }
    }
}

Matrix::~Matrix() {
    for(int i = 0; i < mRows; i++) {
        delete [] pData[i];
    }
    delete [] pData;
}

std::istream& operator >> (std::istream& iStr, Matrix& matrix) {
    using namespace std;

    cout << "Enter the matrix elements\n";

    for(int i = 0; i < matrix.mRows; i++) {
        for(int j = 0; j < matrix.mCols; j++) {
            iStr >> matrix.pData[i][j];
        }
    }

    return iStr;
}

std::ostream& operator << (std::ostream& oStr, const Matrix& matrix) {
    using namespace std;

    for(int i = 0; i < matrix.mRows; i++) {
        for(int j = 0; j < matrix.mCols; j++) {
            oStr << matrix.pData[i][j] << ' ';
        }
        oStr << endl;
    }

    return oStr;
}

Matrix& Matrix::operator=(const Matrix &rhs) {
    if(this == &rhs) {
        throw std::invalid_argument("Left value equals to right value.");
    }
    if(mRows != rhs.mRows || mCols != rhs.mCols) {
        for(int i = 0; i < mRows; i++) {
            for(int j = 0; j < mCols; j++) {
                delete [] pData[i];
            }
        }
        delete [] pData;
        this->mRows = rhs.mRows;
        this->mCols = rhs.mCols;
    }

    this->pData = new int*[mRows];

    for(int i = 0; i < mRows; i++) {
        this->pData[i] = new int[mCols];
    }

    for(int i = 0; i < mRows; i++) {
        for(int j = 0; j < mCols; j++) {
            this->pData[i][j] = rhs.pData[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix &rhs) {
    if(this->mRows != rhs.mRows || this->mCols != rhs.mCols) {
        throw std::invalid_argument("Two matrices with different dimensions.");
    }

    Matrix ansMatrix(*this);
    int** pLhsMatrix = ansMatrix.pData;
    int** pRhsMatrix = rhs.pData;

    for(int i = 0; i < this->mRows; i++) {
        for(int j = 0; j < this->mCols; j++) {
            pLhsMatrix[i][j] += pRhsMatrix[i][j];
        }
    }

    return ansMatrix;
}

Matrix Matrix::operator-(const Matrix &rhs) {
    Matrix minusRhs(rhs);

    for(int i = 0; i < rhs.mRows; i++) {
        for(int j = 0; j < rhs.mCols; j++) {
            minusRhs.pData[i][j] = -rhs.pData[i][j];
        }
    }

    Matrix ansMatrix = *this + minusRhs;

    return ansMatrix;
}
