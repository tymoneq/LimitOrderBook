#include "../include/add_node.h"

/**
 * The function creates a root node in a binary tree data structure with specified attributes based on
 * a new order.
 * 
 * @param newOrder `newOrder` is a pointer to an `Order` object, which contains information about a new
 * order being created.
 * @param tree The `tree` parameter in the `create_root` function is a pointer to a `Limit` struct.
 * 
 * @return the updated Limit tree after setting the properties based on the newOrder provided as input.
 */
Limit *create_root(Order *newOrder, Limit *tree)
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
/**
 * The function `find_place_to_insert_new_node` searches for the appropriate place to insert a new node
 * in a binary search tree based on the limit price of the new order.
 * 
 * @param newOrder `newOrder` is a pointer to an `Order` object, which likely contains information
 * about a new order being inserted into a binary search tree.
 * @param tree The `tree` parameter in the `find_place_to_insert_new_node` function represents a binary
 * search tree where you want to insert a new node. The function traverses the tree to find the correct
 * place to insert the new node based on the `limitPrice` of the new order. The function
 * 
 * @return The function `find_place_to_insert_new_node` returns a `std::pair` containing two pointers
 * to `Limit` objects. The first pointer is the parent node where the new node should be inserted, and
 * the second pointer is the node where the new node should be inserted relative to the parent node.
 */

std::pair<Limit *, Limit *> find_place_to_insert_new_node(Order *newOrder, Limit *tree)
{

    Limit *parent_node = nullptr;

    while (tree != nullptr && tree->limitPrice != newOrder->limit)
    {

        parent_node = tree;
        if (newOrder->limit < tree->limitPrice)
            tree = tree->leftChild;
        else
            tree = tree->rightChild;
    }

    return std::make_pair(parent_node, tree);
}

/**
 * The function `find_place_for_node` determines where to place a new order within a binary tree based
 * on the order's limit price compared to the parent node's limit price.
 * 
 * @param newOrder The `newOrder` parameter is a pointer to an `Order` struct, which likely contains
 * information about a new order being processed in a system.
 * @param parent_node The `parent_node` parameter is a pointer to a `Limit` struct that represents a
 * node in a data structure. It contains information about a limit price.
 * 
 * @return The function `add_new_node` is being called with the parameters `newOrder`, `parent_node`,
 * and a boolean value based on the comparison of `newOrder->limit` and `parent_node->limitPrice`. The
 * return value of this function call is being returned by the `limit *find_place_for_node` function.
 */
Limit *find_place_for_node(Order *newOrder, Limit *parent_node)
{
    if (newOrder->limit < parent_node->limitPrice)
        return add_new_node(newOrder, parent_node, false);
    else
        return add_new_node(newOrder, parent_node, true);
}

/**
 * The function `add_new_node` creates a new node in a binary tree structure and assigns values based
 * on the input order and parent node.
 * 
 * @param newOrder The `newOrder` parameter is a pointer to an `Order` object, which likely contains
 * information about a new order being added to a data structure.
 * @param parent_node The `parent_node` parameter in the `add_new_node` function represents the parent
 * node to which the new node will be added as a child. It is a pointer to a `Limit` structure that
 * holds information about the parent node in a tree data structure.
 * @param rightSon The `rightSon` parameter in the `add_new_node` function is a boolean flag that
 * indicates whether the new node being added should be the right child of the parent node. If
 * `rightSon` is `true`, the new node will be set as the right child of the parent node;
 * 
 * @return The function `add_new_node` is returning a pointer to the newly created `Limit` node.
 */
Limit *add_new_node(Order *newOrder, Limit *parent_node, bool rightSon)
{
    Limit *new_node = new Limit;
    new_node->parent = parent_node;
    if (rightSon)
        parent_node->rightChild = new_node;
    else
        parent_node->leftChild = new_node;

    new_node->size = 1;
    new_node->limitPrice = newOrder->limit;
    new_node->totalVolume = newOrder->shares;

    new_node->headerOrder = newOrder;
    new_node->tailOrder = newOrder;

    return new_node;
}


/**
 * The function `add_to_node` adds a new order to a linked list data structure and updates relevant
 * attributes.
 * 
 * @param newOrder `newOrder` is a pointer to an `Order` struct, which represents a new order to be
 * added to a linked list.
 * @param tree The `tree` parameter is a pointer to a `Limit` struct.
 */
void add_to_node(Order *newOrder, Limit *tree)
{
    tree->size++;
    tree->totalVolume += newOrder->shares;
    tree->tailOrder->nextOrder = newOrder;
    newOrder->prevOrder = tree->tailOrder;
    newOrder->nextOrder = nullptr;
    tree->tailOrder = newOrder;
}