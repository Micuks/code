#include "utils/CLIParser.hpp"
#include <cassert>
#include <chrono>
#include <climits>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int INF = 0x7fffffff;

class Edge {
  public:
    int to;
    int weight;
    Edge *next;

    Edge(int to, int weight) : to(to), weight(weight), next(nullptr){};
};

ostream &operator<<(ostream &os, const Edge &e) {
    auto edge = e;
    // Print first edge.
    os << "to[" << edge.to << "], "
       << "weight[" << edge.weight << "]" << endl;

    // Print following edges.
    while (edge.next != nullptr) {
        edge = *(edge.next);
        os << "to[" << edge.to << "], "
           << "weight[" << edge.weight << "]" << endl;
    }

    return os;
}

class Vertex {
  public:
    int idx;
    int distance;
    int parent;
    Edge *head;
    bool inMST;

    Vertex(int idx = -1, int weight = INF, Edge *head = nullptr)
        : idx(idx), distance(weight), parent(-1), head(head), inMST(false){};
    void addEdge(Edge *&edge);
};

ostream &operator<<(ostream &os, const Vertex &ver) {
    os << ver.idx << ": "
       << "distance[" << ver.distance << "], parent[" << ver.parent
       << "], inMST[" << ver.inMST << "], edges:" << endl;

    // Print edges.
    if (ver.head != nullptr)
        os << *(ver.head);

    return os;
}

// Only insert new edge with new following edges.
void Vertex::addEdge(Edge *&edge) {
    assert(edge->next == nullptr);
    // Allocate and push new edge to vertex a's adjacent list.
    if (this->head == nullptr) {
        this->head = edge;
    } else {
        auto last_edge = this->head;
        // Find last edge in thistex a's adjacent list.
        while (last_edge->next != nullptr) {
            last_edge = last_edge->next;
        }
        // Link new edge next to last_edge's next.
        last_edge->next = edge;
    }
}

class CmpVertexPtr {
  public:
    bool operator()(const Vertex *a, const Vertex *b) const {
        return a->distance < b->distance;
    }
};

class Prim {
  public:
    vector<Vertex *> vertices;
    int begin;
    int target;
    int weight_sum;

    const string vertices_to_string() const;
    const int prim_MST();
    Prim(vector<Vertex *> &vers, int begin)
        : vertices(vers), begin(begin), target(begin), weight_sum(0){};
};

const string Prim::vertices_to_string() const {
    stringstream ss;
    // vertices.size() = V + 1
    for (size_t i = 1; i < vertices.size(); i++) {
        ss << *(vertices[i]);
    }
    return ss.str();
}

const int Prim::prim_MST() {
    priority_queue<Vertex *, vector<Vertex *>, CmpVertexPtr> pq;
    // Initialize the distance between begin and begin to 0.
    auto ver = vertices.at(begin);
    ver->distance = 0;

    // Initialize pq by pushing begin vertex into pq.
    pq.push(ver);

    // Build MST using MinHeap.
    while (!pq.empty()) {
        // Pick the neighbor vertex with minimal distance, add it to set S.
        ver = pq.top();
        pq.pop();

        // Skip current vertex if it is already in MST.
        if (ver->inMST) {
            continue;
        }

        // Target vertex is the last vertex to be included in the MST.
        // By using this, we can find targe vertex. Thus can print the MST with
        // the help of Vertex.parent.
        // Compute the sum of weights when building MST.
        ver->inMST = true;
        target = ver->idx;
        weight_sum += ver->distance;

        // Iterate through ver's neighbor vertices.
        auto edge = ver->head;
        while (edge != nullptr) {
            auto neighbor_ver = vertices[edge->to];
            // Skip neighbor vertices that are already in MST.
            if (neighbor_ver->inMST) {
                edge = edge->next;
                continue;
            }
            // Update neighbor_ver's distance to begin vertex.
            if (neighbor_ver->distance > edge->weight) {
                neighbor_ver->distance = edge->weight;
            }
            pq.push(neighbor_ver);

            // Iterate next edge in vertex's adjacent list.
            edge = edge->next;
        }
    }

    return weight_sum;
}

int fs_main(int argc, char **argv) {
    CLIParser cliParser(argc, argv);
    cliParser.args["--in"] = "data/prim.in";
    cliParser.args["--out"] = "data/prim.out";
    cliParser.argParse();

    fstream fs;
    try {
        fs.open(cliParser.args["--in"], ios_base::in);
    } catch (std::exception &e) {
        cerr << e.what();
        cerr << "Failed to load data from " << cliParser.args["--in"]
             << ". Exit now.";
        exit(-1);
    }

    cout << "Load data from: " << cliParser.args["--in"] << endl;
    cout << "Write data to: " << cliParser.args["--out"] << endl;

    int V, E;
    fs >> V >> E;

    // Initialize vertices.
    vector<Vertex *> vertices;
    for (int i = 0; i <= V; i++) {
        vertices.emplace_back(new Vertex(i));
    }

    for (int i = 0; i < E; i++) {
        int idx_a, idx_b, weight;
        fs >> idx_a >> idx_b >> weight;

        // Initialize vertex a.
        auto ver = vertices.at(idx_a);
        assert(ver->idx == idx_a);
        Edge *edge = new Edge(idx_b, weight);
        ver->addEdge(edge);

        // Initialize vertex b.
        ver = vertices.at(idx_b);
        assert(ver->idx == idx_b);
        edge = new Edge(idx_a, weight);
        ver->addEdge(edge);
    }

    // Initialize Prim which treats vertex 1 as source of MST.
    Prim prim(vertices, 1);
    // cout << prim.vertices_to_string() << endl;

    // End of read and initialize prim.
    fs.close();

    // Use timer to record how much time the Prim algorithm with MinHeap
    // optimization consumes.

    auto begin = chrono::high_resolution_clock::now();

    // Prim algorithm build MST.
    auto result = prim.prim_MST();

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout.precision(6);
    cout << "[Prim] Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";

    // print vertces for debug purpose.
    // cout << prim.vertices_to_string();

    // Print result for debug purpose.
    cout << result << endl;

    // Write result to file.
    fs.open(cliParser.args["--out"], ios_base::out);
    fs << result << endl;
    fs.close();

    return 0;
}

int main(int argc, char **argv) { return fs_main(argc, argv); }
