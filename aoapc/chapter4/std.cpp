#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,mapp[1600];
int sum;		//在check函数中进行计算，表示淹没mid个格子需要的水量
int check(int mid){
    sum=0;
    for(int i=1;i<=mid;i++)
        sum+=(mapp[mid]-mapp[i])*100;
    return sum;
}
int main(){
    int region=0;
    while(scanf("%d%d",&n,&m)==2){
        int v;				//总降水量
        if(n==0&&m==0)return 0;
        region++;
        for(int i=1;i<=n*m;i++)scanf("%d",&mapp[i]);//读入每个格子的高度。因为相当于连通器，格子的位置其实并不重要
        sort(mapp+1,mapp+1+n*m);	//由于格子的位置不重要，所以可以按高矮排序啦
        scanf("%d",&v);			//读入总降水量
        int l=0,r=n*m,ans;		//l表示mid的下界，r表示mid的上界
        double h;			//水位高度
        while(l<=r){			//开始二分
            int mid=l+((r-l)>>1);	//(r-l)>>1就相当于(r-l)/2。只不过前者更快
            if(check(mid)<=v){		//check计算淹没mid个格子需要多少水。如果淹没mid个格子需要的水小于等于总降水量，说明还可以再多淹几格，那么mid的下界l就应该提高
                ans=mid;		//存储答案。每一次二分的答案一定比之前的答案更优
                h=(1.0*v-sum)/(ans*100)+mapp[ans]*1.0;//水位的高度=能够淹没的最高的格子的高度(mapp[ans])+冒出去的水的高度即(总水量-淹没mid个格子需要的水量)/被淹没的格子的面积和
                l=mid+1;		//提高mid的下界
            }
            else r=mid-1;		//否则说明水不够，mid需要减小，即mid的上界r需要减小
        }
        printf("Region %d\n",region);
        printf("Water level is %.2lf meters.\n",h);//输出水位高度
        printf("%.2lf percent of the region is under water.\n\n",ans/(1.0*n*m)*100);//这个地方是整道题最毒瘤的地方！注意看有两个换行符！！！
    }
    return 0;
}