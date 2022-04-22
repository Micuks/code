#include <iostream>

using namespace std;

int** allocate_matrix_space()
    // Allocate space for 4*5 matrix.
    // And return pointer pointing to the matrix.
{
    int** pm = new int* [4];

    if(pm == nullptr) {
        cout << "FAILED TO ALLOCATE MEMORY." << endl;
        abort();
    }

    for(int i = 0; i < 4; i++) {
        pm[i] = new int [5];
        if(pm[i] == nullptr) {
            cout << "FAILED TO ALLOCATE MEMORY." << endl;
            abort();
        }
    }

    return pm;
}

void free_matrix_space(int** &pm)
    //Free the memory space allocated for the matrix.
{
    for(int i = 0; i < 4; i++) {
        delete pm[i];
    }
    delete pm;
    if(pm == NULL)
        cout << "Successfully freed memory space.\n";
}

void input_matrix(int** &pMatrix)
    // Read numbers from cin and save to given 4*5 matrix.
{
    if(pMatrix == nullptr) {
        pMatrix = allocate_matrix_space();
    }

    if(pMatrix == nullptr) {
        cout << "Failed to allocate memory space." << endl;
        abort();
    }

    cout << "Input matrix\n";

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            cin >> pMatrix[i][j];
        }
    }
}

void print_matrix(int** const &pMatrix)
    // Print matrix.
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            cout << pMatrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void matrix_summing(int** const &pMatrix1, int** const &pMatrix2, int** &pMatrixOutput)
    // Add Matrix1 and Matrix2 to get MatrixOutput.
{
    if(pMatrixOutput == nullptr) {
        pMatrixOutput = allocate_matrix_space();
    }

    if(pMatrixOutput == nullptr) {
        cout << "Failed to allocate memory space." << endl;
        abort();
    }

    if(pMatrix1 == nullptr || pMatrix2 == nullptr) {
        cout << "At least one of the incoming matrix pointers is empty." << endl;
        abort();
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            pMatrixOutput[i][j] = pMatrix1[i][j] + pMatrix2[i][j];
        }
    }

    cout << "Addition completed." << endl << endl;
}

void matrix_subtracting(int** const &pMatrix1, int** const &pMatrix2, int** &pMatrixOutput)
    // Matrix1 subtracts Matrix2 to get MatrixOutput.
{
    if(pMatrixOutput == nullptr) {
        pMatrixOutput = allocate_matrix_space();
    }

    if(pMatrixOutput == nullptr) {
        cout << "Failed to allocate memory.\n";
        abort();
    }

    if(pMatrix1 == nullptr || pMatrix2 == nullptr) {
        cout << "One of the incoming matrix pointers is null.";
        abort();
    }

    int** pMinusMatrix2 = allocate_matrix_space();
    if(pMinusMatrix2 == nullptr) {
        cout << "Failed to allocate memory.\n";
        abort();
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            pMinusMatrix2[i][j] = -pMatrix2[i][j];
        }
    }

    matrix_summing(pMatrix1, pMinusMatrix2, pMatrixOutput);
    free_matrix_space(pMinusMatrix2);

    cout << "Subtraction completed.\n\n";
}

int main() {
    int** pMatrix1 = nullptr;
    input_matrix(pMatrix1);

    int** pMatrix2 = allocate_matrix_space();
    input_matrix(pMatrix2);

    int** pMatrix3 = nullptr;

    // input_matrix(pMatrix1);
    // input_matrix(pMatrix2);

    print_matrix(pMatrix1);
    print_matrix(pMatrix2);

    matrix_summing(pMatrix1, pMatrix2, pMatrix3);
    print_matrix(pMatrix3);

    matrix_subtracting(pMatrix1, pMatrix2, pMatrix3);
    print_matrix(pMatrix3);

    free_matrix_space(pMatrix1);
    free_matrix_space(pMatrix2);
    free_matrix_space(pMatrix3);
    return 0;
}
