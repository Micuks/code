#include <cstdio>
#include <cstdlib>
#include <climits>

#define TRUE 1
#define FALSE 0

const int INFINITY = INT_MAX;
const int MAX_VERTEX_NUM = 20;

typedef enum {DG, DN, UDG, UDN} GraphKind;
typedef int InfoType;
typedef int VertexType;

typedef struct ArcNode {
    VertexType adjvex;
    int weight;
    struct ArcNode *nextarc;
    InfoType *info;
} ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
    GraphKind kind;
} ALGraph;

bool CreateGraph(ALGraph &G);

bool DestroyGraph(ALGraph &G);

void DestroyArcNode(ArcNode* parc);

bool InsertArc(ALGraph &G, VertexType v, VertexType w);

bool DeleteArc(ALGraph &G, VertexType v, VertexType w);

int GetInDegree(ALGraph &G, VertexType v);

bool IsSimplePathExist(ALGraph &G, VertexType v, VertexType w, int len);
