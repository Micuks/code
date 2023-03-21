#define DEBUG

#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_set>
#include <vector>

#ifdef DEBUG
#include "debug.h"
#else
#define deb(x...)
#endif // DEBUG

using namespace std;

int n = 0;

class Member;
class Solution {
  public:
    Solution(vector<Member> memberList) : memberList_(memberList){};
    vector<Member> memberList_;
    string getAnsX() const;
    void calculateA();

  private:
    void calculateA(Member &member);
    int getAnsX(const Member &member) const;
};

class Member {
  public:
    Member(int a = 0) : p_(1), a_(a){};
    int p_;
    int a_;
    vector<int> T_;
    vector<int> A_;

    void calculateA();
};

void getChildren(vector<Member> &allMembers, int i) {
    auto &parent = allMembers.at(i);
    unordered_set<int> children(parent.T_.begin(), parent.T_.end());
    deb(children);
    for (auto &idx : parent.T_) {
        auto &mem = allMembers.at(idx);
        children.insert(mem.T_.begin(), mem.T_.end());
    }
    parent.T_ = vector<int>(children.begin(), children.end());
}

auto absDistance = [](int a, int b) { return abs(a - b); };

auto euclideanDistance = [](int a, int b) { return pow((a - b), 2); };

int getMin(int i, vector<int> A) {
    auto ai = A.at(i);
    pair<int, int> minAbsDist = make_pair(0, numeric_limits<int>::max());
    for (int j = 0; j < A.size(); j++) {
        auto aj = A.at(j);
        if (i == j) {
            continue;
        }

        if (absDistance(ai, aj) < minAbsDist.second) {
            minAbsDist = make_pair(aj, euclideanDistance(ai, aj));
        }
    }
    return minAbsDist.second;
}

int Solution::getAnsX(const Member &member) const {
    int result = 0;
    auto size = member.A_.size();
    deb(size);
    if (size == 1) {
        return 0;
    }
    if (size & 1) {
        result += getMin(size / 2, member.A_);
    }
    for (auto i = 0; i < size / 2; i++) {
        result += getMin(i, member.A_) * 2;
    }
    return result;
}

string Solution::getAnsX() const {
    stringstream ss;
    for (int i = 1; i <= n; i++) {
        auto &mem = memberList_.at(i);
        ss << getAnsX(mem) << endl;
    }
    return ss.str();
}

void Solution::calculateA() {
    for (int i = 1; i <= n; i++) {
        auto &mem = memberList_.at(i);
        calculateA(mem);
    }
}

void Solution::calculateA(Member &member) {
    for (auto &idx : member.T_) {
        auto mem = memberList_[idx];
        deb(mem.a_);
        member.A_.push_back(mem.a_);
    }
}

int getAnsX(vector<int> A) {
    int result = 0;
    auto size = n;
    deb(size);
    if (size == 1) {
        return 0;
    }
    if (size & 1) {
        result += getMin(size / 2, A);
    }
    for (auto i = 1; i <= size / 2; i++) {
        result += getMin(i, A) * 2;
    }
    return result;
}

int main() {

    vector<int> p;
    vector<int> a;
    cin >> n;
    deb(n);
    for (auto i = 1; i < n; i++) {
        int tmp;
        cin >> tmp;
        p.push_back(tmp);
    }
    deb(p);
    for (auto i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp;
        a.push_back(tmp);
    }
    deb(a);

    // Set all members and their memberList.
    vector<Member> allMembers;
    // Null member. Append this to let employees range from 1 to n.
    allMembers.push_back(-1);
    for (auto i = 1; i <= n; i++) {
        auto mem = Member(a[i]);
        allMembers.push_back(mem);
    }

    // Set employee for Boss
    allMembers.at(1).T_.push_back(1);
    // Set employees for members
    for (auto i = 2; i <= n; i++) {
        allMembers.at(i).T_.push_back(i);
        allMembers.at(p[i - 2]).T_.push_back(i);
    }
    for (auto i = n; i >= 1; i--) {
        getChildren(allMembers, i);
    }

    for (int i = 1; i <= n; i++) {
        auto &mem = allMembers.at(i);
        deb(mem.T_);
    }

    Solution solution(allMembers);

    // Calculate set A for children and G(A(x))
    solution.calculateA();

    for (int i = 1; i <= n; i++) {
        auto &mem = solution.memberList_.at(i);
        deb(mem.A_);
    }

    // Calculate and output AnsX
    cout << solution.getAnsX();

    return 0;
}
