/*******************************************
 *                                         *
 * 内  容: 单链表相关函数测试              *
 *                                         *
 *******************************************/

#include <stdio.h> 
#include "SinglyLinkedList.h" 						//**单链表**//
				
void visit(ElemType e)                             	//测试函数，打印整型 
{
	printf("%d ", e);
}
	
int main(int argc, char **argv)
{
	LinkList L;
	int i;
	ElemType e;
	
	printf("函数 InitList_L 测试...\n");			//函数InitList_L测试
	{
		printf("初始化单链表 L ...\n");					 
		InitList_L(L);
		printf("\n");	
	}
	PressEnter;
	
	printf("函数 ListEmpty_L 测试...\n");		//函数ListEmpty_L测试
	{
		ListEmpty_L(L) ? printf(" L 为空！！\n") : printf(" L 不为空！\n");
		printf("\n");
	}
	PressEnter;
	
	printf("函数 ListInsert_L 测试...\n");		//函数ListInsert_L测试
	{
		for(i=1; i<=6; i++)									
		{
			printf("在 L 第 %d 个位置插入 \"%d\" ...\n", i, 2*i);
			ListInsert_L(L, i, 2*i);
		}
		printf("\n");
	}
	PressEnter;
	
	printf("函数 ListTraverse_L 测试...\n");	//函数ListTraverse_L测试
	{
		printf(" L 中的元素为：L = ");						 
		ListTraverse_L(L, visit);
		printf("\n\n");
	}
	PressEnter;

	printf("函数 ListLength_L 测试...\n");		//函数ListLength_L测试
	{
		printf(" L 的长度为 %d \n", ListLength_L(L));
		printf("\n");
	}
	PressEnter;
		
	printf("函数 ListDelete_L 测试...\n");		//函数ListDelete_L测试
	{
		ListDelete_L(L, 6, e);
		printf("删除 L 中第 6 个元素 \"%d\" ...\n", e);
		printf(" L 中的元素为：L = ");						 
		ListTraverse_L(L, visit);
		printf("\n\n");
	}
	PressEnter;
		
	printf("函数 GetElem_L 测试...\n");			//函数GetElem_L测试
	{
		GetElem_L(L, 4, e);
		printf(" L 中第 4 个位置的元素为 \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;
	
	printf("函数 LocateElem_L 测试...\n");		//函数LocateElem_L测试
	{
		i = LocateElem_L(L, 10);
		printf(" L 中第一个元素值等于 \"10\" 的元素的位置为 %d \n", i);
		printf("\n");
	}
	PressEnter;
	
	printf("函数 PriorElem_L 测试...\n");		//函数PriorElem_L测试
	{
		PriorElem_L(L, 6, e);
		printf("元素 \"6\" 的前驱为 \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;
	
	printf("函数 NextElem_L 测试...\n");			//函数NextElem_L测试
	{
		NextElem_L(L, 6, e);
		printf("元素 \"6\" 的后继为 \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;
	
	printf("函数 ClearList_L 测试...\n");		//函数ClearList_L测试
	{
		printf("清空 L 前：");
		ListEmpty_L(L) ? printf(" L 为空！！\n") : printf(" L 不为空！\n");
		ClearList_L(L);
		printf("清空 L 后：");
		ListEmpty_L(L) ? printf(" L 为空！！\n") : printf(" L 不为空！\n");
		printf("\n");
	}
	PressEnter;
	
	printf("函数 DestroyList_L 测试...\n");		//函数DestroyList_L测试
	{
		printf("销毁 L 前：");
		L ? printf(" L 存在！\n") : printf(" L 不存在！！\n");
		DestroyList_L(L);
		printf("销毁 L 后：");
		L ? printf(" L 存在！\n") : printf(" L 不存在！！\n");
		printf("\n");
	}
	PressEnter;
	
	printf("函数 CreateList_HL 测试...\n");		//函数CreateList_HL测试
	{
		LinkList L;
		printf("头插法建立单链表 L = ");
		CreateList_HL(L, 5);
		ListTraverse_L(L, visit);
		printf("\n\n");
	} 
	PressEnter;
	
	printf("函数 CreateList_TL 测试...\n");		//函数CreateList_TL测试
	{
		LinkList L;
		printf("尾插法建立单链表 L = ");
		CreateList_TL(L, 5);
		ListTraverse_L(L, visit);
		printf("\n\n");
	} 
	PressEnter;
	
	
	LinkList A,B,C;
	InitList_L(A);
	InitList_L(B);
	InitList_L(C);
	ListInsert_L(A,1,2);
    ListInsert_L(A,2,4);
    ListInsert_L(A,3,5);
    ListInsert_L(A,4,10);
    ListInsert_L(A,5,15);
    ListInsert_L(B,1,1);
    ListInsert_L(B,2,6);
    ListInsert_L(B,3,8);
    ListInsert_L(B,4,12);
    printf("单链表A的元素：");
    ListTraverse_L(A,visit); /* 依次对元素调用visit()，输出元素的值 为 2、4、5、10、15*/  
    printf("\n");
    printf("单链表B的元素："); 
    ListTraverse_L(B,visit); /* 依次对元素调用visit()，输出元素的值 为 1、6、8、12*/   
	printf("\n"); 
    
    PressEnter;
    Merge(A,B,C); 
    printf("合并后单链表C的元素："); 
    ListTraverse_L(C,visit); /* 依次对元素调用visit()，输出元素的值 为 1、2、4、5、6、8、10、12、15*/  
	printf("\n");    
    PressEnter;
    
    
    //将单链表C逆置 
    Reverse(C);
    printf("逆置后单链表C的元素："); 
    ListTraverse_L(C,visit); /* 依次对元素调用visit()，输出元素的值 为 15、12、10、8、6、5、4、2、1、*/  
    printf("\n"); 
	PressEnter;   
   
    DestroyList_L(A);
    DestroyList_L(B);
    DestroyList_L(C);
    PressEnter;
 
	
	
	return 0;
}




