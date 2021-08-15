//
// Created by Chris on 8/9/2021.
//

#ifndef CODEWARSNQUEENSPROBLEM_N_QUEENS_H
#define CODEWARSNQUEENSPROBLEM_N_QUEENS_H


#include <string>

class square {
    int column;
    int row;

public:
    square(int column, int row) {
        this->column = column;
        this->row = row;
    }

    int getColumn() {
        return column;
    }

    int getRow() {
        return row;
    }
};


class iBoard {
public:
    virtual int getSquaresPerSide() = 0;
    virtual bool isQueenAt(int column, int row) = 0;
};

class iColumn_weights {
public:
    virtual void setWeightFor(int row, int totalWeight) = 0;
};

class column_weights;

class square_weight {
    int column;
    int row;
    bool hasQueen = false;
    int weight = 0;

    friend class column_weights;

protected:
    explicit square_weight() {
        this->column = 0;
        this->row = 0;
    }

    void setColumn(int column) {
        this->column = column;
    }

    void setRow(int row) {
        this->row = row;
    }

    void setQueenOnSquare() {
        this->hasQueen = true;
    }

public:
    explicit square_weight(int column, int row, bool hasQueen) {
        this->column = column;
        this->row = row;
        this->hasQueen = hasQueen;
    }

    int getColumn() {
        return column;
    }

    int getRow() {
        return row;
    }

    bool isQueenOnSquare() {
        return hasQueen;
    }

    void setWeight(int totalWeight) {
        weight = totalWeight;
    }

    void addWeight() {
        ++weight;
    }

    int getWeight() {
        return weight;
    }
};

class board : public iBoard {
    int squaresPerSide = 0;
    bool** squares = nullptr;       // column dimensions containing row dimensions [column][row]
    square *fixedQueenLocation = nullptr;

    void prepareBoard(int squaresPerSide) {
        if (squaresPerSide < 4)
            throw std::exception("board size cannot be smaller than 4 per side");
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
            throw std::exception("out of range");
        }
        squares[column][row] = value;
    }

    bool leftPressureOn(int column, int row) {
        if (column <= 0 || column >= squaresPerSide)
            return false;
        for (int index = column - 1; index >= 0; index--) {
            if (isQueenAt(index, row)) {
                return true;
            }
        }
        return false;
    }

    bool rightPressureOn(int column, int row) {
        if (column < 0 || column >= (squaresPerSide - 1))
            return false;
        for (int index = column + 1; index < squaresPerSide; index++) {
            if (isQueenAt(index, row)) {
                return true;
            }
        }
        return false;
    }

    bool topPressureOn(int column, int row) {
        if (row <= 0 || row >= squaresPerSide)
            return false;
        for (int index = row - 1; index >= 0; index--) {
            if (isQueenAt(column, index)) {
                return true;
            }
        }
        return false;
    }

    bool bottomPressureOn(int column, int row) {
        if (row < 0 || row >= (squaresPerSide - 1))
            return false;
        for (int index = row + 1; index < squaresPerSide; index++) {
            if (isQueenAt(column, index)) {
                return true;
            }
        }
        return false;
    }

    bool topLeftPressureOn(int column, int row) {
        if (column <= 0 || column >= squaresPerSide)
            return false;
        if (row <= 0 || row >= (squaresPerSide - 1))
            return false;
        for (int cIndex = column - 1, rIndex = row - 1; cIndex >= 0 && rIndex >= 0; cIndex--, rIndex--) {
            if (isQueenAt(cIndex, rIndex)) {
                return true;
            }
        }
        return false;
    }

    bool bottomLeftPressureOn(int column, int row) {
        if (column <= 0 || column >= squaresPerSide)
            return false;
        if (row < 0 || row >= (squaresPerSide - 1))
            return false;
        for (int cIndex = column - 1, rIndex = row + 1; cIndex >= 0 && rIndex < squaresPerSide; cIndex--, rIndex++) {
            if (isQueenAt(cIndex, rIndex)) {
                return true;
            }
        }
        return false;
    }

    bool topRightPressureOn(int column, int row) {
        if (column < 0 || column >= (squaresPerSide - 1))
            return false;
        if (row <= 0 || row >= squaresPerSide)
            return false;
        for (int cIndex = column + 1, rIndex = row - 1; cIndex < squaresPerSide && rIndex >= 0; cIndex++, rIndex--) {
            if (isQueenAt(cIndex, rIndex)) {
                return true;
            }
        }
        return false;
    }

    bool bottomRightPressureOn(int column, int row) {
        if (column < 0 || column >= (squaresPerSide - 1))
            return false;
        if (row < 0 || row >= (squaresPerSide - 1))
            return false;
        for (int cIndex = column + 1, rIndex = row + 1; cIndex < squaresPerSide && rIndex < squaresPerSide; cIndex++, rIndex++) {
            if (isQueenAt(cIndex, rIndex)) {
                return true;
            }
        }
        return false;
    }

    iColumn_weights *createColumnWeights(iBoard *board, int column);

