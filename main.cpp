#include "Inc/MCTS.hpp"
#include "Inc/Game.hpp"
#include "Inc/Node.hpp"
using namespace std;
int main(){
    Game game;
    int move;
    string line;
    while(game.gameEnded() == -1){
        system("clear");
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