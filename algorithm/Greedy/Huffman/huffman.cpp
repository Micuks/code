#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>

using namespace std;

template <typename T> void swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

class MinHeap {
  private:
    int *harr;
    int capacity;
    int heapSize;

  public:
    // Constructor
    MinHeap(int capacity);

    // Heapify a subtree with the root at given index
    void minHeapify(int rootIdx);

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    // Get root, then let root be INT_MAX, do minHeapify, descend heapSize by 1.
    int extractMin();
    void decKey(int i, int newVal);

    int getMin() { return harr[0]; }

    // Delete key at i.
    void delKey(int i);
    void insertKey(int k);
};

MinHeap::MinHeap(int capacity) {
    harr = new int[capacity];
    this->capacity = capacity;
    cout << "capacity[" << this->capacity << "]" << endl;
    heapSize = 0;
}

// Heapify the min heap recuesively. Assuming that the subtrees of node at
// rootIdx has already been heapified.
void MinHeap::minHeapify(int rootIdx) {
    int l = left(rootIdx);
    int r = right(rootIdx);
    int smallest = rootIdx;
    if (l < heapSize && harr[l] < harr[rootIdx]) {
        smallest = l;
    }
    if (r < heapSize && harr[r] < harr[smallest]) {
        smallest = r;
    }
    if (smallest != rootIdx) {
        swap(harr + rootIdx, harr + smallest);
        minHeapify(smallest);
    }
}

int MinHeap::extractMin() {
    int min = getMin();
    harr[0] = harr[heapSize - 1];
    heapSize--;
    minHeapify(0);

    return min;
}

void MinHeap::decKey(int i, int newVal) {
    cout << "i[" << i << "],heapSize[" << heapSize << "]" << endl;
    assert(i < heapSize);
    harr[i] = newVal;
    while (i != 0 && harr[parent(i)] > harr[i]) {
        swap(harr + i, harr + parent(i));
        i = parent(i);
    }
}

void MinHeap::delKey(int i) {
    harr[i] = INT_MAX;
    minHeapify(0);
    heapSize--;
}

void MinHeap::insertKey(int k) {
    assert(heapSize < capacity);
    int i = heapSize;
    harr[heapSize++] = k;
    cout << "k: " << k << ", heapSize: " << heapSize << endl;
    while (i != 0 && harr[parent(i)] > harr[i]) {
        swap(harr + i, harr + parent(i));
        i = parent(i);
    }
}

class Huffman {};

// int fstream_main(int argc, char **argv) {
//     // std::ios_base::sync_with_stdio(false);
//     fstream fs;
//     // Will attempt to open given file if received more then one
//     // parameters.
//     if (argc > 1) {
//         try {
//             fs.open(argv[1], std::ios_base::in);
//         } catch (std::system_error &e) {
//             std::cerr << e.code().message() << std::endl;
//             exit(-1);
//         }
//     } else {
//         // Open default input file
//         try {
//             char filename[] = "samples/bag.in";
//             fs.open(filename, std::ios_base::in);
//         } catch (std::system_error &e) {
//             std::cerr << e.code().message() << std::endl;
//         }
//     }
//
//     assert(fs.is_open() == true);
//
//     void *p = new char[sizeof(Huffman)];
//     bool verbose = true;
//     Huffman *huffMan = new (p) Huffman(fs, verbose);
//     fs.close();
//
//     auto begin = std::chrono::high_resolution_clock::now();
//
//     __huffman__();
//
//     auto end = std::chrono::high_resolution_clock::now();
//     auto elapsed =
//         std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//     std::cout.precision(6);
//     std::cout << "[BackPack01DP] Time measured: " << elapsed.count() * 1e-9
//               << " seconds.\n";
//
//     char output_file_name[] = "samples/bag.out";
//     fs.open(output_file_name, std::ios_base::out);
//     // Print sorted numbers to output_file_name
//     fs << *backPack01 << std::endl;
//     fs.close();
//
//     if (verbose) {
//         backPack01->backTrace();
//     }
//     std::cout << *backPack01 << std::endl;
//
//     backPack01->~BackPack01();
//     delete[] (char *)p;
//     return 0;
// }

int stdio_main(int argc, char **argv) {
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.delKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    cout << h.extractMin() << endl;
    cout << h.getMin() << endl;
    h.decKey(2, 1);
    cout << h.getMin();
    return 0;
}

int main(int argc, char **argv) {
    stdio_main(argc, argv);
    return 0;
}
