#include "../include/matching_orders.h"
#include "../include/writing_orders_to_file.h"
#include "../include/remove_order_from_tree.h"
#include <math.h>
/**
 * The function `find_matching_orders` checks if a new order matches the best limit order and fills the
 * order if conditions are met.
 *
 * @param newOrder `newOrder` is a pointer to an `Order` struct, which likely contains information
 * about a new order being processed in a trading system.
 * @param bestLimit `bestLimit` is a pointer to a `Limit` struct that contains information about the
 * best limit price for an order.
 *
 * @return The function `find_matching_orders` returns an integer value. If the condition `bestLimit ==
 * nullptr` is true, it returns 1. If the new order matches the best limit price based on the buyOrSell
 * condition, it fills the order and returns 1 if there are still shares left in the new order;
 * otherwise, it returns 0.
 */
int find_matching_orders(Order *newOrder, Limit *bestLimit, Book *limitOrderBook)
{

    if (bestLimit == nullptr)
        return 1;

    if (newOrder->buyOrSell && newOrder->limit >= bestLimit->limitPrice)
        fill_order(newOrder, bestLimit, limitOrderBook);

    if (!newOrder->buyOrSell && newOrder->limit <= bestLimit->limitPrice)
        fill_order(newOrder, bestLimit, limitOrderBook);

    if (newOrder->shares > 0)
        return 1;
    return 0;
}

/**
 * The function `fill_order` processes a new order by matching it with the best available limit order
 * and updating the order details accordingly.
 *
 * @param newOrder The `newOrder` parameter is a pointer to an `Order` object representing a new order
 * that needs to be filled.
 * @param bestLimit BestLimit is a pointer to a Limit struct that contains information about the best
 * limit order in the order book, including the total volume available at that limit and a linked list
 * of orders at that limit.
 */
void fill_order(Order *newOrder, Limit *bestLimit, Book *limitOrderBook)
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
        if (limitOrderBook->highestBuy == bestLimit)
            limitOrderBook->highestBuy = nullptr;
        else
            limitOrderBook->lowestSell = nullptr;
        remove_node(bestLimit, limitOrderBook);
    }
}
