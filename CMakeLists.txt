cmake_minimum_required(VERSION 3.10)

project(Limit_Order_Book CXX)

set(INIT
    init/scr/init_and_free.cpp)
set(LOGGING
    logging/src/writing_orders_to_file.cpp)
set(ORDER_LOGIC

    orders_logic/src/matching_orders.cpp)
set(TREE_LOGIC
    tree_logic/src/adding_to_tree.cpp
    tree_logic/src/auto_balancing_tree.cpp
    tree_logic/src/remove_order_from_tree.cpp
)

add_executable(app main.cpp ${INIT} ${LOGGING} ${ORDER_LOGIC} ${TREE_LOGIC})
