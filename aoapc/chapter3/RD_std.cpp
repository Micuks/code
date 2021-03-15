#include <bits/stdc++.h>
using namespace std;
int n , k , vis[3005];
deque <int> dq;//队列用来存小数部分每一位的值 
int main() {
	while(~scanf("%d%d" , &n , &k)) {
		memset(vis , 0 , sizeof(vis));//初始vis数组，方便在后边判断循环节的边界 
		printf("%d/%d = %d." , n , k , n / k);//直接输出 
		dq.clear();
		dq.push_back(0);//要放个0进去保证队列不为空，亲测，不然会wa 
		n %= k;
		int i = 1;//i是表示现在到了多少位
		for(;!vis[n];i ++) {//如果vis不为0，证明之前已经出现过这个数了，即循环节结束 
			vis[n] = i;// 
			dq.push_back(n * 10 / k);//把小数部分下一位的值存进去 
			n = n * 10 % k;//更新n的值,n表示的是小数部分 
		}
		int tj = 0; //tj表示统计输出的所有小数部分的位数，最后判断是否大于50 
		for(i = 1; i < vis[n]; ++ i , ++ tj) {
			printf("%d" , dq[i]);
		}
		putchar('(');//循环节开始 
		int tongji;//tongji是表示循环节的位数 
		for(tongji = 0; i < dq.size(); i ++) {
			tongji ++;
			tj ++;
			if(tj <= 50) {
				printf("%d" , dq[i]);//判断输出位数有没有超过界限 
			}
		}
		if(tj > 50) {
			printf("...");//按题意输出 
		}
		putchar(')');
		printf("\n   %d = number of digits in repeating cycle\n\n" , tongji);//这里前面要打三个空格，很毒瘤 
	}
	
	return 0;
}