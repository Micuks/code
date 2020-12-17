#include <stdio.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    getchar();
    char a[100001];
    char *p[100];
    p[0] = a;
    int cnt = 1;
    for (int i = 0; cnt < n; i++)
    {
        if (getchar() != '\n')
        {
            a[i] = getchar();
        }

        if (getchar() == '\n')
        {
            a[i] = '\0';
            p[cnt] = a;
            cnt++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        puts(p[i]);
    }

    return 0;
}
