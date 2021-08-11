//
// Created by Chris on 8/9/2021.
//

#ifndef CODEWARSNQUEENSPROBLEM_N_QUEENS_H
#define CODEWARSNQUEENSPROBLEM_N_QUEENS_H


#include <string>

class board {
    int squares_per_side;
    bool** squares;

public:
    explicit board(int squares_per_side) {
        this->squares_per_side = squares_per_side;
        squares = new bool*[squares_per_side];
        for (int index = 0; index < squares_per_side; index++) {
            squares[index] = new bool[squares_per_side];
        }
    }

    ~board() {
        for (int index = 0; index < squares_per_side; index++) {
            delete [] squares[index];
        }
        delete [] squares;
    }
};

class n_queens {
    board *currentBoard;

    explicit n_queens(int squares_per_side){
        this->currentBoard = new board(squares_per_side);
    }

public:
    ~n_queens() {
        delete currentBoard;
    }
    friend n_queens *createNQueens(int squares_per_side);
};


n_queens *createNQueens(int squares_per_side);

std::string hello();

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
