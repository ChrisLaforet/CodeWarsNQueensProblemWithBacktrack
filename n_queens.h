//
// Created by Chris on 8/9/2021.
//

#ifndef CODEWARSNQUEENSPROBLEM_N_QUEENS_H
#define CODEWARSNQUEENSPROBLEM_N_QUEENS_H


#include <string>
#include <cstring>
#include <list>

class square {
    int column;
    int row;

public:
    square(int column, int row) {
        this->column = column;
        this->row = row;
    }

    int getColumn() const {
        return column;
    }

    int getRow() const {
        return row;
    }
};

class board {
    int squaresPerSide = 0;
    bool** squares = nullptr;       // column dimensions containing row dimensions [column][row]
    square *fixedQueenLocation = nullptr;

    void prepareBoard(int squaresPerSide) {
        if (squaresPerSide < 4)
            throw std::exception();
//            throw std::exception("board size cannot be smaller than 4 per side");
        this->squaresPerSide = squaresPerSide;
        squares = new bool*[squaresPerSide];
        for (int column = 0; column < squaresPerSide; column++) {
            squares[column] = new bool[squaresPerSide];
            for (int row = 0; row < squaresPerSide; row++) {
                squares[column][row] = false;
            }
        }
    }

    void flipSquareAt(int column, int row, bool value) {
        if (column >= squaresPerSide || row >= squaresPerSide) {
            throw std::exception();
//            throw std::exception("out of range");
        }
        squares[column][row] = value;
    }

public:
    explicit board(int squaresPerSide) {
        prepareBoard(squaresPerSide);
    }

    explicit board(int squaresPerSide, square *fixedQueenLocation) {
        prepareBoard(squaresPerSide);
        if (fixedQueenLocation->getColumn() >= squaresPerSide ||
                fixedQueenLocation->getRow() >= squaresPerSide) {
            throw std::exception();
//            throw std::exception("fixed queen location is out of bounds of the board");
        }
        this->fixedQueenLocation = fixedQueenLocation;
        flipSquareAt(fixedQueenLocation->getColumn(), fixedQueenLocation->getRow(), true);
    }

    virtual ~board() {
    //    delete [] squares;

    //    delete fixedQueenLocation;
    }

    std::list<square *> findAllQueenSquares() {
        std::list<square *> queens;
        for (int column = 0; column < squaresPerSide; column++) {
            for (int row = 0; row < squaresPerSide; row++) {
                if (squares[column][row]) {
                    auto *queenSquare = new square(column, row);
                    queens.push_front(queenSquare);
                    break;
                }
            }
        }
        return queens;
    }

    int getSquaresPerSide() const {
        return squaresPerSide;
    }

    void setQueenAt(int column, int row) {
        flipSquareAt(column, row,true);
    }

    void removeQueenAt(int column, int row) {
        flipSquareAt(column, row,false);
    }

    bool isQueenAt(int column, int row) {
        return squares[column][row];
    }

    std::string getPrintableRepresentation() {
        std::string result;
        for (int row = 0; row < squaresPerSide; row++) {
            for (int column = 0; column < squaresPerSide; column++) {
                result += squares[column][row] ? "Q" : ".";
            }
            result += "\n";
        }
        return result;
    }

    int *getColumnsWithoutQueens(int &columnCount) {
        int columns = 0;
        for (int column = 0; column < squaresPerSide; column++) {
            bool foundQueen = false;
            for (int row = 0; row < squaresPerSide; row++) {
                if (isQueenAt(column, row)) {
                    foundQueen = true;
                    break;
                }
            }
            if (!foundQueen) {
                ++columns;
            }
        }
        columnCount = columns;
        int *openColumns = new int[columns];
        int offset = 0;
        for (int column = 0; column < squaresPerSide; column++) {
            bool foundQueen = false;
            for (int row = 0; row < squaresPerSide; row++) {
                if (isQueenAt(column, row)) {
                    foundQueen = true;
                    break;
                }
            }
            if (!foundQueen) {
                openColumns[offset++] = column;
            }
        }
//        for (int count = 0; count < columns; count++) {
//            std::cerr << "At " << count << " - " << openColumns[count] << std::endl;
//        }
        return openColumns;
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
        currentBoard = nullptr;
    }

    board& getBoard() {
        return *currentBoard;
    }
};

bool checkSquareIsAvailable(const std::list<square *>& queenSquares, int column, int row) {
    for (auto & queenSquare : queenSquares)
    {
        if (queenSquare->getRow() == row) {
            return false;
        }
        if ((queenSquare->getColumn() + row) == (column + queenSquare->getRow())) {
            return false;
        }
        if ((queenSquare->getColumn() - row) == (column - queenSquare->getRow())) {
            return false;
        }
    }
    return true;
}

bool solveColumn(board& board, std::list<square *>& queenSquares,
                 const int *columnNumbers, int columnCount, int columnOffset) {
    int column = columnNumbers[columnOffset];
    bool isSuccess = false;
    for (int row = 0; row < board.getSquaresPerSide(); row++) {
        if (!checkSquareIsAvailable(queenSquares, column, row)) {
            continue;
        }
        board.setQueenAt(column, row);
        if (columnOffset >= (columnCount - 1)) {
            isSuccess = true;
            break;
        }

        auto *newQueenSquare = new square(column, row);
        queenSquares.push_back(newQueenSquare);

        if (solveColumn(board, queenSquares, columnNumbers, columnCount, columnOffset + 1)) {
            isSuccess = true;
            break;
        }
        queenSquares.pop_back();
        delete newQueenSquare;

        board.removeQueenAt(column, row);
    }

    return isSuccess;
}

std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoordinates) {
    if (n == 1) {
        return "Q\n";
    }
    if (n < 4) {
        return "";
    }

    auto *fixedQueenPosition = new square(mandatoryQueenCoordinates.first, mandatoryQueenCoordinates.second);
    auto *queenSolver = new n_queens(n, fixedQueenPosition);

    auto board = queenSolver->getBoard();
    int columnCount = 0;
    auto columns = board.getColumnsWithoutQueens(columnCount);

    auto queenSquares = board.findAllQueenSquares();
    std::string *returnValue;
    if (solveColumn(board, queenSquares, columns, columnCount, 0)) {
        std::string solution = board.getPrintableRepresentation();
        returnValue = new std::string(solution);
    } else {
        returnValue = new std::string("");
    }
    delete columns;
    for (const auto node: queenSquares)
        delete node;
    queenSquares.clear();

    delete queenSolver;
    //queenSolver = nullptr;
    return *returnValue;
}

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
