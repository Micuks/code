#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Matrix {
    int m,n;
    Matrix(int m=0, int n=0):m(m), n(n) {}
} mtx[26];
stack<Matrix> stk;

int isvalid(Matrix& m1, Matrix& m2);
int calculate(Matrix& m, Matrix& m1, Matrix& m2);

int main() {
    int num, error = 0;
    cin >> num;
    while(num--) {
        string name;
        cin >> name; 
//        cout << "name = " << name << endl;
        cin >> mtx[name[0] - 'A'].m >> mtx[name[0] - 'A'].n;
//        cout << "mtx[" << name[0] - 'A' << "].m = " << mtx[name[0]-'A'].m << " .n = " << mtx[name[0] - 'A'].n << endl;
    }
    string cmd;
    while(cin >> cmd) {
        error = 0;
        int result = 0;
        for(int i = 0;error == 0 && i < cmd.length(); i++) {
            if(isalpha(cmd[i])) {
                stk.push(mtx[cmd[i] - 'A']);
            }
            else if(cmd[i] == ')') {
                Matrix m1 = stk.top();
                stk.pop();
                Matrix m2 = stk.top();
                stk.pop();
                error = isvalid(m2, m1);
                if(error == 0) {
                    Matrix m;
                    result += calculate(m, m2, m1);
                    stk.push(m);
                }
                else {
                    stk.push(m2);
                    stk.push(m1);
                    cout << "error" << endl;
                } 
            }
        }
        if(error == 0)
            cout << result << endl;
    }
    return 0;
}
int isvalid(Matrix& m1, Matrix& m2) {
    return m1.n == m2.m ?0:1;
}
int calculate(Matrix& mat, Matrix& m1, Matrix& m2) {
    mat.m = m1.m;
    mat.n = m2.n;
    return m1.n * m1.m * m2.n;
}
