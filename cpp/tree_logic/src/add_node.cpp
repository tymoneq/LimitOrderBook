#include "../include/add_node.h"

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

Limit *find_place_for_node(Order *newOrder, Limit *parent_node)
{
    if (newOrder->limit < parent_node->limitPrice)
        return add_new_node(newOrder, parent_node, false);
    else
        return add_new_node(newOrder, parent_node, true);
}

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
Limit *add_to_node(Order *newOrder, Limit *tree);