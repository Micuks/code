#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 1000;
bool failed = false;

struct Node {
    int value;
    bool isvalued;
    Node* left;
    Node* right;
    Node():value(0), isvalued(false), left(NULL), right(NULL){};
};

Node* proot;

Node* newnode() {
    return new Node();
}

//void deletetree(Node* proot) {
//    if(proot == NULL)
//        return; 
//    deletetree(proot->left);
//    deletetree(proot->right);
//    delete proot;
//}

bool input(void) {
    char str[maxn];
    //deletetree(proot);
    proot = newnode();
    while(scanf("%s", str) == 1) {
        if(strcmp(str, "()") == 0)
            return true;
        int v;
        Node* pnode = proot;
        sscanf(str+1, "%d", &v);
        for(int i = strchr(str, ',') + 1 - str; str[i] != '\0'; i++) {
            if(str[i] == 'L') {
                if(pnode->left == NULL) pnode->left = newnode();
                pnode = pnode->left;
            }
            else if(str[i] == 'R') {
                if(pnode->right == NULL) pnode->right = newnode();
                pnode = pnode->right;
            }
        }
        if(pnode->isvalued == true) {
            failed = true;
        }
        else {
            pnode->isvalued = true;
            pnode->value = v;
        }
    }
    return false;
}

bool bfs(vector<int>& ans) {
    ans.clear();
    queue<Node*> q;
    q.push(proot);
    while(q.empty() == false) {
        Node* pnode = q.front();
        q.pop();
        ans.push_back(pnode->value);
        if(pnode->left) {
            q.push(pnode->left);
        }
        if(pnode->right) {
            q.push(pnode->right);
        }
        if((pnode->left || pnode->right) && pnode->isvalued == false) {
            failed = true;
        }
    }
    return true;
}

bool print(vector<int> ans) {
    if(failed) {
        printf("-1\n");
        return false;
    }   
    for(int i = 0; i < ans.size(); i++) {
        printf(" %d" + !i, ans[i]);
    }
    putchar('\n');
    return true;
}

int main() {
    char flag; 
    while((flag = getchar()) == '(') {
        vector<int> ans;
        ungetc(flag, stdin);
        input();
        bfs(ans);
        print(ans);
        getchar();
    }
    return 0;
}
