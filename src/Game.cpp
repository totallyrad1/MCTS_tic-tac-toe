#include "../Inc/Game.hpp"
using namespace std;
Game::Game(){
    srand(time(NULL));
    board = vector<vector<int> >(3, vector<int>(3, '-'));
    winner = -1;
    currentPlayer = rand() % 2;
    movesAvailable = 9;
}

Game::~Game(){}

void Game::printBoard(){
    int size = 1;
    for(size_t x = 0; x < board.size(); x++){
        for(size_t y = 0; y < board[x].size(); y++){
            cout << setw(size) << (char)board[x][y];
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
    int winner = checkWin();
    if(winner == 'X')
        return 0; // player X won player 1
    else if(winner == 'O')
        return 1; // player O won player 2
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
    }
    if(board[0][1] != '-'){
        if(board[0][1] == board[1][1] && board[2][1] == board[0][1])
            return board[0][1];
    }
    if(board[0][2] != '-'){
        if(board[0][2] == board[1][2] && board[2][2] == board[0][2])
            return board[0][2];
        if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
            return board[0][2];
    }
    if(board[1][0] != '-'){
        if(board[1][0] == board[1][1] && board[1][0] == board[1][2])
            return board[1][0];
    }
    if(board[2][0] != '-'){
        if(board[2][0] == board[2][1] && board[2][0] == board[2][2])
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
    if(board[x][y] != '-'){
        std::cerr << "Invalid move!\n";
        return 0;
    }
    if(currentPlayer == 0){
        board[x][y] = 'X';
    }else if(currentPlayer == 1){
        board[x][y] = 'O';
    }
    movesAvailable--;
    return 1;
}

void Game::changePlayer(){
    if(currentPlayer == 0)
        currentPlayer = 1;
    else
        currentPlayer = 0;
}

vector<int> Game::generatePossibleMoves(){
    vector<int> result;
    int move = 0;
    while(move < 9){
        int x = move / 3;
        int y = move % 3;
        if(board[x][y] == '-'){
            result.push_back(move);
        }
        move++;
    }
    return result;
}