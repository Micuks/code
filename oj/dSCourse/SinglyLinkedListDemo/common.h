#ifndef COMMON_H
#define COMMON_H

 #include<stdio.h>
 #include <stdlib.h>						//�ṩmalloc��realloc��free��exitԭ��
 #include<process.h> /* exit() */
 
 /* �������״̬���� */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 #define OVERFLOW -2
 

 typedef int Status;	 	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
 typedef int Boolean; 		/* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
 
 
 //��Enter������ 
 #define PressEnter\
 {\
	fflush(stdin);\
	printf("Press Enter...");\
	getchar();\
	fflush(stdin);\
 }
 
#endif
