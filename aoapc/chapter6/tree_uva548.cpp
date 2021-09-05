#include<cstring>
#include<queue>
#include<iostream>
#include<sstream>
#include<string>
#include<cstdio>

using namespace std;

const int maxn = 10010;
int root;
bool input(queue<int>& vec);
int buildtree(queue<int>& inorder, queue<int>& postorder);
void clearqueue(queue<int>& q);
int tleft[maxn], tright[maxn];

int main() {
    queue<int> inorder, postorder;
    while(input(inorder)) {
        memset(tleft, 0, sizeof(tleft));
        memset(tright, 0, sizeof(tright));
        input(postorder);
        //int len = inorder.size();
        //for(int i = 0; i < len; i++) {
        //    cout << inorder[i] << ' ';
        //}
        //len = postorder.size();
        //for(int i = 0; i < len; i++) {
        //    cout << postorder[i] << ' ';
        //}
        root = buildtree(inorder, postorder);
    }
    return 0;
}

bool input(queue<int>& vec) {
    string str;
    int num;
    if(!getline(cin, str))
        return false;
    stringstream ss(str);
    while(ss >> num)
        vec.push(num);
    return true;
}

void clearqueue(queue<int>& q) {
    queue<int> empty;
    swap(empty, q);
}
int buildtree(queue<int>& inorder, queue<int>& postorder) {
    root = postorder.back();
    queue<int> oldin = inorder, oldpo = postorder;
    queue<int> tmpin, tmppo;
    while(oldin.front() != root) {
        tmpin.push(oldin.front());
        tmppo.push(oldpo.front());
        oldin.pop();
        oldpo.pop();
    }
    oldin.pop();
    tleft[root] = buildtree(tmpin, tmppo);
    clearqueue(tmpin);clearqueue(tmppo);
    return root;
}
