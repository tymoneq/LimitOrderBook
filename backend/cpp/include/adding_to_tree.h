#ifndef ADDING
#define ADDING
#include "dataStructures.h"

int add_order(Order *newOrder, Book *limitOrderedBook);
Limit *add_order_to_tree(Order *newOrder, Limit *tree);
Limit *add_tree_node(Order *newOrder, Limit *parent);
int add_order_to_list(Order *newOrder, Limit *treeNode);


#endif
