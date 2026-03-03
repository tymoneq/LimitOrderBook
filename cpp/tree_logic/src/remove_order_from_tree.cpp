#include "../include/remove_order_from_tree.h"
#include "../../init_and_free/include/init_and_free.h"

void remove_node(Limit *node, Book *limitOrderBook)
{

    Limit *new_node_in_this_position = find_new_node(node);

    // delete node because it is a leaf
    if (new_node_in_this_position == nullptr)
    {
        // setting tree pointers for nullptr
        if (limitOrderBook->buyTree == node)
            limitOrderBook->buyTree = nullptr;
        else if (limitOrderBook->sellTree == node)
            limitOrderBook->sellTree = nullptr;
    }
    else if (limitOrderBook->buyTree == node)
    {
        move_tree_pointers(node, new_node_in_this_position);
        limitOrderBook->buyTree = new_node_in_this_position;
    }
    else if (limitOrderBook->sellTree == node)
    {
        move_tree_pointers(node, new_node_in_this_position);
        limitOrderBook->sellTree = new_node_in_this_position;
    }
    else
        move_tree_pointers(node, new_node_in_this_position);

    free_tree_node(node);
    return;
};

Limit *find_new_node(Limit *node)
{
    Limit *new_node = nullptr;
    if (node->leftChild != nullptr)
    {
        new_node = node->leftChild;
        while (new_node != nullptr)
            new_node = new_node->rightChild;
    }

    else if (node->rightChild != nullptr)
    {
        new_node = node->rightChild;
        while (new_node != nullptr)
            new_node = new_node->leftChild;
    }

    return new_node;
}

void move_tree_pointers(Limit *node, Limit *new_node)
{
    // moving son of new node
    move_son_pointers(node, new_node);
    move_new_node_to_node(node, new_node);
}

void move_son_pointers(Limit *node, Limit *new_node)
{
    if (new_node->parent != node)
    {
        Limit *new_node_parent = new_node->parent;

        if (new_node_parent->rightChild == new_node)
        {
            new_node_parent->rightChild = new_node->leftChild;
            if (new_node->leftChild != nullptr)
                new_node->leftChild = new_node_parent;
        }

        else if (new_node_parent->leftChild == new_node)
        {
            new_node_parent->leftChild = new_node->rightChild;
            if (new_node->rightChild != nullptr)
                new_node->rightChild = new_node_parent;
        }
    }
}

void move_new_node_to_node(Limit *node, Limit *new_node)
{

    new_node->parent = node->parent;
    new_node->leftChild = node->leftChild;
    new_node->rightChild = node->rightChild;

    if (node->rightChild != nullptr)
        node->rightChild->parent = new_node;

    if (node->leftChild != nullptr)
        node->leftChild->parent = new_node;
}
