#include "n_queens.h"


std::string hello() {
    return "Hello, World!";
}

n_queens *createNQueens(int squaredPerSide) {
    if (squaredPerSide >= 4)
        return new n_queens(squaredPerSide);
    return nullptr;
}