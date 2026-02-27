#ifndef ADD_NODE
#define ADD_NODE

#include "../../include/dataStructures.h"

Limit *create_root(Order *newOrder, Limit *tree);
Limit *find_place_for_node(Order *newOrder, Limit *parent_node);
Limit *add_new_node(Order *newOrder, Limit *parent_node, bool rightSon);
void add_to_node(Order *newOrder, Limit *tree);
std::pair<Limit *, Limit *> find_place_to_insert_new_node(Order *newOrder, Limit *tree);

#endif