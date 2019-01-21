#include "Game.h"

#include <iostream>

//For randint
#include <ctime>
#include <cstdlib>

#include <cctype>   // toupper

using namespace std;

Game::Game() {

    //Determine tokens to be used
    setPlayerTokens();

    //Pick a random player to go first
    turn = randint(1,2);
    totalMoves = 0;

    //Debug conditions, if any
    //totalMoves = 9;
    //b.debugFillBoard();

    //Begin game
    runGame();
}

Game::Game(Player& human, Player& cylon) {
    turn = 0;
    totalMoves = 0;
}

void Game::setPlayerTokens() {
    char ans;

    cout << "WELCOME TO TIC-TAC-TOE!" << endl;
    cout << "(c) 2019 by Ringo!ware Software inc." << endl;
    cout << endl;

    cout << "Player one: Do you want to use X or O?" << endl;

    do {
        cout << ">" << flush;
        cin >> ans;
    }
    while (ans != 'X' && ans != 'O' && ans != 'x' && ans != 'o');

    //Player tokens should be uppercase
    if (ans == 'x' || ans == 'o') {
        ans = toupper(ans);
    }

    human.setToken(ans);

    //cout << endl;

    //Set up computer's token
    if (human.getToken() == 'X') {
        cout << "The computer will take O's." << endl;
        cylon.setToken('O');
    } else {
        cout << "The computer will take X's." << endl;
        cylon.setToken('X');
    }

    cout << endl;
}

void Game::showStatus() {
    cout << "Turn #" << totalMoves << endl;

    if (turn == 1) {
        cout << "->";
    }
    cout << "Player One\t";
    human.getPlayerInfo();

    if (turn == 2) {
        cout << "->";
    }
    cout << "HAL 9000\t";
    cylon.getPlayerInfo();

    cout << endl;

    //Print the board
    printBoard();

    cout << endl;
}

void Game::printBoard() {
    int val = -99;      // value in square (-1 is empty, 1 is human, 2 is computer)
    int cnt = 0;        // grid square count (for identifying player's possible moves)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cnt++;
            val = b.getDataAtPosition(row,col);
            if (val == -1) {
                cout << cnt << "\t|\t";
            } else if (val == 1) {
                cout << human.getToken() << "\t|\t";
            } else if (val == 2) {
                cout << cylon.getToken() << "\t|\t";
            }
        }
        cout << endl;
        if (row < 2) {
            cout << "-----------------------------------------" << endl;
        }
    }

    cout << endl;
}

///FIXME: Something's screwy with the 'cat got the game' functionality. It's declaring a tie @ turn #5
void Game::runGame() {
    cout << endl;

    //while (!b.isBoardFull() && !b.isWinningBoard()) {
    while (!b.isWinningBoard() && totalMoves < 9) {
        totalMoves++;

        showStatus();

        //Distribute turn order
        if (turn == 1) {
            cout << "PLAYER ONE, it's your turn!" << endl;
            getHumanMove();
        } else {
            cout << "It's HAL's turn" << endl;
            getComputerMove();
        }

        turn++;
        turn %= 2;
    }

    //if (b.isBoardFull()) {
    if (totalMoves == 9 || b.isBoardFull()) {
        //Cat got the game
        drawGame();

    } else {
        //FIXME: This is all fouled up (always throws a tie). Need an easier way to determine win conditions
        //Determine who won
        bool isWin = b.isWinningBoard();
        if (isWin) {
            endGame();
        }
    }

}

void Game::getComputerMove() {
    /*
    cout << "TODO: Computer chooses a move" << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
    */
    bool isSuccess;
    int compMove;
    int row, col;
    //If it's the very first move, put a token in the middle square
    if (totalMoves == 1) {
        isSuccess = b.placeTokenAtPosition(2,1,1);
        if (isSuccess) {
            cout << "Computer placed an " << cylon.getToken() << " in square #5 (1,1)" << endl;
            cout << "----------------------------------------------------------------------" << endl;
            cout << endl;
            return;
        }
    /*
     * This is a mess. I know it. I'd like to design a more robust computer system
     * that actually examines the board and makes moves based on the position of the
     * human player's tokens. This is preliminary/placeholder code for (hopefully) a
     * more elaborate implementation.
     */
    } else {
        //Keep trying a random value until it is successful
        do {
            compMove = randint(1,9);

            //Convert grid square value to an xy coordinate
            std::pair<int,int> xy = convertToCoordinates(compMove);
            row = xy.first;
            col = xy.second;
            isSuccess = b.placeTokenAtPosition(2,row,col);
        }
        while (!isSuccess);
        cout << "Computer placed an " << cylon.getToken() << " in square #" << compMove << "(" << row << "," << col << ")" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << endl;
    }
}

