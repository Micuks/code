#include<iostream>
#include<ctime>
#include<sstream>
#include<string>
using namespace std;
#define random(a,b) ((a)+rand()%((b)-(a)+1))
stringstream ss;
int main(int argc,char *argv[]) {
    int seed=time(NULL);
    if(argc>1) {
        ss.clear();
        ss<<argv[1];
        ss>>seed;
    }
    srand(seed);
    int a=random(1,100000);
    printf("%d %d\n",a,a+random(0,100));
    return 0;
}