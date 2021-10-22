#include<cstdio>
#include<cstring>
//const int maxn = 1010;
int n, m, cnt = 0;
//int cb[maxn][maxn], sto[maxn][2];

int search() {
    if(n%2 == 0 && m %2 == 0)
        return 0;
    else if(n%2 == 1 && m%2 == 0) {
        return 1;       
    }
    else if(n%2 == 0 && m%2 == 1)
        return 2;
    else {
        return 3;
    }
}

void swap(int& n, int& m) {
    int tmp = n;
    n = m;
    m = tmp;
}

void suboutput(int kase) {
    if(kase == 1) {
        for(int i = 2; i <= m; i++) {
            printf("%d %d\n", 1,  i);
        }
        for(int i = 2; i < n; i++) {
            if(i % 2 == 1) {
                for(int j = 1; j <= m; j++) {
                    printf("%d %d\n", i, j);
                }
            }
            else {
                for(int j = m; j >= 1; j--) {
                    printf("%d %d\n", i, j);
                }
            }
        }
        for(int i = 1; i < m; i++) {
            printf("%d %d\n", n, i);
        }
    }
    else if(kase == 2) {
        for(int i = 2; i <= n; i++) {
            printf("%d %d\n", i,  1);
        }
        for(int i = 2; i < m; i++) {
            if(i % 2 == 1) {
                for(int j = 1; j <= n; j++) {
                    printf("%d %d\n", j, i);
                }
            }
            else {
                for(int j = n; j >= 1; j--) {
                    printf("%d %d\n", j, i);
                }
            }
        }
        for(int i = 1; i < n; i++) {
            printf("%d %d\n", i, m);
        }
    }
}

void output(int kase) {
    if(kase == 1) {
        suboutput(1);
    }
    else if(kase == 2) {
        suboutput(2);
    }
    else if(kase == 3) {
        suboutput(1);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    //for(int i = 0; i <= n+1; i++) {
    //    cb[i][0] = 1;
    //    cb[i][m+1] = 1;
    //}
    //for(int i = 0; i <= m+1; i++) {
    //    cb[0][i] = 1;
    //    cb[n+1][i] = 1;
    //}
    //cb[1][1] = 1; cb[n][m] = 1;
    
    int kase = search();
    if(!kase) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
        output(kase);
    }
}
