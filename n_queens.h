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

class queenSquare {
    int column;
    int row;
    int squaresPerSide;
    int forwardCode;
    int backwardCode;
    bool mandatory;
    int conflictCount;

public:
    queenSquare(int column, int row, int squaresPerSide, bool isMandatory) {
        this->column = column;
        this->row = row;
        this->squaresPerSide = squaresPerSide;
        this->forwardCode = calculateForwardCode(column, row);
        this->backwardCode = calculateBackwardCode(column, row, squaresPerSide);
        this->mandatory = isMandatory;
        this->conflictCount = 0;
    }

    void moveQueen(int column, int row) {
        this->conflictCount = 0;
        if (isMandatory()) {
            return;
        }
        this->column = column;
        this->row = row;
        this->forwardCode = calculateForwardCode(column, row);
        this->backwardCode = calculateBackwardCode(column, row, squaresPerSide);
    }

    bool isMandatory() const {
        return mandatory;
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

    int getConflictCount() const {
        return conflictCount;
    }

    void clearConflictCount() {
        conflictCount = 0;
    }

    void incrementConflictCount() {
        conflictCount++;
    }
};

inline bool countConflictsFor(const std::list<queenSquare *>& queenSquares, int boardColumn, int boardRow) {
    int forwardCode = calculateForwardCode(boardColumn, boardRow);
    int backwardCode = calculateBackwardCode(boardColumn, boardRow, (int)queenSquares.size());
    int conflictCount = 0;
    for (auto &queenSquare : queenSquares)
    {
        if (queenSquare->getColumn() == boardColumn) {
            continue;
        }
        if (queenSquare->getRow() == boardRow ||
                queenSquare->getForwardCode() == forwardCode ||
                queenSquare->getBackwardCode() == backwardCode) {
            conflictCount++;
        }
    }
    return conflictCount;
}

std::string createPrintableRepresentationOfBoard(int squaresPerSide, const std::list<queenSquare *>& queenSquares) {
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

void calculateConflictsFor(const std::list<queenSquare *> queenSquares) {
}

bool solveNQueensFor(const std::list<queenSquare *> queenSquares) {
    while (queensAreConflicting(queenSquares)) {

    }
}

std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoordinates) {
    if (n == 1) {
        return "Q\n";
    }
    if (n < 4) {
        return "";
    }

    std::list<queenSquare *> queenSquares;

    std::list<int> columnCollector;
    for (int column = 0; column < n; column++) {
        if (column != mandatoryQueenCoordinates.first) {
            // position all the other queens on row 0
            queenSquares.push_back(new queenSquare(column, 0, n, false)));
        } else {
            // can be extended to multiple mandatory queens if needed
            queenSquares.push_back(new queenSquare(mandatoryQueenCoordinates.first, mandatoryQueenCoordinates.second, n, true));
        }
    }

    std::string *returnValue;
    if (solveNQueensFor(queenSquares)) {
        std::string solution = createPrintableRepresentationOfBoard(n, queenSquares);
        returnValue = new std::string(solution);
    } else {
        returnValue = new std::string("");
    }

    for (const auto node: queenSquares)
        delete node;
    queenSquares.clear();

    return *returnValue;
}

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
