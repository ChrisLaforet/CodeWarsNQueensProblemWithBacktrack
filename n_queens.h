//
// Created by Chris on 8/9/2021.
//

#ifndef CODEWARSNQUEENSPROBLEM_N_QUEENS_H
#define CODEWARSNQUEENSPROBLEM_N_QUEENS_H


#include <string>
#include <cstring>
#include <list>

inline int calculateForwardCode(int column, int row) {
    return column + row;
}

inline int calculateBackwardCode(int column, int row, int squaresPerSide) {
    return row - column + (squaresPerSide - 1);
}

class boardSquare {
    int column;
    int row;
    int squaresPerSide;
    int forwardCode;
    int backwardCode;

public:
    boardSquare(int column, int row, int squaresPerSide) {
        this->column = column;
        this->row = row;
        this->squaresPerSide = squaresPerSide;
        this->forwardCode = calculateForwardCode(column, row);
        this->backwardCode = calculateBackwardCode(column, row, squaresPerSide);
    }

    void setValues(int column, int row) {
        this->column = column;
        this->row = row;
        this->forwardCode = calculateForwardCode(column, row);
        this->backwardCode = calculateBackwardCode(column, row, squaresPerSide);
    }

    int getColumn() const {
        return column;
    }

    int getRow() const {
        return row;
    }

    int getForwardCode() const {
        return forwardCode;
    }

    int getBackwardCode() const {
        return backwardCode;
    }
};

class solveColumnData {
    int squaresPerSide;
    int columnOffset;
    int column;
    int row = 0;
    boardSquare *queenSquare = nullptr;
    bool queenSquarePushed = false;

public:
    solveColumnData(int columnOffset, int column, int squaresPerSide) {
        this->columnOffset = columnOffset;
        this->column = column;
        this->squaresPerSide = squaresPerSide;
        this->queenSquare = new boardSquare(0, 0, squaresPerSide);
    }

    ~solveColumnData() {
        delete queenSquare;
    }

    void setQueenSquare() {
        queenSquare->setValues(column, row);
    }

    boardSquare *getQueenSquare() {
        return queenSquare;
    }

    void releaseQueenSquare() {
        queenSquare = new boardSquare(0, 0, squaresPerSide);
    }

    bool isQueenSquarePushed() const {
        return queenSquarePushed;
    }

    void setQueenSquarePushed(bool isPushed) {
        queenSquarePushed = isPushed;
    }

    int getColumnOffset() const {
        return columnOffset;
    }

    int getColumn() const {
        return column;
    }

    int getRow() const {
        return row;
    }

    bool isNextRowAvailable() {
        return row < (squaresPerSide - 1);
    }

    bool nextRow() {
        if (!isNextRowAvailable()) {
            return false;
        }
        ++row;
        return true;
    }
};

inline bool checkSquareIsAvailable(const std::list<boardSquare *>& queenSquares, int boardColumn, int boardRow, int squaresPerSide) {
    int forwardCode = calculateForwardCode(boardColumn, boardRow);
    int backwardCode = calculateBackwardCode(boardColumn, boardRow, squaresPerSide);
    for (auto &queenSquare : queenSquares)
    {
        if (queenSquare->getRow() == boardRow ||
                queenSquare->getForwardCode() == forwardCode ||
                queenSquare->getBackwardCode() == backwardCode) {
            return false;
        }
    }
    return true;
}

std::string createPrintableRepresentationOfBoard(int squaresPerSide, const std::list<boardSquare *>& queenSquares) {
    std::string result;
    for (int row = 0; row < squaresPerSide; row++) {
        for (int column = 0; column < squaresPerSide; column++) {
            bool found = false;
            for (auto &queenSquare : queenSquares) {
                if (queenSquare->getRow() == row && queenSquare->getColumn() == column) {
                    found = true;
                }
            }
            result += found ? "Q" : ".";
        }
        result += "\n";
    }
    return result;
}

bool solveColumn(int squaresPerSide, std::list<boardSquare *>& queenSquares,
                 const int *openColumns, int openColumnCount) {
    std::list<solveColumnData *> solveStack;
    auto *columnData = new solveColumnData(0, openColumns[0], squaresPerSide);
    solveStack.push_front(columnData);

    bool isSuccess = false;
    do {
        do {
            if (checkSquareIsAvailable(queenSquares, columnData->getColumn(), columnData->getRow(), squaresPerSide)) {
                int nextColumnOffset = columnData->getColumnOffset() + 1;

                columnData->setQueenSquare();
                if (!columnData->isQueenSquarePushed()) {
                    queenSquares.push_back(columnData->getQueenSquare());
                    columnData->setQueenSquarePushed(true);
                }
                if (nextColumnOffset >= openColumnCount) {
                    isSuccess = true;
                    break;
                }
                columnData = new solveColumnData(nextColumnOffset, openColumns[nextColumnOffset], squaresPerSide);
                solveStack.push_front(columnData);
            } else if (!columnData->nextRow()) {
                break;
            }
        } while (true);

        if (!isSuccess) {
            do {
                if (columnData->isQueenSquarePushed()) {
                    queenSquares.pop_back();
                }
                delete columnData;
                columnData = nullptr;

                solveStack.pop_front();

                if (solveStack.empty()) {
                    break;
                }
                columnData = solveStack.front();

                if (columnData->nextRow()) {
                    break;
                }
            } while (true);
        } else {
            columnData->releaseQueenSquare();
            columnData->setQueenSquarePushed(false);
            break;
        }
    } while (!solveStack.empty());

    while (!solveStack.empty()) {
        columnData = solveStack.front();
        solveStack.pop_front();
        if (columnData->isQueenSquarePushed()) {
            columnData->releaseQueenSquare();
        }
        delete columnData;
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

    std::list<boardSquare *> queenSquares;
    queenSquares.push_front(new boardSquare(mandatoryQueenCoordinates.first, mandatoryQueenCoordinates.second, n));

    std::list<int> columnCollector;
    for (int column = 0; column < n; column++) {
        if (column != mandatoryQueenCoordinates.first) {
            columnCollector.push_back(column);
        }
    }

    int *openColumns = new int[columnCollector.size()];
    int offset = 0;
    for (int const &column : columnCollector) {
        openColumns[offset++] = column;
    }

    std::string *returnValue;
    if (solveColumn(n, queenSquares, openColumns, columnCollector.size())) {
        std::string solution = createPrintableRepresentationOfBoard(n, queenSquares);
        returnValue = new std::string(solution);
    } else {
        returnValue = new std::string("");
    }
    for (const auto node: queenSquares)
        delete node;
    queenSquares.clear();

    delete [] openColumns;
    return *returnValue;
}

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
