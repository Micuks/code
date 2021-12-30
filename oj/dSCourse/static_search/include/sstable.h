const int LIST_INT_SIZE = 1000;

typedef int ElemType;

typedef struct {
    ElemType *elem;
    int length;
} SSTable;

bool InitTable(SSTable &T);

bool DestroyTable(SSTable &T);

int SearchTable(SSTable T, ElemType key);

int InsertTable(SSTable &T, ElemType e);

bool DeleteTable(SSTable &T, ElemType key);

void TraverseTable(SSTable T, void(*Visit)(ElemType));

void PrintTable(SSTable T);
