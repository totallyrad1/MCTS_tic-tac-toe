#include "../Inc/Game.hpp"
using namespace std;
Game::Game(){
    srand(time(NULL));
    board = vector<vector<int> >(3, vector<int>(3, -1));
    winner = -1;
    currentPlayer = rand() % 2;
    movesAvailable = 9;
}

Game::~Game(){}

void Game::printBoard(){
    int size = 1;
    for(int x = 0; x < board.size(); x++){
        for(int y = 0; y < board[x].size(); y++){
            if(board[x][y] == -1){
                cout << setw(size) << "-";
            }else if(board[x][y] == 0){
                cout << setw(size) << "O";
            }else{
                cout << setw(size) << "X";
            }
            if(y < 2)
                cout << "|";
        }
        cout << endl;
    }
}

int Game::gameEnded(){
    if(!movesAvailable){
        int winner = checkWin();
        if(winner == 'X')
            return 0; // player X won player 1
        else if(winner == 'O')
            return 1; // player O won player 2
        return 2; // DRAW
    }
    return (-1); // game didnt end yet
}

int Game::checkWin(){
    if(board[0][0] != '-'){
        if(board[0][0] == board[0][1]  && board[0][2] == board[0][0])
            return board[0][0];
        if(board[0][0] == board[1][0]  && board[2][0] == board[0][0])
            return board[0][0];
        if(board[0][0] == board[1][1]  && board[0][0] == board[2][2])
            return board[0][0];
    }else if(board[0][1] != '-'){
        if(board[0][1] == board[1][1] && board[2][1] == board[0][1])
            return board[0][1];
    }else if(board[0][2] != '-'){
        if(board[0][2] == board[1][2] && board[2][2] == board[0][2])
            return board[0][2];
    }else if(board[1][0] != '-'){
        if(board[1][0] == board[1][1] && board[1][0] == board[1][2])
            return board[1][0];
    }else if(board[2][0] != '-'){
        if(board[2][0] == board[2][1] && board[2][0] == board[2][2])
            return board[2][0];
        if(board[2][0] == board[1][1] && board[2][0] == board[0][2])
            return board[2][0];
    }
    return -1;
}

int Game::makeMove(int move){
    if (move < 0 || move > 8) {
        std::cerr << "Invalid move! Must be between 0 and 8.\n";
        return 0;
    }
    if(!movesAvailable){
        cerr << "no Move Available " << endl;
        return 0;
    }
    int x = move / 3;
    int y = move % 3;
    if(currentPlayer == 0){
        board[x][y] = 'X';
    }else if(currentPlayer == 1){
        board[x][y] = 'O';
    }
    return 0;
}