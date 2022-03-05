 #include<stdio.h>
 #define MAXN 100
 int main() {
    int number_of_truth_tellers;
    scanf("%d",&number_of_truth_tellers);
    int a[15];
    for(int i=0;i<5;i++) {
        scanf("%d%d",&a[2*i],&a[2*i+1]);
            // printf("%d %d\n",a[2*i],a[2*i+1]);
    }
    int count;
    int ans[MAXN];
    for(int i=0;i<MAXN;i++) ans[i]=0;
    for(int i=0;i<5;i++) {
        if(a[2*i+1]==1) ans[a[2*i]]++;
        else if(a[(i<<1)+1]==0){
            for(int j=0;j<MAXN;j++) ans[j]++;
            ans[a[2*i]]--;
        }
    }
    for(int i=0;i<MAXN;i++) {
        // printf("ans[%d] = %d\n",i,ans[i]);
        if(ans[i]==number_of_truth_tellers) {
            printf("%d\n",i);
        }
    }
    return 0;
 }