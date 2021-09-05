#include<cstring>
#include<queue>
#include<iostream>
#include<sstream>
#include<string>
#include<cstdio>

using namespace std;

const int maxn = 10010;
int root, cnt = 0;
int tleft[maxn], tright[maxn], value[maxn], sum[maxn];

int addnode(void) {
    int node = ++cnt;
    tleft[node] = tright[node] = value[node] = 0;
    return node;
}

void pq(queue<int> tin) {
    while(!tin.empty()) {
        cout << tin.front() << ' ';
        tin.pop();
    }
    cout << endl;
}

void clearqueue(queue<int>& q) {
    queue<int> empty;
    swap(empty, q);
}

bool input(queue<int>& vec) {
    clearqueue(vec);
    string str;
    int num;
    if(!getline(cin, str))
        return false;
    stringstream ss(str);
    while(ss >> num)
        vec.push(num);
    return true;
}

int buildtree(int pvalue, queue<int> inorder, queue<int> postorder) {
    int node = addnode();
    value[node] = postorder.back();
    sum[node] = pvalue + value[node];
    //cout << "value[node] = " << value[node] << endl;
    queue<int> oldin = inorder, oldpo = postorder;
    queue<int> tmpin, tmppo;
    while(oldin.front() != value[node]) {
        tmpin.push(oldin.front());
        tmppo.push(oldpo.front());
        oldin.pop();
        oldpo.pop();
    }
    //cout << "oldin: ";
    //pq(oldin);
    //cout << "oldpo: ";
    //pq(oldpo);
    //cout << "tmpin: ";
    //pq(tmpin);
    //cout << "tmppo: ";
    //pq(tmppo);
    oldin.pop();
    if(!tmpin.empty() || !tmppo.empty()) {
        //cout << "add left subtree" << endl;
        tleft[node] = buildtree(value[node], tmpin, tmppo);
    }
    clearqueue(tmpin);clearqueue(tmppo);
    while(!oldin.empty()) {
        tmpin.push(oldin.front());
        tmppo.push(oldpo.front());
        oldin.pop();
        oldpo.pop();
    }
    //cout << "oldin: ";
    //pq(oldin);
    //cout << "oldpo: ";
    //pq(oldpo);
    //cout << "tmpin: ";
    //pq(tmpin);
    //cout << "tmppo: ";
    //pq(tmppo);
    if(!tmpin.empty() || !tmppo.empty()) {
        //cout << "add right subtree" << endl;
        tright[node] = buildtree(value[node], tmpin, tmppo);
    }
    return node;
}

void debugtree(void) {
    queue<int> q;
    vector<int> ans;
    ans.clear();
    q.push(root);
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(value[node]);
        if(tleft[node])
            q.push(tleft[node]);
        if(tright[node])
            q.push(tright[node]);
    }
    int len = ans.size();
    cout << "print tree" << endl;
    for(int i = 0; i < len; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}

void output(void) {
    int ndmin = maxn;
    for(int i = 1; i <= cnt; i++) {
        
    }
}
int main() {
    queue<int> inorder, postorder;
    while(input(inorder)) {
        input(postorder);

        cnt = 0;
        //memset(tleft, 0, sizeof(tleft));
        //memset(tright, 0, sizeof(tright));
        //memset(value, 0, sizeof(value));
        memset(sum, 0, sizeof(sum));
        root = buildtree(0, inorder, postorder);
        debugtree();
    }
    return 0;
}

