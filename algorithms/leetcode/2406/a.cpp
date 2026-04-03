#include <bitset>
#include <exception>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
  public:
    Solution() : num_groups(0) {
        for (auto &g : gs) {
            g.clear();
        }
    }

    int minGroups(vector<vector<int>> &intervals) { int idx = 0; }

  private:
    int num_groups;
    unordered_set<pair<int, int>> gs[2];
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
    // cout << s.findShortestCycle(n, edges) << endl;
    return 0;
}
