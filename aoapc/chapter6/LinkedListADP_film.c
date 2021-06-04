#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "LinkedListADTPractice.h"
void showmovies(Item item);
char* s_gets(char* a,int n);
int main() {
    List movies;
    Item temp;

    InitializeList(&movies);
    if(ListIsFull(&movies)) {
        fprintf(stderr,"No memory available! Bye!\n");
        exit(1);
    }

    puts("Enter first movie title:");
    while(s_gets(temp.title,TSIZE)!=NULL&&temp.title[0]!='\0') {
        puts("Enter your rating <0-10>:");
        scanf("%d",&temp.rating);
        while(getchar()!='\n')
            ;
        if(AddItem(temp,&movies)==false) {
            fprintf(stderr,"Problem allocating memory!\n");
            break;
        }
        if(ListIsFull(&movies)==true) {
            fprintf(stderr,"The list is now full.\n");
            break;
        }
        puts("Enter next movie title(empty line to stop):");
    }

    printf("movies = %p\n",movies);
    
    if(ListIsEmpty(&movies)==true)
        printf("No data entered. ");
    else {
        printf("Here is the movie list:\n");
        Traverse(&movies,showmovies);
    }
    printf("You entered %d movies.\n",ListItemCount(&movies));

    EmptyTheList(&movies);
    printf("Bye!\n");
    return 0;
}
void showmovies(Item item) {
    printf("Movie: %s   Rating: %d\n",item.title,item.rating);
}
char* s_gets(char* s,int n) {
    char* ret_val;
    char* find;

    ret_val=fgets(s,n,stdin);
    if(ret_val!=NULL) {
        find=strchr(s,'\n');
        if(find!=NULL)
            *find='\0';
        else {
            while(getchar()!='\n')
                ;
        }
    }
    return ret_val;
}