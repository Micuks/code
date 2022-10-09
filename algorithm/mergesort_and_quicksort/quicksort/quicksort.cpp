#include <chrono>
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <system_error>
#include <vector>

/**
 *
 */
class QuickSort {
  public:
    QuickSort(int *_arr, int _n) : n(_n) {
        arr = new int[n + 1];
        memcpy(arr, _arr, _n * sizeof(int));
        quickSort(arr, 0, n - 1);
    }
    ~QuickSort() { delete[] arr; }
    void quickSort(int arr[], int l, int h);
    void print() {
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    void fprint(std::fstream &fs) {
        fs << n << std::endl;
        for (int i = 0; i < n; i++) {
            fs << arr[i] << " ";
        }
        fs << std::endl;
    }

  private:
    // array to store integers
    int *arr;
    // number of given integers
    int n;
    int partition(int arr[], int l, int r, int k);
    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
};

/**
 * Main function to perform quicksort on arr[],
 * optimized with **tail call elimination**
 */
void QuickSort::quickSort(int arr[], int l, int h) {
    while (l < h) {
        // Median of arr[]
        int pivor = arr[(l + h) / 2];

        // Partition the array around median
        int p = partition(arr, l, h, pivor);

        // If left half has less elements, recur for left half.
        // Else recur for right half.
        if (p - l < h - p) {
            quickSort(arr, l, p - 1);
            l = p + 1;
        } else {
            quickSort(arr, p + 1, h);
            h = p - 1;
        }
    }
}

// Search for x in arr[l, ..., r], then partition
// arr[] around x.
int QuickSort::partition(int arr[], int l, int r, int x) {
    int i = 0;
    // Search for x in arr[l, ..., r], if found, move it to end
    for (i = l; i < r; i++) {
        if (arr[i] == x) {
            break;
        }
    }
    swap(arr + i, arr + r);

    // Make partition
    i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(arr + i, arr + j);
            i++;
        }
    }
    swap(arr + i, arr + r);
    return i;
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
            char filename[] = "samples/quicksort.in";
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
    void *p = new char[sizeof(QuickSort)];
    QuickSort *pQuickSort = new (p) QuickSort(&arr[0], arr.size());
    int n = arr.size();
    auto begin = std::chrono::high_resolution_clock::now();

    pQuickSort->quickSort(&arr[0], 0, n - 1);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout.precision(6);
    std::cout << "[QuickSort] Time measured: " << elapsed.count() * 1e-9
              << " seconds.\n";
    char output_file_name[] = "samples/quicksort.out";
    fs.open(output_file_name, std::ios_base::out);
    // Print sorted numbers to output_file_name
    pQuickSort->fprint(fs);
    // Print sorted numbers to console
    pQuickSort->~QuickSort();
    delete[] (char *)p;
    return 0;
}
