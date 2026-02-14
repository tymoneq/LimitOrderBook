#ifndef BALANCING
#define BALANCING

#include "dataStructures.h"
void calculate_balances(Limit *node);
void get_balance(Limit *node);
void left_rotation(Limit *node);
void right_rotation(Limit *node);
void left_right_rotation(Limit *node);
void right_left_rotation(Limit *node);

#endif