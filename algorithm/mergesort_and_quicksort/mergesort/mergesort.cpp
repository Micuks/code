#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <system_error>
#include <vector>

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
    }
    ~MergeSort() {
        delete[] a;
        delete[] b;
    }
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
    void print() {
        for (int i = 0; i < n; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << std::endl;
    }
    void fprint(std::fstream &fs) {
      fs << n << std::endl;
        for (int i = 0; i < n; i++) {
            fs << a[i] << " ";
        }
        fs << std::endl;
    }

  private:
    // assistant arrays for merge sort
    int *a;
    int *b;
    // number of given integers
    int n;
    void mergePass(int x[], int y[], int s, int n);
    void merge(int c[], int d[], int l, int m, int r);
};

/**
 * Iterative mergesort function to sort a[0, ..., n-1],
 * Merge subarrays in bottam up manner. First merge subarrays of
 * size 1 to create sorted subarrays of size 2, then merge subarrays
 * of size 2 to create sorted subarrays of size 4, and vice versa.
 */
void MergeSort::mergeSort() {
    // merge step size
    int s = 1;
    while (s < n) {
        // treat b as assistant array
        mergePass(a, b, s, n);
        s += s;
        // treat a as assistant array
        mergePass(b, a, s, n);
        s += s;
    }
}

/**
 * A pass of merge with step size of s.
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
        // append smaller element of c[i] and c[j] to d[k]
        // and increase i and k or j and k
        if (c[i] <= c[j]) {
            d[k++] = c[i++];
        } else {
            d[k++] = c[j++];
        }
    }
    // if left half of array c reaches the end, append rest elements
    // of right half of array c to d
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
    std::ios_base::sync_with_stdio(false);
    std::fstream fs;
    // Will attempt to open given file if received more then one
    // parameters.
    if (argc > 1) {
        try {
            fs.open(argv[1], std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
    } else {
        // Open default input file
        try {
            char filename[] = "samples/mergesort.in";
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
    void *p = new char[sizeof(MergeSort)];
    MergeSort *pMergeSort = new (p) MergeSort(&arr[0], arr.size());
    auto begin = std::chrono::high_resolution_clock::now();

    pMergeSort->mergeSort();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout.precision(6);
    std::cout << "[MergeSort] Time measured: " << elapsed.count() * 1e-9
              << " seconds.\n";
    // Print sorted numbers to console
    // pMergeSort->print();
    char output_file_name[] = "samples/mergesort.out";
    fs.open(output_file_name, std::ios_base::out);
    // Print sorted numbers to output_file_name
    pMergeSort->fprint(fs);
    pMergeSort->~MergeSort();
    delete[] (char *)p;
    return 0;
}
