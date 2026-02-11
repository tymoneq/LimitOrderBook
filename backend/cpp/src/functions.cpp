#include "../include/functions.h"
#include "../include/dataStructures.h"

#include <iostream>

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

    limitOrderBook->highestBuy = new Limit;
    limitOrderBook->lowestSell = new Limit;
    limitOrderBook->buyTree = new Limit;
    limitOrderBook->sellTree = new Limit;

    return 0;
}

int add_order(Order *newOrder, Book *limitOrderedBook)
{
    // buyOrder
    if (newOrder->buyOrSell == true)
        add_order_to_tree(newOrder, limitOrderedBook->buyTree);

    // sellOrder
    else
        add_order_to_tree(newOrder, limitOrderedBook->sellTree);

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
int add_order_to_tree(Order *newOrder, Limit *tree)
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
        return 0;
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

    return 0;
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

int free_memory(Book *limitOrderBook)
{

    return 0;
}