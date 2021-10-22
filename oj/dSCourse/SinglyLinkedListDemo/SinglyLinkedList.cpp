/*******************************************
 *                                         *
 * 文件名: SinglyLinkedList.cpp            *
 *                                         *
 *                                         *
 *******************************************/

#ifndef SINGLYLINKEDLIST_C
#define SINGLYLINKEDLIST_C

#include "SinglyLinkedList.h" 			//**单链表**//

Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));  //创建头结点，然后把头结点的地址存放到L中 
	if(!(L))
		exit(OVERFLOW);
	L->next = NULL; //头结点的next域为NULL 
	
	return OK;
}

Status ClearList_L(LinkList L)		//清空链表，保留头结点 
{	
	LinkList pre, p;
	
	if(!L)
		return ERROR;
	
	pre = L->next;  //pre指向第一个结点 

	while(pre)
	{
		p = pre->next;
		free(pre);  //释放pre指向的结点 
		pre = p;
	}

	L->next = NULL; //头结点的next域设置为NULL 

	return OK; 
}

void DestroyList_L(LinkList &L)			//销毁所有结点 
{
	LinkList p = L;	

	while(p)
	{
		p = L->next;
		free(L);
		L = p;
	}
}

Status ListEmpty_L(LinkList L)
{
	if(L!=NULL && L->next==NULL)		//链表存在且只有头结点 
		return TRUE;
	else
		return FALSE;
}

int ListLength_L(LinkList L)
{
	LinkList p;
	int i;
	
	if(L)
	{
		i = 0;
		p = L->next;
		while(p)
		{
			i++;
			p = p->next;
		}		
	}
	
	return i;
}



Status GetElem_L(LinkList L, int i, ElemType &e)
{
	int j;
	LinkList p = L->next;
	
	j = 1;
	p = L->next;
	
	while(p && j<i)						//p不为空且还未到达i处
	{
		j++;
		p = p->next;
	}

	if(!p || j>i)						//第i个元素不存在 
		return ERROR;

	e = p->data;

	return OK; 
}

int LocateElem_L(LinkList L, ElemType e)
{
	int i;
	LinkList p;
	
	i = -1;								//L不存在时返回-1 
	
	if(L)
	{
		i = 0;
		p = L->next;
		
		while(p)
		{
			i++;
			
			if(e!=p->data)
			{
				p = p->next;
				if(p==NULL)		//失配时已经是最后一个结点 
					i++;
			}
			else
				break;
		}	
	}

	return i;	
}


		
Status PriorElem_L(LinkList L, ElemType cur_e, ElemType &pre_e)
{
	LinkList p, suc;
	
	if(L)
	{
		p = L->next;
		
		if(p->data!=cur_e)				//第一个结点无前驱 
		{
			while(p->next)				//若p结点有后继 
			{
				suc = p->next;			//suc指向p的后继
				if(suc->data==cur_e)
				{
					pre_e = p->data;
					return OK;
				}
				p = suc;
			}			
		}	
	}

	return ERROR;
}

Status NextElem_L(LinkList L, ElemType cur_e, ElemType &next_e)
{
	//请大家自行完成此函数
	
	printf("请大家自行编写NextElem_L函数!\n");

	return ERROR;
}


Status ListInsert_L(LinkList L, int i, ElemType e)
{
	LinkList p, s;
	int j;
	
	p = L;
	j = 0; 
	
	while(p && j<i-1)					//寻找第i-1个结点 
	{
		p = p->next;
		++j;
	}
	
	if(!p || j>i-1)
		return ERROR;

	s = (LinkList)malloc(sizeof(LNode));
	if(!s)
		exit(OVERFLOW);
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}



Status ListDelete_L(LinkList L, int i, ElemType &e)
{
	//请大家自行完成此函数
	
	printf("请大家自行编写ListDelete_L函数!\n");

	return OK; 
}

Status ListTraverse_L(LinkList L, void(Visit)(ElemType))
{
	LinkList p;

	if(!L)
		return ERROR;
	else
		p = L->next;	

	while(p)
	{
		Visit(p->data);
		p = p->next;
	}

	return OK;
}


Status CreateList_HL(LinkList &L, int n)
{
	int i;
	LinkList p;
	ElemType tmp;
		
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(OVERFLOW);
	L->next = NULL;							//建立头结点 
	
	for(i=1; i<=n; ++i)
	{
		if(scanf("%d", &tmp)==1)
		{
			p = (LinkList)malloc(sizeof(LNode));
			if(!p)
				exit(OVERFLOW);
			p->data = tmp;						//录入数据 
			p->next = L->next;
			L->next = p;		
		}
		else
			return ERROR;
	}
	
	return OK;
}  

Status CreateList_TL(LinkList &L, int n)
{

	//请大家自行完成此函数
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(OVERFLOW);
	L->next = NULL;							//建立头结点 
		
	printf("请大家自行编写尾插法创建单链表的CreateList_TL函数!\n");
	return OK;
}

Status Merge(LinkList A, LinkList B, LinkList C) 
{  printf("请大家自行完成合并程序！\n");
   return OK;
}
 

Status Reverse(LinkList C) 
{  printf("请大家自行完成逆置程序！\n");
   return OK;
}
 
 
#endif

