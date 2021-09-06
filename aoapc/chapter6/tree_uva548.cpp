#include<cstring>
#include<queue>
#include<iostream>
#include<sstream>
#include<string>

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
    queue<int> qem;
    swap(q, qem);
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

int buildtree(int psum, queue<int> inorder, queue<int> postorder) {
    int node = addnode();
    value[node] = postorder.back();
    sum[node] = psum + value[node];
    queue<int> oldin = inorder, oldpo = postorder;
    queue<int> tmpin, tmppo;
    while(oldin.front() != value[node]) {
        tmpin.push(oldin.front());
        tmppo.push(oldpo.front());
        oldin.pop();
        oldpo.pop();
    }
    oldin.pop();
    if(!tmpin.empty() || !tmppo.empty()) {
        tleft[node] = buildtree(sum[node], tmpin, tmppo);
    }
    clearqueue(tmpin);clearqueue(tmppo);
    while(!oldin.empty()) {
        tmpin.push(oldin.front());
        tmppo.push(oldpo.front());
        oldin.pop();
        oldpo.pop();
    }
    if(!tmpin.empty() || !tmppo.empty()) {
        tright[node] = buildtree(sum[node], tmpin, tmppo);
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

void sort_unit(vector<int>& leaflist, vector<int>& valuelist, int begin, int end) {
    int dad = begin;
    int son = 2 * begin + 1;
    while(son <= end) {
        if(son < end && valuelist[son+1] > valuelist[son])
            son++;
        if(valuelist[dad] >= valuelist[son])
            return;
        else {
            swap(leaflist[dad], leaflist[son]);
            swap(valuelist[dad], valuelist[son]);
            dad = son;
            son = 2 * son + 1;
        }
    }
}

void heap_sort(vector<int>& leaflist, vector<int>& valuelist) {
    int len = leaflist.size();
    for(int i = len/2 - 1; i >= 0; i--) {
        sort_unit(leaflist, valuelist, i, len-1);
    }
    for(int i = len - 1; i >= 0; i--) {
        swap(leaflist.front(), leaflist[i]);
        swap(valuelist.front(), valuelist[i]);
        sort_unit(leaflist, valuelist, 0, i-1);
    }
}

void addlist(vector<int>& leaflist, vector<int>& valuelist) {
    int node = root;
    queue<int> q;
    q.push(root);
    while(!q.empty()) {
        node = q.front();
        q.pop();
        if(tleft[node]) q.push(tleft[node]);
        else if(!tright[node]) {
            leaflist.push_back(node);
            valuelist.push_back(sum[node]);
        }
        if(tright[node]) q.push(tright[node]);
    }
}

int minleaf(vector<int> leaflist, vector<int> valuelist) {
    int vsum = valuelist.front();
    int res = leaflist.front();
    while(!leaflist.empty() && valuelist.front() == vsum) {
        //cout << vsum << ' ' << res << endl;
        if(value[leaflist.front()] < value[res])
            res = leaflist.front();
        valuelist.erase(valuelist.begin());
        leaflist.erase(leaflist.begin());
        //cout << "minimum leaf: " << res << '(' << value[res] << ") ";
    }
    //cout << endl;
    return res;
}

void debugoutput(vector<int> leaflist, vector<int> valuelist) {
    cout << "leaflist" << endl;
    while(!leaflist.empty()) {
        cout << leaflist.front() << '(' << value[leaflist.front()] << ") ";
        leaflist.erase(leaflist.begin());
    }
    putchar('\n');
    cout << "valuelist" << endl;
    while(!valuelist.empty()) {
        cout << valuelist.front() << ' ';
        valuelist.erase(valuelist.begin());
    }
    putchar('\n');
}

void output(void) {
    vector<int> leaflist, valuelist;
    addlist(leaflist, valuelist);
    //debugoutput(leaflist, valuelist);

    heap_sort(leaflist, valuelist);
    //cout << "output" << endl;
    cout << value[minleaf(leaflist, valuelist)] << endl;
}
int main() {
    queue<int> inorder, postorder;
    while(input(inorder)) {
        input(postorder);

        cnt = 0;
        memset(sum, 0, sizeof(sum));
        root = buildtree(0, inorder, postorder);
        //debugtree();
        output();
    }
    return 0;
}

