//
// Created by Chris on 8/9/2021.
//

#ifndef CODEWARSNQUEENSPROBLEM_N_QUEENS_H
#define CODEWARSNQUEENSPROBLEM_N_QUEENS_H


#include <string>

class board {
    int squaresPerSide;
    bool** squares;

    void flipSquareAt(int x, int y, bool value) {
        if (x >= squaresPerSide || y >= squaresPerSide) {
            throw std::exception("out of range");
        }
        squares[x][y] = value;
    }

public:
    explicit board(int squaresPerSide) {
        this->squaresPerSide = squaresPerSide;
        squares = new bool*[squaresPerSide];
        for (int index = 0; index < squaresPerSide; index++) {
            squares[index] = new bool[squaresPerSide];
        }
    }

    ~board() {
        for (int index = 0; index < squaresPerSide; index++) {
            delete [] squares[index];
        }
        delete [] squares;
    }

    int getSquaresPerSide() {
        return squaresPerSide;
    }

    void setQueenAt(int x, int y) {
        flipSquareAt(x, y, true);
    }

    void removeQueenAt(int x, int y) {
        flipSquareAt(x, y, false);
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

    board& getBoard() {
        return *currentBoard;
    }

    friend n_queens *createNQueens(int squaredPerSide);
};


n_queens *createNQueens(int squaredPerSide);

std::string hello();

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
