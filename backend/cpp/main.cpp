#include "include/dataStructures.h"
#include "include/functions.h"
#include <iostream>
#include <vector>

int main()
{
    Book *LimitOrderBook = new Book;

    int code = init_book(LimitOrderBook);

    // sample input data
    const int N = 20;

    for (int i = 0; i < N; i++)
    {
        std::cout << "i: " << i << "\n";
        Order *o1 = new Order{i, rand() % 2, rand() % 50, rand() % 100, 1, 1, nullptr, nullptr, nullptr};
        add_order(o1, LimitOrderBook);

        
    }

    return 0;
}