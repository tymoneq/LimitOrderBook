#include "../include/auto_balancing_tree.h"
#include <math.h>

/**
 * The function `calculate_balances` iterates through a tree structure, updating balances and
 * performing rotations if necessary to maintain balance factors within a specified range.
 *
 * @param node The `node` parameter in the `calculate_balances` function seems to be a pointer to a
 * structure or class named `Limit`. This function is likely part of a tree data structure
 * implementation, possibly an AVL tree or a similar self-balancing binary search tree.
 */
void calculate_balances(Limit *node)
{

    while (node != nullptr)
    {
        get_balance(node);

        if (std::abs(node->balance) > 1)
        {

            // left rotation
            if (node->balance > 1 && (node->leftChild != nullptr && (node->leftChild->balance == 0 || node->leftChild->balance == 1)))
                left_rotation(node);

            else if (node->balance < -1 && (node->rightChild != nullptr && (node->rightChild->balance == 0 || node->rightChild->balance == -1)))
                right_rotation(node);

            else if (node->balance > 1 && (node->leftChild != nullptr && node->leftChild->balance == -1))
                right_left_rotation(node);
            else if (node->balance < -1 && (node->rightChild != nullptr && node->rightChild->balance == 1))
                left_right_rotation(node);
        }
        node = node->parent;
    }
}

/**
 * The function calculates the balance factor of a node in a binary tree based on its left and right
 * children.
 *
 * @param node The `node` parameter in the `get_balance` function is a pointer to a `Limit` struct.
 * This struct likely represents a node in a binary tree data structure, as it contains pointers to
 * left and right child nodes, as well as a `balance` field.
 */
void get_balance(Limit *node)
{
    if (node == nullptr)
        return;
    int balance = 0;
    int height = 0;
    if (node->leftChild == nullptr)
    {
        balance = 0;
        height = 0;
    }
    else
        balance = height = node->leftChild->height;

    if (node->rightChild == nullptr)
        height = std::max(height, 0);
    else
    {
        balance -= node->rightChild->height;
        height = std::max(height, node->rightChild->height);
    }
    node->height = height + 1;

    node->balance = balance;
}

/**
 * The function performs a left rotation operation on a binary tree node.
 *
 * @param node The `left_rotation` function you provided performs a left rotation operation on a binary
 * tree node.
 */
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

    get_balance(node);
    get_balance(new_root);
}

/**
 * The above function performs a right rotation operation on a binary tree node.
 *
 * @param node The `right_rotation` function performs a right rotation operation on a binary tree node.
 * The `node` parameter represents the node around which the rotation is performed. During the
 * rotation, the right child of the `node` becomes the new root of the subtree, and the `node` becomes
 * the left
 */
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

    get_balance(node);
    get_balance(new_root);
}

void left_right_rotation(Limit *node)
{
    left_rotation(node->rightChild);
    right_rotation(node);
}
void right_left_rotation(Limit *node)
{
    right_rotation(node->leftChild);
    left_rotation(node);
}
