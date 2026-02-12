#ifndef INIT
#define INIT
#include "dataStructures.h"

int init_book(Book *limitOrderBook);
int free_memory(Book *limitOrderBook);
void free_tree(Limit *node);
void free_list(Order *order);

#endif
