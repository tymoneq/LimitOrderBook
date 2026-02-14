#include "../include/dataStructures.h"
#include "../include/matching_orders.h"
#include "../include/writing_orders_to_file.h"
#include <math.h>
#include <iostream>

int find_matching_orders(Order *newOrder, Limit *bestLimit)
{

    if (bestLimit == nullptr)
        return 1;

    if (newOrder->buyOrSell && newOrder->limit >= bestLimit->limitPrice)
        fill_order(newOrder, bestLimit);

    if (!newOrder->buyOrSell && newOrder->limit <= bestLimit->limitPrice)
        fill_order(newOrder, bestLimit);

    if (newOrder->shares > 0)
        return 1;
    return 0;
}
void fill_order(Order *newOrder, Limit *bestLimit)
{

    while (bestLimit->totalVolume != 0 && newOrder->shares != 0 && bestLimit->headerOrder != nullptr)
    {
        int shares_count = std::min(bestLimit->headerOrder->shares, newOrder->shares);

        write_to_file(newOrder, bestLimit->headerOrder);

        newOrder->shares -= shares_count;
        bestLimit->totalVolume -= shares_count;
        if (shares_count == bestLimit->headerOrder->shares)
        {
            bestLimit->size--;
            Order *filling_order = bestLimit->headerOrder;
            bestLimit->headerOrder = filling_order->nextOrder;
            if (bestLimit->headerOrder != nullptr)
                bestLimit->headerOrder->prevOrder = nullptr;

            delete filling_order;
        }
    }

    if (bestLimit->size == 0)
    {

        // erease form tree
    }
}
