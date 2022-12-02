#include "utils/CLIParser.hpp"
#include <cassert>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

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
        ss << arr[i];
    }
    ss << std::endl;
    return ss.str();
}

class Node {
  public:
    int identifier;
    double freq;
    Node *left, *right;
    Node(int identifier = -10, double freq = 0.0, Node *left = nullptr,
         Node *right = nullptr)
        : identifier(identifier), freq(freq), left(left), right(right) {}
};

ostream &operator<<(ostream &os, Node node) {
    os << setw(2) << "(" << node.identifier << ", " << setw(2) << node.freq
       << ")";
    return os;
}

class MinHeap {
  private:
    Node **harr;
    int capacity;
    int heapSize;

    double comparator(Node *a, Node *b) { return (a->freq - b->freq); }
    int parent(int idx) { return (idx - 1) / 2; }
    int left(int idx) { return (idx * 2) + 1; }
    int right(int idx) { return (idx * 2) + 2; }

  public:
    // Constructor
    MinHeap(int capacity);

    MinHeap(int identifiers[], double freq[], int size);
    MinHeap(double freq[], int size);

    MinHeap(MinHeap &minHeap)
        : harr(minHeap.harr), capacity(minHeap.capacity),
          heapSize(minHeap.heapSize) {}

    Node *newNode(int identifier, double freq);

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

MinHeap::MinHeap(double freq[], int size) {
    int *identifiers = new int[size];
    for (int i = 0; i < size; i++) {
        identifiers[i] = i;
    }
    heapSize = 0;
    capacity = size;
    harr = new Node *[capacity];

    for (int i = 0; i < capacity; i++) {
        harr[i] = newNode(identifiers[i], freq[i]);
        heapSize++;
    }
    buildMinHeap();
}

MinHeap::MinHeap(int identifiers[], double freq[], int size) {
    heapSize = 0;
    capacity = size;
    harr = new Node *[capacity];

    for (int i = 0; i < capacity; i++) {
        harr[i] = newNode(identifiers[i], freq[i]);
        heapSize++;
    }

    buildMinHeap();
}

Node *MinHeap::newNode(int identifier, double freq) {
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
    for (int i = 0; i < heapSize; i++) {
        ss << *harr[i] << " ";
    }
    ss << std::endl;
    return ss.str();
}

class CmpNodePtrs {
  public:
    bool operator()(const Node *lhs, const Node *rhs) const {
        return lhs->freq > rhs->freq;
    }
};

class Huffman {
  private:
    MinHeap minHeap;
    Node *huffmanTree;

  public:
    Huffman(MinHeap minHeap);
    Huffman(int identifiers[], double freq[], int size);
    Huffman(double freq[], int size);

    // Separate build huffman tree alone to test how much time it costs.
    void buildHuffmanTree();
    void priority_queue_huild_huffman_tree();

    double getExpectation(double &exp, int top);
    double getExpectation(Node *root, double &exp, int top);

    string codesToString(Node *root, int arr[], int top);
    string codesToString(int arr[], int top);
};

Huffman::Huffman(MinHeap minHeap) : minHeap(minHeap) {}

Huffman::Huffman(int identifiers[], double freq[], int size)
    : minHeap(identifiers, freq, size) {}
Huffman::Huffman(double freq[], int size) : minHeap(freq, size) {}

void Huffman::buildHuffmanTree() {
    Node *left, *right, *top;

    while (!(minHeap.getHeapSize() == 1)) {
        // Extract two minimum freq items from min heap.
        left = minHeap.extractMin();
        right = minHeap.extractMin();
        // cout << *left << ", " << *right << endl;

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

void Huffman::priority_queue_huild_huffman_tree() {
    priority_queue<Node *, vector<Node *>, CmpNodePtrs> pqHeap;
    while (minHeap.getHeapSize()) {
        pqHeap.push(minHeap.extractMin());
    }

    while (pqHeap.size() > 1) {
        auto left = pqHeap.top();
        pqHeap.pop();
        auto right = pqHeap.top();
        pqHeap.pop();

        auto new_node = new Node(-10, left->freq + right->freq, left, right);
        pqHeap.push(new_node);
    }

    huffmanTree = pqHeap.top();
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
        ss << arrayToString(arr, top);
    }

    return ss.str();
}

string Huffman::codesToString(int arr[], int top) {
    return codesToString(huffmanTree, arr, top);
}

double Huffman::getExpectation(double &exp, int top) {
    return getExpectation(huffmanTree, exp, top);
}

// Get expectation of Huffman code length by adding each leaf's code length *
// appearance frequnce recursively in DFS way.
double Huffman::getExpectation(Node *root, double &exp, int top) {
    if (root->left) {
        exp += getExpectation(root->left, exp, top + 1);
    }
    if (root->right) {
        exp += getExpectation(root->right, exp, top + 1);
    }
    if (minHeap.isLeaf(root)) {
        return top * root->freq;
    }
    return 0.0;
}

int fstream_main(int argc, char **argv) {
    CLIParser cliParser(argc, argv);
    cliParser.args["--in"] = "../data/huffman/huffman.in";
    cliParser.args["--out"] = "../data/huffman/huffman.out";
    cliParser.argParse();

    fstream fs;
    try {
        fs.open(cliParser.args["--in"], ios_base::in);
    } catch (std::system_error &e) {
        cerr << e.what();
        exit(-1);
    }

    cout << cliParser.args["--in"] << endl;
    cout << cliParser.args["--out"] << endl;

    int size;
    fs >> size;

    double freq[size];
    for (int i = 0; i < size; i++) {
        fs >> freq[i];
    }

    Huffman huffman(freq, size);
    fs.close();

    double exp = 0;
    auto begin = std::chrono::high_resolution_clock::now();

    // BUG: Bug in self-implemented Min Heap.
    // huffman.buildHuffmanTree();
    huffman.priority_queue_huild_huffman_tree();
    huffman.getExpectation(exp, 0);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout.precision(6);
    std::cout << "[Huffman] Time measured: " << elapsed.count() * 1e-9
              << " seconds.\n";

    // Max precision for double.
    cout << "Expectation:\n" << fixed << setprecision(3) << exp << endl;

#ifdef DEBUG
    int huffmanArr[MAXN], top = 0;
    cout << huffman.codesToString(huffmanArr, top);

#endif // DEBUG

    fs.open(cliParser.args["--out"], std::ios_base::out);
    // Print sorted numbers to output_file_name
    fs << fixed << setprecision(3) << exp << std::endl;
    fs.close();

    return 0;
}

int main(int argc, char **argv) {
    fstream_main(argc, argv);
    return 0;
}
