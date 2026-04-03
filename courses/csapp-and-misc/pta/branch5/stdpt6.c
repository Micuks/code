#include <stdio.h>

struct id {
    int ca;//操作类型
    char name[36];//姓名
    long long ID;
    int sc1;//数学
    int sc2;//英语
    int sc3;//计算机
};

int add(struct id *ptr[], int i, struct id a[], struct id b[], int c);
//添加信息操作
void del(struct id *ptr[], int i, struct id a[], struct id b[], int c);
//删除信息操作
void readd(struct id *ptr[], int i, struct id a[], struct id b[], int c);
//重写信息操作
void print(struct id *ptr[], int i, struct id a[], struct id b[], int c);
//打印信息操作
int main() {
    struct id a[300];
    struct id b[300];
    int n;
    b[299].ID = -1;
    scanf("%d", &n);
    struct id *ptr[300];
    //录入输入
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i].ca);
        if (a[i].ca == 1) {
            scanf("%lld", &a[i].ID);
            scanf("%s", a[i].name);
            scanf("%d", &a[i].sc1);
            scanf("%d", &a[i].sc2);
            scanf("%d", &a[i].sc3);
        }
        if (a[i].ca == 2 || a[i].ca == 4) {
            scanf("%lld", &a[i].ID);
        }
        if (a[i].ca == 3) {
            scanf("%lld", &a[i].ID);
            scanf("%d", &a[i].sc1);
            scanf("%d", &a[i].sc2);
            scanf("%d", &a[i].sc3);
        }
    }
    int c = 0;//记录成功写入的次数
    for (int i = 0; i < n; i++) {
        if (a[i].ca == 1) {
            c = add(ptr, i, a, b, c);
        }
        if (a[i].ca == 2) {
            del(ptr, i, a, b, c);
        }
        if (a[i].ca == 3) {
            readd(ptr, i, a, b, c);
        }
        if (a[i].ca == 4) {
            print(ptr, i, a, b, c);
        }
    }
    return 0;
}

int add(struct id *ptr[], int i, struct id a[], struct id b[], int c) {
    int f = 1;
    for (int j = 0; j < c; j++) {
        if (ptr[j]->ID == a[i].ID) {
            f = 0;
        }
    }
    if (f == 1) {
        ptr[c] = &b[c];
        b[c] = a[i];
        printf("Add success\n");
        c++;
    }
    if (f == 0) {
        printf("Students already exist\n");
    }
    return c;
}

void del(struct id *ptr[], int i, struct id a[], struct id b[], int c) {
    int f = 1;
    for (int j = 0; j < c; j++) {
        if (ptr[j]->ID == a[i].ID) {
            ptr[j] = &b[299];//不是真的删除，而是指向一个不可能存在的数据，使其条件不成立，执行结果和删除一样（不是一个好方法）
            f = 0;
        }
    }
    if (f == 0) {
        printf("Delete success\n");
    }
    if (f == 1) {
        printf("Students do not exist\n");
    }
}

void readd(struct id *ptr[], int i, struct id a[], struct id b[], int c) {
    int f = 1;
    for (int j = 0; j < c; j++) {
        if (ptr[j]->ID == a[i].ID) {
            ptr[j]->sc1 = a[i].sc1;
            ptr[j]->sc2 = a[i].sc2;
            ptr[j]->sc3 = a[i].sc3;
            f = 0;
        }
    }
    if (f == 0) {
        printf("Update success\n");
    }
    if (f == 1) {
        printf("Students do not exist\n");
    }
}

void print(struct id *ptr[], int i, struct id a[], struct id b[], int c) {
    int f = 1, m;
    double ave;
    for (int j = 0; j < c; j++) {
        if (ptr[j]->ID == a[i].ID) {
            f = 0;
            m = j;
        }
    }
    if (f == 1) {
        printf("Students do not exist\n");
    }
    if (f == 0) {
        printf("Student ID:%lld\n", ptr[m]->ID);
        printf("Name:");
        puts(ptr[m]->name);
        ave = ((double) ptr[m]->sc1 + (double) ptr[m]->sc2 + (double) ptr[m]->sc3) / 3;
        printf("Average Score:%.1lf\n", ave);
    }
}
