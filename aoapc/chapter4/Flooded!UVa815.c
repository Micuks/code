#include<stdio.h>
#define MAXN 1000
#define S 100
int k;
void binSort(int* a,int len) {
    int mid,left,right,temp;
    for(int i=1;i<len;i++) {
        left=0;
        right=i-1;
        temp=a[i];
        while(left<=right) {
            mid=(left+right)/2;
            if(temp<a[mid]) right=mid-1;
            else left=mid+1;
        }
        for(int j=i-1;j>=left;j--) a[j+1]=a[j];
        if(left!=i) a[left]=temp;
    }
}
int f(int mid,int* a) {
    int sum=mid*a[mid];
    for(int i=0;i<mid;i++) sum-=a[i];
    return sum*S;
}
double binarysearch(int* a,int v,int n) {
    int mid,left=0,right=n-1;
    int temp=v;
    double result=0;
    while(left<=right) {
        mid=(left+right)/2;
        if(temp>f(mid,a)) left=mid+1;
        else right=mid-1;
    }
    k=left;
    result=(double)v/(double)S;
    for(int i=0;i<k;i++) result+=a[i];
    return result/(double)k;
}
int main() {
    int m,n,v,kase=1;
    int vector[MAXN];
    while(scanf("%d%d",&m,&n)==2&&m&&n) {
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&vector[i*n+j]);
        binSort(vector,m*n);
        scanf("%d",&v);
        printf("Region %d\n"
                "Water level is %.2lf meters.\n",
                kase++,binarysearch(vector,v,m*n));
        printf("%.2lf percent of the region is under water.\n\n",100.00*(double)k/(double)(m*n));
    }
    return 0;
}