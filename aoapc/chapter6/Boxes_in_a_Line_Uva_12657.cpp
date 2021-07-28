//#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 100000 + 100;
//using namespace std;
int Left[maxn], Right[maxn];
void link(int& a, int& b);
void swap2(int&a, int&b);
long long output(int n, int inv);
//void debug(void);

int main() {
    int n, m, kase = 0;
    //    while(cin >> n >> m) {
    while(scanf("%d%d",&n,&m) == 2) {
        int cmd[3];
        Left[0] = n, Right[0] = 1;
        for(int i = 1; i <= n; i++) {
            Left[i] = i-1;
            Right[i] = (i+1) % (n+1);
        }
        //        debug();
        int inv = 0;
        while(m--) {
            //            cin >> cmd[0];
            scanf("%d",cmd);
            if(cmd[0] == 4) {
                inv = !inv;
            }
            else {
                //                cin >> cmd[1] >> cmd[2];
                scanf("%d%d",cmd+1, cmd+2);
                if(cmd[0] == 3) {
                    swap2(cmd[1], cmd[2]);
                }
                else if((cmd[0] == 1 && inv == 0) || (cmd[0] == 2 && inv == 1)) {
                    if(Left[cmd[2]] != cmd[1]) {
                        link(Left[cmd[1]], Right[cmd[1]]);
                        link(Left[cmd[2]], cmd[1]);
                        link(cmd[1], cmd[2]);
                    }       
                }
                else {
                    if(Right[cmd[2]] != cmd[1]) {
                        link(Left[cmd[1]], Right[cmd[1]]);
                        link(cmd[1], Right[cmd[2]]);
                        link(cmd[2], cmd[1]);
                    }
                }
            }
            //            debug();   
        }
        printf("Case %d: %lld\n", ++kase, output(n, inv));
    }
}

void link(int& a, int& b) {
    Right[a] = b;
    Left[b] = a;
}

void swap2(int&a, int&b) {
    int leftb = Left[b], rightb = Right[b];
    link(Left[a], b);
    link(b, Right[a]);

    link(leftb, a);
    link(a, rightb);
    //    debug();

}
long long output(int n, int inv) {
    long long result = 0;
    int tmp = Right[0];
    if(inv && !(n & 1)) tmp = Right[tmp];
    for(int i = 1; i <= n; i+=2) {
        result += tmp;
        tmp = Right[Right[tmp]];
    }
    return result;
}
//void debug(void) {
//    int front, rear;
//    front = rear = 1;
//    while(Left[front] != -1)
//        front = Left[front];
//    while(Right[rear] != -1)
//        rear = Right[rear]; 
//    int tmp = front;
//    while(tmp != -1) {
//        printf("%d ", tmp);
//        tmp = Right[tmp];
//    }
//    putchar('\n');
//}
