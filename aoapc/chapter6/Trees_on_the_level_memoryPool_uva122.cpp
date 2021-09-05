#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int maxn = 1000;
int root, cnt;
int left[maxn], right[maxn], value[maxn];
bool isvalued[maxn], failed = false;

int newnode() {
    int node = ++cnt;
    left[node] = right[node] = value[node] = isvalued[node] = 0;
    return node;
}

bool input(void) {
    char str[maxn];
    cnt = 0;
    failed = false;
    root = 1;
    memset(left,0,sizeof(left));
    memset(right, 0, sizeof(right));
    memset(value, 0, sizeof(value));
    root = newnode();
    while(scanf("%s", str) == 1) {
        if(strcmp(str, "()") == 0)
            return true;
        int v;
        int node = root;
        sscanf(str+1, "%d", &v);
        int len = strlen(str);
        for(int i = strchr(str, ',') + 1 - str; i < len; i++) {
            if(str[i] == 'L') {
                if(!left[node]) left[node] = newnode();
                node = left[node];
            }
            else if(str[i] == 'R') {
                if(!right[node]) right[node] = newnode();
                node = right[node];
            }
        }
        if(isvalued[node]) {
            failed = true;
        }
        else {
            isvalued[node] = true;
            value[node] = v;
        }
    }
    return false;
}

bool bfs(vector<int>& ans) {
    ans.clear();
    queue<int> q;
    q.push(root);
    while(q.empty() == false) {
        int node = q.front();
        q.pop();
        ans.push_back(value[node]);
        if(left[node]) {
            q.push(left[node]);
        }
        if(right[node]) {
            q.push(right[node]);
        }
        if(!isvalued[node]) {
            failed = true;
        }
    }
    return true;
}

bool print(vector<int> ans) {
    if(failed) {
        printf("not complete\n");
        return false;
    }
    int len = ans.size();
    for(int i = 0; i < len; i++) {
        printf(&" %d" [ !i], ans[i]);
    }
    putchar('\n');
    return true;
}

int main() {
    while(input()) {
        vector<int> ans;
        bfs(ans);
        print(ans);
        getchar();
    }
    return 0;
}
