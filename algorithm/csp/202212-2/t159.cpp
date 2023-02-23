#include <iostream>
#include <limits>
#include <vector>
using namespace std;

bool validLatestTime = true;
int n, m;

class Node {
  public:
    int t;
    int idx;
    Node *parent;
    vector<Node *> children;
    int earliestTime;
    int latestTime;

    Node(int idx = 0, int t = 0) : t(t), idx(idx), latestTime(0) {}
    int numchildren() { return children.size(); }
    friend ostream &operator<<(ostream &os, Node *pnode);
};

void printNodes(vector<Node *> nodes) {
    auto nullNode = nodes.at(0);
    cout << "0"
         << ": "
         << "t: " << nullNode->t
         << ", "
            "children("
         << nullNode->children.size() << "): ";
    for (auto &ch : nullNode->children) {
        cout << ch->idx << ", ";
    }
    cout << endl;
    for (int i = 1; i < nodes.size(); i++) {
        auto &currNode = nodes.at(i);
        cout << i << ": "
             << "t: " << currNode->t << ", "
             << "parent: " << currNode->parent->idx << ", children("
             << currNode->children.size() << "): ";
        for (auto &ch : currNode->children) {
            cout << ch->idx << ", ";
        }
        cout << endl;
    }
}

int main() {
    cin >> n >> m;
    vector<int> p;
    p.push_back(0); // Empty p[0]
    vector<Node *> nodes;
    nodes.push_back(new Node()); // Empty node[0]

    // Begin of reading input
    for (int i = 1; i <= m; i++) {
        int tmp;
        cin >> tmp;
        p.push_back(tmp);

        auto pnode = new Node(i);
        nodes.push_back(pnode);

        pnode->parent = nodes.at(tmp);
        nodes.at(tmp)->children.push_back(pnode);
    }

    vector<int> t;
    t.push_back(0); // Empty node[0]

    for (int i = 1; i <= m; i++) {
        int tmp;
        cin >> tmp;
        t.push_back(tmp);

        nodes.at(i)->t = tmp;
    }
    // End of reading input
#ifdef DEBUG
    printNodes(nodes);
#endif // DEBUG

    // compute earliest start time
    for (int i = 1; i <= m; i++) {
        auto &node = nodes.at(i);
        if (node->parent->idx == 0) {
            node->earliestTime = 1;
        } else {
            auto &parent = node->parent;
            node->earliestTime = parent->earliestTime + parent->t;
        }

        validLatestTime =
            (node->earliestTime + node->t > n) ? false : validLatestTime;
    }

    // Compute latest start time
    for (auto iter = nodes.rbegin(); iter != nodes.rend(); iter++) {
        auto &node = *iter;
        if (!node->children.size()) {
            node->latestTime = n - node->t + 1;
        } else {
            auto &childs = node->children;
            int latestTime = numeric_limits<int>::max();
            for (auto &ch : childs) {
                latestTime = min(ch->latestTime, latestTime);
            }

            node->latestTime = latestTime - node->t;
        }
    }

    for (int i = 1; i <= m; i++) {
        auto &a = nodes.at(i);
        cout << a->earliestTime << " ";
    }
    cout << endl;

    // Output latest start time when valid
    if (validLatestTime) {
        for (int i = 1; i <= m; i++) {
            auto &a = nodes.at(i);
            cout << a->latestTime << " ";
        }
        cout << endl;
    }

    return 0;
}
