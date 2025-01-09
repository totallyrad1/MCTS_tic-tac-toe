#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
class Game {
    private:
        vector<vector<int> > board;
        int winner;
        int currentPlayer;
        int movesAvailable;
    public:
        Game();
        ~Game();
        void printBoard();
        int gameEnded();
        int checkWin();
        int makeMove(int move);
};