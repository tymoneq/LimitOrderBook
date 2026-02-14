#include "../include/adding_to_tree.h"
#include "../include/matching_orders.h"
#include "../include/auto_balancing_tree.h"

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
    // buyOrder
    if (newOrder->buyOrSell == true)
    {
        int code = find_matching_orders(newOrder, limitOrderedBook->lowestSell);

        if (code == 0)
            return 0;

        auto node = add_order_to_tree(newOrder, limitOrderedBook->buyTree);

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

        int code = find_matching_orders(newOrder, limitOrderedBook->highestBuy);

        if (code == 0)
            return 0;

        auto node = add_order_to_tree(newOrder, limitOrderedBook->sellTree);

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

/**
 * The function `add_order_to_tree` adds a new order to a binary search tree based on the order's limit
 * price.
 *
 * @param newOrder `newOrder` is a pointer to an `Order` struct, which likely contains information
 * about a new order to be added to a binary search tree.
 * @param tree The `tree` parameter in the provided code snippet seems to be a pointer to a `Limit`
 * structure, representing a binary search tree. The binary search tree is being traversed to find the
 * correct position to add a new order.
 */
Limit *add_order_to_tree(Order *newOrder, Limit *tree)
{

    if (tree->limitPrice == -1)
    {
        tree->limitPrice = newOrder->limit;
        tree->size = 1;
        tree->totalVolume = newOrder->shares;
        tree->headerOrder = newOrder;
        tree->tailOrder = newOrder;
        tree->headerOrder->parentLimit = tree;

        tree->parent = nullptr;
        tree->leftChild = nullptr;
        tree->rightChild = nullptr;
        return tree;
    }

    Limit *parent = nullptr;

    while (tree != nullptr && tree->limitPrice != newOrder->limit)
    {
        parent = tree;
        if (newOrder->limit < tree->limitPrice)
            tree = tree->leftChild;
        else
            tree = tree->rightChild;
    }

    if (tree == nullptr)
    {
        tree = add_tree_node(newOrder, parent);

        if (parent != nullptr && parent->limitPrice < tree->limitPrice)
            parent->rightChild = tree;
        else
            parent->leftChild = tree;
    }
    else
        add_order_to_list(newOrder, tree);

    // calculate balance
    calculate_balances(tree);

    return tree;
}
/**
 * The function `add_order_to_list` adds a new order to a linked list within a binary search tree node.
 *
 * @param newOrder A pointer to a struct representing a new order to be added to the list.
 * @param treeNode The `treeNode` parameter seems to be a pointer to a `Limit` struct. This struct
 * likely represents a node in a tree data structure, possibly a binary search tree used for order book
 * management in a financial system. The `Limit` struct probably contains information about the limit
 * price and other relevant
 */
int add_order_to_list(Order *newOrder, Limit *treeNode)
{
    // to del after writing tree balancing
    if (treeNode->size == 0)
    {

        treeNode->size = 1;
        treeNode->totalVolume = newOrder->shares;
        treeNode->tailOrder = newOrder;
        newOrder->prevOrder = nullptr;
        newOrder->parentLimit = treeNode;
        treeNode->headerOrder = newOrder;
        newOrder->prevOrder = nullptr;

        return 0;
    }

    treeNode->size++;
    treeNode->totalVolume += newOrder->shares;
    treeNode->tailOrder->nextOrder = newOrder;
    newOrder->prevOrder = treeNode->tailOrder;
    newOrder->parentLimit = treeNode;
    treeNode->tailOrder = newOrder;

    return 0;
}

/**
 * The function `add_tree_node` initializes a new tree node with the provided order information and
 * links it to the parent node.
 *
 * @param newOrder `newOrder` is a pointer to an `Order` struct which contains information about a new
 * order to be added to a tree node.
 * @param treeNode `treeNode` is a pointer to a `Limit` struct, which represents a node in a tree data
 * structure used for storing order limits.
 * @param parent The `parent` parameter in the `add_tree_node` function represents the parent node of
 * the current node being added to the tree. It is a pointer to a `Limit` structure that points to the
 * parent node in the binary tree structure.
 *
 * @return The function `add_tree_node` is returning an integer value of 0.
 */
Limit *add_tree_node(Order *newOrder, Limit *parent)
{
    Limit *node = new Limit;

    node->limitPrice = newOrder->limit;
    node->size = 1;
    node->totalVolume = newOrder->shares;
    node->headerOrder = newOrder;
    node->tailOrder = newOrder;
    node->headerOrder->parentLimit = node;

    node->parent = parent;
    node->leftChild = nullptr;
    node->rightChild = nullptr;

    return node;
}
