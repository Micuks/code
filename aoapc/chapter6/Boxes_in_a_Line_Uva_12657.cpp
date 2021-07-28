#include <iostream>
#include <cstring>

const int maxn = 100000 + 100;
using namespace std;
int Left[maxn], Right[maxn];
void link(int& a, int& b);
int position_judge(int a, int b);
void swap2(int&a, int&b);
long long output(int n, int inv);
void debug(void);

int main() {
    int n, m, kase = 0;
    while(cin >> n >> m) {
        int cmd[3];
        memset(Left,-1,sizeof(Left));
        memset(Right,-1,sizeof(Right));
        Left[1] = -1; Right[1] = 2;
        Left[n] = n-1; Right[n] = -1;
        for(int i = 2; i < n; i++) {
            Left[i] = i-1;
            Right[i] = i+1;
        }
//        debug();
        int inv = 0;
        while(m--) {
            cin >> cmd[0];
            if(cmd[0] == 4) {
                inv = !inv;
            }
            else {
                cin >> cmd[1] >> cmd[2];
                if(cmd[0] == 3) {
                    swap2(cmd[1], cmd[2]);
                }
                else if((cmd[0] == 1 && inv == 0) || (cmd[0] == 2 && inv == 1)) {
                    if(position_judge(cmd[1], cmd[2]) != 1) {
                        if(Right[cmd[1]] == -1) Right[Left[cmd[1]]] = -1;
                        else link(Left[cmd[1]], Right[cmd[1]]);
                        if(Left[cmd[2]] == -1) Left[cmd[1]] = -1;
                        else link(Left[cmd[2]], cmd[1]);
                        link(cmd[1], cmd[2]);
                    }       
                }
                else {
                    if(position_judge(cmd[1], cmd[2]) != 0) {
                        if(Left[cmd[1]] == -1) Left[Right[cmd[1]]] = -1;
                        else link(Left[cmd[1]], Right[cmd[1]]);
                        if(Right[cmd[2]] == -1) Right[cmd[1]] = -1;
                        else link(cmd[1], Right[cmd[2]]);
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

int position_judge(int a, int b) {
//    int tmp = a;
//    while(Right[tmp] != b && Right[tmp] != -1) {
//        tmp = Right[tmp];
//    }
//    if(Right[tmp] == b) return 0;
    if(Right[a] == b) return 1;
    else if(Left[a] == b) return 0;
    else return -1;
}
// BUG!!!!NOOO!!!
void swap2(int&a, int&b) {
    int leftb = Left[b], rightb = Right[b];
    if(Left[a] == -1) Left[b] = -1;
    else link(Left[a], b);
    if(Right[a] == -1) Right[b] = -1;
    else link(b, Right[a]);

    if(leftb == -1) Left[a] = -1;
    else link(leftb, a);
    if(rightb == -1) Right[a] = -1;
    else link(a, rightb);
//    debug();
//    link(Left[a], b);
//    link(b, Right[a]);
//    if(Left[a] == -1)  {
//        Left[b] = -1; 
//    }
//    if(Right[a] == -1) Right[b] = -1;
//
//    link(leftb, a);
//    link(a, rightb);
//    if(leftb == -1) Left[a] = -1;
//    if(rightb == -1) Right[a] = -1;
//    debug();
    
}
long long output(int n, int inv) {
    long long result = 0;
    int front, rear;
    front = rear = 1;
    while(Left[front] != -1)
        front = Left[front];
    while(Right[rear] != -1)
        rear = Right[rear]; 
    int tmp = front;
    if(inv && !(n & 1)) tmp = Right[tmp];
//    if(inv && n % 2 == 0) tmp = Right[tmp];
    while(Right[tmp] != -1) {
        result += tmp;
        tmp = Right[tmp];
        if(Right[tmp] != -1) tmp = Right[tmp];
    }    
    if(n & 1 || (inv && !(n & 1))) result += tmp;
    return result;
}
void debug(void) {
    int front, rear;
    front = rear = 1;
    while(Left[front] != -1)
        front = Left[front];
    while(Right[rear] != -1)
        rear = Right[rear]; 
    int tmp = front;
    while(tmp != -1) {
        printf("%d ", tmp);
        tmp = Right[tmp];
    }
    putchar('\n');
}
