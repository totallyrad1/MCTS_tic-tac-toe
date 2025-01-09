#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;
class Game {
    private:
        vector<vector<int> > board;
        int winner;
        int movesAvailable;
    public:
        int currentPlayer;
        Game();
        ~Game();
        void printBoard();
        int gameEnded();
        int checkWin();
        int makeMove(int move);
        void changePlayer();
        vector<int> generatePossibleMoves();
};