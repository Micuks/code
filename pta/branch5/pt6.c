#include<stdio.h>
typedef struct{
    int id;
    char name[15];
    int c1;
    int c2;
    int c3;
} STUDENT;
int main() {
    int n,ptr=0;
    STUDENT stu[135];
    scanf("%d",&n);
    while(n--) {
        int opr;
        scanf("%d",&opr);
        int flag;
        int p;
        double f;
            // printf("opr = %d\n",opr);
        switch(opr) {
            case 1://ptr++
                scanf("%d",&stu[ptr].id);
                // getchar();
                for(int i=0;i<ptr;i++) {
                    if(stu[i].id==stu[ptr].id) {
                        printf("Students already exist\n");
                        scanf("%s%d%d%d",stu[ptr].name,&stu[ptr].c1,&stu[ptr].c2,&stu[ptr].c3);
                        stu[ptr].id=-1;
                        break;
                    }
                }
                char ch;
                p=0;
                scanf("%s",stu[ptr].name);
                scanf("%d%d%d",&stu[ptr].c1,&stu[ptr].c2,&stu[ptr].c3);
                printf("Add success\n");
                ptr++;
                break;
            case 2:
                scanf("%d",&stu[ptr].id);
                flag=1;
                for(int i=0;(i<ptr)&&flag;i++) {
                    if(stu[i].id==stu[ptr].id) {
                        stu[i].id=-2147483647;
                        printf("Delete success\n");
                        flag=0;
                    }
                }
                if(flag) printf("Students do not exist\n");
                break;
            case 3://ptr++ or ptr = ptr;
                scanf("%d",&stu[ptr].id);
                // getchar();
                flag=1;
                for(int i=0;i<ptr;i++) {
                    if(stu[i].id==stu[ptr].id) {
                        scanf("%d%d%d",&stu[i].c1,&stu[i].c2,&stu[i].c3);
                        printf("Update success\n");
                        // ptr++;
                        flag=0;
                    }
                }
                if(flag) {
                    printf("Students do not exist\n");
                    scanf("%d%d%d",&stu[ptr].c1,&stu[ptr].c2,&stu[ptr].c3);
                }
                break;
            case 4:
                scanf("%d",&stu[ptr].id);
                // getchar();
                flag=1;
                for(int i=0;i<ptr;i++) {
                    if(stu[i].id==stu[ptr].id) {
                        f=stu[i].c1+stu[i].c2+stu[i].c3;
                        f/=3;
                        printf(
                            "Student ID:%d\n"
                            "Name:%s\n"
                            "Average Score:%.1lf\n",stu[i].id,stu[i].name,f);
                        flag=0;
                    }
                }
                if(flag) printf("Students do not exist\n");
                break;
            default:
                break;
        }
    }
    return 0;
}