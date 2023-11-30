//
// Created by 吴清柳 on 11/30/23.
//
#include <vector>
#include <iostream>

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() {
        removedNums.clear();
    }
    int popSmallest() {
        sort(removedNums.begin(),removedNums.end());
        int max = 1;
        if(removedNums.size()) {
            max = removedNums.back()+1;
        }
        for(int i=1;i<=max;i++) {
            auto pCurr = std::find(removedNums.begin(), removedNums.end(), i);
            if(pCurr != removedNums.end()) {
                continue;
            }else {
                removedNums.push_back(i);
                return i;
            }
        }
        return -1;
    }
    void addBack(int num) {
        auto ptr = find(removedNums.begin(), removedNums.end(), num);
        if(ptr != removedNums.end()) {
            removedNums.erase(ptr);
        }
    }
    std::vector<int> removedNums;
};

int main() {
    auto obj = new SmallestInfiniteSet();
    int num = 1;
    int param_1 = obj->popSmallest();
    obj->addBack(num);
}
