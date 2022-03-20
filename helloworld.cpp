#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 10;
int n, k;
int cnt, sum;
int visited[maxn];
char matrix[maxn][maxn];

void dfs(int row);

int main() {
    while(scanf("%d%d", &n, &k) == 2) {
        getchar();
        if(n == -1 && k == -1)
            break;
        else {
            for(int i = 0; i < n; i++)
                scanf("%s", matrix[i]);
            memset(visited, 0, sizeof(visited));
            cnt = sum = 0;
            dfs(0);
            printf("%d\n", sum);
        }
    }
}

void dfs(int row) {
    if(cnt == k) {
        sum++;
        return;
    }
    else if(cnt > k || row >= n)
        return;
    else {
        for(int i = 0; i < n; i++) {
            if(matrix[row][i] == '#' && !visited[i]) {
                visited[i] = 1;
                cnt++;
                dfs(row+1);
                cnt--;
                visited[i] = 0;
            }
        }
        dfs(row+1);
    }
}
