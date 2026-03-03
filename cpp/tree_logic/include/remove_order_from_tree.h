#ifndef REMOVE
#define REMOVE
#include "../../include/dataStructures.h"

Limit *find_new_node(Limit *node);
void remove_node(Limit *node, Book *limitOrderBook);
void move_tree_pointers(Limit *node, Limit *new_node);
void move_son_pointers(Limit *node, Limit *new_node);
void move_new_node_to_node(Limit *node, Limit *new_node);

#endif