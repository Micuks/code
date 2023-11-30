//
// Created by 吴清柳 on 11/30/23.
//
#include <vector>
#include <iostream>
#include <set>

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() {
    }
    int popSmallest() {
        int ans;
        if(s.empty()) {
            ans=thres;
            thres++;
        } else {
            ans = *s.begin();
            s.erase(s.begin());
        }

        return ans;
    }
    void addBack(int num) {
        if(num >= thres) {return;}
        s.insert(num);
    }
    int thres=1;
    std::set<int> s;
};

int main() {
    auto obj = new SmallestInfiniteSet();
    int num = 1;
    int param_1 = obj->popSmallest();
    obj->addBack(num);
}
