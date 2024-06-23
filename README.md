# Payment Processor

## Description
A simple payment processor in `C++` that handles user accounts and transactions. The system is designed with thread safety in mind, making it suitable for a multi-threaded environment.

## Build
1. Ensure you have `g++` and `make` installed.
2. Clone the repository.
3. Navigate to the project root directory via CLI.
4. Run:<br>
```sh
make clean && make && make run
```

## Test
1. Ensure you have `cmake` installed.
2. Ensure you have no `build` dir at the project root dir. Either remove it or run `make clean` first.
3. Ensure you're pointing to the <root-dir> in CLI.
4. Run:<br>
```sh
mkdir build && cd build
```

5. Run:<br>
```sh
cmake .. && cmake --build . && ctest --output-on-failure
```

## Usage
The program creates accounts, processes transactions, and displays account balances.

## License
This project is licensed under the `MIT` License && `WTFPL` as dual licensed!
Enjoy..
Drink Water, Get hydrated

## TODOS
- Use Mocks for testing without deps.
- Use in-memory data structures to store transactions.

### Disclaimer
Built & Tested on `Linux/Ubuntu 22.04.4 LTS 64-bit` and `GNOME Version 42.9`.
