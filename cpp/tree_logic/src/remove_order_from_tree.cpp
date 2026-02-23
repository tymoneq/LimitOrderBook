#include "../include/remove_order_from_tree.h"
#include "../include/init_and_free.h"
#include "../include/auto_balancing_tree.h"


Limit *find_new_node(Limit *node)
{
    // go left
    if (node->leftChild != nullptr)
    {
        Limit *new_node = node->leftChild;
        while (new_node->rightChild != nullptr)
            new_node = new_node->rightChild;

        return new_node;
    }
    else if (node->rightChild != nullptr)
    {
        Limit *new_node = node->rightChild;
        while (new_node->leftChild != nullptr)
            new_node = new_node->leftChild;

        return new_node;
    }
    else
        return nullptr;
}

void move_tree_pointers(Limit *node, Limit *new_node)
{
    new_node->leftChild = node->leftChild;
    new_node->rightChild = node->rightChild;

    if (node->leftChild != nullptr)
        node->leftChild->parent = new_node;

    if (node->rightChild != nullptr)
        node->rightChild->parent = new_node;

    free_tree_node(node);
}

void remove_node(Limit *node, Book *limitOrderBook)
{

    Limit *new_node = find_new_node(node);
    Limit *parent_node = node->parent;

    if (parent_node != nullptr)
    {
        if (parent_node->limitPrice < new_node->limitPrice)
            parent_node->rightChild = new_node;
        else
            parent_node->leftChild = new_node;
    }
    // changing root
    else if (parent_node == nullptr)
    {
        if (node == limitOrderBook->buyTree)
            limitOrderBook->buyTree = new_node;
        else
            limitOrderBook->sellTree = new_node;
    }

    // leaf
    if (new_node == nullptr)
    {
        free_tree_node(node);
        rotate(new_node);
        return;
    }

    Limit *prev_parent = new_node->parent;
    new_node->parent = parent_node;

    if (prev_parent == node)
    {
        move_tree_pointers(node, new_node);
        return;
    }

    if (prev_parent->leftChild == new_node)
        prev_parent->leftChild = nullptr;
    else
        prev_parent->rightChild = nullptr;

    // changing left / right son of new node
    if (new_node->leftChild != nullptr)
    {
        prev_parent->leftChild = new_node->leftChild;
        new_node->leftChild->parent = prev_parent;
    }
    else if (new_node->rightChild != nullptr)
    {
        prev_parent->rightChild = new_node->rightChild;
        new_node->rightChild->parent = prev_parent;
    }

    move_tree_pointers(node, new_node);

    std::cout << "DEBUGGING\n";
    std::cout << &prev_parent << " " << prev_parent->limitPrice << "\n";

    rotate(prev_parent);
}
