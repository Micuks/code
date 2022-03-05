#include "../include/haffman.h"
#include <cstring>

void select(HuffmanTree &HT, int n, int &s1, int &s2) {
    HT[0].w = 0;
    s1 = 1, s2 = 2;
    for(int i = 1; i <= n; i++) {
        if(HT[i].w < HT[s1].w) {
            s1 = i;
        }
        if(s1 != i && HT[i].w < HT[s2].w) {
            s2 = i;
        }
    }
}

void BuildHT(HuffmanTree &HT, int *w, int n) {
    if(n <= 1) {
        HT = NULL;
        return;
    }
    int m = 2 * n -1;
    HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
    HuffmanTree p = HT+1;
    for(int i = 1; i <= n; p++, i++, w++) {
        *p = {*w, 0, 0, 0};
    }
    for(int i = n+1; i <= m; i++) {
        int s1, s2;
        select(HT, i-1, s1, s2);
        HT[i].lch = s1; HT[i].rch = s2;
        HT[i].parent = 0;
        HT[s1].parent = i; HT[s2].parent = i;
        HT[i].w = HT[s1].w + HT[s2].w;
    }
}

void HuffmanCoding(HuffmanTree HT, int n, HuffmanCode &HC) {
    HC = (HuffmanCode)malloc((n+1) *sizeof(char*));
    char* cd = (char*)malloc(n * sizeof(char));
    cd[n-1] = '\0';
    for(int i = 1; i <= n; i++) {
        int start = n-1;
        for(int c = i, f = HT[i].parent; f; c = f, f = HT[f].parent) {
            if(HT[f].lch == c) cd[--start] = '0';
            else cd[--start] = '1';
        }
        HC[i] = (char*)malloc((n-start)*sizeof(char));
        strcpy(HC[i], cd+start);
    }
    free(cd);
}

void HuffManEncoding(HuffmanCode HC, char *src, char** dest) {
    int i = 0;
    while(src[i] != '\0') {
        if(src[i] == ' ') {
            strcpy(dest[i], *(HC+1));
        }
        else {
            strcpy(dest[i], *(HC+src[i]-'A'+1));
        }
        i++;
    }
    strcpy(dest[i], "\0");
}

void HuffmanDecoding(HuffmanCode HC, char **src, char* dest) {
    int i = 0;
    while(strcmp(src[i], "\0")) {
        if(!strcmp(src[i], HC[1])) {
            dest[i] = ' ';
        }
        else for(int j = 2; j <= 27; j++) {
            if(!strcmp(src[i], HC[j])) {
                dest[i] = 'A' + j-2;
            }
        }
        i++;
    }
    dest[i] = '\0';
}

int main() {
    FILE* fp;
    fp = fopen("Conf", "r");
    int n = 0;
    int w[maxn];
    char c[maxn];
    fscanf(fp, "%d", &n);
    for(int i = 1; i <= n; i++) {
        fscanf(fp, "%c %d", &c[i], &w[i]);
    }
    HuffmanTree HT;
    BuildHT(HT, w, n);
    fclose(fp);

    fp = fopen("ToBeTran", "r");
    HuffmanCode HC;
    HuffmanCoding(HT, n, HC);
    char src[maxn];
    fscanf(fp, "%s", src);
    char** dest;
    dest = (char**)malloc(maxn*sizeof(char*));
    for(int i = 0; i < maxn; i++)
        dest[i] = (char*)malloc(sizeof(char));
    HuffManEncoding(HC, src, dest);
    fclose(fp);

    fp = fopen("CodeFile", "w");
    for(int i = 0; strcmp(dest[i], "\0"); i++) {
        fprintf(fp, "%s", dest[i]);
    }
    fclose(fp);

    fp = fopen("CodeFile", "r");
    for(int i = 0; fscanf(fp, "%s", dest[i]) == 1; i++) {
        ;
    }
    HuffmanDecoding(HC, dest, src);
    fclose(fp);

    fopen("TextFile", "w");
    fprintf(fp, "%s", src);
    fclose(fp);
    return 0;
}
