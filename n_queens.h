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

public:
    queenSquare(int column, int row, int squaresPerSide, bool isMandatory) {
        this->column = column;
        this->row = row;
        this->squaresPerSide = squaresPerSide;
        this->forwardCode = calculateForwardCode(column, row);
        this->backwardCode = calculateBackwardCode(column, row, squaresPerSide);
        this->mandatory = isMandatory;
    }

    void moveQueen(int column, int row) {
        if (isMandatory()) {
            return;
        }
        this->column = column;
        setRow(row);
    }

    void setRow(int row) {
        if (isMandatory()) {
            return;
        }
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
};

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

inline bool isInConflictAt(const std::list<queenSquare *>& queenSquares, int column, int row) {
    int forwardCode = calculateForwardCode(column, row);
    int backwardCode = calculateBackwardCode(column, row, (int)queenSquares.size());
    for (auto &queenSquare : queenSquares)
    {
        if (queenSquare->getColumn() == column) {
            continue;
        }
        if (queenSquare->getRow() == row ||
                queenSquare->getForwardCode() == forwardCode ||
                queenSquare->getBackwardCode() == backwardCode) {
            return true;
        }
    }
    return false;
}

inline int calculateConflictWeightAt(const std::list<queenSquare *>& queenSquares, int column, int row) {
    int forwardCode = calculateForwardCode(column, row);
    int backwardCode = calculateBackwardCode(column, row, (int)queenSquares.size());
    int totalConflicts = 0;
    for (auto &queenSquare : queenSquares)
    {
        if (queenSquare->getColumn() == column) {
            continue;
        }
        if (queenSquare->getRow() == row ||
        queenSquare->getForwardCode() == forwardCode ||
        queenSquare->getBackwardCode() == backwardCode) {
            ++totalConflicts;
        }
    }
    return totalConflicts;
}

inline int calculateConflictWeight(const std::list<queenSquare *> queenSquares) {
    int conflictWeight = 0;
    for (auto &target : queenSquares) {
        for (auto &source : queenSquares) {
            if (source->getColumn() == target->getColumn()) {
                continue;
            }
            if (target->getRow() == source->getRow() ||
                target->getForwardCode() == source->getForwardCode() ||
                target->getBackwardCode() == source->getBackwardCode()) {
                ++conflictWeight;
            }
        }
    }
    return conflictWeight;
}

queenSquare *findQueenSquareByIndex(const std::list<queenSquare *> queenSquares, int index) {
    if (index < 0 || index >= (int)queenSquares.size()) {
        throw;      // invalid index
    }
    auto it = std::next(queenSquares.begin(), index);
    return *it;
}

void moveQueenToMinConflictPosition(const std::list<queenSquare *> queenSquares, queenSquare *targetQueen, int initialConflictWeight) {
    int originalRow = targetQueen->getRow();
    int minConflictRow = targetQueen->getRow();
    int minConflictWeight = (int)queenSquares.size() + 1;
    for (int row = 0; row < (int)queenSquares.size(); row++) {
//        if (row == originalRow) {
//            continue;
//        }
//        if (isInConflictAt(queenSquares, targetQueen->getColumn(), row)) {
//            continue;
//        }
//        targetQueen->setRow(row);
        int conflictWeight = calculateConflictWeightAt(queenSquares, targetQueen->getColumn(), row);
        if (conflictWeight < minConflictWeight) {
            minConflictWeight = conflictWeight;
            minConflictRow = row;
        }
    }
std::cout << "Move queen at " << targetQueen->getColumn() << " to " << minConflictRow << " from " << originalRow << std::endl;
    targetQueen->setRow(minConflictRow);
}

bool solveNQueensFor(const std::list<queenSquare *> queenSquares) {
    int squaresPerSide = (int)queenSquares.size();
    int conflictWeight = calculateConflictWeight(queenSquares);
//    int nextQueenIndex = 0;
    while (conflictWeight != 0) {
//std::cout << conflictWeight << std::endl;
//        int queenIndex = nextQueenIndex++;
//        nextQueenIndex = nextQueenIndex % squaresPerSide;
        int queenIndex = rand() % squaresPerSide;
        auto whichQueen = findQueenSquareByIndex(queenSquares, queenIndex);
        if (whichQueen->isMandatory() || !isInConflictAt(queenSquares, whichQueen->getColumn(), whichQueen->getRow())) {
            continue;
        }
        moveQueenToMinConflictPosition(queenSquares, whichQueen, conflictWeight);
        conflictWeight = calculateConflictWeight(queenSquares);
    }
    // how to detect a non-solvable condition?????
    return true;
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
            // position all the other queens on random rows
            queenSquares.push_back(new queenSquare(column, rand() % n, n, false));
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
