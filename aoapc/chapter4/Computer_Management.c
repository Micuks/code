#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAXN 200
#define EPS 1e-5
const char* subject[]={"Chinese","Mathematics","English","Computerming","ALL"};

#define bool int
#define true 1
#define false 0

typedef struct COMPUTER {
    char no[12];
    char name[40];
    float dj;
    int num;
    float jine;
} Computer;

typedef struct node {
	Computer computer;
	struct node* next;
	struct node* last;
} Node;

typedef struct queue {
	Node* front;
	Node* rear;
	int computers;
} Queue;

void InitializeQueue(Queue* pq);

bool IsQueueEmpty(const Queue* pq);

bool IsQueueFull(const Queue* pq);

int QueueItemCount(const Queue* pq);

//type == 1为从队首进入，type == 2为从队尾进入
bool EnQueue(int type,Computer pro,Queue* pq);

void EmptyTheQueue(Queue* pq);

int n=0,u=0;
Queue list;


int removed[MAXN];

void InitializeQueue(Queue* pq) {
	pq->front = NULL;
	pq->rear = NULL;
	pq->computers = 0;
}

bool IsQueueEmpty(const Queue* pq) {
	return pq->computers == 0;
}

bool IsQueueFull(const Queue* pq) {
	return pq->computers == MAXN;
}

int QueueItemCount(const Queue* pq) {
	return pq->computers;
}
bool EnQueue(int type,Computer pro,Queue* pq) {
	Node* pnode = (Node*)malloc(sizeof(Node));
	if(pnode == NULL)
		return false;
	pnode->computer = pro;
	pnode->last = NULL;
	pnode->next = NULL;

	if(IsQueueFull(pq) == true) return false;
	if(IsQueueEmpty(pq) == true) {
		pq->front = pnode;
		pq->rear = pnode;
		pq->computers = 1;
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
	pq->computers++;

	return true;
}

bool DeQueue(int type,Computer* ppr,Queue* pq) {
	if(IsQueueEmpty(pq) == true) return false;
	if(QueueItemCount(pq) == 1) {
		*ppr = pq->front->computer;
		free(pq->front);
		InitializeQueue(pq);
		return true;
	}
	else if(type == 1) {
		*ppr = pq->front->computer;

		Node* pnode = pq->front->next;
		pnode->last = NULL;
		free(pq->front);
		pq->front = pnode;
	}
	else if(type == 2) {
		*ppr = pq->rear->computer;

		Node* pnode = pq->rear->last;
		pnode->next = NULL;
		free(pq->rear);
		pq->rear = pnode;
	}
	pq->computers--;
	return true;
}

void EmptyTheQueue(Queue* pq) {
	while(IsQueueEmpty(pq) == false) {
		Computer dustbin;
		DeQueue(2,&dustbin,pq);
	}
}

//type == 1为add，type == 0为change
void add(int type) {
    for(;;) {
        Computer temp;
        int flag=1;
        printf("Please enter the 编号、名字、单价、数量. Enter 0 to finish.\n");
        scanf("%s",temp.no);
        if(!strcmp(temp.no,"0")) break;
        Node* pnode = list.front;
        for(int i=0;i<n;i++) {
            if(strcmp(temp.no,pnode->computer.no) == 0) {

                // printf("temp.no = %s, pnode->computer.no = %s, n = %d\n",temp.no,pnode->computer.no,n);
                
                flag=0;
                if(removed[i]==1) flag=1;
                if(type == 1 && flag == 0) printf("Duplicated 编号.\n");
                if(flag == 0) break;
            }
            pnode = pnode -> next;
        }
        scanf("%s%f%d",temp.name,&temp.dj,&temp.num);
        temp.jine = (double)temp.num * temp.dj;
        if(!flag && !type) {
            pnode->computer = temp;
        }
        if(flag && type) {
            n++;
            EnQueue(2,temp,&list);
        }
    }
}

char* itoa(int num,char* str,int radix)
{
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum;
    int i=0,j,k;

    if(radix==10&&num<0)
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num;
 
    do
    {
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
    }while(unum);
 
    str[i]='\0';
 
    if(str[0]=='-') k=1;
    else k=0;
 
    char temp;
    for(j=k;j<=(i-1)/2;j++)
    {
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
 
    return str;
 
}

void rem(int type) {
    int cnt;
    char stringid[15]={};
    for(;;) {
        cnt=0;
        printf("Please enter 编号 or name. Enter 0 to finish.\n");
        int id;
        scanf("%d",&id);
        if(id == 0) return;
        Node* pnode;
        itoa(id,stringid,10);
        pnode = list.front;
        for(int i=0;i<n;i++) {
            if(!removed[i]&&(!strcmp(pnode->computer.no,stringid)||!strcmp(pnode->computer.name,stringid))) {
                if(!type) {
                    cnt++;
                    removed[i]=1;
                    pnode->last->next = pnode->next;
                    pnode->next->last = pnode->last;
                    free(pnode);
                    list.computers--;
                }
                else {
                    printf("%s %s %f %d %f\n",pnode->computer.no,pnode->computer.name,pnode->computer.dj,pnode->computer.num,pnode->computer.jine);
                }
                if(*stringid>='0'&&*stringid<='9') break;
            }
            pnode = pnode->next;
        }
        if(!type) printf("%d computers(s) removed.\n",cnt);
    }
}

void show_statistics() {
    int num = 0;
    double total = 0;
    Node* pnode = list.front;
    for(int i=0;i<n;i++) {
        if(removed[i]==0) {
            num += pnode->computer.num;
            total += pnode->computer.jine;
        }
        pnode = pnode->next;
    }
    printf("Number of computers: %d\n"
        "Total cost of computers: %f\n",
        num,total);
}

void printmenu() {
    printf("\nWelcome to Computer Management System:\n\n"
            "A - Add\n"
            "B - Remove\n"
            "C - Query\n"
            "D - Change\n"
            "E - Show Statistics\n"
            "Q - Exit\n\n");
}

int IsChoiceValid(char ch) {
    if((ch - 'A' <= 4 && ch - 'A' >= 0) || ch == 'Q')
        return 1;
    return 0;
}

int main() {
    InitializeQueue(&list);
    for(;;) {
        printmenu();//啊
        char choice = 0;
        scanf("%c",&choice);
        while(!IsChoiceValid(choice)) {
            char ch;
            scanf("%c",&choice);
            while((ch = getchar())!='\n')
                ;
        }
        if(choice == 'A') add(1);
        else if(choice == 'B') rem(0);
        else if(choice == 'C') rem(1);
        else if(choice == 'D') add(0);
        else if(choice == 'E') show_statistics();
        else if(choice == 'Q') break;
    }
    return 0;
}