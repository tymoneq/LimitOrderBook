#ifndef ADD_ORDER
#define ADD_ORDER

#include "../../include/dataStructures.h"

int add_order(Order *newOrder, Book *limitOrderedBook);
Limit *place_order_to_tree(Order *newOrder, Limit *tree);

#endif