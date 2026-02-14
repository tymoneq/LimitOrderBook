#include "../include/dataStructures.h"
#include "../include/writing_orders_to_file.h"
#include <fstream>

void write_to_file(Order *order1, Order *order2)
{
    std::ofstream file("transaction_logs.txt");
    time_t current_time = time(0);

    file << "Orders completed at " << current_time << "\n";
    file << "Orders ID1 : " << order1->idNumber << " ID2 : " << order2->idNumber << "\n";
    file << "Bid price : " << std::max(order1->limit, order2->limit) << "\n";
    file << "Ask price : " << std::min(order1->limit, order2->limit) << "\n";
    file << "Volume : " << std::min(order1->shares, order2->shares) << "\n";
}