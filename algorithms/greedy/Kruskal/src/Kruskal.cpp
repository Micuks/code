#include "utils/CLIParser.hpp"
#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

// Kruskal is Edge - oriented, so there's no need to implement adjacent list for
// vertices.
typedef int Vertex;
typedef int Distance;
typedef int Weight;

template <typename T> string set_to_string(unordered_set<T *> set) {
    stringstream ss;
    for (auto &a : set) {
        ss << *a << " ";
    }
    return ss.str();
}

class ConnectedBranch {
  public:
    // Vertices in the connected branch.
    unordered_set<Vertex, vector<Vertex>, equal_to<Vertex>> vertices;

    ConnectedBranch(){};
};

class Edge {
  public:
    Vertex a;
    Vertex b;
    Weight weight;
    Edge(const Vertex &a, const Vertex &b, int weight)
        : a(a), b(b), weight(weight){};
    Edge(const Edge &e) : a(e.a), b(e.b), weight(e.weight){};
};

ostream &operator<<(ostream &os, const Edge &edge) {
    if (edge.a <= edge.b) {
        os << "(" << edge.a << ", " << edge.b << "): " << edge.weight;
    } else {
        os << "(" << edge.b << ", " << edge.a << "): " << edge.weight;
    }
    return os;
}

bool operator==(const Edge &edge_a, const Edge &edge_b) {
    return ((edge_a.weight == edge_b.weight) &&
            (((edge_a.a == edge_b.a) && (edge_a.b == edge_b.b)) ||
             ((edge_a.b == edge_b.a) && (edge_a.a == edge_b.b))));
}

/**
 * Edge hasher for unordered_set.
 */
class EdgeHash {
  public:
    size_t operator()(const Edge &edge) const {
        return hash<int>()(edge.a + edge.b + edge.weight);
    }
};

/**
 * Edge equal for unordered_set.
 */
class EdgeEq {
  public:
    bool operator()(const Edge &a, const Edge &b) const { return a == b; }
};

/**
 * Edge pointer comparator for priority_queue.
 */
class CmpEdgePtr {
  public:
    bool operator()(const Edge *edge_a, const Edge *edge_b) const {
        auto greater = [&](auto a, auto b) { return a > b; };
        auto eq = [&](auto a, auto b) { return a == b; };

        if (eq(edge_a->weight, edge_b->weight)) {
            if (eq(edge_a->a, edge_b->a)) {
                return greater(edge_a->b, edge_b->b);
            } else {
                return greater(edge_a->a, edge_b->a);
            }
        }
        return edge_a->weight > edge_b->weight;
    }
};

/**
 * Edge comparator for priority_queue
 */
class CmpEdge {
  public:
    bool operator()(const Edge eda, const Edge edb) const {
        if (eda.weight == edb.weight) {
            if (eda == edb) {
                return false;
            } else {
                if (eda.a == edb.a) {
                    return eda.b > edb.b;
                } else {
                    return eda.a > edb.a;
                }
            }
        } else {
            return eda.weight > edb.weight;
        }
    }
};

class Kruskal {
  public:
    Vertex source;
    // Number of edges.
    int e;
    // Number of vertices.
    int v;
    // Sum of weights of edges in MST.
    Weight weight_sum;

    unordered_set<Edge, EdgeHash, EdgeEq> edges_in_mst;
    unordered_set<Vertex, hash<Vertex>, equal_to<Vertex>> vertices_in_mst;

    vector<Edge> edges;

    Kruskal(Vertex source, int e, int v, vector<Edge> &edges)
        : source(source), e(e), v(v), weight_sum(0), edges(edges){};
    Distance kruskal_MST();

    // Debug strings.
    string ver_in_mst_to_string() const;
    string edges_in_mst_to_string() const;
};

string Kruskal::ver_in_mst_to_string() const {
    stringstream ss;
    ss << vertices_in_mst.size() << " Vertices in MST: \n";
    for (auto &a : vertices_in_mst) {
        ss << a << " ";
    }
    return ss.str();
}

string Kruskal::edges_in_mst_to_string() const {
    stringstream ss;
    ss << edges_in_mst.size() << " Edges in MST:\n";
    for (auto &a : edges_in_mst) {
        ss << a << endl;
    }
    return ss.str();
}

