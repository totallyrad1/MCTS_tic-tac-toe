#include "Inc/MCTS.hpp"
#include "Inc/Game.hpp"
#include "Inc/Node.hpp"
#include <unistd.h>
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
            int aimove = mcts.RUN(currState, 10000);
            cerr << "aimove "<<aimove << endl;
            if(game.makeMove(aimove))
                game.changePlayer();
            // sleep(2);
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