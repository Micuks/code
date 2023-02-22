#include <iostream>
#include <vector>
using namespace std;
class Node {
  public:
    int t;
    int idx;
    Node *parent;
    vector<Node *> childs;
    int earliestTime;
    int latestTime;

    Node(int idx = 0, int t = 0) : t(t), idx(idx) {}
    int numChilds() { return childs.size(); }
    friend ostream &operator<<(ostream &os, Node *pnode);
};

void getEarliestStartTime(Node *currNode, int currTime);

void printNodes(vector<Node *> nodes) {
        auto nullNode = nodes.at(0);
        cout << "0" << ": "
             << "t: " << nullNode->t << ", "
             "childs("
             << nullNode->childs.size() << "): ";
        for (auto &ch : nullNode->childs) {
            cout << ch->idx << ", ";
        }
        cout << endl;

    for (int i = 1; i < nodes.size(); i++) {
        auto &currNode = nodes.at(i);
        cout << i << ": "
             << "t: " << currNode->t << ", "
             << "parent: " << currNode->parent->idx << ", childs("
             << currNode->childs.size() << "): ";
        for (auto &ch : currNode->childs) {
            cout << ch->idx << ", ";
        }
        cout << endl;
    }
}

int main() {
    int n, m;
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
        nodes.at(tmp)->childs.push_back(pnode);
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
    printNodes(nodes);

    // compute earliest start time
    auto cNode = nodes.at(0);
    try {
        getEarliestStartTime(cNode, 1);
    } catch (exception &e) {
        cout << e.what();
    }

    for (auto &a : nodes) {
        cout << a->earliestTime << " ";
    }
    cout << endl;

    return 0;
}

void getEarliestStartTime(Node *currNode, int currTime) {
    currNode->earliestTime = currTime;
    if (currNode->childs.size()) {
        for (auto &node : currNode->childs) {
            getEarliestStartTime(node, currTime + currNode->t);
        }
    }
}
