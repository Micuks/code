// treedemo.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<stdlib.h> 

/* �������״̬���� */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

typedef char datatype;
datatype Nil='0'; /* �ַ�����0Ϊ�� */

 /* �������Ķ�������洢��ʾ */
 typedef struct bitnode
 {
   datatype data;
   struct bitnode *lchild,*rchild; /* ���Һ���ָ�� */                
 }BiTNode,*BiTree;


 Status InitBiTree(BiTree &T)
 { /* �������: ����ն�����T */
   T=NULL;
   return OK;
 }

 void DestroyBiTree(BiTree &T)
 { /* ��ʼ����: ������T���ڡ��������: ��������������T */
   if(T) /* �ǿ��� */
   {
     if(T->lchild) /* ������ */
       DestroyBiTree(T->lchild); /* ������������ */
     if(T->rchild) /* ���Һ��� */
       DestroyBiTree(T->rchild); /* �����Һ������� */
     free(T); /* �ͷŸ���� */
     T=NULL; /* ��ָ�븳0 */
   }
 }

 
 Status CreateBiTree(BiTree &T)
 { /* �㷨6-4,�������������������н���ֵ��������������ʾ�Ķ�����T������Nil��ʾ�գ��ӣ�����*/
   datatype ch;
   scanf("%c",&ch);
   if(ch==Nil) /* �� */
     T=NULL;
   else
   {
     T=(BiTNode *)malloc(sizeof(BiTNode));
     if(!T)
       exit(OVERFLOW);
     T->data=ch; /* ���ɸ���� */
     CreateBiTree(T->lchild); /* ���������� */
     CreateBiTree(T->rchild); /* ���������� */
   }
   return OK;
 }


 Status BiTreeEmpty(BiTree T)
 { /* ��ʼ����: ������T���� */
   /* �������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE */
   if(T)
     return FALSE;
   else
     return TRUE;
 }


 int BiTreeDepth(BiTree T)
 { /* ��ʼ����: ������T���ڡ��������: ����T����� */
   int i=0,j=0;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);

   if(T->rchild)
     j=BiTreeDepth(T->rchild);

   return i>j?i+1:j+1;
 }

 int CountLeaf(BiTree bt) //��Ҷ�ӽ������    
 {
 	return 0;
 }

void Exchange(BiTree T)   //�������н����������� 
{

}


 void PreOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú����� */
   /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */
   if(T) /* T���� */
   {
     Visit(T->data); /* �ȷ��ʸ���� */
     PreOrderTraverse(T->lchild,Visit); /* ��������������� */
     PreOrderTraverse(T->rchild,Visit); /* ���������������� */
   }
 }

 void InOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
   /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */

 }


 void PostOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
   /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */

 }

 
  void LevelOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
   /* �������: ��εݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */

 }
   
 
 void PreOrderTraverseNoRecursive(BiTree T,Status(*Visit)(datatype))
 { /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
   /* �������: ����ǵݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */

 }
 
  void InOrderTraverseNoRecursive(BiTree T,Status(*Visit)(datatype))
 { /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
   /* �������: ����ǵݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */

 }
 
 Status visitT(datatype e)
 {

   printf("%c ",e);
   return OK;
 }
 


int main(int argc, char* argv[])
{
   BiTree T;
   InitBiTree(T);
   printf("���������������(��:ABD0G000CE00F00)\n");

   CreateBiTree(T);

   int depth=BiTreeDepth(T);
   printf("�����������Ϊ��%d\n",depth);    //������ 
   
   int countleaf=CountLeaf(T);             //����Ҷ�ӽ�����Ŀ 
   printf("Ҷ�ӽ�����ĿΪ��%d\n",countleaf); 

   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");

   printf("����ݹ����������:\n");
   InOrderTraverse(T,visitT);
   printf("\n");

   printf("����ݹ����������:\n");
   PostOrderTraverse(T,visitT);
   printf("\n");
   
   printf("��α���������:\n");
   LevelOrderTraverse(T,visitT);
   printf("\n");
   
   
   printf("����ǵݹ����������:\n");
   PreOrderTraverseNoRecursive(T,visitT);
   printf("\n");

   printf("����ǵݹ����������:\n");
   InOrderTraverseNoRecursive(T,visitT);
   printf("\n");

   printf("--------------------------\n");
   printf("�����������н���\n");
   printf("--------------------------\n");
   Exchange(T);   

   printf("����������ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");

   printf("����������ݹ����������:\n");
   InOrderTraverse(T,visitT);
   printf("\n");

   printf("���������ݹ����������:\n");
   PostOrderTraverse(T,visitT);
   printf("\n");


   DestroyBiTree(T);
   system("pause");

	return 0;
}

