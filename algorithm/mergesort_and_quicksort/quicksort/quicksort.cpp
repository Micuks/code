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
    int findMedian(int arr[], int n);
    int kthSmallest(int arr[], int l, int r, int k);
    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
};

void QuickSort::quickSort(int arr[], int l, int h) {
    if (l < h) {
        // Size of current subarray
        int n = h - l + 1;

        // Median of arr[]
        int med = kthSmallest(arr, l, h, n / 2);

        // Partition the array around median
        int p = partition(arr, l, h, med);

        // Recur for two halves of partition
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, h);
    }
}

int QuickSort::kthSmallest(int arr[], int l, int r, int k) {
    // Indeces range from 1.
    // If k is smaller than number of elements in array.
    if (k > 0 && k <= r - l + 1) {
        // Number of elements in arr.
        int n = r - l + 1;

        int i = 0;
        // Divide arr[] in groups of size 5, then store median
        // of each group in median[] array.
        int median[(n + 4) / 5]; // Make sure there are enough space
                                 // even if there are rest elements
                                 // after modular 5.
        for (int i = 0; i < n / 5; i++) {
            median[i] = findMedian(arr + l + 5 * i, 5);
        }
        if (5 * i < n) { // For last group with less than 5 elements.
            median[i] = findMedian(arr + l + i * 5, n % 5);
            i++;
        }

        // Recursively find median of all medians.
        int medOfMed =
            (i == 1) ? median[0] : kthSmallest(median, 0, i - 1, i / 2);

        int pos = partition(arr, l, r, medOfMed);

        if (pos - l == k - 1) {
            return arr[pos];
        } else if (pos - l > k - 1) {
            return kthSmallest(arr, l, pos - 1, k);
        }

        return kthSmallest(arr, pos + 1, r, k - (pos - l) - 1);
    }

    // If k is more than number of elements in arr[]
    return INT_MAX;
}

// A simple function to find median of arr[]. This is called
// only for an array of size 5 in this program, thus has an
// time complexity of O(1).
int QuickSort::findMedian(int arr[], int n) {
    // Simple insertion sort
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    std::cout << "[";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]" << std::endl;
    return arr[n / 2];
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
    for (int j = l; j < r - 1; j++) {
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
    pQuickSort->print();
    pQuickSort->~QuickSort();
    delete[] (char *)p;
    return 0;
}
