#include "../include/B_tree.h"
#include <algorithm>
#include <cstdint>
#include <memory>

/**
 * @file B_tree.cpp
 * @brief Implementation of the B_tree class methods.
 * 
 * This file contains the implementation of the sorting, searching, and data addition
 * methods for the B-tree used in the limit order book.
 */

namespace B_TREE {

/**
 * @brief Sorts the orders in a node by price level in ascending order.
 * 
 * Uses std::sort with a lambda comparator to sort orders based on price_level.
 * 
 * @param node The node whose data array needs to be sorted.
 */
void B_tree::sort_node(Node &node) {
    std::sort(node.data.begin(), node.data.end(),
              [](const Orders &lhs, const Orders &rhs) {
                  return lhs.price_level < rhs.price_level;
              });
}

/**
 * @brief Searches for an order with the specified price in the given node.
 * 
 * Iterates through the node's data array to find a matching price_level.
 * 
 * @param price The price level to search for.
 * @param node The node to search in.
 * @return The index of the order if found, -1 if not found.
 */
int32_t B_tree::find_value(const int32_t &price, Node &node) {
    for (int i = 0; i < node.max_node_size; i++)
        if (node.data[i].price_level == price)
            return i;

    return -1;
}

/**
 * @brief Adds a new order or updates an existing order with the given price and volume.
 * 
 * If an order with the same price exists, increments its volume.
 * Otherwise, adds a new order to the root node, sorts the node, and increments the node size.
 * 
 * Note: This implementation only adds to the root node and does not handle splitting or tree balancing.
 * 
 * @param price The price level of the order.
 * @param volume The volume to add.
 */
void B_tree::add_data(int32_t price, int32_t volume) {

    int32_t indx = this->find_value(price, *this->root);

    if (indx != -1)
        this->root->data[indx].volume += volume;
    else {
        this->root->data[this->root->node_size] = {price, volume,
                                                   std::make_unique<Node>()};

        this->sort_node(*this->root);
    }

    this->root->node_size++;
}
} // namespace B_TREE