#include <climits>
#include <iostream>
#include <queue>
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

class Vertex {
  public:
    int idx;
    int distance;
    int parent;
    Edge *head;
    bool inMST;

    Vertex(int idx = -1, int weight = INF, Edge *head = nullptr)
        : idx(idx), distance(weight), inMST(false), head(head), parent(-1){};
};

class CmpVertexPtr {
  public:
    bool operator()(const Vertex *a, const Vertex *b) const {
        return a->distance < b->distance;
    }
};

class Prim {
  public:
    vector<Vertex *> vertices;
    vector<Edge *> edges;
    int begin;
    int target;
    int weight_sum;

    const int prim_MST();
    Prim(vector<Vertex *> &vers, vector<Edge *> &edges, int begin)
        : vertices(vers), edges(edges), begin(begin), target(begin),
          weight_sum(0){};
};

// class State {
//   public:
//     Edge *edge;
//     Vertex *vertex;
//     State(Edge *edge, Vertex *vertice) : edge(edge), vertex(vertice){};
//     State(Vertex *vertice, Edge *edge) : edge(edge), vertex(vertice){};
// };
//
// class CmpState {
//   public:
//     bool operator()(const State *a, const State *b) const {
//         return a->vertex->distance < b->vertex->distance;
//     }
// };

const int Prim::prim_MST() {
    priority_queue<Vertex *, vector<Vertex *>, CmpVertexPtr> pq;
    // Initialize the distance between begin and begin to 0.
    auto &ver = vertices.at(begin);
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
        auto &edge = ver->head;
        while (edge != nullptr) {
            auto &neighbor_ver = vertices[edge->to];
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
