/*******************************************
 *                                         *
 * �ļ���: SinglyLinkedList.cpp            *
 *                                         *
 *                                         *
 *******************************************/

#ifndef SINGLYLINKEDLIST_C
#define SINGLYLINKEDLIST_C

#include "SinglyLinkedList.h" 			//**������**//

Status InitList_L(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));  //����ͷ��㣬Ȼ���ͷ���ĵ�ַ��ŵ�L�� 
	if(!(L))
		exit(OVERFLOW);
	L->next = NULL; //ͷ����next��ΪNULL 
	
	return OK;
}

Status ClearList_L(LinkList L)		//�����������ͷ��� 
{	
	LinkList pre, p;
	
	if(!L)
		return ERROR;
	
	pre = L->next;  //preָ���һ����� 

	while(pre)
	{
		p = pre->next;
		free(pre);  //�ͷ�preָ��Ľ�� 
		pre = p;
	}

	L->next = NULL; //ͷ����next������ΪNULL 

	return OK; 
}

void DestroyList_L(LinkList &L)			//�������н�� 
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
	if(L!=NULL && L->next==NULL)		//���������ֻ��ͷ��� 
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
	
	while(p && j<i)						//p��Ϊ���һ�δ����i��
	{
		j++;
		p = p->next;
	}

	if(!p || j>i)						//��i��Ԫ�ز����� 
		return ERROR;

	e = p->data;

	return OK; 
}

int LocateElem_L(LinkList L, ElemType e)
{
	int i;
	LinkList p;
	
	i = -1;								//L������ʱ����-1 
	
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
				if(p==NULL)		//ʧ��ʱ�Ѿ������һ����� 
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
		
		if(p->data!=cur_e)				//��һ�������ǰ�� 
		{
			while(p->next)				//��p����к�� 
			{
				suc = p->next;			//sucָ��p�ĺ��
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
	//����������ɴ˺���
	
	printf("�������б�дNextElem_L����!\n");

	return ERROR;
}


Status ListInsert_L(LinkList L, int i, ElemType e)
{
	LinkList p, s;
	int j;
	
	p = L;
	j = 0; 
	
	while(p && j<i-1)					//Ѱ�ҵ�i-1����� 
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
	//����������ɴ˺���
	
	printf("�������б�дListDelete_L����!\n");

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
	L->next = NULL;							//����ͷ��� 
	
	for(i=1; i<=n; ++i)
	{
		if(scanf("%d", &tmp)==1)
		{
			p = (LinkList)malloc(sizeof(LNode));
			if(!p)
				exit(OVERFLOW);
			p->data = tmp;						//¼������ 
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

	//����������ɴ˺���
	L = (LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(OVERFLOW);
	L->next = NULL;							//����ͷ��� 
		
	printf("�������б�дβ�巨�����������CreateList_TL����!\n");
	return OK;
}

Status Merge(LinkList A, LinkList B, LinkList C) 
{  printf("����������ɺϲ�����\n");
   return OK;
}
 

Status Reverse(LinkList C) 
{  printf("��������������ó���\n");
   return OK;
}
 
 
#endif

