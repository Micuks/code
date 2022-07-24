#ifndef _t6_20220724_
#define _t6_20220724_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 100000;
int best_cost = MAXN;

bool isPrime(int num) {
    int n = (int)sqrt(num) + 1;
    for (int i = 2; i < n; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int dfs(int begin, int end, int layer = 0, int cost = 0) {
    if (begin == end) {
        if (cost < best_cost)
            best_cost = cost;
        return 0;
    }
    if (layer == 4) {
        return 0;
    }
    for (int i = (layer == 3) ? 1 : 0; i < 10; i++) {
        // printf("%d, %d, %d\n", begin / (int)pow(10, layer + 1) * (int)pow(10,
        // layer + 1),
        //        begin % (int)pow(10, layer), i * (int)pow(10, layer));
        int tmp = (begin / (int)pow(10, layer + 1) * (int)pow(10, layer + 1)) +
                (begin % (int)pow(10, layer)) + (int)pow(10, layer) * i;
        if(tmp == begin) {
            continue;
        }
        if (isPrime(tmp)) {
            printf("tmp[%d],layer[%d],cost[%d]\n", tmp, layer, cost);
            dfs(tmp, end, layer + 1, cost + 1);
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        best_cost = MAXN;
        int begin, end;
        scanf("%d%d", &begin, &end);
        dfs(begin, end);
        if (best_cost < MAXN) {
            cout << best_cost << endl;
        } else {
            cout << "Impossible\n";
        }
    }
    return 0;
};

#endif
