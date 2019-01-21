#ifndef GAME_H
#define GAME_H

#include <utility>      // std::pair

#include "Player.h"
#include "Board.h"

using namespace std;

class Game
{
public:
    /**
     * Declaration of a new default game
     */
    Game();

    /**
     * Declaration of a new game with previously
     * created players so that the game can be resumed.
     * @param Player one  The human player
     * @param Player two  The computer player
     */
    Game(Player&, Player&);

    /**
     * Allows human player to set whichever token (X or O)
     * they will use for the game. The computer will take
     * the token that is not used.
     */
    void setPlayerTokens();

    /**
     * Print information for each player and the current
     * status of the board.
     */
    void showStatus();

    /**
     * Displays a user-friendly version of the board on the
     * screen, showing player tokens (X or O) as well as
     * numbering for empty grid squares.
     */
    void printBoard();

    /**
     * Main game routine. Checks the board to see if there
     * is a winner. If not, move to the next player's turn.
     */
    void runGame();

    /**
     * Determines a move for the computer (pending).
     */
    void getComputerMove();

    /**
     * Prints the board and prompts the human user for their
     * next move.
     */
    void getHumanMove();

    /**
     * If the board is completely occupied without any player
     * winning a Tic-Tac-Toe, the 'cat has gotten the game'.
     * Declare a tie and ask human user if they would like to
     * play another game.
     */
    void drawGame();

    /**
     * Someone won
     */
    void endGame();

    /**
     * Helper function that chooses a random integer number
     * in the range [low, high].
     * @param int lower  Lower bound
     * @param int upper  Upper bound
     * @return a random number in the given range.
     */
    int randint(int, int);

    /**
     * EXPERIMENTAL
     * Another helper function that converts a grid square number
     * (1-9) into x-y coordinates that can be used to place a token
     * in the puzzle.
     * @pre grid square number must be in range [1,9].
     * @param int sq  The grid square
     * @return an x-y pair corresponding to a position in the array
     *         that represents the game board.
     */
     std::pair<int,int> convertToCoordinates(int);



private:
    Player human;       // player one
    Player cylon;       // player two (computer)
    Board b;
    int turn;           // current player's turn
    int totalMoves;     // how many turns have been completed
};
#endif // GAME_H
