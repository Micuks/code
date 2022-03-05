// treedemo.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<stdlib.h> 

/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef char datatype;
datatype Nil='0'; /* 字符型以0为空 */

 /* 二叉树的二叉链表存储表示 */
 typedef struct bitnode
 {
   datatype data;
   struct bitnode *lchild,*rchild; /* 左右孩子指针 */                
 }BiTNode,*BiTree;


 Status InitBiTree(BiTree &T)
 { /* 操作结果: 构造空二叉树T */
   T=NULL;
   return OK;
 }

 void DestroyBiTree(BiTree &T)
 { /* 初始条件: 二叉树T存在。操作结果: 销毁线索二叉树T */
   if(T) /* 非空树 */
   {
     if(T->lchild) /* 有左孩子 */
       DestroyBiTree(T->lchild); /* 销毁左孩子子树 */
     if(T->rchild) /* 有右孩子 */
       DestroyBiTree(T->rchild); /* 销毁右孩子子树 */
     free(T); /* 释放根结点 */
     T=NULL; /* 空指针赋0 */
   }
 }

 
 Status CreateBiTree(BiTree &T)
 { /* 算法6-4,按先序次序输入二叉树中结点的值，构造二叉链表表示的二叉树T。变量Nil表示空（子）树。*/
   datatype ch;
   scanf("%c",&ch);
   if(ch==Nil) /* 空 */
     T=NULL;
   else
   {
     T=(BiTNode *)malloc(sizeof(BiTNode));
     if(!T)
       exit(OVERFLOW);
     T->data=ch; /* 生成根结点 */
     CreateBiTree(T->lchild); /* 构造左子树 */
     CreateBiTree(T->rchild); /* 构造右子树 */
   }
   return OK;
 }


 Status BiTreeEmpty(BiTree T)
 { /* 初始条件: 二叉树T存在 */
   /* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
   if(T)
     return FALSE;
   else
     return TRUE;
 }


 int BiTreeDepth(BiTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
   int i=0,j=0;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);

   if(T->rchild)
     j=BiTreeDepth(T->rchild);

   return i>j?i+1:j+1;
 }

 int CountLeaf(BiTree bt) //求叶子结点数量    
 {
 	return 0;
 }

void Exchange(BiTree T)   //交换所有结点的左右子树 
{

}


 void PreOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数。 */
   /* 操作结果: 先序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
   if(T) /* T不空 */
   {
     Visit(T->data); /* 先访问根结点 */
     PreOrderTraverse(T->lchild,Visit); /* 再先序遍历左子树 */
     PreOrderTraverse(T->rchild,Visit); /* 最后先序遍历右子树 */
   }
 }

 void InOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 中序递归遍历T,对每个结点调用函数Visit一次且仅一次 */

 }


 void PostOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */

 }

 
  void LevelOrderTraverse(BiTree T,Status(*Visit)(datatype))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 层次递归遍历T,对每个结点调用函数Visit一次且仅一次 */

 }
   
 
 void PreOrderTraverseNoRecursive(BiTree T,Status(*Visit)(datatype))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 先序非递归遍历T,对每个结点调用函数Visit一次且仅一次 */

 }
 
  void InOrderTraverseNoRecursive(BiTree T,Status(*Visit)(datatype))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 中序非递归遍历T,对每个结点调用函数Visit一次且仅一次 */

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
   printf("请先序输入二叉树(如:ABD0G000CE00F00)\n");

   CreateBiTree(T);

   int depth=BiTreeDepth(T);
   printf("二叉树的深度为：%d\n",depth);    //输出深度 
   
   int countleaf=CountLeaf(T);             //计算叶子结点的数目 
   printf("叶子结点的数目为：%d\n",countleaf); 

   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");

   printf("中序递归遍历二叉树:\n");
   InOrderTraverse(T,visitT);
   printf("\n");

   printf("后序递归遍历二叉树:\n");
   PostOrderTraverse(T,visitT);
   printf("\n");
   
   printf("层次遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   printf("\n");
   
   
   printf("先序非递归遍历二叉树:\n");
   PreOrderTraverseNoRecursive(T,visitT);
   printf("\n");

   printf("中序非递归遍历二叉树:\n");
   InOrderTraverseNoRecursive(T,visitT);
   printf("\n");

   printf("--------------------------\n");
   printf("左、右子树进行交换\n");
   printf("--------------------------\n");
   Exchange(T);   

   printf("交换后先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");

   printf("交换后中序递归遍历二叉树:\n");
   InOrderTraverse(T,visitT);
   printf("\n");

   printf("交换后后序递归遍历二叉树:\n");
   PostOrderTraverse(T,visitT);
   printf("\n");


   DestroyBiTree(T);
   system("pause");

	return 0;
}

