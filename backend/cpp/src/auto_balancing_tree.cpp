#include "../include/auto_balancing_tree.h"
#include <math.h>
#include <iostream>

void calculate_balances(Limit *node)
{

    while (node != nullptr)
    {
        int balance = 0;
        if (node->leftChild == nullptr)
            balance -= 1;
        else
            balance += node->leftChild->balance;

        if (node->rightChild == nullptr)
            balance += 1;
        else
            balance -= node->rightChild->balance;

        if (std::abs(balance) > 1)
        {

            std::cout << "Rotating\n";
            // left rotation
            if (balance > 1 && (node->leftChild != nullptr && (node->leftChild->balance == 0 || node->leftChild->balance == 1)))
                left_rotation(node);

            else if (balance < -1 && (node->rightChild != nullptr && (node->rightChild->balance == 0 || node->rightChild->balance == 1)))
                right_rotation(node);

            else
                node = node->parent;
        }
        else
        {
            node->balance = balance;
            node = node->parent;
        }
    }
}

void left_rotation(Limit *node)
{

    Limit *new_root = node->leftChild;

    new_root->parent = node->parent;

    if (node->parent != nullptr)
    {
        if (new_root->limitPrice < node->parent->limitPrice)
            node->parent->leftChild = new_root;
        else
            node->parent->rightChild = new_root;
    }

    node->leftChild = new_root->rightChild;
    if (new_root->rightChild != nullptr)
        new_root->rightChild->parent = node;

    node->parent = new_root;
    new_root->rightChild = node;
}

void right_rotation(Limit *node)
{

    Limit *new_root = node->rightChild;

    new_root->parent = node->parent;

    if (node->parent != nullptr)
    {
        if (new_root->limitPrice < node->parent->limitPrice)
            node->parent->leftChild = new_root;
        else
            node->parent->rightChild = new_root;
    }

    node->rightChild = new_root->leftChild;
    if (new_root->leftChild != nullptr)
        new_root->leftChild->parent = node;

    node->parent = new_root;
    new_root->leftChild = node;
}
