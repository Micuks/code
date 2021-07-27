#include <iostream>
#include <cstring>

const int MAXN = 100000;

using namespace std;

int pop(int* stack);
int push(int item, int len, int* stack);
int isEmpty(int* stack);
int isValid(int* target, int len);
int main() {
    int len;
    int order[MAXN];
    int target[MAXN];
    cin >> len;
    while(len) {
        int tmp;
        cin >> tmp;
        while(tmp) {
            memset(order,-1,sizeof(order));
            memset(target,-1,sizeof(target));
            int ptr = 0;
            order[0] = 1;
            target[0] = tmp;
            for(int i = 1; i < len; i++) {
                cin >> tmp;
                order[i] = i+1;
                target[i] = tmp;
            }
            if(isValid(target, len))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            cin >> tmp;
        }
        cout << endl;
        cin >> len;
    }
}

int pop(int* stack) {
    int top = *stack;
    int tmp = 0;
    while(stack[tmp+1] != -1) {
        stack[tmp] = stack[tmp+1];
        tmp++;
    }
    stack[tmp] = stack[tmp+1];
    return top;
}
int push(int item,int len, int* stack) {
    for(int i = len-1; i >= 0; i--) {
        stack[i+1] = stack[i];
    }
    stack[0] = item;
    return 0;
}

int isEmpty(int* stack) {
    if(stack[0] == -1)
        return 1;
    else return 0;
}
int isValid(int* target, int len) {
    int ptr = 0, flag = 1;
    int wait[MAXN], stack[MAXN];
    memset(wait, -1, sizeof(wait));
    memset(stack, -1, sizeof(stack));
    for(int i = 1; i <= len; i ++) {
        wait[i-1] = i;
    }
    while(isEmpty(wait) == 0 || isEmpty(stack) == 0) {
        if(target[ptr] == wait[0]) {
            int tmp = pop(wait);
            ptr++;
        } 
        else if(target[ptr] == stack[0]) {
            int tmp = pop(stack);
            ptr++;
        }
        else {
            if(isEmpty(wait) == 1) {
                flag = 0;
                break;
            }
            else {
                int tmp = pop(wait);
                push(tmp, len, stack);
            }      
        }
    }
    return flag;
}
