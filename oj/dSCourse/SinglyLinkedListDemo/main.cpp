/*******************************************
 *                                         *
 * ��  ��: ��������غ�������              *
 *                                         *
 *******************************************/

#include <stdio.h> 
#include "SinglyLinkedList.h" 						//**������**//
				
void visit(ElemType e)                             	//���Ժ�������ӡ���� 
{
	printf("%d ", e);
}
	
int main(int argc, char **argv)
{
	LinkList L;
	int i;
	ElemType e;
	
	printf("���� InitList_L ����...\n");			//����InitList_L����
	{
		printf("��ʼ�������� L ...\n");					 
		InitList_L(L);
		printf("\n");	
	}
	PressEnter;
	
	printf("���� ListEmpty_L ����...\n");		//����ListEmpty_L����
	{
		ListEmpty_L(L) ? printf(" L Ϊ�գ���\n") : printf(" L ��Ϊ�գ�\n");
		printf("\n");
	}
	PressEnter;
	
	printf("���� ListInsert_L ����...\n");		//����ListInsert_L����
	{
		for(i=1; i<=6; i++)									
		{
			printf("�� L �� %d ��λ�ò��� \"%d\" ...\n", i, 2*i);
			ListInsert_L(L, i, 2*i);
		}
		printf("\n");
	}
	PressEnter;
	
	printf("���� ListTraverse_L ����...\n");	//����ListTraverse_L����
	{
		printf(" L �е�Ԫ��Ϊ��L = ");						 
		ListTraverse_L(L, visit);
		printf("\n\n");
	}
	PressEnter;

	printf("���� ListLength_L ����...\n");		//����ListLength_L����
	{
		printf(" L �ĳ���Ϊ %d \n", ListLength_L(L));
		printf("\n");
	}
	PressEnter;
		
	printf("���� ListDelete_L ����...\n");		//����ListDelete_L����
	{
		ListDelete_L(L, 6, e);
		printf("ɾ�� L �е� 6 ��Ԫ�� \"%d\" ...\n", e);
		printf(" L �е�Ԫ��Ϊ��L = ");						 
		ListTraverse_L(L, visit);
		printf("\n\n");
	}
	PressEnter;
		
	printf("���� GetElem_L ����...\n");			//����GetElem_L����
	{
		GetElem_L(L, 4, e);
		printf(" L �е� 4 ��λ�õ�Ԫ��Ϊ \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;
	
	printf("���� LocateElem_L ����...\n");		//����LocateElem_L����
	{
		i = LocateElem_L(L, 10);
		printf(" L �е�һ��Ԫ��ֵ���� \"10\" ��Ԫ�ص�λ��Ϊ %d \n", i);
		printf("\n");
	}
	PressEnter;
	
	printf("���� PriorElem_L ����...\n");		//����PriorElem_L����
	{
		PriorElem_L(L, 6, e);
		printf("Ԫ�� \"6\" ��ǰ��Ϊ \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;
	
	printf("���� NextElem_L ����...\n");			//����NextElem_L����
	{
		NextElem_L(L, 6, e);
		printf("Ԫ�� \"6\" �ĺ��Ϊ \"%d\" \n", e);
		printf("\n");
	}
	PressEnter;
	
	printf("���� ClearList_L ����...\n");		//����ClearList_L����
	{
		printf("��� L ǰ��");
		ListEmpty_L(L) ? printf(" L Ϊ�գ���\n") : printf(" L ��Ϊ�գ�\n");
		ClearList_L(L);
		printf("��� L ��");
		ListEmpty_L(L) ? printf(" L Ϊ�գ���\n") : printf(" L ��Ϊ�գ�\n");
		printf("\n");
	}
	PressEnter;
	
	printf("���� DestroyList_L ����...\n");		//����DestroyList_L����
	{
		printf("���� L ǰ��");
		L ? printf(" L ���ڣ�\n") : printf(" L �����ڣ���\n");
		DestroyList_L(L);
		printf("���� L ��");
		L ? printf(" L ���ڣ�\n") : printf(" L �����ڣ���\n");
		printf("\n");
	}
	PressEnter;
	
	printf("���� CreateList_HL ����...\n");		//����CreateList_HL����
	{
		LinkList L;
		printf("ͷ�巨���������� L = ");
		CreateList_HL(L, 5);
		ListTraverse_L(L, visit);
		printf("\n\n");
	} 
	PressEnter;
	
	printf("���� CreateList_TL ����...\n");		//����CreateList_TL����
	{
		LinkList L;
		printf("β�巨���������� L = ");
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
    printf("������A��Ԫ�أ�");
    ListTraverse_L(A,visit); /* ���ζ�Ԫ�ص���visit()�����Ԫ�ص�ֵ Ϊ 2��4��5��10��15*/  
    printf("\n");
    printf("������B��Ԫ�أ�"); 
    ListTraverse_L(B,visit); /* ���ζ�Ԫ�ص���visit()�����Ԫ�ص�ֵ Ϊ 1��6��8��12*/   
	printf("\n"); 
    
    PressEnter;
    Merge(A,B,C); 
    printf("�ϲ�������C��Ԫ�أ�"); 
    ListTraverse_L(C,visit); /* ���ζ�Ԫ�ص���visit()�����Ԫ�ص�ֵ Ϊ 1��2��4��5��6��8��10��12��15*/  
	printf("\n");    
    PressEnter;
    
    
    //��������C���� 
    Reverse(C);
    printf("���ú�����C��Ԫ�أ�"); 
    ListTraverse_L(C,visit); /* ���ζ�Ԫ�ص���visit()�����Ԫ�ص�ֵ Ϊ 15��12��10��8��6��5��4��2��1��*/  
    printf("\n"); 
	PressEnter;   
   
    DestroyList_L(A);
    DestroyList_L(B);
    DestroyList_L(C);
    PressEnter;
 
	
	
	return 0;
}




