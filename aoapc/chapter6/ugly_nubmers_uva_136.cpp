#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;
const int multi[3] = {2, 3, 5};
int main() {
    priority_queue<long long, vector<long long>, greater<long long> > pq;
    set<long long> un;
    pq.push(1);
    un.insert(1);
    for(int i = 1;i < 10000;i++) {
        long long x = pq.top();
        pq.pop();
        cout << "The " << i << "\'th" << " ugly number is " << x << endl;
//        int c = cin.get();
//        pause();
        for(int j = 0; j < 3; j++) {
            long long x2 = x * multi[j];
            if(!un.count(x2)) {
                un.insert(x2);
                pq.push(x2);
            }
        }
    }
    return 0;
}
