#include "utils/CLIParser.hpp"
#include <cassert>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

const int MAXN = 1 << 20;
using namespace std;

// MinHeap
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

// Dijkstra
class Edge {
  public:
    int len;
    int to;
    Edge *next;
    Edge() : len(0), to(0), next(nullptr){};
    Edge(int to, int len = 0x7fffffff, Edge *next = nullptr)
        : len(len), to(to), next(next){};
};

ostream &operator<<(ostream &os, Edge &edge) {
    os << "To[" << edge.to << "], Len[" << edge.len << "]";
    return os;
}

class Node {
  public:
    int idx;
    int dis;
    bool visited;
    Edge *head;
    Node() : idx(-1), dis(0x7fffffff), visited(false), head(nullptr){};
    Node(int node, int dis, bool visited = false)
        : idx(node), dis(dis), visited(visited){};
    bool operator<(const Node &y) const { return y.dis < dis; }
    void linkEdge(Edge *&edge) {
        if (this->head == nullptr) {
            this->head = edge;
        } else {
            auto pEdge = this->head;
            while (pEdge->next != nullptr) {
                // cout << "[" << *pEdge << "]";
                pEdge = pEdge->next;
                // cout << ".nextEdge[" << *pEdge << "] ";
            }
            // now pEdge points to the last edge in current node's adjancent
            // list.
            pEdge->next = edge;
        }
    }
};

ostream &operator<<(ostream &os, Node &node) {
    os << node.idx << ": "
       << "dis[" << node.dis << "], vis[" << node.visited << "], edges:\n";
    Edge *edge = node.head;
    do {
        os << *edge << endl;
    } while ((edge = edge->next) != nullptr);

    return os;
}

class Dijkstra {
  private:
    int begin;
    int end;
    vector<Node *> nodes;

    class CmpNodePtrs {
      public:
        bool operator()(const Node *lhs, const Node *rhs) const {
            return lhs->dis > rhs->dis;
        }
    };

  public:
    Dijkstra(int begin, int end, vector<Node *> &nodes);
    int dijkstra();
};

Dijkstra::Dijkstra(int begin, int end, vector<Node *> &nodes)
    : begin(begin), end(end), nodes(nodes){};

// Do dijkstra computation. Return distance from begin node to end node.
int Dijkstra::dijkstra() {
    priority_queue<Node *, vector<Node *>, CmpNodePtrs> pq;
    nodes.at(begin)->dis = 0;
    pq.push(nodes.at(begin));

    while (!pq.empty()) {
        Node *node = pq.top();
        pq.pop();
        // Skip nodes that has already visited.
        if (node->visited) {
            continue;
        }

        // Return immediately once we reach the end node.
        // if (node->idx == end) {
        //     return node->dis;
        // }

        node->visited = true;
        Edge *edge = node->head;
        // Iter through current node's edges.
        do {
            Node *nextNode = nodes.at(edge->to);
            // Renew the distance from start point to next node.
            if (nextNode->dis > node->dis + edge->len) {
                nextNode->dis = node->dis + edge->len;
                // If next node has not been visited, push it to priority queue.
                if (!nextNode->visited) {
                    pq.push(nextNode);
                }
            }
        } while ((edge = edge->next) != nullptr);
    }

    return (nodes.at(end)->dis == 0x7fffffff) ? -1 : nodes.at(end)->dis;
}

int fstream_main(int argc, char **argv) {
    CLIParser cliParser(argc, argv);
    cliParser.args["--in"] = "data/dijkstra.in";
    cliParser.args["--out"] = "data/dijkstra.out";
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
    // assert(fs.is_open() == true);

    int V, E;
    fs >> V >> E;
    cout << V << " " << E << endl;

    vector<Node *> nodes;
    for (int i = 0; i <= V; i++) {
        Node *node = new Node();
        nodes.emplace_back(node);
    }

    for (int i = 1; i <= E; i++) {
        int nodeA, nodeB, dis;
        fs >> nodeA >> nodeB >> dis;

        // Add edge to nodeA
        Edge *tmp = new Edge(nodeB, dis);
        Node *node = nodes.at(nodeA);
        node->idx = nodeA;
        // Link new edge to nodeA's adjacent list.
        node->linkEdge(tmp);

        // Add edge to nodeB
        tmp = new Edge(nodeA, dis);
        node = nodes.at(nodeB);
        node->idx = nodeB;
        // Link new edge to nodeB's adjacant list.
        node->linkEdge(tmp);
    }

    for (int i = 1; i <= V; i++) {
        cout << *nodes.at(i) << endl;
    }

    Dijkstra dij(1, V, nodes);

    fs.close();

    auto begin = std::chrono::high_resolution_clock::now();

    int result = dij.dijkstra();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout.precision(6);
    std::cout << "[dijkstra] Time measured: " << elapsed.count() * 1e-9
              << " seconds.\n";

    for (int i = 1; i <= V; i++) {
        cout << *nodes.at(i) << endl;
    }

    cout << result << endl;

    fs.open(cliParser.args["--out"], std::ios_base::out);
    // Print sorted numbers to output_file_name
    fs << result << std::endl;
    fs.close();

    return 0;
}

int stdio_main(int argc, char **argv) {
    int V, E;
    cin >> V >> E;
    vector<Node *> nodes;
    for (int i = 0; i <= V; i++) {
        Node *node = new Node();
        nodes.emplace_back(node);
    }

    for (int i = 1; i <= E; i++) {
        int nodeA, nodeB, dis;
        cin >> nodeA >> nodeB >> dis;

        // Add edge to nodeA
        Edge *tmp = new Edge(nodeB, dis);
        Node *node = nodes.at(nodeA);
        node->idx = nodeA;
        node->head = tmp;

        // Add edge to nodeB
        tmp = new Edge(nodeA, dis);
        node = nodes.at(nodeB);
        node->idx = nodeB;
        node->head = tmp;
    }

    Dijkstra dij(1, V, nodes);
    cout << dij.dijkstra();
    return 0;
}

int main(int argc, char **argv) {
    // stdio_main(argc, argv);
    fstream_main(argc, argv);
    return 0;
}
