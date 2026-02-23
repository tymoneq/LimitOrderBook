#include "include/dataStructures.h"
#include "tree_logic/include/adding_to_tree.h"
#include "init_and_free/include/init_and_free.h"
#include <iostream>
#include <vector>

int main()
{
    Book *LimitOrderBook = new Book;

    init_book(LimitOrderBook);

    // sample input data
    const int N = 100;

    for (int i = 0; i < N; i++)
    {
        std::cout << i << "\n";
        Order *o1 = new Order{i, rand() % 2, 10 * i + (rand() % 50), rand() % 100 + 10, 1, 1, nullptr, nullptr, nullptr};
        add_order(o1, LimitOrderBook);
    }

    // Order *o1 = new Order{1, true, 1, 10, 1, 1, nullptr, nullptr, nullptr};
    // Order *o2 = new Order{2, true, 1, 12, 1, 1, nullptr, nullptr, nullptr};
    // Order *o3 = new Order{3, true, 1, 11, 1, 1, nullptr, nullptr, nullptr};

    // add_order(o1, LimitOrderBook);
    // add_order(o2, LimitOrderBook);
    // add_order(o3, LimitOrderBook);

    std::cout << LimitOrderBook->buyTree->limitPrice << "\n";

    free_memory(LimitOrderBook);

    return 0;
}