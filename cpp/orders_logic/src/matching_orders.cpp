#include "../include/matching_orders.h"
#include "../../logging/include/writing_orders_to_file.h"

#include <math.h>
// returning 0 if no transactions 1 if Order filled 2 if bestLimit filled 3 if both filled
int find_matching_orders(Order *newOrder, Limit *bestLimit, bool buyOrSell)
{

    if (buyOrSell && newOrder->limit >= bestLimit->limitPrice)
        return fill_order(newOrder, bestLimit);

    else if (!buyOrSell && newOrder->limit <= bestLimit->limitPrice)
        return fill_order(newOrder, bestLimit);

    return 0;
}

int fill_order(Order *newOrder, Limit *bestLimit)
{
    int code = 0;
    if (newOrder->shares == bestLimit->totalVolume)
        code = 3;
    else if (newOrder->shares < bestLimit->totalVolume)
        code = 1;
    else
        code = 3;

    while (newOrder->shares != 0 && bestLimit->totalVolume != 0)
    {
        int shares_matched = std::min(newOrder->shares, bestLimit->headerOrder->shares);

        // write to log
        write_to_file(newOrder, bestLimit->headerOrder);

        newOrder->shares -= shares_matched;
        bestLimit->headerOrder->shares -= shares_matched;

        if (bestLimit->headerOrder->shares == 0)
        {
            Order *old_node = bestLimit->headerOrder;

            bestLimit->size--;
            bestLimit->headerOrder = old_node->nextOrder;
            if (bestLimit->headerOrder != nullptr)
                bestLimit->headerOrder->prevOrder = nullptr;

            // remove old headerOrder;
            // remove old_node
        }
    }

    // freeing  memory
    if (code == 3)
    {
    }
    else if (code == 2)
    {
    }
    else
    {
    }

    return code;
}
