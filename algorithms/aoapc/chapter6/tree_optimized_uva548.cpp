#include<cstring>
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

const int maxn = 10010;
int root, best, sumbest, n, inorder[maxn], postorder[maxn], lch[maxn], rch[maxn];

bool input(int* a) {
    string str;
    int num;
    n = 0;
    if(!getline(cin, str))
        return false;
    stringstream ss(str);
    while(ss >> num) {
        a[n++] = num;
    }
    return n > 0;
}

int buildtree(int l1, int r1, int l2, int r2) {
    int b = postorder[r2];
    int cnt = 0;
    if(l1 > r1)
        return 0;
    while(inorder[l1 + cnt] != b) {
        cnt++;
    }
    lch[b] = buildtree(l1, l1 + cnt - 1, l2, l2 + cnt - 1);
    rch[b] = buildtree(l1 + cnt + 1, r1, l2 + cnt, r2 - 1);
    return b;
}

void dfs(int b, int sum) {
    sum += b;
    if(!lch[b] && !rch[b]) {
        if(sumbest > sum) {
            sumbest = sum;
            best = b;
        }
        else if(sumbest == sum) {
            if(best > b)
                best = b;
        }
    }
    if(lch[b]) {
        dfs(lch[b], sum);
    }
    if(rch[b]) {
        dfs(rch[b], sum);
    }
}

int main() {
    while(input(inorder)) {
        input(postorder);
        sumbest = 2147483647;
        memset(lch, 0, sizeof(lch));
        memset(rch, 0, sizeof(rch));
        root = buildtree(0, n-1, 0, n-1);
        dfs(root, 0);
        cout << best << endl;
    }
    return 0;
}

