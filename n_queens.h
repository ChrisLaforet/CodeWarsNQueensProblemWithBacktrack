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
    bool queenSquarePushed = false;

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

inline bool checkSquareIsAvailable(const std::list<square *>& queenSquares, int boardColumn, int boardRow) {
    for (auto &queenSquare : queenSquares)
    {
        if (queenSquare->getRow() == boardRow) {
            return false;
        }
        int row = boardRow + 1;
        int column = boardColumn + 1;
        int queenRow = queenSquare->getRow() + 1;
        int queenColumn = queenSquare->getColumn() + 1;
        if ((queenColumn + row) == (column + queenRow)) {
            return false;
        }
        if ((queenColumn - row) == (column - queenRow)) {
            return false;
        }
    }
    return true;
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
//int totalRecursions = 0;

bool solveColumn(int squaresPerSide, std::list<square *>& queenSquares,
                 const int *openColumns, int openColumnCount) {
//++totalRecursions;

    std::list<solveColumnData *> solveStack;
    auto *columnData = new solveColumnData(0, openColumns[0], squaresPerSide);
    solveStack.push_front(columnData);
std::cout << "PUSH_FRONT" << std::endl;

    bool isSuccess = false;
    do {
//std::cout <<  ">>>Col, Row = " << columnData->getColumn() << "," << columnData->getRow() << std::endl;
        do {
std::cout << "At Col, Row = " << columnData->getColumn() << "," <<  columnData->getRow() << std::endl;
            if (!isSuccess && checkSquareIsAvailable(queenSquares, columnData->getColumn(), columnData->getRow())) {
std::cout << "Possible square at Col, Row = " << columnData->getColumn() << "," << columnData->getRow() << std::endl;
                int nextColumnOffset = columnData->getColumnOffset() + 1;
//for (int count = 0; count < solveStack.size(); count++) {
//    std::cout<<" ";
//}
//std::cout<<nextColumnOffset<<" ("<<queenSquares.size()<< ")"<<std::endl<<std::flush;
                columnData->setQueenSquare();
                if (!columnData->isQueenSquarePushed()) {
                    queenSquares.push_back(columnData->getQueenSquare());
//std::cout << "> PUSH_BACK" << std::endl;
                    columnData->setQueenSquarePushed(true);
                }
                if (nextColumnOffset >= openColumnCount) {
                    isSuccess = true;
std::cout << "SOLVED " << nextColumnOffset << "/" << openColumnCount << std::endl;
                    break;
                }
                columnData = new solveColumnData(nextColumnOffset, openColumns[nextColumnOffset], squaresPerSide);
                solveStack.push_front(columnData);
//std::cout << "PUSH_FRONT" << std::endl;
            } else if (!columnData->nextRow()) {
                break;
            }
std::cout << "In LEV " << solveStack.size() << " Col, Row = " << columnData->getColumn() << "," << columnData->getRow() << std::endl;
std::cout <<  createPrintableRepresentationOfBoard(squaresPerSide, queenSquares);
        } while (!isSuccess);

std::cout << "Exit LEV " << std::endl;
        if (!isSuccess) {
//            solveStack.pop_front();
            do {
                if (columnData->isQueenSquarePushed()) {
                    queenSquares.pop_back();
//std::cout << ">POP_BACK" << std::endl;
                }
                delete columnData;
                columnData = nullptr;

                solveStack.pop_front();
//std::cout << "POP_FRONT" << std::endl;

                if (solveStack.empty()) {
                    break;
                }
                columnData = solveStack.front();

//std::cout << "In LEV " << solveStack.size() << " Col, Row = " << columnData->getColumn() << "," << columnData->getRow() << std::endl;
                if (columnData->nextRow()) {
std::cout << "CIRCLE" << std::endl;
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
std::cout << "Final queensquares size:"<< queenSquares.size() <<std::endl;
    return isSuccess;
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
