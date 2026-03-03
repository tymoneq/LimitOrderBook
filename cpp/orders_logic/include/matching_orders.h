#ifndef MATCHING
#define MATCHING

#include "../../include/dataStructures.h"

int find_matching_orders(Order *newOrder, Limit *bestLimit, bool buyOrSell);
int fill_order(Order *newOrder, Limit *bestLimit);
void order_fulled(Limit *bestLimit);
void iterating_over_orders(Order *newOrder, Limit *bestLimit);
void freeing_structures(int code, Order *newOrder, Limit *bestLimit);

#endif
