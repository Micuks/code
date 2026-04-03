#include <bits/stdc++.h>
using namespace std;
#define random(a,b) ((a)+rand()%((b)-(a)+1))

int main(int argc, char *argv[]) {
    int seed = time(NULL);
    srand(seed);

    printf("f(x)=");
    int deg = 99999;
    int a = random(1, 99999);
    int b = random(1, 999);
    int c = random(1, 2);
    if(c==1) {
        printf("-");
    }
    deg -= b;
    printf("%dx^%d", a, deg);
    while(deg >= 1) {
        a = random(1, 99999);
        b = random(1, 9);
        c = random(1, 2);
        if(c==1) {
            printf("-");
        }
        else printf("+");
        deg -= b;
        printf("%dx^%d", a, deg);
    }
    return 0;
}
