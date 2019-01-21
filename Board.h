#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
    Board();

    /**
     * Prints a 'raw' (no player tokens; just data) version of
     * the game board on the screen for debugging purposes.
     */
    void print();

    //Getters and setters
    /**
     * Returns the raw data value (to be processed by the game)
     * of the space at the given position.
     * @param int r  the row
     * @param int c  the column
     * @return -1 if unoccupied, 1 if P1, and 2 if P2. 99 if position
     *         is invalid.
     */
    int getDataAtPosition(int, int);

    /**
     * Places a player token at a specified position on the board (if
     * it is possible to do so).
     * @pre Position must be clear and player number must be 0 or 1.
     * @param int pNum  which player's token is being placed
     * @param int r     the row
     * @param int c     the column
     * @return true if the token was successfully placed
     */
    bool placeTokenAtPosition(int pNum, int, int);

    /**
     * Clears any player tokens at a specified position on the board.
     * @param int r  the row
     * @param int c  the column
     * @post Value at position is set to -1 (denoting that it's empty)
     */
    void clearPosition(int, int);

    /**
     * Clear the entire board by resetting all values contained therein.
     * @post value in each grid square set to -1.
     */
    void emptyBoard();


    //Board management
    /**
     * Multiplies all the values contained in the game board to determine
     * whether the game board is full. If the product of all the values is
     * negative, there are empty squares on the board.
     * @return true if the board is completely occupied.
     */
    bool isBoardFull();

    /**
     */
    bool isWinningBoard();

    /**
     * Checks to see if a player has captured an entire row of the board.
     * @param int r  the row
     * @return true if the same player token (1 or 2) occupies every
     * square in the row.
     */
    bool isWinInRow(int);

    /**
     * Checks to see if a player has captured an entire column of the board.
     * @param int c  the column
     * @return true if the same player token (1 or 2) occupies every square
     * in the column.
     */
    bool isWinInColumn(int);

    /**
     * Checks to see if a player has captured every column in the front
     * diagonal spaces (squares 1,5,9).
     * @return true if the same player token (1 or 2) occupies every square
     * in the diagonal.
     */
    bool isWinInForwardDiagonal();

    /**
     * Checks to see if a player has captured every column in the back
     * diagonal spaces (squares 3,5,7).
     * @return true if the same player token (1 or 2) occupies every square
     * in the diagonal.
     */
    bool isWinInBackwardDiagonal();


    //Debugging tools
    /**
     * Prints the raw board data (values contained in the grid) and checks
     * for all win conditions.
     */
    void debugGetStats();

    /**
     * Fills board with alternating player tokens to ensure that class is
     * accurately detecting a completely occupied game board.
     */
    void debugFillBoard();

    /**
     * Places a player one token in every space of a given row.
     * @param int r  the row
     */
    void debugSetRowWinAt(int);

    /**
     * Places a player one token in every space of a given column.
     * @param int c  the column
     */
    void debugSetColumnWinAt(int);

private:
    /**
     * A 3 x 3 Tic-Tac-Toe board.
     * -1 denotes an unoccupied space
     *  1 denotes a Player 1 token (human)
     *  2 denotes a Player 2 token (computer)
     */
    int gameBoard[3][3];
};
#endif // BOARD_H