void Game::getHumanMove() {
    cout << "Player one: Please type a number (1~9)" << endl;
    int playerMove;     // grid square chosen by player

    do {
        cout << ">" << flush;
        cin >> playerMove;
    }
    while (playerMove < 0 || playerMove > 9);

    //Debugging back door
    if (playerMove == 0) {
        //Force end game
        playerMove = 9 - totalMoves;
        totalMoves += playerMove;
        return;
    }

    bool isSuccess;     // was the token successfully placed

    //todo: This code is all cocked up
    /*
    int row,col;
    if (playerMove < 4) {
        row = 0;
        col = playerMove - 1;
    } else if (playerMove < 7) {
        row = 1;
        col = playerMove - (playerMove - 1);
    } else  {
        row = 2;
        //FIXME: 7 should be (2,0) - is currently (2,1)
        //col = playerMove - (playerMove - 1);
        col = (9 - playerMove) - 2;
    }

    if (playerMove == 6 || playerMove == 9) {
        col++;
    }

    cout << "\tROW and COL: (" << row << ", " << col << ")" << endl;
    isSuccess = b.placeTokenAtPosition(1,row,col);
    if (isSuccess) {
        cout << "-------------------------------------------" << endl;
    } else {
        cout << "ERROR: That square is taken. Please choose another" << endl;
        getHumanMove();
    }
    */
    int row,col;        // absolute location on board
    std::pair<int, int> xy = convertToCoordinates(playerMove);
    row = xy.first;
    col = xy.second;

    isSuccess = b.placeTokenAtPosition(1,row,col);
    if (isSuccess) {
        cout << "Player One places an " << human.getToken() << " at square #" << playerMove << " (" << row << ", " << col << ")" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << endl;
        //cout << endl;
    } else {
        cout << "ERROR: That square is occupied! Please choose another one." << endl;
        getHumanMove();
    }
}

void Game::drawGame() {
    cout << endl;
    cout << "Cat got the game!" << endl;

    cout << endl;
    cout << "This game ended in a draw. Would you like to play again?" << endl;
    cout << "Type Y or N" << endl;
    char ans;

    do {
        cout << ">" << flush;
        cin >> ans;
    }
    while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');

    if (ans == 'Y' || ans == 'y') {
        b.emptyBoard();
        runGame();
    }
}

void Game::endGame() {
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "SOMEONE WON!" << endl;

    //Print the board
    int val = -99;      // value in square (-1 is empty, 1 is human, 2 is computer)
    int cnt = 0;        // grid square count (for identifying player's possible moves)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cnt++;
            val = b.getDataAtPosition(row,col);
            if (val == -1) {
                cout << cnt << "\t|\t";
            } else if (val == 1) {
                cout << human.getToken() << "\t|\t";
            } else if (val == 2) {
                cout << cylon.getToken() << "\t|\t";
            }
        }
        cout << endl;
        if (row < 2) {
            cout << "-----------------------------------------" << endl;
        }
    }

    cout << endl;
}

int Game::randint(int lower, int upper) {
    srand((unsigned)time(0));
    return rand() % upper + lower;
}

std::pair<int, int> Game::convertToCoordinates(int sq) {
    /*
     * Coord.first:  x coordinate
     * Coord.second: y coordinate
     */
    std::pair<int, int> coord;

    if (sq < 4) {
        coord.first = 0;
        coord.second = sq - 1;
    } else if (sq < 7) {
        coord.first = 1;
        coord.second = sq - 4;
    } else if (sq > 6) {
        coord.first = 2;
        coord.second = sq - 7;
    }

    return coord;
}
