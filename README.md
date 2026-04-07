# LimitOrderBook

This repository contains a simple C++ implementation of a B-tree data structure designed for a limit order book. The B-tree is used to manage orders sorted by price levels, allowing efficient insertion and lookup operations.

## Overview

The implementation includes:
- **B_tree class**: Manages the root node and provides methods to add orders.
- **Node struct**: Represents a node in the B-tree, containing an array of orders.
- **Orders struct**: Represents individual orders with price level, volume, and a leaf pointer.

This is a basic implementation that maintains orders in a single root node, sorted by price. It does not implement full B-tree balancing or splitting mechanisms.

## Project Structure

```
LimitOrderBook/
├── cpp/                  # C++ source code and build configuration
│   ├── CMakeLists.txt    # CMake build configuration
│   ├── main.cpp          # Main executable entry point
│   ├── include/          # Header files
│   │   └── B_tree.h      # B-tree class and struct definitions
│   ├── src/              # Source files
│   │   └── B_tree.cpp    # B-tree implementation
│   ├── tests/            # Unit tests
│   │   └── test.cpp      # Catch2 test cases
│   └── build/            # Build directory (generated)
├── LICENSE               # Project license
├── README.md             # This file
└── to_do.md              # Development notes
```

## Building

The project uses CMake for building. Ensure you have CMake and a C++ compiler installed.

```bash
cd cpp
mkdir -p build && cd build
cmake ..
cmake --build .
```

This produces executables in the `cpp/build` directory.

## Running

To run the main application:

```bash
cd cpp/build
./app
```

To run the tests:

```bash
cd cpp/build
./tests
```

## API Documentation

### B_tree Class

- `void add_data(int32_t price, int32_t volume)`: Adds a new order or updates an existing order with the given price and volume.

### Node Struct

- Contains an array of Orders, node size, and parent pointer.

### Orders Struct

- `int32_t price_level`: The price level of the order.
- `int32_t volume`: The volume of the order.
- `std::unique_ptr<Node> leaf`: Pointer to a leaf node.

## Development

The code is documented with Doxygen-style comments. Key methods include:
- `sort_node`: Sorts orders in a node by price.
- `find_value`: Searches for an order by price in a node.

Unit tests are provided using the Catch2 framework to verify basic functionality.

## Contributing

Contributions are welcome. Please ensure code is well-documented and tests are updated.

## License

MIT
