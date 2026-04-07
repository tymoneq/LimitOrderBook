#include "../include/B_tree.h"
#include <catch2/catch_test_macros.hpp>
using namespace B_TREE;

/**
 * @file test.cpp
 * @brief Unit tests for the B_tree class using Catch2 framework.
 * 
 * This file contains test cases to verify the functionality of the B_tree implementation,
 * including initialization, adding new orders, and handling duplicate prices.
 */

TEST_CASE("B_tree test", "[B_tree]") {
    B_tree b_tree;

    SECTION("INIT") { 
        /// Test that the root node has no parent initially
        REQUIRE(b_tree.root->parent == nullptr); 
    }

    SECTION("Add new values to the tree") {
        /// Test adding two different price levels and verify sorting
        int32_t price1 = 5;
        int32_t volume = 5;
        b_tree.add_data(price1, volume);
        int32_t price = 3;
        b_tree.add_data(price, volume);
        REQUIRE(b_tree.root->data[0].price_level == price);
        REQUIRE(b_tree.root->data[1].price_level == price1);
    }

    SECTION("Add same value few times") {
        /// Test adding the same price multiple times, expecting volume accumulation
        int32_t price = 5;
        int32_t volume = 5;
        b_tree.add_data(price, volume);
        b_tree.add_data(price, volume);
        REQUIRE(b_tree.root->data[0].price_level == price);
        REQUIRE(b_tree.root->data[1].price_level == INF);  // Assuming INF is the default for unused slots
    }
}