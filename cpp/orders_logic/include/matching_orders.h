#ifndef MATCHING
#define MATCHING

#include "../../include/dataStructures.h"

int find_matching_orders(Order *newOrder, Limit *bestLimit, bool buyOrSell);
int fill_order(Order *newOrder, Limit *bestLimit);

#endif
