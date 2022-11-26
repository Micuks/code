#include <cassert>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const int MAXN = 1 << 20;
using namespace std;

template <typename T> void swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

string arrayToString(int *arr, int len) {
    stringstream ss;
    for (int i = 0; i < len; i++) {
        ss << arr[i] << " ";
    }
    ss << std::endl;
    return ss.str();
}

class Node {
  public:
    int identifier;
    int freq;
    class Node *left, *right;
};

ostream &operator<<(ostream &os, Node node) {
    os << "(" << setw(2) << node.identifier << ", " << setw(2) << node.freq
       << ")";
    return os;
}

class MinHeap {
  private:
    Node **harr;
    int capacity;
    int heapSize;

    int comparator(Node *a, Node *b) { return (a->freq - b->freq); }
    int parent(int idx) { return (idx - 1) / 2; }
    int left(int idx) { return (idx * 2) + 1; }
    int right(int idx) { return (idx * 2) + 2; }

  public:
    // Constructor
    MinHeap(int capacity);

    MinHeap(int identifiers[], int freq[], int size);

    MinHeap(MinHeap &minHeap)
        : harr(minHeap.harr), capacity(minHeap.capacity),
          heapSize(minHeap.heapSize) {}

    Node *newNode(int identifier, int freq);

    void minHeapify(int rootIdx);

    Node *extractMin();

    void insertNode(Node *minHeapNode);

    void buildMinHeap();

    bool isLeaf(Node *node) { return !(node->left) && !(node->right); }

    int getHeapSize() { return heapSize; }

    string toString();
};

MinHeap::MinHeap(int capacity) {
    heapSize = 0;
    this->capacity = capacity;
    this->harr = new Node *[capacity];
}

MinHeap::MinHeap(int identifiers[], int freq[], int size) {
    heapSize = 0;
    capacity = size;
    harr = new Node *[capacity];

    for (int i = 0; i < capacity; i++) {
        harr[i] = newNode(identifiers[i], freq[i]);
        heapSize++;
    }

    buildMinHeap();
}

Node *MinHeap::newNode(int identifier, int freq) {
    Node *tmp = new Node;
    tmp->left = tmp->right = NULL;
    tmp->identifier = identifier;
    tmp->freq = freq;

    return tmp;
};

void MinHeap::minHeapify(int rootIdx) {
    int smallest = rootIdx;
    int left = rootIdx * 2 + 1;
    int right = rootIdx * 2 + 2;
    if (left < heapSize && (comparator(harr[left], harr[smallest]) < 0)) {
        smallest = left;
    }
    if (right < heapSize && (comparator(harr[right], harr[smallest]) < 0)) {
        smallest = right;
    }
    if (smallest != rootIdx) {
        swap(harr + smallest, harr + rootIdx);
        minHeapify(smallest);
    }
}

void MinHeap::insertNode(Node *newNode) {
    int i = heapSize;
    harr[heapSize++] = newNode;
    while (i != 0 && (comparator(newNode, harr[parent(i)]) < 0)) {
        swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}

Node *MinHeap::extractMin() {
    Node *minNode = harr[0];
    harr[0] = harr[--heapSize];
    minHeapify(0);
    return minNode;
}

// Build min heap by minHeapifying from bottom to top.
void MinHeap::buildMinHeap() {
    int n = heapSize - 1;
    for (int i = parent(n); i >= 0; i--) {
        minHeapify(i);
    }
}

string MinHeap::toString() {
    stringstream ss;
    cout << "heapSize: " << heapSize << endl;
    for (int i = 0; i < heapSize; i++) {
        ss << *harr[i] << " ";
    }
    ss << std::endl;
    return ss.str();
}

class Huffman {
  private:
    MinHeap minHeap;
    Node *huffmanTree;

  public:
    Huffman(MinHeap minHeap);
    Huffman(int identifiers[], int freq[], int size);

    // Separate build huffman tree alone to test how much time it costs.
    void buildHuffmanTree();

    string minHeapToString() { return minHeap.toString(); }
    string codesToString(Node *root, int arr[], int top);
    string codesToString(int arr[], int top);
};

Huffman::Huffman(MinHeap minHeap) : minHeap(minHeap) {}

Huffman::Huffman(int identifiers[], int freq[], int size)
    : minHeap(identifiers, freq, size) {}

void Huffman::buildHuffmanTree() {
    Node *left, *right, *top;
    while (!(minHeap.getHeapSize() == 1)) {
        // Extract two minimum freq items from min heap.
        left = minHeap.extractMin();
        right = minHeap.extractMin();

        // Create a new internal node with frequency equal to the sum of the two
        // nodes' frequencies. Make the two extracted nodes as left and right
        // child of this new node.
        // Add the new internal node to the min heap. -10 is its identifier
        // which is never used.
        top = minHeap.newNode(-10, left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.insertNode(top);
    }

    // The remaining node is the root node. Now the huffman tree is complete.
    huffmanTree = minHeap.extractMin();
}

string Huffman::codesToString(Node *root, int *arr, int top) {
    stringstream ss;
    if (root->left) {
        arr[top] = 0;
        ss << codesToString(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        ss << codesToString(root->right, arr, top + 1);
    }
    if (minHeap.isLeaf(root)) {
        ss << *root << ": ";
        ss << arrayToString(arr + top, top);
    }

    return ss.str();
}

string Huffman::codesToString(int arr[], int top) {
    return codesToString(huffmanTree, arr, top);
}

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
//         std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//         begin);
//     std::cout.precision(6);
//     std::cout << "[BackPack01DP] Time measured: " << elapsed.count() *
//     1e-9
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

void huffmanCodes(int identifiers[], int freq[], int size) {
    Huffman huffman(identifiers, freq, size);
    huffman.buildHuffmanTree();
    huffman.minHeapToString();

    int huffmanArr[MAXN], top = 0;
    cout << huffman.codesToString(huffmanArr, top);
}

int stdio_main(int argc, char **argv) {
    int identifiers[] = {1, 2, 3, 4, 5, 6};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(identifiers) / sizeof(identifiers[0]);
    MinHeap minHeap(identifiers, freq, size);
    cout << minHeap.toString();
    huffmanCodes(identifiers, freq, size);

    return 0;
}

int main(int argc, char **argv) {
    stdio_main(argc, argv);
    return 0;
}
