#ifndef REMOVE
#define REMOVE

#include "dataStructures.h"

Limit *find_new_node(Limit *node);
void remove_node(Limit *node, Book *limitOrderBook);
void move_tree_pointers(Limit *node, Limit *new_node);

#endif