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

//int totalRecursions = 0;

bool solveColumn(int squaresPerSide, std::list<square *>& queenSquares,
                 const std::vector<int>& openColumns, int columnOffset) {
//++totalRecursions;
    if (columnOffset >= openColumns.size()) {
        return true;
    }

    int column = openColumns[columnOffset];
    bool isSuccess = false;
    for (int row = 0; row < squaresPerSide; row++) {
        if (!checkSquareIsAvailable(queenSquares, column, row)) {
            continue;
        }
        auto *newQueenSquare = new square(column, row);
        queenSquares.push_back(newQueenSquare);

        if (solveColumn(squaresPerSide, queenSquares, openColumns, columnOffset + 1)) {
            isSuccess = true;
            break;
        }
        delete newQueenSquare;
        queenSquares.pop_back();
    }

    return isSuccess;
}

std::string getPrintableRepresentation(int squaresPerSide, const std::list<square *>& queenSquares) {
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
if (solveColumn(n, queenSquares, openColumns, 0)) {
        std::string solution = getPrintableRepresentation(n, queenSquares);
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