Distance Kruskal::kruskal_MST() {
    // Use MinHeap to optimize.
    priority_queue<Edge, vector<Edge>, CmpEdge> heap;

    /** Initialize all connected branches by treating all vertices as indepedent
     * connected branch.
     *
     * To merge two connected branches i and j, let
     * branches[i] and branches[j] point to the same ConnectedBranch after
     * unordered_set::merge.
     * To check whether Vertex a and Vertex b are in the same ConnectedBranch,
     * Test if branches[a].contains(b);
     */
    typedef unordered_set<Vertex> ConnectedBranch;
    vector<ConnectedBranch *> branches;

    // Detemine whether two vertices are in the same branch.
    auto in_same_branch = [&](Vertex a, Vertex b) {
        return (branches[a]->find(b) != branches[a]->end());
    };

    // Merge two ConnectedBranched.
    auto merge_branches = [&](ConnectedBranch *&p_branch_a,
                              ConnectedBranch *&p_branch_b) {
        auto new_branch = new ConnectedBranch;
        merge(p_branch_a->begin(), p_branch_a->end(), p_branch_b->begin(),
              p_branch_b->end(), inserter(*new_branch, new_branch->begin()));

        // Modify branches in new_branch to point to new_branch and free
        // p_branch_a and p_branch_b' memory. Assuming that the two branches are
        // in different branches.
        delete p_branch_a;
        delete p_branch_b;
        for (auto &ver : *new_branch) {
            branches[ver] = new_branch;
        }
    };

    for (Vertex i = 0; i <= v; i++) {
        auto new_branch = new ConnectedBranch;
        new_branch->insert(i);
        branches.push_back(new_branch);
    }

    // Inithalize MinHeap by pushing all edges in.
    for (auto &e : edges) {
        // Copy construct when push.
        heap.push(e);
    }
#ifdef DEBUG
    cout << "edges[" << edges.size() << "], heap[" << heap.size() << "]"
         << endl;

#endif // DEBUG

    // Count merge times.
    int merge_cnt = 0;

    // Pick edges to build Minimal Spanning Tree until all vertices exist in
    // MST.
    while ((merge_cnt < v - 1) && !(heap.empty())) {
        // Pick edge with minimal weight from MinHeap.
        auto e = heap.top();
        heap.pop();
        // cout << "Current edge: " << e << endl;

        /**
         * TODO: Considering the requirement of starting from source, skip the
         * edges with source vertex as one of its endpoints when source vertex
         * is already in the MST.
         *
         * WARNING: However, by doing so, the Kruskal algorithm can be proven to
         * be wrong.
         *
         * TODO: Prove that it is illegal to provide Kruskal a specific source.
         */
        /**
         * if (in_edge(source) && in_mst(source)) {
         *    cout << "source[" << source << "] already in MST, "
         *         << "skip edge: " << e << endl;
         *    continue;
         * }
         */

        // If neither of its two endpoints is already in MST,
        //     append this edge and its two endpoints to MST.
        if (!in_same_branch(e.a, e.b)) {
            vertices_in_mst.insert(e.a);
            vertices_in_mst.insert(e.b);
            // Collect edges in MST for debug purpose.
            edges_in_mst.insert(e);

            // Merge two endpoints' connected branches.
            merge_branches(branches[e.a], branches[e.b]);
            merge_cnt++;

            // Add current edge's weight to weight sum of MST.
            weight_sum += e.weight;
        }
    }

    // Return sum of weights of edges in MST.
    return weight_sum;
}

int main(int argc, char **argv) {
    CLIParser cliParser(argc, argv);
    cliParser.args["--in"] = "data/kruskal.in";
    cliParser.args["--out"] = "data/kruskal.out";
    cliParser.argParse();
    auto in_file = cliParser.args["--in"];
    auto out_file = cliParser.args["--out"];

    fstream fs;
    try {
        fs.open(cliParser.args["--in"], ios_base::in);
    } catch (exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to load data from " << cliParser.args["--in"]
             << ".\nExiting..." << endl;
        exit(-1);
    }

    cout << "Load data from: " << in_file << endl;
    cout << "Write data to: " << out_file << endl;

    // Read data from file with exception handler.
    int v, e;

    try {
        fs >> v >> e;
    } catch (exception &e) {
        cerr << "Error occurred during reading V and E:\n" << e.what();
        exit(-1);
    }

    // Initialize edges.
    vector<Edge> edges;
    // Considering that vertex index in sample starts from 1.
    for (int i = 0; i < e; i++) {
        Vertex a, b;
        Weight w;
        try {
            fs >> a >> b >> w;
        } catch (exception &e) {
            cerr << "Error occurred during read edge:\n" << e.what();
            exit(-1);
        }

        Edge edge = Edge(a, b, w);
        edges.emplace_back(edge);
    }

#ifdef DEBUG
    auto edges_to_string = [&](vector<Edge> edges) { // Print edges.
        auto in_edge = [&](Vertex v, Edge edge) {
            return ((edge.a == v) || (edge.b == v));
        };
        stringstream ss;

        // First, print edges in vertices' view.
        for (int i = 1; i <= v; i++) {
            ss << i << ":\n";
            for (auto &e : edges) {
                if (in_edge(i, e)) {
                    ss << "to[" << ((e.a == i) ? e.b : e.a) << "], weight["
                       << e.weight << "]\n";
                }
            }
        }
        cout << endl << "Edges:" << endl;

        // Second, print edges in edges' view.
        for (auto &e : edges) {
            ss << e << endl;
        }
        return ss.str();
    };

    cout << edges_to_string(edges) << endl;

#endif // DEBUG

    // End of data loading, close filestream.
    fs.close();

    // Initialize Kruskal.
    // Build Kruskal MST from vertex 1.
    Vertex source = 1;
    Kruskal kruskal(source, e, v, edges);

    // Initialize timer.
    auto begin = chrono::high_resolution_clock::now();

    // Kruskal build MST.
    auto distance = kruskal.kruskal_MST();

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout.precision(6);
    cout << "[Kruskal] Time measured: " << elapsed.count() * 1e-9
         << " seconds.\n";

#ifdef DEBUG
    // Print vertices in MST to debug.
    cout << kruskal.ver_in_mst_to_string() << endl;
    // Print edges in MST to debug.
    cout << kruskal.edges_in_mst_to_string();

#endif // DEBUG

    // Print weight sum of MST.
    cout << "Weight sum of MST:\n" << distance << endl;
    // Write weight sum of MST to out file.
    try {
        fs.open(out_file, ios_base::out);
    } catch (exception &e) {
        cerr << "Error occurred during writing result to file:\n" << e.what();
    }
    fs << distance << endl;
    fs.close();

    return 0;
}
