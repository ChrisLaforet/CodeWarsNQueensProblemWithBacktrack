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

class square_weight {
    int x;
    int y;
    bool hasQueen = false;
    int weight = 0;

public:
    explicit square_weight(int x, int y, bool hasQueen) {
        this->x = x;
        this->y = y;
        this->hasQueen = hasQueen;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    bool isQueenSquare() {
        return hasQueen;
    }

    void addWeight() {
        ++weight;
    }

    int getWeight() {
        return weight;
    }
};

class board {
    int squaresPerSide = 0;
    bool** squares = nullptr;
    square *fixedQueenLocation = nullptr;

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

    bool leftPressureOn(int x, int y) {
        if (x <= 0 || x >= squaresPerSide)
            return false;
        for (int xIndex = x - 1; x >= 0; x--) {
            if (isQueenAt(xIndex, y)) {
                return true;
            }
        }
        return false;
    }

    bool rightPressureOn(int x, int y) {
        if (x < 0 || x >= (squaresPerSide - 1))
            return false;
        for (int xIndex = x + 1; x < squaresPerSide; x++) {
            if (isQueenAt(xIndex, y)) {
                return true;
            }
        }
        return false;
    }

    bool topLeftPressureOn(int x, int y) {
        if (x <= 0 || x >= squaresPerSide)
            return false;
        if (y <= 0 || y >= (squaresPerSide - 1))
            return false;
        for (int xIndex = x - 1, yIndex = y - 1; x >= 0, y >= 0; x--, y--) {
            if (isQueenAt(xIndex, yIndex)) {
                return true;
            }
        }
        return false;
    }

    bool bottomLeftPressureOn(int x, int y) {
        if (x <= 0 || x >= squaresPerSide)
            return false;
        if (y < 0 || y >= (squaresPerSide - 1))
            return false;
        for (int xIndex = x - 1, yIndex = y + 1; x >= 0, y < squaresPerSide; x--, y++) {
            if (isQueenAt(xIndex, yIndex)) {
                return true;
            }
        }
        return false;
    }

    bool topRightPressureOn(int x, int y) {
        if (x < 0 || x >= (squaresPerSide - 1))
            return false;
        if (y <= 0 || y >= (squaresPerSide - 1))
            return false;
        for (int xIndex = x + 1, yIndex = y + 1; x < squaresPerSide, y < squaresPerSide; x++, y++) {
            if (isQueenAt(xIndex, yIndex)) {
                return true;
            }
        }
        return false;
    }

    bool bottomRightPressureOn(int x, int y) {
        if (x < 0 || x >= (squaresPerSide - 1))
            return false;
        if (y < 0 || y >= (squaresPerSide - 1))
            return false;
        for (int xIndex = x + 1, yIndex = y + 1; x < squaresPerSide, y < squaresPerSide; x++, y++) {
            if (isQueenAt(xIndex, yIndex)) {
                return true;
            }
        }
        return false;
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

        delete fixedQueenLocation;
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

    bool isQueenAt(int x, int y) {
        return squares[y][x];
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

    square_weight **getWeights(int x) {
        square_weight **weights = new square_weight *[squaresPerSide];
        for (int yIndex = 0; yIndex < squaresPerSide; yIndex++) {
            weights[yIndex] = new square_weight(x, yIndex, isQueenAt(x, yIndex));
            if (leftPressureOn(x, yIndex)) {
                weights[yIndex]->addWeight();
            }
            if (rightPressureOn(x, yIndex)) {
                weights[yIndex]->addWeight();
            }
            if (topLeftPressureOn(x, yIndex)) {
                weights[yIndex]->addWeight();
            }
            if (bottomLeftPressureOn(x, yIndex)) {
                weights[yIndex]->addWeight();
            }
            if (topRightPressureOn(x, yIndex)) {
                weights[yIndex]->addWeight();
            }
            if (bottomRightPressureOn(x, yIndex)) {
                weights[yIndex]->addWeight();
            }
        }
        return weights;
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

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
