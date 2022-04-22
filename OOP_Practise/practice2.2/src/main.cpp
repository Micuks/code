#include <iostream>
#include "Matrix.h"

using namespace std;

void task1();
void task2();

int main() {
    task1();
    cout << endl;
    task2();
}

void task1() {
    int row, col;
    cout << "Enter the number of rows and columns of matrix\n";
    cin >> row >> col;
    Matrix A1(row, col);
    cin >> A1;
    cout << "Matrix A1:\n";
    cout << A1;

    Matrix A2(row, col);
    cin >> A2;
    cout << "Matrix A2:\n";
    cout << A2;

    Matrix A3 = A1 + A2;
    cout << "Matrix A3 = A1 + A2:\n";
    cout << A3;
    
    A3 = A1 - A2;
    cout << "Matrix A3 = A1 - A2:\n";
    cout << A3;
}

void task2() {
    int row, col;
    cout << "task2:\n";
    cout << "Enter the number of rows and columns of matrix.\n";
    cin >> row >> col;

    Matrix* pA1 = new Matrix(row, col);
    cin >> *pA1;
    cout << "Matrix pA1:\n";
    cout << *pA1;

    Matrix* pA2 = new Matrix(row, col);
    cin >> *pA2;
    cout << "Matrix pA2:\n";
    cout << *pA2;

    Matrix *pA3 = new Matrix();
    *pA3 = *pA1 + *pA2;
    cout << "Matrix pA3 = pA1 + pA2:\n";
    cout << *pA3;

    *pA3 = *pA1 - *pA2;
    cout << "Matrix pA3 = pA1 - pA2:\n";
    cout << *pA3;

    delete pA1;
    delete pA2;
    delete pA3;
    cout << "pA1, pA2, pA3 deleted.\n";
}
