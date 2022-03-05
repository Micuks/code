#include <cstdlib>
#include <cstring>
#include <cstdio>
#define Status int
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
#define MAXSTRLEN 1000

typedef unsigned char SString[MAXSTRLEN+1];

Status findnext(int* &next, SString t) {
    next = (int*)malloc(t[0] * sizeof(int));
    if(!next) {
        printf("overflow\n");
        return FALSE;
    }
    next[1] = 0;
    for(int i = 2; i <= t[0]; i++) {
        next[i] = 1;
        for(int j = 1; j < i-1; j++) {
            if(t[1] == t[i-j]) {
                int flag = 1;
                for(int k = j; k > 0; k--) {
                    if(t[i-k] != t[j-k+1]) {
                        flag = 0;
                        break;
                    }
                }
                if(flag) {
                    next[i] = j+1;
                }
            }
        }
    }
    return TRUE;
}

Status kmp(SString s, SString t) {
    int i = 1, j = 1;
    int* next = NULL;
    findnext(next, t);
    for(int i = 1; i <= t[0]; i++)
        printf("%d ", next[i]);
    putchar('\n');
    while(i <= s[0] && j <= t[0]) {
        if(s[i] == t[j]) {
            i++; j++;
        }
        else if(next[j]) {
            j = next[j];
        }
        else {
            i++; j = 1;
        }
    }
    if(j > t[0])
        printf("kmp: index = %d\n", i - t[0]);
    else
        printf("kmp: 0\n");
    free(next);
    if(j > t[0])
        return i - t[0];
    else
        return FALSE;
}

Status delchain(SString &s, SString t) {
    int ind = -1;
    if(!s[0])
        return FALSE;
    while((ind = kmp(s, t))) {
        for(int i = ind; i < ind + t[0]; i++) {
            s[i] = s[i+t[0]];
        }
        s[0] -= t[0];
        printf("successfully deleted!\n");
        printf("s = %d%s\n", *s, s+1);
    }
    return TRUE;
}

int main() {
    SString s, t;
    char s1[] = "ADBADABBAABADABBADADA", t1[] = "ADABBADADA";
    s[0] = strlen(s1);
    t[0] = strlen(t1);
    for(int i = 1; i <= s[0]; i++) {
        s[i] = s1[i-1];
    }
    s[s[0]+1] = '\0';
    for(int i = 1; i <= t[0]; i++) {
        t[i] = t1[i-1];
    }
    t[t[0]+1] = '\0';
    printf("s = %d%s, t = %d%s.\n", *s, s+1, *t, t+1);
    delchain(s, t);
    return 0;
}
