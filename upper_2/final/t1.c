#include <stdio.h>
#include <stdlib.h>

int **pascal(int n);

int main()
{
    int i, j, n;
    int **array;

    scanf("%d", &n);

    array = pascal(n);

    if (array != NULL)
    {
        for (i = 0; i < n; i++) //输出杨辉三角
        {
            for (j = 0; j < i; j++)
                printf("%d ", array[i][j]);
            printf("%d\n", array[i][j]);
        }
        //内存释放
        for (i = 0; i < n; i++)
            free(array[i]);
        free(array);
        array = NULL;
    }

    return 0;
}

int** pascal(int n) {
    int** array=(int**)malloc((n+1)*sizeof(int*));
    for(int i=0;i<n;i++)
        array[i]=(int*)malloc((i+1)*sizeof(int));
    for(int i=0;i<n;i++) {
        array[i][0]=1;
        array[i][i]=1;
    }
    for(int i=2;i<n;i++) {
        for(int j=1;j<i;j++) {
            array[i][j]=array[i-1][j-1]+array[i-1][j];
        }
    }
    return array;
}