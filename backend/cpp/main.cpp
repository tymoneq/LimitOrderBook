#include "include/dataStructures.h"
#include "include/adding_to_tree.h"
#include "include/init_and_free.h"
#include "include/matching_orders.h"
#include <iostream>
#include <vector>

int main()
{
    Book *LimitOrderBook = new Book;

    init_book(LimitOrderBook);

    // sample input data
    const int N = 10000;

    for (int i = 0; i < N; i++)
    {
        Order *o1 = new Order{i, rand() % 2, rand() % 50 + 1, rand() % 100 + 10, 1, 1, nullptr, nullptr, nullptr};
        add_order(o1, LimitOrderBook);
    }

    std::cout << LimitOrderBook->highestBuy->limitPrice << "\n";
    std::cout << LimitOrderBook->highestBuy->size << "\n";
    std::cout << LimitOrderBook->lowestSell->limitPrice << "\n";
    std::cout << LimitOrderBook->lowestSell->size << "\n";

    free_memory(LimitOrderBook);

    return 0;
}