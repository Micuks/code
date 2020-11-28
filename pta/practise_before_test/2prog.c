#include<stdio.h>
long long fastpow(int base,int power) {
    long long result=1;
    while(power) {
        if(power&1) result*=base;
        power>>=1;
        base=1ll*base*base;
    }
    return result;
}
int main() {
    int n,count_of_books,o_count_of_books=0;
    int books[105],ans,oans=0;
    scanf("%d",&n);
    long long maximum=fastpow(2,n);
    for(int i=0;i<n;i++) {
        scanf("%d",books+i);
    }
        // printf("maximum = %d\t",maximum);
        // for(int i=0;i<n;i++) printf("%d ",books[i]);
        // putchar('\n');
    for(long long i=1;i<=maximum;i++) {
        ans=0;
        count_of_books=0;
            // printf("oans = ");
        for(int j=0;j<n;j++) {
            if((i>>j)&1) {
                ans+=books[j]; 
                count_of_books++;
                    // printf("%d ",ans);
            }
        }
        if(ans>=oans&&ans<=1000) {
            oans=ans;
            if(o_count_of_books<count_of_books) o_count_of_books=count_of_books;
        }
            // printf("%d ",oans);
            // putchar('\n');
    }
    printf("%d\n",o_count_of_books);
    return 0;
}