// ConcurrencySimulator_UVa210.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int main() {
//	printf("hello\n");
//	return 0;
//}

#define bool int
#define true 1
#define false 0

#define MAXN 100

typedef struct program {
	int id,time,num,tot;
	char order[30][MAXN];
} Program;

typedef struct node {
	Program program;
	struct node* next;
	struct node* last;
} Node;

typedef struct queue {
	Node* front;
	Node* rear;
	int programs;
} Queue;

int vars[27];
int n,t[MAXN],q;
int locked;

void InitializeQueue(Queue* pq);

bool IsQueueEmpty(const Queue* pq);

bool IsQueueFull(const Queue* pq);

int QueueItemCount(const Queue* pq);

//type == 1为从队首进入，type == 2为从队尾进入
bool EnQueue(int type,Program pro,Queue* pq);

//type == 1为从队首删除，type == 2为从队尾删除
bool DeQueue(int type,Program* ppr,Queue* pq);

void EmptyTheQueue(Queue* pq);

void run(Queue* preadyqueue,Queue* pblockedqueue);

bool OrderIsPrint(char* str);

int main() {
	int kase;
	Program temp;
	Queue readyqueue;
	Queue blockedqueue;
	
	scanf("%d",&kase);

	for(int _i = 0;_i < kase; _i++) {
		if(_i) putchar('\n');

		locked = 0;
		memset(vars,0,sizeof(vars));
		InitializeQueue(&readyqueue);
		InitializeQueue(&blockedqueue);

		scanf("%d",&n);
		for(int i=0;i<5;i++) scanf("%d",t+i);
		scanf("%d",&q);
		getchar();	//eat the'\n'
		for(int i=0;i<n;i++) {
			temp.id = i;
			temp.time = q;
			char st[MAXN];
			gets(st);
			int cnt = 0;
			while(strcmp(st , "end") != 0) {
				strcpy(temp.order[cnt++],st);

				gets(st);
			}
			temp.tot = 0;
			temp.num = cnt;
			EnQueue(2,temp,&readyqueue);
		}

		while(IsQueueEmpty(&readyqueue) == 0) {
			run(&readyqueue,&blockedqueue);
		}

		EmptyTheQueue(&readyqueue);
		EmptyTheQueue(&blockedqueue);
	}
	return 0;
}

void InitializeQueue(Queue* pq) {
	pq->front = NULL;
	pq->rear = NULL;
	pq->programs = 0;
}

bool IsQueueEmpty(const Queue* pq) {
	return pq->programs == 0;
}

bool IsQueueFull(const Queue* pq) {
	return pq->programs == MAXN;
}

int QueueItemCount(const Queue* pq) {
	return pq->programs;
}
bool EnQueue(int type,Program pro,Queue* pq) {
	Node* pnode = (Node*)malloc(sizeof(Node));
	if(pnode == NULL)
		return false;

	pnode->program = pro;
	pnode->last = NULL;
	pnode->next = NULL;

	if(IsQueueFull(pq) == true) return false;
	if(IsQueueEmpty(pq) == true) {
		pq->front = pnode;
		pq->rear = pnode;
		pq->programs = 1;
		return true;
	}
	if(type == 2) {
		pnode->last = pq->rear;
		pnode->next = NULL;
		pq->rear->next = pnode;
		pq->rear = pnode;
	}
	else if(type == 1) {
		pnode->last = NULL;
		pnode->next = pq->front;
		pq->front->last = pnode;
		pq->front = pnode;
	}
	pq->programs++;

	return true;
}

bool DeQueue(int type,Program* ppr,Queue* pq) {
	if(IsQueueEmpty(pq) == true) return false;
	if(QueueItemCount(pq) == 1) {
		*ppr = pq->front->program;
		free(pq->front);
		InitializeQueue(pq);
		return true;
	}
	else if(type == 1) {
		*ppr = pq->front->program;

		Node* pnode = pq->front->next;
		pnode->last = NULL;
		free(pq->front);
		pq->front = pnode;
	}
	else if(type == 2) {
		*ppr = pq->rear->program;

		Node* pnode = pq->rear->last;
		pnode->next = NULL;
		free(pq->rear);
		pq->rear = pnode;
	}
	pq->programs--;
	return true;
}

void EmptyTheQueue(Queue* pq) {
	while(IsQueueEmpty(pq) == false) {
		Program dustbin;
		DeQueue(2,&dustbin,pq);
	}
}

bool OrderIsPrint(char* str) {
	char temp[MAXN];
	strcpy(temp,str);
	temp[5] = '\0';

	//printf("order keyword = %s\n",temp);

	return !strcmp(temp,"print");
}

void run(Queue* preadyqueue,Queue* pblockedqueue) {
	Node* pnow = preadyqueue->front;

	//printf("\n"
	//"num = %d,\n"
	//"time left = %d.\n"
	//"tot = %d, "
	//"order = %s.\n"
	//"left programs ready = %d\n"
	//"left programs blocked = %d\n",
	//pnow->program.num,pnow->program.time,pnow->program.tot,pnow->program.order[pnow->program.tot],preadyqueue->programs,pblockedqueue->programs);

	/*while(pnow->program.time > 0) */{

		//printf("	Into while!\n"
		//	"num = %d,\n"
		//	"time left = %d.\n"
		//	"tot = %d, "
		//	"order = %s.\n",
		//	pnow->program.num,pnow->program.time,pnow->program.tot,pnow->program.order[pnow->program.tot]);
		//printf("OrderIsPrint(pnow->program.order[pnow->program.tot]) = %d\n",OrderIsPrint(pnow->program.order[pnow->program.tot]));

		if(OrderIsPrint(pnow->program.order[pnow->program.tot]) == true) {

			//printf("print the value of %c\n",pnow->program.order[pnow->program.tot][6]);

			int var = vars[pnow->program.order[pnow->program.tot][6]-'a'];
			printf("%d: %d\n",pnow->program.id+1, var);
			pnow->program.time-=t[1];
		}
		else if(!strcmp(pnow->program.order[pnow->program.tot],"lock")) {

			//printf("lock\n");

			if(locked) {
				Program temp;
				DeQueue(1,&temp,preadyqueue);
				temp.time = q;
				EnQueue(2,temp,pblockedqueue);

				pnow = preadyqueue->front;

				return;

			}
			locked = 1;
			pnow->program.time-=t[2];
		}
		else if(!strcmp(pnow->program.order[pnow->program.tot],"unlock")) {

			locked = 0;

			if(IsQueueEmpty(pblockedqueue) == true)
				;

			else {
				Program temp;
				DeQueue(1,&temp,pblockedqueue);
				EnQueue(1,temp,preadyqueue);
			}

			pnow->program.time-=t[3];
		}
		else {

			int value=0;
			for(int i = 4;i<MAXN && pnow->program.order[pnow->program.tot][i] != '\0';i++) {
				value=value*10+pnow->program.order[pnow->program.tot][i]-'0';
			}
			vars[pnow->program.order[pnow->program.tot][0]-'a'] = value;

			pnow->program.time-=t[0];

		}

		pnow->program.tot++;
		if(pnow->program.num == pnow->program.tot) {
			Program temp;
			DeQueue(1,&temp,preadyqueue);
			//continue;

			return;

		}
		if(pnow->program.time<=0) {
			Program temp;
			DeQueue(1,&temp,preadyqueue);
			temp.time = q;
			EnQueue(2,temp,preadyqueue);
		}

		pnow = preadyqueue->front;
	}
}