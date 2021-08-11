#include "n_queens.h"


std::string hello() {
    return "Hello, World!";
}

n_queens *createNQueens(int squaredPerSide) {
    return new n_queens(squaredPerSide);
}