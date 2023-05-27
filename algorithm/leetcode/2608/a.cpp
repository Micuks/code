#include <bitset>
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    void build_adjlist(int n, vector<vector<int>> &edges) {
        adj_list.reserve(n);
        for (int i = 0; i < n; i++)
            adj_list.push_back(vector<int>());
        for (auto it = edges.begin(); it != edges.end(); it++) {
            auto f = it->at(0);
            auto s = it->at(1);
            adj_list.at(f).push_back(s);
            adj_list.at(s).push_back(f);
        }
    }
    void print_adjlist() {
        for (auto it = adj_list.begin(); it != adj_list.end(); it++) {
            auto es = *it;
            cout << (it - adj_list.begin()) << "[";
            for (auto &e : es) {
                cout << e << ", ";
            }
            cout << "]\n";
        }
    }
    void dfs(int node, int depth) {
        if (visited.test(node)) {
            cout << "node: " << node << ", depth: " << depth
                 << visited.test(node) << endl;
            if (find(adj_list.at(node).begin(), adj_list.at(node).end(),
                     root) != adj_list.at(node).end() &&
                depth >= 2) {
                optimal = min(optimal, depth);
            }
            return;
        }
        visited.set(node);

        auto es = adj_list.at(node);
        for (auto &e : es) {
            dfs(e, depth + 1);
        }
    }
    int findShortestCycle(int n, vector<vector<int>> &edges) {
        build_adjlist(n, edges);
        print_adjlist();
        visited.reset();
        root = 0;
        for (; root != n; root++) {
            // Visit if unvisited
            if (!visited.test(root)) {
                // visited.set(root);

                dfs(root, 0);
            }
        }

        return ((optimal == (1 << 30)) ? -1 : optimal);
    }

    // current root node
    int root;
    int optimal = 1 << 30;
    bitset<1024> visited;
    vector<vector<int>> adj_list;
};

int main(int argc, char *argv[]) {
    Solution s;
    int n;
    vector<vector<int>> edges;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ta, tb;
        cin >> ta >> tb;
        vector<int> tv({ta, tb});
        edges.push_back(tv);
    }
    cout << s.findShortestCycle(n, edges) << endl;
    return 0;
}
