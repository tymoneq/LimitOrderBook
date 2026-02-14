#ifndef DATASTRUCTURES
#define DATASTRUCTURES
#include <ctime>

// The code snippet defines a struct named `Order` that represents an order in a trading system. Each `Order` object contains the following members:
struct Limit;

struct Order
{
    int idNumber;
    bool buyOrSell;
    int shares;
    int limit;
    time_t entryTime;
    time_t eventTime;
    Order *nextOrder = nullptr;
    Order *prevOrder = nullptr;
    Limit *parentLimit;
};

// The `struct Limit` defines a data structure that represents a limit order in a trading system. Each `Limit` object contains the following members:
struct Limit
{
    int balance = -1;
    int height = 0;
    int limitPrice = -1;
    int size = 0;
    int totalVolume = 0;
    Limit *parent = nullptr;
    Limit *leftChild = nullptr;
    Limit *rightChild = nullptr;
    Order *headerOrder = nullptr;
    Order *tailOrder = nullptr;
};

// The `struct Book` is defining a data structure that represents a book in a trading system. It contains pointers to different limits and orders within the book. Here's a breakdown of each member:
struct Book
{
    Limit *buyTree;
    Limit *sellTree;
    Limit *lowestSell;
    Limit *highestBuy;
};

#endif