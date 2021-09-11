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
                 const int *openColumns, int openColumnCount) {
//++totalRecursions;

    std::list<solveColumnData *> solveStack;
    auto *columnData = new solveColumnData(0, openColumns[0], squaresPerSide);
    bool isSuccess = false;
    do {
        do {
            if (!isSuccess && checkSquareIsAvailable(queenSquares, columnData->getColumn(), columnData->getRow())) {
                int nextColumnOffset = columnData->getColumnOffset() + 1;
for (int count = 0; count < solveStack.size(); count++) {
    std::cout<<" ";
}
std::cout<<nextColumnOffset<<" ("<<queenSquares.size()<< ")"<<std::endl<<std::flush;
                columnData->setQueenSquare();
                if (nextColumnOffset >= openColumnCount) {
                    queenSquares.push_back(columnData->getQueenSquare());
                    columnData->releaseQueenSquare();
                    isSuccess = true;
std::cout << "SOLVED " << nextColumnOffset << "/" << openColumnCount << std::endl;
                    break;
                }

                solveStack.push_front(columnData);
                columnData = new solveColumnData(nextColumnOffset, openColumns[nextColumnOffset], squaresPerSide);
                queenSquares.push_back(columnData->getQueenSquare());
            }
        } while (!isSuccess && columnData->nextRow());

        if (!isSuccess) {
            queenSquares.pop_back();
            delete columnData;
            if (!solveStack.empty()) {
                columnData = solveStack.front();
                solveStack.pop_front();
            }
        } else {
            columnData->releaseQueenSquare();
            delete columnData;
            break;
        }
    } while (!solveStack.empty());

    while (!solveStack.empty()) {
        columnData = solveStack.front();
        solveStack.pop_front();
        delete columnData;
    }
    std::cout << "Final queensqares size:"<< queenSquares.size() <<std::endl;
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
//totalRecursions = 0;
std::cout << "START SOLVING " <<  n << std::endl;
    if (solveColumn(n, queenSquares, openColumns, columnCollector.size())) {
        std::string solution = createPrintableRepresentationOfBoard(n, queenSquares);
        returnValue = new std::string(solution);
    } else {
        returnValue = new std::string("");
    }
//std::cerr << totalRecursions << std::endl;
    for (const auto node: queenSquares)
        delete node;
    queenSquares.clear();

    delete openColumns;
    return *returnValue;
}

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
