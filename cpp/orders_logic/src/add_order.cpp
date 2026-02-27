#include "../include/add_order.h"
#include "../include/matching_orders.h"
#include "../../tree_logic/include/auto_balancing_tree.h"
#include "../../tree_logic/include/add_node.h"

int add_order(Order *newOrder, Book *limitOrderedBook)
{
    // buy order
    if (newOrder->buyOrSell)
    {
        Limit *potential_best_buy = place_order_to_tree(newOrder, limitOrderedBook->buyTree);
    }
    // sell order
    else
    {
        Limit *potential_best_sell = place_order_to_tree(newOrder, limitOrderedBook->buyTree);
    }
}

Limit *place_order_to_tree(Order *newOrder, Limit *tree)
{

    auto node = find_place_to_insert_new_node(newOrder, tree);
    Limit *potential_best = nullptr;

    if (node.first == nullptr && node.second == nullptr)
        potential_best = create_root(newOrder, tree);

    else if (node.second == nullptr)
        potential_best = find_place_for_node(newOrder, node.first);
    else
    {
        add_to_node(newOrder, node.second);
        potential_best = node.second;
    }

    return potential_best;
}