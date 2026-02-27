# LimitOrderBook

This repository contains a C++ implementation of a limit order book used for matching buy and sell orders in a trading system. The project is structured with modular components handling initialization, tree logic, order processing, and logging.

## Project Structure

```
LimitOrderBook/
├── cpp/                  # C++ source code and build configuration
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── include/          # Public headers
│   ├── init_and_free/    # Initialization and cleanup logic
│   ├── logging/          # Order logging utilities
│   ├── orders_logic/     # Order matching and processing
│   ├── tree_logic/       # Binary search tree implementation for limits
│   └── tests/            # (Optional) unit tests
├── backend/              # (Older or alternate codebase)
└── README.md             # This file
```

## Building

The primary build system uses CMake. Ensure you have a compatible C++ compiler and CMake installed.

```bash
cd cpp
mkdir -p build && cd build
cmake ..
cmake --build .
```

This produces an executable named `app` in the `cpp/build` directory.

## Running

From the `cpp/build` directory run:

```bash
./app
```

The example `main.cpp` populates the book with random orders and prints some information. Adjust or extend for further experimentation.

## Development

- **Initialization**: `init_and_free/src/init_and_free.cpp` contains `init_book` and cleanup functions.
- **Order Logic**: `orders_logic` handles adding and matching orders.
- **Tree Logic**: `tree_logic` implements a self-balancing binary search tree of price limits.

Unit tests may be added under each `tests` subdirectory.

## Contributing

Feel free to submit enhancements or bug fixes. Follow standard C++ coding conventions and update documentation.

## License

MIT
