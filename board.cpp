#include "Board.h"

#include <iostream>

using namespace std;

Board::Board() {
    //Initialize each 'square' in the board to -1 (denoting that it's empty)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            gameBoard[i][j] = -1;
        }
    }
}

void Board::print() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << gameBoard[i][j] << "\t";
        }

        cout << endl;
    }
}

int Board::getDataAtPosition(int r, int c) {
    if (r < 3 && c < 3) {
        return gameBoard[r][c];
    } else {
        //Not a valid position
        return 99;
    }
}

bool Board::placeTokenAtPosition(int pNum, int r, int c) {
    //Must be a valid player number (1 or 2)
    if (pNum < 1 || pNum > 2)
        return false;

    //Is the square already occupied?
    int square = gameBoard[r][c];
    if (square > -1) {
        return false;
    } else {
        gameBoard[r][c] = pNum;
        return true;
    }
}

void Board::clearPosition(int r, int c) {
    //Must be a valid position
    if (r > 2 || r < 0 || c > 2 || c < 0)
        return;

    gameBoard[r][c] = -1;
}


void Board::emptyBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            gameBoard[i][j] = -1;
        }
    }
}

bool Board::isBoardFull() {
    int prod = 1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            prod *= gameBoard[i][j];
        }
    }

    if (prod < 0) {
        //Any empty spaces (denoted by -1) will make the product negative
        return false;
    }

    return true;
}

bool Board::isWinningBoard() {
    bool rows,cols,leftDiag,rightDiag;

    //Check for a win in any row
    for (int i = 0; i < 3; ++i) {
        rows = isWinInRow(i);

        if (rows) {
            return true;
        }
    }

    //Check for a win in any column
    for (int j = 0; j < 3; ++j) {
        cols = isWinInColumn(j);

        if (cols) {
            return true;
        }
    }

    //Check for a win in a diagonal
    leftDiag = isWinInForwardDiagonal();
    rightDiag = isWinInBackwardDiagonal();

    if (leftDiag || rightDiag) {
        return true;
    }

    return false;
}

bool Board::isWinInRow(int r) {
    int sum = 0;

    for (int col = 0; col < 3; ++col) {
        sum += gameBoard[r][col];
    }

    /*
     * A sum of 3 (player 1) or 6 (player 2) means that
     * one player has captured the entire row.
     */
    if (sum > 0 && sum % 3 == 0) {
        return true;
    }

    return false;
}

bool Board::isWinInColumn(int c) {
    int sum = 0;

    for (int row = 0; row < 3; ++row) {
        sum += gameBoard[row][c];
    }

    /*
     * A sum of 3 (player 1) or 6 (player 2) means that
     * one player has captured the entire column.
     */
    if (sum > 0 && sum % 3 == 0) {
        return true;
    }

    return false;
}

bool Board::isWinInForwardDiagonal() {
    int sum = 0;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0 ; c < 3; ++c) {
            if (r == c) {
                sum += gameBoard[r][c];
            }
        }
    }

    if (sum > 0 && sum % 3 == 0) {
        return true;
    }

    return false;
}

bool Board::isWinInBackwardDiagonal() {
    int sum = 0;

    //Revisit this later
    sum += gameBoard[0][2];
    sum += gameBoard[1][1];
    sum += gameBoard[2][0];

    if (sum > 0 && sum % 3 == 0) {
        return true;
    }

    return false;
}

void Board::debugGetStats() {
    bool isFull;            // is the board full?
    bool isRowWin;          // is there a win in a given row?
    bool isColWin;          // is there a win in a given column?
    bool isFrontDiagWin;    // is there a win in the front diagonal?
    bool isBackDiagWin;     // is there a win in the back diagonal?

    cout << endl;
    cout << "----------------------------------" << endl;
    cout << "Current Board Conditions (Debug)" << endl;
    print();

    cout << endl;
    isFull = isBoardFull();
    cout << "Board is full: " << std::boolalpha << isFull << endl;

    cout << endl;

    //Check each row for a win
    for (int i = 0; i < 3; ++i) {
        cout << "Row " << i << " win: ";
        isRowWin = isWinInRow(i);
        cout << std::boolalpha << isRowWin << endl;
    }

    cout << endl;

    //Check each column for a win
    for (int j = 0; j < 3; ++j) {
        cout << "Column " << j << " win: ";
        isColWin = isWinInColumn(j);
        cout << std::boolalpha << isColWin << endl;
    }

    cout << endl;

    //Check both diagonals for a win
    isFrontDiagWin = isWinInForwardDiagonal();
    cout << "Front diagonal win: " << std::boolalpha << isFrontDiagWin << endl;
    isBackDiagWin = isWinInBackwardDiagonal();
    cout << "Back diagonal win: " << std::boolalpha << isBackDiagWin << endl;

    cout << "----------------------------------" << endl;
}

void Board::debugFillBoard() {
    int pl = 0;     // player token

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            pl++;
            gameBoard[r][c] = pl;
            pl %= 2;
        }
    }
}

void Board::debugSetRowWinAt(int r) {
    for (int col = 0; col < 3; ++col) {
        gameBoard[r][col] = 1;
    }
}

void Board::debugSetColumnWinAt(int c) {
    for (int row = 0; row < 3; ++row) {
        gameBoard[row][c] = 1;
    }
}
