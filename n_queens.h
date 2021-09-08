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

    void setValues(int column, int row) {
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

class solveColumnData {
    int squaresPerSide;
    int columnOffset;
    int column;
    int row = 0;
    square *queenSquare = new square(0, 0);


public:
    solveColumnData(int columnOffset, int column, int squaresPerSide) {
        this->columnOffset = columnOffset;
        this->column = column;
        this->squaresPerSide = squaresPerSide;
    }

    ~solveColumnData() {
        delete queenSquare;
    }

    void setQueenSquare() {
        queenSquare->setValues(column, row);
    }

    square *getQueenSquare() {
        return queenSquare;
    }

    void releaseQueenSquare() {
        queenSquare = new square(0, 0);
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

    bool nextRow() {
        if (row >= (squaresPerSide - 1)) {
            return false;
        }
        ++row;
        return true;
    }
};

inline bool checkSquareIsAvailable(const std::list<square *>& queenSquares, int column, int row) {
    for (auto &queenSquare : queenSquares)
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

//int totalRecursions = 0;

bool solveColumn(int squaresPerSide, std::list<square *>& queenSquares,
                 const std::vector<int>& openColumns) {
//++totalRecursions;

    std::list<solveColumnData *> solveStack;
    auto *columnData = new solveColumnData(0, openColumns[0], squaresPerSide);
    bool isSuccess = false;
    do {
        queenSquares.push_back(columnData->getQueenSquare());
        do {
            if (checkSquareIsAvailable(queenSquares, columnData->getColumn(), columnData->getRow())) {
                columnData->setQueenSquare();
                if (columnData->getColumnOffset() >= openColumns.size()) {
                    isSuccess = true;
                    break;
                }

                solveStack.push_front(columnData);
                int nextColumnOffset = columnData->getColumnOffset() + 1;
                columnData = new solveColumnData(nextColumnOffset, openColumns[nextColumnOffset], squaresPerSide);
            }
        } while (columnData->nextRow());
        if (!isSuccess) {
            queenSquares.pop_back();
        } else {
            columnData->releaseQueenSquare();
        }
        delete columnData;
        columnData = solveStack.front();
        solveStack.pop_front();
    } while (!isSuccess && !solveStack.empty());

    return isSuccess;
}

std::string createPrintableRepresentationOfBoard(int squaresPerSide, const std::list<square *>& queenSquares) {
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

std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoordinates) {
    if (n == 1) {
        return "Q\n";
    }
    if (n < 4) {
        return "";
    }

    std::list<square *> queenSquares;
    queenSquares.push_front(new square(mandatoryQueenCoordinates.first, mandatoryQueenCoordinates.second));

    std::vector<int> openColumns;
    for (int column = 0; column < n; column++) {
        if (column != mandatoryQueenCoordinates.first) {
            openColumns.push_back(column);
        }
    }

    std::string *returnValue;
//totalRecursions = 0;
    if (solveColumn(n, queenSquares, openColumns)) {
        std::string solution = createPrintableRepresentationOfBoard(n, queenSquares);
        returnValue = new std::string(solution);
    } else {
        returnValue = new std::string("");
    }
//std::cerr << totalRecursions << std::endl;
    for (const auto node: queenSquares)
        delete node;
    queenSquares.clear();
    return *returnValue;
}

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
