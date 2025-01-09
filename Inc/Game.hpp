#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;
class Game {
    public:
        vector<vector<int> > board;
        int winner;
        int movesAvailable;
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