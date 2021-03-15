#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
using namespace std;
#define random(a,b) (a+rand()%(b-a+1))
stringstream ss;
int main(int argc,char* argv[]) {
    int seed=time(NULL);
    if(argc>1) {
        ss.clear();
        ss<<argv[1];
        ss>>seed;
    }
    srand(seed);
    char colors[]={'b','r','g','y'};
    int len=random(1,101);
    int tot=random(1,len);
    char c=colors[random(0,63)%4];
    char str[len+5];
    for(int i=0;i<len;i++) str[i]=colors[random(0,63)%4];
    str[len]='\0';
    printf("%c %d %s\n",c,tot,str);
} 
