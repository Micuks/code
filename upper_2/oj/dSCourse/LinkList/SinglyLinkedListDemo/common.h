#ifndef COMMON_H
#define COMMON_H

 #include<stdio.h>
 #include <stdlib.h>						//提供malloc、realloc、free、exit原型
 #include<process.h> /* exit() */
 
 /* 函数结果状态代码 */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 #define OVERFLOW -2
 

 typedef int Status;	 	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
 typedef int Boolean; 		/* Boolean是布尔类型,其值是TRUE或FALSE */
 
 
 //摁Enter键继续 
 #define PressEnter\
 {\
	fflush(stdin);\
	printf("Press Enter...");\
	getchar();\
	fflush(stdin);\
 }
 
#endif
