#ifndef MATCHING
#define MATCHING

#include "dataStructures.h"

int find_matching_orders(Order *newOrder, Limit *bestLimit);
void fill_order(Order *newOrder, Limit *bestLimit);

#endif