public:
    explicit board(int squaresPerSide) {
        prepareBoard(squaresPerSide);
    }

    explicit board(int squaresPerSide, square *fixedQueenLocation) {
        prepareBoard(squaresPerSide);
        if (fixedQueenLocation->getColumn() >= squaresPerSide ||
                fixedQueenLocation->getRow() >= squaresPerSide) {
            throw std::exception("fixed queen location is out of bounds of the board");
        }
        this->fixedQueenLocation = fixedQueenLocation;
        flipSquareAt(fixedQueenLocation->getColumn(), fixedQueenLocation->getRow(), true);
    }

    virtual ~board() {
        for (int index = 0; index < squaresPerSide; index++) {
            delete [] squares[index];
        }
        delete [] squares;

        delete fixedQueenLocation;
    }

    int getSquaresPerSide() override {
        return squaresPerSide;
    }

    void setQueenAt(int column, int row) {
        flipSquareAt(column, row,true);
    }

    void removeQueenAt(int column, int row) {
        flipSquareAt(column, row,false);
    }

    bool isQueenAt(int column, int row) override {
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

    int getWeightFor(int column, int row) {
        int totalWeight = 0;
        if (leftPressureOn(column, row)) {
            ++totalWeight;
        }
        if (rightPressureOn(column, row)) {
            ++totalWeight;
        }
        if (topPressureOn(column, row)) {
            ++totalWeight;
        }
        if (bottomPressureOn(column, row)) {
            ++totalWeight;
        }
        if (topLeftPressureOn(column, row)) {
            ++totalWeight;
        }
        if (bottomLeftPressureOn(column, row)) {
            ++totalWeight;
        }
        if (topRightPressureOn(column, row)) {
            ++totalWeight;
        }
        if (bottomRightPressureOn(column, row)) {
            ++totalWeight;
        }
        return totalWeight;
    }

    column_weights *getWeights(int column) {
        iColumn_weights *weights = createColumnWeights((iBoard *)this, column);
        for (int row = 0; row < squaresPerSide; row++) {
            weights->setWeightFor(row, getWeightFor(column, row));
        }
        return (column_weights *)weights;
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
        return openColumns;
    }
};

class column_weights : public iColumn_weights {
    square_weight *weights = nullptr;
    int rows;
    int column;

public:
    column_weights(iBoard *board, int column) {
        rows = board->getSquaresPerSide();
        this->column = column;
        weights = new square_weight[rows];
        for (int row = 0; row < rows; row++) {
            weights[row].setColumn(column);
            weights[row].setRow(row);
            if (board->isQueenAt(column, row)) {
                weights[row].setQueenOnSquare();
            }
        }
    }
    virtual ~column_weights() {
        delete [] weights;
    }

    void setWeightFor(int row, int totalWeight) override {
        if (row >= rows) {
            throw std::exception("illegal row in column weights");
        }
        weights[row].setWeight(totalWeight);
    }

    int getWeightFor(int row) {
        return weights[row].getWeight();
    }
};

iColumn_weights *board::createColumnWeights(iBoard *board, int column) {
    return new column_weights(board, column);
}

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

bool solveColumn(board& board, int *columnNumbers, int columnCount, int columnOffset) {
    int column = columnNumbers[columnOffset];
    auto *weights = board.getWeights(column);
    bool isSuccess = false;
    for (int row = 0; row < board.getSquaresPerSide(); row++) {
        if (weights->getWeightFor(row) != 0) {
            continue;
        }
        board.setQueenAt(column, row);
        if (columnOffset == (columnCount - 1)) {
            isSuccess = true;
            break;
        } else if (solveColumn(board, columnNumbers, columnCount, columnOffset + 1)) {
            isSuccess = true;
            break;
        }
        board.removeQueenAt(column, row);
    }
    delete weights;
    return isSuccess;
}

std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoordinates) {
    if (n < 4) {
        return "";
    }

    auto *fixedQueenPosition = new square(mandatoryQueenCoordinates.first, mandatoryQueenCoordinates.second);
    auto *queenSolver = new n_queens(n, fixedQueenPosition);

    auto board = queenSolver->getBoard();
    int columnCount = 0;
    auto columns = board.getColumnsWithoutQueens(columnCount);

    std::string returnValue;
    if (solveColumn(board, columns, columnCount, 0)) {
        returnValue = board.getPrintableRepresentation();
    }
    delete queenSolver;
    return returnValue;
}

#endif //CODEWARSNQUEENSPROBLEM_N_QUEENS_H
