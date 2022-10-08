#include <cstring>
#include <fstream>
#include <iostream>
#include <system_error>
#include <vector>

using namespace std;

/**
 * The non-recursive implementation of mergesort algorithm for integers
 */
// template<typename T>
class MergeSort {
  public:
    MergeSort(int *_a, int _n) : n(_n) {
        a = new int[n + 1];
        b = new int[n + 1];
        memcpy(a, _a, _n * sizeof(int));
        printA();
        printB();
    }
    ~MergeSort() { delete[] a; }
    void mergeSort();
    void printA() {
        std::cout << "Array A:\n";
        for (int i = 0; i < n; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << std::endl;
    }
    void printB() {
        std::cout << "Array B:\n";
        for (int i = 0; i < n; i++) {
            std::cout << b[i] << " ";
        }
        std::cout << std::endl;
    }

  private:
    void mergePass(int x[], int y[], int s, int n);
    void merge(int c[], int d[], int l, int m, int r);
    // assistant arrays for merge sort
    int *a;
    int *b;
    // number of given integers
    int n;
};

/**
 * Iterative mergesort function to sort a[0, ..., n-1]
 */
void MergeSort::mergeSort() {
    // merge step size
    int s = 1;
    cout<<endl;
    while (s < n) {
        // treat b as assistant array
        mergePass(a, b, s, n);
        // exponential increase step size
        cout << "s["<<s<<"]"<<endl;
        printA();
        printB();
        cout<<endl;
        s += s;
        // treat a as assistant array
        mergePass(b, a, s, n);
        // exponential increase step size
        cout << "s["<<s<<"]"<<endl;
        printA();
        printB();
        cout<<endl;
        s += s;
    }
}

/**
 * Merge subarrays in bottam up manner. First merge subarrays of
 * size 1 to create sorted subarrays of size 2, then merge subarrays
 * of size 2 to create sorted subarrays of size 4, and vice versa.
 */
void MergeSort::mergePass(int *x, int *y, int s, int n) {
    int i = 0;
    // mergesort until less than 2*s elements left.
    while (i + 2 * s - 1 < n) {
        merge(x, y, i, i + s - 1, i + 2 * s - 1);
        i += 2 * s;
    }
    if (i + s - 1 < n) {
        merge(x, y, i, i + s - 1, n - 1);
    } else {
        for (int j = i; j <= n - 1; j++) {
            y[j] = x[j];
        }
    }
}

/**
 * Function to merge the two halves c[l, ..., m] and c[m+1, ..., r]
 * to d
 */
void MergeSort::merge(int *c, int *d, int l, int m, int r) {
    int i = l;
    int j = m + 1;
    int k = i;
    // Merge the two halves of array c to array d
    while ((i <= m) && (j <= r)) {
        if (c[i] <= c[j]) {
            d[k++] = c[i++];
        } else {
            d[k++] = c[j++];
        }
    }
    if (i > m) {
        // Copy the remaining elements in the left half of c to d
        while (j <= r) {
            d[k++] = c[j++];
        }
    } else {
        // Copy the remaining elements in the right half of c to d
        while (i <= m) {
            d[k++] = c[i++];
        }
    }
}

int main(int argc, char **argv) {
    std::fstream fs;
    // Will attempt to open given file if received more then one
    // parameters.
    if (argc > 1) {
        try {
            fs.open(argv[1], std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
        std::cout << argv[1] << std::endl; // debug
    } else {
        // Open default input file
        try {
            char filename[] = "samples/mergesort.in";
            std::cout << filename << std::endl; // debug
            fs.open(filename, std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
    }

    int num;
    fs >> num; // eat n
    std::vector<int> arr;
    while (fs >> num) {
        arr.push_back(num);
    }
    fs.close();
    std::cout << std::endl;
    MergeSort mSort(&arr[0], arr.size());
    mSort.mergeSort();
    mSort.printA();
    mSort.printB();

    return 0;
}
