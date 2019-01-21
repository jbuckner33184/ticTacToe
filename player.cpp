#include "Player.h"

#include <iostream>

using namespace std;

Player::Player() {
    token = 'X';
    wins = 0;
}

Player::Player(char tok) {
    token = tok;
    wins = 0;
}

void Player::getPlayerInfo() {
    cout << token << "\t Wins: " << wins << endl;
}
