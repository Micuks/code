#include <cstdio>
#include <cstring>

const int maxn = 20;
int tree[1<<maxn];

int main() {
    int d,n;
    while(scanf("%d%d", &d, &n) == 2) {
        memset(tree, 0, sizeof(tree));
        int ptr = 1;
        for(int i = 0; i < n; i++) {
            ptr = 1;
            while(ptr < 1<<(d-1)) {
                //printf("tree[%d] = %d,\n", ptr, tree[ptr]);
                tree[ptr] = !tree[ptr];
                if(tree[ptr]) {
                    ptr = ptr<<1;
                }
                else {
                    ptr = (ptr<<1)+1;
                }
                //printf("i: %d, ptr: %d\n",i, ptr);
            }
        }
        printf("%d\n", ptr);
    }
    return 0;
}
