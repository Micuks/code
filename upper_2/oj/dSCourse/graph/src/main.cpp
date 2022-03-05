#include "../include/stack.h"
#include "../include/graph.h"

int main() {
    int n, e;
    scanf("%d%d", &n, &e);
    ALGraph G;
    CreateGraph(G);
    G.arcnum = e;
    G.vexnum = n;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &(G.vertices[i].data));
    }
    int tmp[3];
    for(int i = 0; i < G.arcnum; i++) {
        for(int j = 0; i < 3; i++)
            scanf("%d", tmp+j);
        InsertArc(G, *tmp, tmp[1]);
    }
    DestroyGraph(G);
}
