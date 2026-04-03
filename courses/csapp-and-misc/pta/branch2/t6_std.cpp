#include <iostream>
#include <cmath>
using namespace std;
//bool finish = false;
int isPrime(int n){
    for (int i = 2; i <= sqrt(n); i++){
        if (n % i == 0)
            return 0;
    }
    return 1;
}
void recurPrintFactor(int n){
    if (isPrime(n)){
        cout << n << endl;
        //finish = true;
        return; //只能返回到上一次递归的地方，return后遇到break，一层层退出直到最外层
    }
    else{
        int i = 2;
        while (i <= n / 2){
            if (isPrime(i)) {//&&!finish
                if (n % i == 0){
                    cout << i << "*";
                    recurPrintFactor(n / i);
                    break; //退出while循环
                }
                else
                    i++;
            }
            else
                i++;
        }
    }
}
int main(){
    int a, b;
    cin >> a >> b;
    for (int i = a; i <= b; i++){
        //finish = false;
        cout << i << "=";
        recurPrintFactor(i);
    }
    return 0;
}