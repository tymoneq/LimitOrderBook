#ifndef MATCHING
#define MATCHING

#include "dataStructures.h"

int find_matching_orders(Order *newOrder, Limit *bestLimit, Book *limitOrderBook);
void fill_order(Order *newOrder, Limit *bestLimit, Book *limitOrderBook);

#endif
