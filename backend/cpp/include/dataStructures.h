#ifndef DATASTRUCTURES
#define DATASTRUCTURES




// The code snippet defines a struct named `Order` that represents an order in a trading system. Each `Order` object contains the following members:
struct Order
{
    int idNumber;
    bool buyOrSell;
    int shares;
    int limit;
    int entryTime;
    int eventTime;
    Order *nextOrder;
    Order *prevOrder;
    Limit *parentLimit;
};


// The `struct Limit` defines a data structure that represents a limit order in a trading system. Each `Limit` object contains the following members:
struct Limit
{
    int limitPrice;
    int size;
    int totalVolume;
    Limit *parent;
    Limit *leftChild;
    Limit *rightChild;
    Order *headerOrder;
    Order *tailOrder;
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