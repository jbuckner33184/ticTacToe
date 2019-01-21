#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player
{
public:
    //Default player with an X token
    Player();

    /**
     * Player with a user-specified token.
     * @param char tok  Player's token (X or O)
     */
    Player(char);

    //Getters and setters
    char getToken() {return token;}
    void setToken (char tok) {token = tok;}

    int getTotalWins() {return wins;}
    void setNumberOfWins(int gms) {wins = gms;}


    /**
     * Prints the player's token and number of wins
     */
    void getPlayerInfo();

private:
    char token;     // player's piece (X or O)
    int wins;
};
#endif // PLAYER_H
