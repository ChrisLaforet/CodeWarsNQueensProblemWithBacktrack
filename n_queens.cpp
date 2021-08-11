#include "n_queens.h"


std::string hello() {
    return "Hello, World!";
}

n_queens *createNQueens(int squares_per_side) {
    if (squares_per_side >= 4)
        return new n_queens(squares_per_side);
    return nullptr;
}