//
// Created by Chris on 8/9/2021.
//

#ifndef CODEWARSNQUEENSPROBLEM_N_QUEENS_H
#define CODEWARSNQUEENSPROBLEM_N_QUEENS_H


#include <string>

class square {
    int x;
    int y;

public:
    square(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class board {
    int squaresPerSide;
    bool** squares;
    square *fixedQueenLocation;

    void prepareBoard(int squaresPerSide) {
        if (squaresPerSide < 4)
            throw std::exception("board size cannot be smaller than 4 per side");
        this->squaresPerSide = squaresPerSide;
        squares = new bool*[squaresPerSide];
        for (int index = 0; index < squaresPerSide; index++) {
            squares[index] = new bool[squaresPerSide];
        }
    }

    void flipSquareAt(int x, int y, bool value) {
        if (x >= squaresPerSide || y >= squaresPerSide) {
            throw std::exception("out of range");
        }
        squares[y][x] = value;
    }

public:
    explicit board(int squaresPerSide) {
        prepareBoard(squaresPerSide);
    }

    explicit board(int squaresPerSide, square *fixedQueenLocation) {
        prepareBoard(squaresPerSide);
        if (fixedQueenLocation->getX() >= squaresPerSide ||
            fixedQueenLocation->getY() >= squaresPerSide) {
            throw std::exception("fixed queen location is out of bounds of the board");
        }
        this->fixedQueenLocation = fixedQueenLocation;
        flipSquareAt(fixedQueenLocation->getX(), fixedQueenLocation->getY(), true);
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

    std::string getPrintableRepresentation() {
        std::string result;
        for (int yIndex = 0; yIndex < squaresPerSide; yIndex++) {
            for (int xIndex = 0; xIndex < squaresPerSide; xIndex++) {
                result += squares[yIndex][xIndex] ? "Q" : ".";
            }
            result += "\n";
        }
        return result;
    }
};

class n_queens {
    board *currentBoard;

public:
    explicit n_queens(int squaresPerSide){
        this->currentBoard = new board(squaresPerSide);
    }
    
    explicit n_queens(int squaresPerSide, square *fixedQueenPosition)  {
        this->currentBoard = new board(squaresPerSide, fixedQueenPosition);
    }

    ~n_queens() {
        delete currentBoard;
    }

    board& getBoard() {
        return *currentBoard;
    }
};


n_queens *createNQueens(int squaresPerSide);

std::string hello();

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
