#ifndef SCHEMAS_H
#define SCHEMAS_H
#include "util.h"

void fragmentation_statistics(int in_frag, Block *b, int m);
void re_init(Process *p, Block *b, int n, int m);
void first_fit(Process *p, Block *b, int n, int m);
void best_fit(Process *p, Block *b, int n, int m);
#endif // !SCHEMAS_H
