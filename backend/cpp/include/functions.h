#ifndef FUNCTIONS
#define FUNCTIONS
#include "dataStructures.h"

int init_book(Book *limitOrderBook);
int add_order(Order *newOrder, Book *limitOrderedBook);
int add_order_to_tree(Order *newOrder, Limit *tree);
Limit *add_tree_node(Order *newOrder, Limit *parent);
int add_order_to_list(Order *newOrder, Limit *treeNode);
int free_memory(Book *limitOrderBook);

#endif
