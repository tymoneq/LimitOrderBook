#pragma once
#include <array>
#include <cstdint>
#include <memory.h>
#include <memory>

/**
 * @file B_tree.h
 * @brief Header file for a simple B-tree implementation used in a Limit Order Book.
 * 
 * This file defines the structures and classes for a basic B-tree data structure
 * designed to manage orders in a limit order book. It includes nodes containing
 * orders sorted by price level.
 */

/**
 * @namespace B_TREE
 * @brief Namespace containing B-tree related classes and structures.
 */
namespace B_TREE {

constexpr int32_t INF = 1e9 + 7;

/**
 * @struct Orders
 * @brief Represents a single order in the limit order book.
 * 
 * Each order has a price level, volume, and a pointer to a leaf node
 * for further hierarchical organization.
 */
struct Node;

struct Orders {
    int32_t price_level = INF; ///< The price level of the order
    int32_t volume;            ///< The volume or quantity of the order
    std::unique_ptr<Node> leaf; ///< Pointer to the leaf node (for tree structure)
};

/**
 * @struct Node
 * @brief Represents a node in the B-tree.
 * 
 * A node contains an array of orders and maintains the node's size and parent reference.
 */
struct Node {
    static const int32_t max_node_size = 8; ///< Maximum number of orders per node
    int32_t node_size = 0;                  ///< Current number of orders in the node
    Node *parent = nullptr;                 ///< Pointer to the parent node
    std::array<Orders, max_node_size + 1> data; ///< Array of orders (plus one for extra leaf)
};

/**
 * @class B_tree
 * @brief A simple B-tree implementation for managing limit orders.
 * 
 * This class provides basic operations to add orders to the tree,
 * maintaining them sorted by price level.
 */
class B_tree {

  private:
    /**
     * @brief Sorts the orders in a node by price level.
     * @param node The node to sort.
     */
    void sort_node(Node &node);
    
    /**
     * @brief Finds the index of an order with the given price in a node.
     * @param price The price level to search for.
     * @param node The node to search in.
     * @return The index of the order if found, -1 otherwise.
     */
    int32_t find_value(const int32_t &price, Node &node);

  public:
    std::unique_ptr<Node> root = std::make_unique<Node>(); ///< The root node of the B-tree
    
    /**
     * @brief Adds a new order or updates an existing one with the given price and volume.
     * @param price The price level of the order.
     * @param volume The volume to add to the order.
     */
    void add_data(int32_t price, int32_t volume);
};
} // namespace B_TREE