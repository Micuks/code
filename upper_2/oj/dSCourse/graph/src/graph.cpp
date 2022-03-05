#include "../include/graph.h"
#include "../include/stack.h"

bool CreateGraph(ALGraph &G) {
    G.arcnum = 0;
    G.vexnum = 0;
    G.kind = DG;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        G.vertices[i].data = 0;
        G.vertices[i].firstarc = NULL;
    }
    return TRUE;
}

void DestroyArcNode(ArcNode *parc) {
    if(parc->nextarc != NULL)
        DestroyArcNode(parc->nextarc);
    if(parc->nextarc == NULL)
        free(parc);
}

bool DestroyGraph(ALGraph &G) {
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        DestroyArcNode(G.vertices[i].firstarc);
    }
    return TRUE;
}

bool InsertArc(ALGraph &G, VertexType v, VertexType w) {
    ArcNode *parc = NULL;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        if(G.vertices[i].data == v) {
            parc = G.vertices[i].firstarc;
            break;
        }
    }
    ArcNode *pnew = (ArcNode*)malloc(sizeof(ArcNode));
    if(pnew == NULL) {
        printf("Failed to allocate memory!\n");
        return FALSE;
    }
    pnew->adjvex = w;
    pnew->weight = 1;
    if(parc == NULL) {
        parc = pnew;
        parc->nextarc = NULL;
    }
    else if(parc->nextarc == NULL) {
        parc->nextarc = pnew;
        pnew->nextarc = NULL;
    }
    else {
        ArcNode* ptmp = parc->nextarc;
        parc->nextarc = pnew;
        pnew->nextarc = ptmp;
    }
    return TRUE;
}

bool DeleteArc(ALGraph &G, VertexType v, VertexType w) {
    ArcNode *parc = NULL;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        if(G.vertices[i].data == v) {
            parc = G.vertices[i].firstarc;
            break;
        }
    }
    if(parc == NULL) {
        printf("In DeleteArc: <v,w> not found!\n");
        return FALSE;
    }
    ArcNode *ppre = parc;
    while(parc->adjvex != w && parc != NULL) {
        ppre = parc;
        parc = parc->nextarc;
    }
    if(parc == NULL) {
        printf("In DeleteArc: <v,w> not found!\n");
        return FALSE;
    }
    ppre->nextarc = parc->nextarc;
    free(parc);
    return TRUE;
}

int GetInDegree(ALGraph &G, VertexType v) {
    int cnt = 0;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        ArcNode *parc = G.vertices[i].firstarc;
        if(parc == NULL)
            continue;
        if(parc->adjvex == v)
            cnt++;
        while(parc != NULL) {
            if(parc->adjvex == v)
                cnt++;
        }
        parc = parc->nextarc;
    }
    return cnt;
}

bool IsSimplePathExist(ALGraph &G, VertexType v, VertexType w, int len) {
    Stack *ps;
    InitStack(ps);
    ArcNode *parc = NULL;
    int depth[MAX_VERTEX_NUM];
    int visited[MAX_VERTEX_NUM];

    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        depth[i] = 1;
        visited[i] = 0;
    }

    for(int i = 0; i < MAX_VERTEX_NUM; i++) {
        if(G.vertices[i].data == v) {
            parc = G.vertices[i].firstarc;
            if(parc != NULL) {
                push(&(parc->adjvex), ps);
            }
            while((parc = parc->nextarc) != NULL) {
                push(&(parc->adjvex), ps);
            }
            break;
        }
    }

    VertexType vex;
    while(!StackEmpty(ps)) {
        pop(&vex, ps);
        visited[vex] = 1;
        if(vex == w && depth[vex] <= len)
            return TRUE;
        for(int i = 0; i < MAX_VERTEX_NUM; i++) {
            if(G.vertices[i].data == vex) {
                parc = G.vertices[i].firstarc;
                if(parc != NULL) {
                    depth[parc->adjvex] = depth[vex]+1;
                    push(&(parc->adjvex), ps);
                }
                while((parc = parc->nextarc) != NULL) {
                    depth[parc->adjvex] = depth[vex]+1;
                    push(&(parc->adjvex), ps);
                }
                break;
            }
        }
    }
    return FALSE;
}
