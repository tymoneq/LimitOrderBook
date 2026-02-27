#include "../include/add_order.h"
#include "../include/matching_orders.h"
#include "../../tree_logic/include/auto_balancing_tree.h"
#include "../../tree_logic/include/add_node.h"

/**
 * The function `add_order` adds a new order to a book's buy or sell tree based on the order type and
 * updates the highest buy or lowest sell order accordingly.
 *
 * @param newOrder The `newOrder` parameter is a pointer to an `Order` struct, which likely contains
 * information about a new order being added to a book.
 * @param limitOrderedBook The `limitOrderedBook` parameter seems to be a struct or class that contains
 * information about buy and sell orders for a particular book. It likely has attributes such as
 * `buyTree` and `sellTree` which are probably binary search trees storing buy and sell orders
 * respectively. The `highestBuy`
 *
 * @return The function `add_order` returns an integer value. If the function successfully adds the new
 * order to the appropriate tree (buyTree or sellTree) based on whether it is a buy order or a sell
 * order, and updates the highestBuy or lowestSell node accordingly, it returns 0. If there is an issue
 * adding the order to the tree or if the node is null, it returns
 */
int add_order(Order *newOrder, Book *limitOrderedBook)
{
    std::cout << "add_order\n";
    // buyOrder
    if (newOrder->buyOrSell == true)
    {
        int code = find_matching_orders(newOrder, limitOrderedBook->lowestSell, limitOrderedBook);
        std::cout << "found matching\n";

        if (code == 0)
            return 0;

        auto node = add_order_to_tree(newOrder, limitOrderedBook->buyTree);

        std::cout << "added to tree\n";

        if (limitOrderedBook->highestBuy == nullptr || (limitOrderedBook->highestBuy != nullptr && limitOrderedBook->highestBuy->limitPrice < newOrder->limit))
        {
            if (node == nullptr)
                return 1;

            limitOrderedBook->highestBuy = node;
        }

        while (limitOrderedBook->buyTree->parent != nullptr)
            limitOrderedBook->buyTree = limitOrderedBook->buyTree->parent;
    }
    // sellOrder
    else
    {

        int code = find_matching_orders(newOrder, limitOrderedBook->highestBuy, limitOrderedBook);
        std::cout << "found matching\n";
        if (code == 0)
            return 0;

        auto node = add_order_to_tree(newOrder, limitOrderedBook->sellTree);

        std::cout << "added to tree\n";

        if (limitOrderedBook->lowestSell == nullptr || (limitOrderedBook->lowestSell != nullptr && limitOrderedBook->lowestSell->limitPrice > newOrder->limit))
        {
            if (node == nullptr)
                return 1;

            limitOrderedBook->lowestSell = node;
        }

        while (limitOrderedBook->sellTree->parent != nullptr)
            limitOrderedBook->sellTree = limitOrderedBook->sellTree->parent;
    }
    return 0;
}

Limit *add_order_to_tree(Order *newOrder, Limit *tree)
{

    if (tree->limitPrice == -1)
        return create_root(newOrder, tree);

    Limit *parent_node = nullptr;
    auto v = find_place_to_insert_new_node(newOrder, tree);
    parent_node = v.first;
    tree = v.second;

    if (tree == nullptr)
        tree = find_place_for_node(newOrder, parent_node);

    // calculate balance
    std::cout << "before rotating\n";
    rotate(tree);

    std::cout << "After rotating\n";

    return tree;
}
