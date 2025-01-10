#include "Inc/MCTS.hpp"
#include "Inc/Game.hpp"
#include "Inc/Node.hpp"
#include <unistd.h>
#include <chrono>
using namespace std;
int main(){
    srand(time(0));
    Game game;
    int move;
    string line;
    while(game.gameEnded() == -1){
        system("clear");
        if(game.currentPlayer == 0){
            cout << "PLAYER " << game.currentPlayer + 1 << " TURN " << endl;
            game.printBoard();
            getline(cin, line);
            stringstream ss(line);
            ss >> move;
            if(!ss.eof() || ss.fail()){
                cerr << "Invalid move \n";
                continue;
            }
            if(game.makeMove(move))
                game.changePlayer();
        }else{
            cout << "AI TURN " << endl;
            game.printBoard();
            Node *currState = new Node(game, NULL, 1, -1);
            MCTS mcts;
            auto start = std::chrono::high_resolution_clock::now();
            int iterations = 1000;
            int aimove = mcts.RUN(currState, iterations);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if(game.makeMove(aimove))
                game.changePlayer();
            cout << "AI decided " << aimove << " in " << (int)(duration.count()/1000.0) << " microseconds " << iterations << " iterations" << endl;
            sleep(1);
        }
    }
    system("clear");
    game.printBoard();
    int winner = game.gameEnded();
    if(winner == 2)
        cout << "DRAW" << endl;
    else
        cout << "PLAYER " << winner +1 << " WON\n";
    return 0;
}