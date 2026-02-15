#include "../include/init_and_free.h"

/**
 * The function initializes a limit order book structure by setting its pointers to null.
 *
 * @param limitOrderBook The `limitOrderBook` parameter is a pointer to a `Book` struct, which likely
 * represents a limit order book used in trading systems. The function `init_book` initializes this
 * limit order book by setting its `highestBuy` and `lowestSell` pointers to `nullptr`, as well as
 *
 * @return The function `init_book` is returning an integer value. If the `limitOrderBook` pointer is
 * `nullptr`, the function returns -1. Otherwise, it initializes the fields of the `limitOrderBook`
 * struct and returns 0.
 */
int init_book(Book *limitOrderBook)
{
    if (!limitOrderBook)
        return -1;

    limitOrderBook->buyTree = new Limit;
    limitOrderBook->sellTree = new Limit;
    limitOrderBook->lowestSell = nullptr;
    limitOrderBook->highestBuy = nullptr;

    return 0;
}

int free_memory(Book *limitOrderBook)
{
    limitOrderBook->highestBuy = nullptr;
    limitOrderBook->lowestSell = nullptr;

    free_tree(limitOrderBook->buyTree);
    free_tree(limitOrderBook->sellTree);

    delete limitOrderBook;

    return 0;
}

void free_tree(Limit *node)
{

    if (node == nullptr)
        return;

    if (node->leftChild != nullptr)
        free_tree(node->leftChild);
    if (node->rightChild != nullptr)
        free_tree(node->rightChild);

    free_tree_node(node);
}

void free_tree_node(Limit *node)
{
    node->parent = nullptr;
    node->leftChild = nullptr;
    node->rightChild = nullptr;

    if (node->headerOrder != nullptr)
        free_list(node->headerOrder);

    node->headerOrder = nullptr;
    node->tailOrder = nullptr;

    delete node;
}
void free_list(Order *order)
{

    if (order == nullptr)
        return;

    Order *next_order = order->nextOrder;

    delete order;

    if (next_order != nullptr)
        free_list(next_order);
}