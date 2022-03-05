#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
using namespace std;
#define random(a,b) ((a)+rand()%(b-a+1))
stringstream ss;
int main(int argc,char* argv[]) {
    int seed=time(NULL);
    if(argc>1) {
        ss.clear();
        ss<<argv[1];
        ss>>seed;
    }
    srand(seed);
    int n=random(0,100);
    printf("%d\n",n);
    while(n--) {
        printf("%d %d %.1lf\n",random(1,4),random(1,5),(double)random(0,100000)/100);

    }
}