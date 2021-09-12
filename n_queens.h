//
// Created by Chris on 8/9/2021.
//

#ifndef CODEWARSNQUEENSPROBLEM_N_QUEENS_H
#define CODEWARSNQUEENSPROBLEM_N_QUEENS_H


#include <string>
#include <cstring>
#include <list>
#include <math.h>

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
    bool matchedForward = false;
    bool matchedBackward = false;
    for (auto &queenSquare : queenSquares)
    {
        if (queenSquare->getColumn() == column) {
            continue;
        }
        if (queenSquare->getRow() == row) {
            ++totalConflicts;
        }
        if (!matchedForward && queenSquare->getForwardCode() == forwardCode) {
            ++totalConflicts;
            matchedForward = true;
        }
        if (!matchedBackward && queenSquare->getBackwardCode() == backwardCode) {
            ++totalConflicts;
            matchedBackward = true;
        }
    }
    return totalConflicts;
}

inline int calculateConflictWeight(const std::list<queenSquare *> queenSquares) {
    int conflictWeight = 0;
    bool matchedForward = false;
    bool matchedBackward = false;
    for (auto &target : queenSquares) {
        for (auto &source : queenSquares) {
            if (source->getColumn() == target->getColumn()) {
                continue;
            }
            if (target->getRow() == source->getRow()) {
                ++conflictWeight;
            }
            if (!matchedForward && target->getForwardCode() == source->getForwardCode()) {
                ++conflictWeight;
                matchedForward = true;
            }
            if (!matchedBackward && target->getBackwardCode() == source->getBackwardCode()) {
                ++conflictWeight;
                matchedBackward = true;
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

bool moveQueenToMinConflictPosition(const std::list<queenSquare *> queenSquares, queenSquare *targetQueen) {
    int initialRow = targetQueen->getRow();
    int minConflictRow = targetQueen->getRow();
    int minConflictWeight = (int)queenSquares.size() + 1;
    for (int row = 0; row < (int)queenSquares.size(); row++) {
        int conflictWeight = calculateConflictWeightAt(queenSquares, targetQueen->getColumn(), row);
        if (conflictWeight < minConflictWeight) {
            minConflictWeight = conflictWeight;
            minConflictRow = row;
        }
    }
//std::cout << "Move queen at " << targetQueen->getColumn() << " to " << minConflictRow << " from " << originalRow << std::endl;
    if (initialRow != minConflictRow) {
        targetQueen->setRow(minConflictRow);
        return true;
    }
    return false;
}

queenSquare *getNextQueenThatIsNotMandatory(const std::list<queenSquare *> queenSquares) {
    while (true) {
        int index = rand() % queenSquares.size();
        auto queen = findQueenSquareByIndex(queenSquares, index);
        if (!queen->isMandatory()) {
            return queen;
        }
    }
}

bool solveNQueensFor(const std::list<queenSquare *> queenSquares) {
    int squaresPerSide = (int)queenSquares.size();
    int conflictWeight = calculateConflictWeight(queenSquares);
    int lastConflictWeight = -1;
    int failedIterations = 0;
    int failsToTriggerReset = squaresPerSide * (int)ceil(sqrt(squaresPerSide));
//    int numberOfQueensToMoveOnReset =  squaresPerSide / (int)ceil(sqrt(squaresPerSide));
    int numberOfQueensToMoveOnReset = (int)ceil(sqrt(squaresPerSide));
    int resetsToTriggerStalemate = failsToTriggerReset;
    int totalResets = 0;
    bool status = true;
    while (conflictWeight != 0) {
        auto queen = getNextQueenThatIsNotMandatory(queenSquares);
        if (!isInConflictAt(queenSquares, queen->getColumn(), queen->getRow())) {
            continue;
        }
        if (moveQueenToMinConflictPosition(queenSquares, queen)) {
            conflictWeight = calculateConflictWeight(queenSquares);
        }

        // break a stalemate?
        if (conflictWeight != lastConflictWeight) {
            lastConflictWeight = conflictWeight;
            failedIterations = 0;
        } else {
            failedIterations++;
            if (failedIterations > failsToTriggerReset) {
//std::cout << "FAILED" << std::endl;
                queen->setRow(rand() % squaresPerSide);
                for (int moves = 0; moves < numberOfQueensToMoveOnReset - 1; moves++) {
                    getNextQueenThatIsNotMandatory(queenSquares)->setRow(rand() % squaresPerSide);
                }
                conflictWeight = calculateConflictWeight(queenSquares);

                failedIterations = 0;
                ++totalResets;
                if (totalResets > resetsToTriggerStalemate) {
//std::cout << "STALEMATE" << std::endl;
                    status = false;
                    break;
                }
            }
        }
    }
    return status;
}

std::string *solveNQueens(int n, std::pair<int, int> mandatoryQueenCoordinates, std::list<queenSquare *> queenSquares) {
    std::string *returnValue;
    for (int attempt = 0; attempt < 3; attempt++) {
        for (int column = 0; column < n; column++) {
            if (column != mandatoryQueenCoordinates.first) {
                // position all the other queens on random rows
                queenSquares.push_back(new queenSquare(column, rand() % n, n, false));
            } else {
                // can be extended to multiple mandatory queens if needed
                queenSquares.push_back(new queenSquare(mandatoryQueenCoordinates.first, mandatoryQueenCoordinates.second, n, true));
            }
        }
        std::string *returnValue = nullptr;
        if (solveNQueensFor(queenSquares)) {
            std::string solution = createPrintableRepresentationOfBoard(n, queenSquares);
            returnValue = new std::string(solution);
            std::cout << "SOLVED" << std::endl;

            for (const auto node: queenSquares)
                delete node;
            queenSquares.clear();

            return returnValue;
        }

std::cout << "RETRY" << std::endl;
        for (const auto node: queenSquares)
            delete node;
        queenSquares.clear();
    }
    return new std::string("");
}

std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoordinates) {
    if (n == 1) {
        return "Q\n";
    }
    if (n < 4) {
        return "";
    }

    srand(time(NULL));

    std::list<queenSquare *> queenSquares;
    std::string *returnValue = solveNQueens(n, mandatoryQueenCoordinates, queenSquares);

    return *returnValue;
}

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
