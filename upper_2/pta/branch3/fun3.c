#include<stdio.h>

//函数功能：二分查找
//函数参数：分别为被查找的数组，数组长度，所查找的元素
//函数返回值：如果找到，则返回该元素在数组中的下标，否则返回-1 
// void sort(int a[],int n) {
//     for(int m=0;m<n-1;m++) {
//         for(int i=m;i<n-1;i++) {
//             if(a[i]>a[i+1]) {
//                 a[i]+=a[i+1];
//                 a[i+1]=a[i]-a[i+1];
//                 a[i]-=a[i+1];
//             }
//         }
//     }
// }
int BinarySearch(int a[],int n,int key) {
    // sort(a,n);
    int left=0,right=n-1,mid;
    while(left<=right) {
        mid=(left+right)>>1;
        // printf("\nleft = %d, right = %d,a[%d] = %d\n",left,right,mid,a[mid]);
        if(a[mid]==key) return mid;
        else if(a[mid]>key) right=mid-1;
        else if(a[mid]<key) left=mid+1;
    }
    return -1;
}

int    num[2000010] ;//数据量比较大，将该数组放在全局区 

int main()
{
    int        n , m, i;    
    int        key ;

    scanf("%d%d",&n,&m); 
    for( i = 0 ; i < n ; i++ ) 
        scanf("%d",&num[i]) ;

    for( i = 0 ; i < m ; i++ ) 
    {
        scanf("%d",&key) ;
        printf("%d",BinarySearch(num,n,key)) ;
        if ( i != m - 1 ) printf(" ") ;
        else printf("\n") ;
    }
    return 0 ;
}


/* 请在这里填写答案 */